#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "bit_util.h"
#include "biterator.h"



#define __PASS ((void) 0)

#define __BITARCH for(;false;)

#ifdef BITARRAY_OOP
    #if BITARRAY_OOP > 0
        #define __BITARRAY_USE_OOP 1
    #endif
#endif

#ifndef BITARRAY_SIZE_T
#define BITARRAY_SIZE_T size_t
#endif

typedef BITARRAY_SIZE_T bitarray_size_t;

uint8_t _bitarray_ssize_t = sizeof(bitarray_size_t);
uint8_t _bitarray_ssize_t_bits = sizeof(bitarray_size_t)*8;



/* ---------------------------------------- */

// MACROS TO LATER IMPLEMENT FLAGS ON 4 MSBs
bitarray_size_t bitarray_umask = ((bitarray_size_t)0xF) << ((sizeof(bitarray_size_t)*8)-4);
uint8_t bitarray_umask_amt = (sizeof(bitarray_size_t)*8)-4;
bitarray_size_t bitarray_lmask = ~(((bitarray_size_t)0xF) << ((sizeof(bitarray_size_t)*8)-4));
bitarray_size_t bitarray_max_bytes = (~(((bitarray_size_t)0xF) << ((sizeof(bitarray_size_t)*8)-4))) >> 3;

/* ---------------------------------------- */




#ifdef __BITARRAY_USE_OOP

typedef struct _BitArray
{
    bitarray_size_t size;
    uint8_t *data;
    void (*set)(struct _BitArray *self, bool bit, size_t index);
    void (*append)(struct _BitArray *self, size_t val);
    uint8_t (*get)(struct _BitArray *self, size_t i);
    size_t (*slice)(struct _BitArray *self, size_t i, size_t j);
    char* (*to_str)(struct _BitArray *self);
    void (*resize)(struct _BitArray *self, size_t n);
    void (*for_each)(struct _BitArray *self, void (*f)(bool), int m);
    void (*transform)(struct _BitArray *self, bool (*f)(bool), int m);
    void (*iterate)(struct _BitArray *self, Biterator *iter);
} BitArray;

#else

typedef struct _BitArray
{
    bitarray_size_t size;
    uint8_t *data;
} BitArray;

#endif


static bitarray_size_t inline bitarray_num_bytes(BitArray *self)
{
    if(self->size & 0b111)
        return (self->size >> 3)+1;
    else
        return self->size >> 3;
}

// SHOULD BE CHECKED ONLY WHEN ABOUT TO APPEND
static bool inline bitarray_needs_new_byte(BitArray *self)
{
    return !(self->size & 0b111);
}




/* ----------------------- */

static bitarray_size_t inline _byte_part(bitarray_size_t n)
{
    return n >> 3;
}

static uint8_t inline _bit_part(bitarray_size_t n)
{
    return n & 0b111;
}

/* ----------------------- */




void del_BitArray(BitArray* obj)
{
    free(obj->data);
    free(obj);
}


void bitarray_set(BitArray *self, bool bit, bitarray_size_t i)
{
    if(i >= self->size)
    {
        printf("Index out of bounds\n");
        del_BitArray(self);
        exit(1);
    }
    bitarray_size_t byte_index = _byte_part(i);
    uint8_t bit_index = _bit_part(i);
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


uint8_t bitarray_get(BitArray *self, bitarray_size_t i)
{
    if(i >= self->size)
    {
        printf("Index out of bounds\n");
        del_BitArray(self);
        exit(1);
    }
    bitarray_size_t byte_index = _byte_part(i);
    uint8_t bit_index = _bit_part(i);
    uint8_t masker = 1 << (7-bit_index);
    masker = (self->data[byte_index] & masker) >> (7-bit_index);
    return masker;
}


size_t bitarray_slice(BitArray *self, bitarray_size_t i, bitarray_size_t j)
{
    size_t diff = j - i - 1;
    size_t mask = 1 << diff;
    size_t val = 0;
    // Start at j-1, end at i ?? (less shifting idk)
    while(i < j)
    {
        if(bitarray_get(self, i))
        {
            val |= mask;
        }
        mask >>= 1;
        i++;
    }
    return val;
}


char* bitarray_to_str(BitArray *self)
{
    char* repr = (char *) calloc((self->size)+3, sizeof(char));
    if(repr == NULL)
    {
        printf("Memory could not be allocated\n");
        del_BitArray(self);
        exit(1);
    }
    uint8_t curr;
    repr[0] = '0';
    repr[1] = 'b';
    for(size_t i=0; i<self->size; i++)
    {
        curr = bitarray_get(self, i);
        if(curr)
        {
            repr[i+2] = '1';
        }
        else {
            repr[i+2] = '0';
        }
    }
    repr[self->size+2] = '\0';
    return repr;
}



void bitarray_resize(BitArray* self, bitarray_size_t new_size)
{
    bitarray_size_t new_memsize; 
    if(new_size)
        new_memsize = byte_size(new_size);
    else
        new_memsize = 1;

    uint8_t* new = (uint8_t*) realloc(self->data, new_memsize);
    if(new == NULL)
    {
        printf("Memory could not be allocated\n");
        del_BitArray(self);
        exit(1);
    }
    uint8_t diff = _bit_part(new_size);
    bitarray_size_t n_bytes = bitarray_num_bytes(self);

    if(new_memsize > n_bytes)
        memset(&new[n_bytes], 0, new_memsize-n_bytes);
    else if(diff)
    {
        uint8_t mask = ~((1 << (8-diff)) - 1);
        new[new_memsize-1] &= mask;
    }

    self->size = new_size;
    self->data = new;
}

void bitarray_append(BitArray *self, size_t val)
{
    size_t w = bit_width(val);
    size_t byte_w = byte_size(w);
    bitarray_size_t n_bytes = bitarray_num_bytes(self);
    uint8_t fill = _bit_part(self->size);
    uint8_t remaining = 8-fill;
    if(fill && w <= remaining)
    {
        self->data[n_bytes-1] |= val << (remaining - w);
        self->size += w;
    }
    else
    {
        if(fill)
        {
            uint8_t amt = (byte_w-1)>>3; // *8
            uint8_t bits_in_sh = w - amt;

            amt += bits_in_sh - remaining;
            uint8_t shifted_val = val >> amt;
            self->data[n_bytes-1] |= shifted_val;

            self->size += w;

            w -= remaining;
            val &= ((1 << w) - 1);
        }

        bitarray_size_t prev_num_bits = self->size;
        bitarray_resize(self, prev_num_bits+w);
        size_t mask = 1 << (w-1);
        w += prev_num_bits;
        for(size_t i=prev_num_bits;i<w;i+=1)
        {
            if(val & mask)
                bitarray_set(self, true, i);
            mask >>= 1;
        }

    }

}


void bitarray_for_each(BitArray *self, void (*func)(bool), int max)
{
	if(max < 0)
		max = self->size+1+max;
	for(size_t i=0; i<max; i++)
	{
		(*func)(bitarray_get(self, i));
	}
}

void bitarray_transform(BitArray *self, bool(*func)(bool), int max)
{
	if(max < 0)
		max = self->size+1+max;
	bool result;
	for(size_t i=0; i<max; i++)
	{
		result = (*func)(bitarray_get(self, i));
		bitarray_set(self, result, i);
	}
}


void bitarray_iterate(BitArray *self, Biterator *iter)
{
    iter->parent = self;
    Function *cont = (Function*) iter->function;
    int max = iter->max;
    if(max < 0)
        max = self->size+1+max;
    max -= iter->increment;
    bool curr;
    switch(iter->sig)
    {
        case VOID_INT:
            while(iter->curr <= max)
            {
                (*(cont->void_int_f))(bitarray_slice(self, 
                                                  iter->curr, 
                                                  iter->curr+iter->increment));
                iter->curr += iter->increment;
            }
            if(iter->curr <= max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                (*(cont->void_int_f))(bitarray_slice(self, 
                                                  iter->curr, 
                                                  iter->curr+diff));
                iter->curr += diff;
            }
            break;
        case INT_INT:
            while(iter->curr <= max)
            {
                curr = (*(cont->int_int_f))(bitarray_slice(self, 
                                                        iter->curr, 
                                                        iter->curr+iter->increment));
                bitarray_set(self, curr, iter->curr);
                iter->curr += iter->increment;
            }
            /* ----- NEEDS FIX ------- */
            // Fails when <= is set, but others work...
            if(iter->curr < max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                curr = (*(cont->int_int_f))(bitarray_slice(self, 
                                                  iter->curr, 
                                                  iter->curr+diff));
                bitarray_set(self, curr, iter->curr);
                iter->curr += diff;
            }
            break;
        case VOID_INT_IDX:
            while(iter->curr <= max)
            {
                (*(cont->void_int_idx_f))(bitarray_slice(self, 
                                                        iter->curr, 
                                                        iter->curr+iter->increment), 
                                            iter->curr);
                iter->curr += iter->increment;
            }
            if(iter->curr <= max+iter->increment)
            {
                unsigned int diff = max+iter->increment - iter->curr;
                (*(cont->void_int_idx_f))(bitarray_slice(self, 
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

#ifdef BITARRAY_MODULE

typedef struct _BitArrayModule
{
    void (*set)(BitArray *self, bool bit, size_t index);
    void (*append)(BitArray *self, size_t val);
    uint8_t (*get)(BitArray *self, size_t i);
    size_t (*slice)(BitArray *self, size_t i, size_t j);
    char* (*to_str)(BitArray *self);
    void (*resize)(BitArray *self, size_t n);
    void (*for_each)(BitArray *self, void (*f)(bool), int m);
    void (*transform)(BitArray *self, bool (*f)(bool), int m);
    void (*iterate)(BitArray *self, Biterator *iter);
} BitArrayModule;

BitArrayModule BITARRAY_MODULE = {
    .set = &bitarray_set,
    .append = &bitarray_append,
    .get = &bitarray_get,
    .slice = &bitarray_slice,
    .to_str = &bitarray_to_str,
    .resize = &bitarray_resize,
    .for_each = &bitarray_for_each,
    .transform = &bitarray_transform,
    .iterate = &bitarray_iterate
};

#endif


BitArray* new_BitArray(bitarray_size_t size)
{
    bitarray_size_t num_bytes = byte_size(size);
    
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

    memset(data, 0, num_bytes);
    new->size = size;
    new->data = data;

    #ifdef __BITARRAY_USE_OOP

    new->set = bitarray_set;
    new->get = bitarray_get;
    new->slice = bitarray_slice;
    new->append = bitarray_append;
    new->resize = bitarray_resize;
    new->to_str = bitarray_to_str;
    new->for_each = bitarray_for_each;
    new->transform = bitarray_transform;
    new->iterate = bitarray_iterate;

    #endif

    return new;
}


#endif /* _BITARRAY_H */





