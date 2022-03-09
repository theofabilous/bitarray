# bitarray
A small, header-only C library for dynamic bitfield manipulations.

## Overview
*bitarray* was designed to imitate C++ dynamic bit vector implementations such as [std::vector\<bool\>](https://en.cppreference.com/w/cpp/container/vector_bool) and [boost::dynamic_bitset\<\>](https://www.boost.org/doc/libs/1_36_0/libs/dynamic_bitset/dynamic_bitset.html) in pure C. Unfortunately, most implementations do not guarantee space efficiency (in both C++ and C), since memory addresses cannot be subdivided beyond their absolute unit: the **byte**. Further, when a bit vector *is* designed in a space efficient manner, manipulating it like a regular container type is complex. Often, only one of these two features can be chosen.

*bitarray* provides space efficient tools for bit vectors and binary data operations. The `BitArray` struct can be used very much like [std::vector\<bool\>](https://en.cppreference.com/w/cpp/container/vector_bool) and guarantees that one bit takes up exactly one bit of data. [^1] 

Features include (but are not limited to):
  - Resizing
  - Indexing
  - Slicing
  - Appending single bits
  - Appending any type of integral value (`int`, `char`, `float`, `unsigned long long`, `size_t`, ...)
  - String representation

<!-- Arbitary sized (up to `sizeof(size_t)`) integral values can be appended to it dynamically.  -->
<!-- It can be resized, sliced, indexed, accessed, modified, converted to a binary string... -->

`BitArray` structs provide basic functional tools like `for_each` and `transform`. These tools are useful for simple iterative procedures. However, the library also provides the `Biterator` struct which allows for complex functional binary operations on bit vectors.

[^1]: Of course, memory must be allocated byte-wise. However, the maximum extra "useless" size (in bits) of the internal buffer is 8. So, the actual size in memory of the buffer is always within \[num_of_bits, num_of_bits+8].

## Examples

### Getting started
```C
#include <stdbool.h>
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

bits->append(bits, 0b1101);
str = bits->to_str(bits);
printf("%s\n", str); // prints 0b1000011101
free(str);

del_BitArray(bits);
```


### Iterators
```C

/* ... */

size_t counter;

void count_bits(bool bit) { counter += bit; }

void print_bits(bool bit) { printf("%d", bit); }

bool flip_bits(bool bit) { return !bit;  }

/* ... */

int main()
{
    BitArray *bits = new_BitArray(0);
    bits->append(bits, 0b100000010101111000011);
    
    counter = 0;
    bits->for_each(bits, count_bits, -1); // second arg is the function, third is max
                                          // (where -1 means size of bitarray)
    printf("counter: %d\n", counter); // prints 9
    
    bits->for_each(bits, print_bits, -1); // prints each bit
    printf("\n"); 
    
    bits->transform(bits, flip_bits, -1); // flips each bit
    // bitarray now looks like:
    // 011111101010000111100
    
    del_BitArray(bits);
    
    return 0;
}
```

<!-- If bit-level packing is to be used so as to optimize memory usage, loweach data quantum must itself hold   -->
