#ifndef _BITERATOR_H
#define _BITERATOR_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* ! ! ! ! */
/* ! ! ! ! */
/*   WIP   */
/* ! ! ! ! */
/* ! ! ! ! */




/* Defined in bitarray.h */

struct _BitArray;

size_t bitarray_slice(struct _BitArray *self, size_t i, size_t j);

/* --------------------- */



/* Defined later in this file */

struct _Biterator;

/* --------------------- */


enum CallbackSig
{
	VOID_INT = 0,
	INT_INT = 1,
	VOID_INT_IDX = 2,
	VOID_ITER = 10
};


typedef union _Function
{
	void *raw;
	void (*void_int_f)(size_t bit);
	size_t (*int_int_f)(size_t bit);
	void (*void_int_idx_f)(size_t bit, size_t index);
	void (*void_iter_f)(struct _Biterator*);
} Function;


typedef struct _Biterator
{
	size_t increment;
	size_t curr;
	long long int max;
	uint8_t sig;
	Function *function;
	struct _BitArray *parent;
	size_t (*read)(struct _Biterator* self, size_t n);
} Biterator;


Function *new_Function(void *f)
{
	Function *func = (Function *) malloc(sizeof(Function));
	if(func == NULL)
	{
		return NULL;
	}
	func->raw = f;
	return func;
}

void init_Function(void *f, Function* cont)
{
	cont->raw = f;
}

void del_Function(Function *func)
{
	free(func);
}


void reset_Biterator(Biterator *it)
{
	it->curr = 0;
}


void detach_Biterator(Biterator *it)
{
	it->curr = 0;
	it->parent = NULL;
	it->read = NULL;
}


size_t read_Biterator(Biterator *it, size_t n)
{
	if(it->parent == NULL)
	{
		printf("Cannot read from biterator without parent array\n");
		return -1;
	}
	long int diff = it->curr - it->max;
	size_t ret;
	if(diff > 0 && diff < it->increment)
	{
		ret = bitarray_slice(it->parent, it->curr, it->curr + diff);
		it->curr += diff;
		return ret;
	}
	else if(diff > 0)
	{
		ret = bitarray_slice(it->parent, it->curr, it->curr + it->increment);
		it->curr += it->increment;
		return ret;
	}
	else
		return -1;
}


Biterator *new_Biterator(int increment, long long int max, uint8_t sig, void* f)
{
	Biterator *it = (Biterator *) malloc(sizeof(Biterator));
	if(it == NULL)
	{
		printf("Memory could not be allocated\n");
		exit(1);
	}
	Function *func = new_Function(f);
	if(func == NULL)
	{
		printf("Memory could not be allocated\n");
		free(it);
		exit(1);
	}
	it->increment = increment;
	it->max = max;
	it->curr = 0;
	it->sig = sig;
	it->function = func;
	it->parent = NULL;
	it->read = read_Biterator;
	return it;
}


void del_Biterator(Biterator* it, bool delete_function)
{
	if(delete_function)
	{
		free(it->function);
	}
	free(it);
}


#endif
