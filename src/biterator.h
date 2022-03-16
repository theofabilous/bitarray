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

uint8_t bitarray_get(struct _BitArray *self, size_t i);

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

// To impl
typedef struct _BiteratorTemplate
{
	void **data;
} BiteratorTemplate;


// add some useful flags:
// 1) FUNCTION_WAS_ALLOCATED
// 2) ...
typedef struct _Biterator
{
	size_t increment;
	size_t curr;
	size_t max;
	uint8_t sig;
	Function *function;
	struct _BitArray *parent;
	size_t (*read)(struct _Biterator* self, size_t n);
	size_t (*skip)(struct _Biterator* self, size_t n);
	size_t (*peek)(struct _Biterator* self, size_t n);
	void *user_data;
} Biterator;


static inline bool biterator_finished(Biterator* self)
{
	return self->curr < self->max;
}

static inline bool biterator_ok(Biterator* self)
{
	return !(self->curr < self->max) && !(self->parent == NULL);
}

bool biterator_read_bit(Biterator *it)
{
	// handle errors needed....
	if(biterator_finished(it))
		return false;

	// prob could optimize
	bool read = bitarray_get(it->parent, it->curr);
	it->curr++;
	return read;
}

bool biterator_expect_bit(Biterator* self, bool bit)
{
	if(biterator_read_bit(self) == bit)
		return true;
	else
	{
		self->curr--;
		return false;
	}
	// switch(bit | (biterator_read_bit(self) << 1))
	// {
	// 	case 0b10:
	// 	case 0b01:
	// 		self->curr--;
	// 		return false;
	// 	default:
	// 		return true;
	// }
}

size_t biterator_read(Biterator *it, size_t n)
{
	if(it->parent == NULL)
		return -1;
	size_t diff = it->curr - it->max;
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

// Could possibly be optimized by adding a single bit flag
// for if its a leaf, and then another for left(0), right(1)
// which would make switch case more direct (? i think)
/*
FLAGS: 0 0 0 0 0 0 0 0
----------------------
    &  0 0 0 0 0 0 0 1         The bit **currently unused**
    &  0 0 0 0 0 0 1 0         Right child?
    &  0 0 0 0 0 1 0 0         Left child?
    &  0 0 0 0 0 1 1 0         (Is a leaf?)
    &  0 0 0 0 1 0 0 0         ? Has defined fallback : uses default fallback
	!!! ADD A FLAG FOR ITERATOR CHILDREN (?)
	!!! ADD FLAG(S) FOR INT <-> COMMON ITERATOR EFFECTS (ex.: read certain size, skip...)
	.... todo
*/
typedef struct _ContextNode
{
	uint8_t flags;
	union _data {
		struct _ContextNode* children[2];
		Biterator* iters[2];
		void (*funcs[2])(void);
	} data;
	
} ContextNode;

typedef struct _ContextTreeNav
{
	ContextNode* curr;
	uint8_t max_height;
	size_t accumulator;
} ContextTreeNav;

// Assumes biterator reads one bit at a time
// Could be generalized easily by adding a field in node struct
// and checking if the read corresponds to either
void parse_tree(Biterator* itr, ContextNode* node, void (*fallback)(void))
{
	// 	if(node == NULL || biterator_finished(itr) ||
	//	biterator_read(itr, 1) != node->flags & 1)
	if(node == NULL || biterator_finished(itr))
		return fallback();

	// i.e. by default if both children null,
	// fallback should be at 0
	bool bit = 0;
	// break needed when func called? idk
	switch(node->flags & 0b110)
	{
		case 0b110:
			parse_tree(itr, node->
			data.children[biterator_read_bit(itr)], fallback);
		case 0b010:
			bit = 1;
		case 0b100:
			if(biterator_expect_bit(itr, bit))
				parse_tree(itr, node->data.children[bit], fallback);
			else
				bit = !bit;
		case 0b000:
			if(node->flags & 0b1000)
				(*(node->data.funcs[bit]))();
			else
				fallback();
	}
}


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


void biterator_reset(Biterator *it)
{
	it->curr = 0;
}


void detach_Biterator(Biterator *it)
{
	it->curr = 0;
	it->parent = NULL;
	it->read = NULL;
}



Biterator *new_Biterator(int increment, size_t max, uint8_t sig, void* f)
{
	Biterator *it = (Biterator *) malloc(sizeof(Biterator));
	if(it == NULL)
		return NULL;
	Function *func = new_Function(f);
	if(func == NULL)
	{
		free(it);
		return NULL;
	}
	it->increment = increment;
	it->max = max;
	it->curr = 0;
	it->sig = sig;
	it->function = func;
	it->parent = NULL;
	it->read = biterator_read;
	it->skip = NULL;
	it->peek = NULL;
	return it;
}

bool init_Biterator(Biterator* it, int increment, size_t max, uint8_t sig, void* f)
{
	Function *func = new_Function(f);
	if(func == NULL)
		return false;
	it->increment = increment;
	it->max = max;
	it->curr = 0;
	it->sig = sig;
	it->function = func;
	it->parent = NULL;
	it->read = biterator_read;
	it->skip = NULL;
	it->peek = NULL;
	return true;
}

// Prob could do use init_Function instead
// of reallocating and (re)set function_was_alloc flag
// accordingly
bool replace_Biterator(Biterator* it, int increment, size_t max, uint8_t sig, void* f)
{
	// If was alloced, could keep allocation
	// and read into pointer (i.e. no deletion)
	del_Function(it->function);
	it->function = new_Function(f);
	if(it->function == NULL)
		return false;

	// If wasn't, ..?
	
	it->increment = increment;
	it->max = max;
	it->curr = 0;
	it->sig = sig;
	it->parent = NULL;
	it->read = biterator_read;
	it->skip = NULL;
	it->peek = NULL;
	return true;
}


// Use & impl function_was_allocated flag instead
void del_Biterator(Biterator* it, bool delete_function)
{
	if(delete_function)
	{
		free(it->function);
	}
	free(it);
}


#endif
