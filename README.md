# bitarray
A small C library for dynamic bitfield manipulations, iterations & procedures.

## Overview

*Please note that this library is a work in progress and is most definitely not complete. Some features are currently useable but should not be considered stable, fully optimized or memory safe. The library's structure, usage and features may change drastically and spontaneously. For these reasons, the documentation is light and incomplete. It may contain errors, deprecated information and does not elucidate the full extent of bitarray's features. When in doubt, always refer to the source code.*

*bitarray* provides space efficient tools for bit vectors and binary data operations. The `BitArray` struct can be used very much like [std::vector\<bool\>](https://en.cppreference.com/w/cpp/container/vector_bool) and guarantees that one bit takes up exactly one bit of data. [^1] This library was designed to facilitate looping over large binary buffers and to make such programs more declarative/functional. The end goal is to yield a lightweight yet complete binary parsing library.  

Features include (but are not limited to):
  - Resizing
  - Indexing
  - Slicing
  - Appending single bits
  - Appending any type of integral value (`int`, `char`, `float`, `unsigned long long`, ...)
  - String representation
  - Iterative/functional tools

`BitArray` structs provide basic functional tools like `for_each` and `transform`. These tools are useful for simple iterative procedures. However, the library also provides the `Biterator` struct which allows for complex functional binary operations on bit vectors.

This library also includes the `BitBuffer` struct for binary file I/O. It is only defined for POSIX-compliant operating systems as the I/O operations are optimized with [<sys/mman.h>](https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html) for memory-mapping.

*bitarray* is built and reasoned about in a way that would allow it to be eventually extended to a python module. The end goal is to have a library wherein the user can declaratively create a complex set of rules for binary parsing through the python interface, and then apply the constructed "procedure" to all sorts of binary formats. The procedure, although constructed in python, would have all of its functionality in C. The end result should more or less resemble [Construct](https://construct.readthedocs.io/en/latest/index.html#), with the key difference that its functionality would remain in C while still offering complex conditional rules and callbacks.

[^1]: Of course, memory must be allocated byte-wise. However, the maximum extra "useless" size (in bits) of the internal buffer is 8. So, the actual size in memory of the buffer is always within \[num_of_bits, num_of_bits+8].

---

## The BitArray Struct

```C
typedef struct _BitArray
{
    bitarray_size_t size;
    uint8_t *data;
} BitArray;
```

### Usage
First, define any *bitarray*-specific macros (if needed). Then, `#include "/path/to/bitarray.h"`.  
BitArray objects can be initialized dynamically with `new_Bitarray(size_t num_of_bits)`:
```C
BitArray *bits = new_Bitarray(12);
if(bits == NULL)
    // handle memory error
```
or initialized by reference with `init_Bitarray(BitArray* bitarray, size_t num_of_bits)`:
```C
BitArray bits;
if(!init_Bitarray(&bits, 12))
    // false -> memory error, handle it
```
`BitArray`s can also be created from a file using a `const char*` to the file's path. For large files and complex parsing procedures, one should use `BitBuffer` instead of `BitArray` if the OS is POSIX-like, since the former takes advantage of memory mapping for read/write operations. It also behaves more like a `FILE*`/`std::iostream`, in that it allows reading and seeking the underlying file.

Functions operating on `BitArray`s have the `bitarray_` prefix:
```C
// set a bit to true/1 or false/0
void bitarray_set(BitArray *self, bool bit, size_t i);

// get a bit
uint8_t bitarray_get(BitArray *self, size_t i); 

// get the unsigned integer value of a section of the bits
size_t bitarray_slice(BitArray *self, size_t i, size_t j); 

// set a section of the bits to a certain value
void bitarray_set_slice(BitArray *self, size_t i, size_t j, size_t val);

// set all the bits within a section to true/1 or false/0
void bitarray_fill_slice(BitArray *self, size_t i, size_t j, bool bit);

/* ... */

// append an integral value to the end of the array dynamically
bool bitarray_append(BitArray *self, size_t val);

/* ... */

// do something for every bit with a (bit) -> (void) callback pointer
void bitarray_for_each(BitArray *self, void (*func)(bool), int max);

/* ... */

// iterate over all the bits and do cool stuff with a Biterator
void bitarray_iterate(BitArray *self, Biterator *iter);

/* ... */
```
The same is true for the other defined structs. If one wants to omit the prefixes, the `IMPORT_BITARRAY_MODULE_AS(name)` macro can be used:
```C
#include "bitarray.h"
IMPORT_BITARRAY_MODULE_AS(Bin);
/* ... */
BitArray *bits = new_BitArray(0);
Bin.resize(bits, 12);
/* ... */
```
The macro essentially expands to instantiating a struct which holds all the libraries' functions as pointers whose names are identical to those referenced, but without their prefixes. Depending on the project, one may prefer making such a declaration in the outer-most scope such that the struct may be syntactically used like a Python/C++20 module import.

## Examples

### Getting started
```C
/* ... */
#include "bitarray.h"
/* ... */

IMPORT_BITARRAY_MODULE_AS(Bin);

void get_started()
{
  BitArray *bits = new_BitArray(12); // Initiliaze with 12 bits (all zero by default)
  Bin.set(bits, true, 0); // set first bit to 1
  Bin.set(bits, true, 5); // set the 5-th bit to 1
  Bin.resize(bits, 6); // resize the bitarray, defaulting all
                       // extra bits to 0 (if new size is bigger)
  Bin.append(bits, 0b1101); // append a value to the end

  // get a slice of the bitarray as a bit string
  char bit_str[11];
  Bin.bit_strcpy(bits, 0, -1, bit_str);
  printf("%s\n", bit_str);

  // or just use the print function
  Bin.print_bits(bits, 0, -1);

  // free the bits if dynamically allocated
  del_BitArray(bits);
}
```


### Iterators
```C

IMPORT_BITARRAY_MODULE_AS(Bin);
/* ... */

size_t counter;

void count_bits(bool bit) { counter += bit; }

void print_bits(bool bit) { putchar(bit ? '1' : '0'); }

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
