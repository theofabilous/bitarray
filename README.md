# bitarray
A small C library for dynamic bitfield manipulations, iterations & procedures.

## Overview

*Please note that this library is a work in progress and is most definitely not complete.*

<!-- *bitarray* was designed to imitate C++ dynamic bit vector implementations such as [std::vector\<bool\>](https://en.cppreference.com/w/cpp/container/vector_bool) and [boost::dynamic_bitset\<\>](https://www.boost.org/doc/libs/1_36_0/libs/dynamic_bitset/dynamic_bitset.html) in pure C, while keeping memory usage at a minimum and  -->

<!-- Unfortunately, most implementations do not guarantee space efficiency (in both C++ and C), since memory addresses cannot be subdivided beyond their absolute unit: the **byte**. Further, when a bit vector *is* designed in a space efficient manner, manipulating it like a regular container type is complex. Often, only one of these two features can be chosen. -->

*bitarray* provides space efficient tools for bit vectors and binary data operations. The `BitArray` struct can be used very much like [std::vector\<bool\>](https://en.cppreference.com/w/cpp/container/vector_bool) and guarantees that one bit takes up exactly one bit of data. [^1] This library was designed to facilitate looping over large binary buffers and to make such programs more declarative/functional. The end goal is to yield a lightweight yet complete binary parsing library.  

Features include (but are not limited to):
  - Resizing
  - Indexing
  - Slicing
  - Appending single bits
  - Appending any type of integral value (`int`, `char`, `float`, `unsigned long long`, `size_t`, ...)
  - String representation
  - Iterative/functional tools

<!-- Arbitary sized (up to `sizeof(size_t)`) integral values can be appended to it dynamically.  -->
<!-- It can be resized, sliced, indexed, accessed, modified, converted to a binary string... -->

`BitArray` structs provide basic functional tools like `for_each` and `transform`. These tools are useful for simple iterative procedures. However, the library also provides the `Biterator` struct which allows for complex functional binary operations on bit vectors.

*bitarray* is built and reasoned about in a way that would allow it to be eventually extended to a python module. The end goal is to have a library wherein the user can declaratively create a complex set of rules for binary parsing through the python interface, and then apply the constructed "procedure" to all sorts of binary formats. The procedure, although constructed in python, would have all of its functionality in C. The end result should more or less resemble [Construct](https://construct.readthedocs.io/en/latest/index.html#), with the key difference that its functionality will remain in C while offering complex conditional rules and callbacks.

<!-- This library was created with the intention of being extended to python bindings for declarative, complex parsing of binary formatings at the level of individual bits, while keeping most computational logi -->

[^1]: Of course, memory must be allocated byte-wise. However, the maximum extra "useless" size (in bits) of the internal buffer is 8. So, the actual size in memory of the buffer is always within \[num_of_bits, num_of_bits+8].

## The BitArray Struct

```C
typedef struct _BitArray
{
    size_t num_bits;
    size_t memsize;
    uint8_t *data;
    
    // if BITARRAY_OOP is defined && BITARRAY_OOP > 0...
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
```

Two macros are available to control how the various functions are used.

**No macros**
```C
#include "bitarray.h"
/* ... */
BitArray *bits = new_BitArray(0);
bitarray_resize(bits, 12); // same names as in function pointers,
                     // but with bitarray_ prefix
/* ... */
```

**BITARRAY_OOP macro**
```C
#define BITARRAY_OOP 1
#include "bitarray.h"
/* ... */
BitArray *bits = new_BitArray(0);
bits->resize(bits, 12);
/* ... */
```
This macro should not be defined if many small `BitArray`s are created, as they grow the size of such objects
by `num_of_functions * sizeof(void *)`. For projects that use few, large bit vectors, this shouldn't make much of
a difference and may yield more readable code.

**BITARRAY_MODULE macro**
```C
#define BITARRAY_MODULE Bin // or any other name
#include "bitarray.h"
/* ... */
BitArray *bits = new_BitArray(0);
Bin.resize(bits, 12);
/* ... */
```
Defining the module macro is useful in that it reduces the character length of functional calls (one can 
omit the `bitarray_` prefix) while avoiding possible name clashes (for example, another function 
named `resize` may already have been defined). However, this introduces a global struct that holds all the
function pointers. 

## Examples

### Getting started
```C
#include <stdbool.h>
#define BITARRAY_OOP 1 // adds function pointers to BitArray struct
#include "bitarray.h"

/* ... */

BitArray *bits = new_BitArray(12); // Initiliaze with 12 bits (all zero by default)
bits->set(bits, true, 0); // set first bit to 1
bits->set(bits, true, 5);

char *str = bits->to_str(bits);
printf("%s\n", str); // prints 0b100001000000
free(str); // to_str returns a stack-allocated char*
           // a scanf-like function is coming soon...

bits->resize(bits, 6);

str = bits->to_str(bits);
printf("%s\n", str); // prints 0b100001
free(str);

/* append */
bits->append(bits, 0b1101);
/* currently, append forces the size in bits of the appended
value to its exact bit width (i.e. no leading zeros). thus
zeros cannot yet be appended */
   
                            
str = bits->to_str(bits);
printf("%s\n", str); // prints 0b1000011101
free(str);

del_BitArray(bits);
```


### Iterators
```C

#define BITARRAY_MODULE Bin
/* ... */

size_t counter;

void count_bits(bool bit) { counter += bit; }

void print_bits(bool bit) { printf("%d", bit); }

bool flip_bits(bool bit) { return !bit;  }

/* ... */

int main()
{
    BitArray *bits = new_BitArray(0);
    Bin.append(bits, 0b100000010101111000011);
    
    counter = 0;
    Bin.for_each(bits, count_bits, -1); // second arg is the function, third is max
                                          // (where -1 means size of bitarray)
    printf("counter: %d\n", counter); // prints 9
    
    Bin.for_each(bits, print_bits, -1); // prints each bit
    printf("\n"); 
    
    Bin.transform(bits, flip_bits, -1); // flips each bit
    // bitarray now looks like:
    // 011111101010000111100
    
    del_BitArray(bits);
    
    return 0;
}
```

### Complex Iterators

*Coming soon*  
However, some examples can be found in `tests/bitarray_tests.c`

## Coming Soon

- The `BitStream` struct
- Custom allocators/deallocators
- More "slicing" functions
- The `ComplexBiterator` struct (with C++ like custom iterators)
- Implement `new_BitArray_from_file()`

<!-- ## To-Do

- [ ] Don't force exit when memory error occurs
- [ ] Add scanf-like function to get string repr instead of always allocating buffer
- [ ] Add slice-wise editing ( !! also needed for iterators that read more than 1 bit at a time)
- [ ] Add complex iterator examples in README
- [ ] Add callback function signature that takes in the iterator itself
- [ ] Implement iterator read()
- [ ] Implement iterator options to break iterations
- [ ] Add void* user_data field to iterator and add signature that takes it in (??)
- [ ] Trash CallbackSig (or at least not exposed to user), use binary flags and OR operators instead
- [ ] Implement even more versatile iterator struct where next index/next value/continue condition are user functions
- [ ] Add BitStream -->


<!-- If bit-level packing is to be used so as to optimize memory usage, loweach data quantum must itself hold   -->
