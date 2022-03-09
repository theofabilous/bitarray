#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bit_util.h"
#include "biterator.h"


typedef struct _BitArray
{
    int num_bits;
    int memsize;
    uint8_t *data;
    void (*set)(struct _BitArray *self, bool bit, int index);
    void (*append)(struct _BitArray *self, int val);
    uint8_t (*get)(struct _BitArray *self, int i);
    size_t (*slice)(struct _BitArray *self, size_t i, size_t j);
    char* (*to_str)(struct _BitArray *self);
    void (*resize)(struct _BitArray *self, int n);
    void (*for_each)(struct _BitArray *self, void (*f)(bool), int m);
    void (*transform)(struct _BitArray *self, bool (*f)(bool), int m);
    void (*iterate)(struct _BitArray *self, Biterator *iter);
} BitArray;


void del_BitArray(BitArray* obj)
{
    free(obj->data);
    free(obj);
}


void set(BitArray *self, bool bit, int i)
{
    if(i >= self->num_bits)
    {
        printf("Index out of bounds\n");
        del_BitArray(self);
        exit(1);
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t masker;
    if(bit)
    {
        masker = 1 << (7-bit_index);
        self->data[byte_index] |= masker;
    }
    else
    {
        masker = ~(1 << (7-bit_index));
        self->data[byte_index] &= masker;
    }
}


uint8_t get(BitArray *self, int i)
{
    if(i >= self->num_bits)
    {
        printf("Index out of bounds\n");
        del_BitArray(self);
        exit(1);
    }
    int byte_index = i / 8;
    int bit_index = i % 8;
    uint8_t masker = 1 << (7-bit_index);
    masker = (self->data[byte_index] & masker) >> (7-bit_index);
    return masker;
}


size_t slice(BitArray *self, size_t i, size_t j)
{
    unsigned int diff = j - i - 1;
    unsigned int mask = 1 << diff;
    size_t val = 0;
    // Start at j-1, end at i ?? (less shifting idk)
    while(i < j)
    {
        if(self->get(self, i))
        {
            val |= mask;
        }
        mask >>= 1;
        i++;
    }
    return val;
}


char* to_str(BitArray *self)
{
    char* repr = (char *) calloc(self->num_bits+3, sizeof(char));
    if(repr == NULL)
    {
        printf("Memory could not be allocated\n");
        del_BitArray(self);
        exit(1);
    }
    uint8_t curr;
    repr[0] = '0';
    repr[1] = 'b';
    for(int i=0; i<self->num_bits; i++)
    {
        curr = self->get(self, i);
        if(curr)
        {
            repr[i+2] = '1';
        }
        else {
            repr[i+2] = '0';
        }
    }
    repr[self->num_bits+2] = '\0';
    return repr;
}



void resize(BitArray* self, int new_size)
{
    int new_memsize = byte_size(new_size);
    if(!new_memsize)
        new_memsize = 1;
    uint8_t* new = (uint8_t*) realloc(self->data, new_memsize);
    if(new == NULL)
    {
        printf("Memory could not be allocated\n");
        del_BitArray(self);
        exit(1);
    }
    uint8_t diff = new_size % 8;
    if(diff)
    {
        uint8_t mask = ~((1 << (8-diff)) - 1);
        new[new_memsize-1] &= mask;
    }
    for(int i=self->memsize; i<new_memsize; i++)
    {
        new[i] = '\0';
    }
    self->num_bits = new_size;
    self->memsize = new_memsize;
    self->data = new;
}

void append(BitArray *self, int val)
{
    int w = bit_width(val);
    int byte_w = byte_size(w);
    uint8_t fill = self->num_bits % 8;
    uint8_t remaining = 8-fill;
    if(fill && w <= remaining)
    {
        self->data[self->memsize-1] |= val << (remaining - w);
        self->num_bits += w;
    }
    else
    {
        if(fill)
        {
            uint8_t amt = (byte_w-1)*8;
            uint8_t bits_in_sh = w - amt;
            amt += bits_in_sh - remaining;
            uint8_t shifted_val = val >> amt;
            self->data[self->memsize-1] |= shifted_val;
            self->num_bits += remaining;
            w -= remaining;
            val &= ((1 << w) - 1);
        }
        bool bit;
        uint8_t prev_num_bits = self->num_bits;
        self->resize(self, self->num_bits+w);
        for(int i=0; i<w; i++)
        {
            bit = (val & (1 << (w-i-1))) >> (w-i-1);
            self->set(self, bit, i+prev_num_bits);
        }
    }

}


void for_each(BitArray *self, void (*func)(bool), int max)
{
	if(max < 0)
		max = self->num_bits+1+max;
	for(int i=0; i<max; i++)
	{
		(*func)(self->get(self, i));
	}
}

void transform(BitArray *self, bool(*func)(bool), int max)
{
	if(max < 0)
		max = self->num_bits+1+max;
	bool result;
	for(int i=0; i<max; i++)
	{
		result = (*func)(self->get(self, i));
		self->set(self, result, i);
	}
}


void iterate(BitArray *self, Biterator *iter)
{
    iter->parent = self;
    Function *cont = (Function*) iter->function;
    int max = iter->max;
    if(max < 0)
        max = self->num_bits+1+max;
    max -= iter->increment;
    bool curr;
    switch(iter->sig)
    {
        case VOID_INT:
            while(iter->curr <= max)
            {
                (*(cont->void_int_f))(self->slice(self, 
                                                  iter->curr, 
                                                  iter->curr+iter->increment));
                iter->curr += iter->increment;
            }
            if(iter->curr <= max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                (*(cont->void_int_f))(self->slice(self, 
                                                  iter->curr, 
                                                  iter->curr+diff));
                iter->curr += diff;
            }
            break;
        case INT_INT:
            while(iter->curr <= max)
            {
                curr = (*(cont->int_int_f))(self->slice(self, 
                                                        iter->curr, 
                                                        iter->curr+iter->increment));
                self->set(self, curr, iter->curr);
                iter->curr += iter->increment;
            }
            /* ----- NEEDS FIX ------- */
            // Fails when <= is set, but others work...
            if(iter->curr < max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                curr = (*(cont->int_int_f))(self->slice(self, 
                                                  iter->curr, 
                                                  iter->curr+diff));
                self->set(self, curr, iter->curr);
                iter->curr += diff;
            }
            break;
        case VOID_INT_IDX:
            while(iter->curr <= max)
            {
                (*(cont->void_int_idx_f))(self->slice(self, 
                                                        iter->curr, 
                                                        iter->curr+iter->increment), 
                                            iter->curr);
                iter->curr += iter->increment;
            }
            if(iter->curr <= max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                (*(cont->void_int_idx_f))(self->slice(self, 
                                                  iter->curr, 
                                                  iter->curr+diff),
                                            iter->curr);
                iter->curr += diff;
            }
            break;
        case VOID_ITER:
            /* To be implemented */
            break;
    }
};




BitArray* new_BitArray(int size)
{
    int num_bytes = size / 8;
    if(num_bytes * 8 < size)
    {
        num_bytes++;
    }
    BitArray* new = (BitArray *) malloc(sizeof(BitArray));
    if(new == NULL)
    {
        printf("Memory could not be allocated\n");
        exit(1);
    }
    uint8_t* data = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
    if(data == NULL)
    {
        printf("Memory could not be allocated\n");
        free(new);
        exit(1);
    }
    for(int i=0; i<num_bytes; i++)
    {
        data[i] = 0;
    }
    new->memsize = num_bytes;
    new->num_bits = size;
    new->data = data;
    new->set = set;
    new->get = get;
    new->slice = slice;
    new->append = append;
    new->resize = resize;
    new->to_str = to_str;
    new->for_each = for_each;
    new->transform = transform;
    new->iterate = iterate;
    return new;
}


#endif /* _BITARRAY_H */





