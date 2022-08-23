#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct List;

typedef struct Cell
{
    union
    {
        size_t zu;
        int i;
        char c;
        uint8_t b;
        void *opaque;
        char *str;
        struct List* list;
    };
    uint8_t set;
} Cell;

typedef struct List
{
	size_t real_size;
	size_t size;
	Cell* array;
} List;

typedef struct PerfectHash
{
    List G, V;
} PerfectHash;

typedef struct MaxHeap
{
    size_t size;
    List* array;
} MaxHeap;

void swap(List* a, List* b) { List t = *a; *a = *b;  *b = t; }

void maxHeapify(MaxHeap* maxHeap, size_t idx)
{
    size_t largest = idx;
    size_t left = (idx << 1) + 1;
    size_t right = (idx + 1) << 1;

    if (left < maxHeap->size &&
        maxHeap->array[left].size > maxHeap->array[largest].size)
        largest = left;

    if (right < maxHeap->size &&
        maxHeap->array[right].size > maxHeap->array[largest].size)
        largest = right;

    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

void createAndBuildHeap(MaxHeap* maxHeap, List *array, size_t size)
{
    int64_t i;
    maxHeap->size = size;
    maxHeap->array = array;

    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
}

void heapSort(List* array, size_t size)
{
    MaxHeap maxHeap;
    createAndBuildHeap(&maxHeap, array, size);
    while (maxHeap.size > 1)
    {
        swap(&maxHeap.array[0], &maxHeap.array[maxHeap.size - 1]);
        --maxHeap.size;  // Reduce heap size
        maxHeapify(&maxHeap, 0);
    }
}


void list_append_ptr(List* l, Cell* item)
{
    if(!l->real_size || l->array == NULL)
    {
        l->array = (Cell*) calloc(2, sizeof(Cell));
        if(l->array == NULL) exit(1);
        l->real_size = 2;
    }
	else if(l->size+1 > l->real_size)
	{
		Cell* new = realloc(l->array, sizeof(Cell)*l->real_size*2);
        if(new == NULL) exit(1);
        l->array = new;
        l->real_size = l->real_size*2;
	}
    l->array[l->size++] = *item;
}

void list_append(List* l, Cell item)
{
    if(!l->real_size || l->array == NULL)
    {
        l->array = (Cell*) calloc(2, sizeof(Cell));
        if(l->array == NULL) exit(1);
        l->real_size = 2;
    }
	else if(l->size+1 > l->real_size)
	{
		Cell* new = realloc(l->array, sizeof(Cell)*l->real_size*2);
        if(new == NULL) exit(1);
        l->array = new;
        l->real_size = l->real_size*2;
	}
    l->array[l->size++] = item;
}

bool list_set(List* l, Cell* item, size_t i)
{
    if(!l->real_size || l->array == NULL || i >= l->size)
        return false;
	l->array[i] = *item;
    return true;
}

Cell* list_get(List* l, size_t i)
{
    if(i >= l->size)
        return NULL;
    return &(l->array[i]);
}

List new_list(size_t init)
{
    List l = {0, 0, NULL};
    if(init)
    {
        l.array = (Cell*) calloc(init, sizeof(Cell));
        l.real_size = init;
    }
    return l;
}

void list_init_from(
    List* l, 
    Cell* cells, 
    size_t size, 
    size_t m_size)
{
    l->size = size;
    l->real_size = m_size;
    l->array = cells;
}

int hash(int d, const char* str)
{
    if(!d) d = 0x01000193;
    char c;
    while( (c = *(str++)) )
        d = ( (d * 0x01000193) ^ c ) & 0xffffffff;
    return d;
}


PerfectHash create_min_hash(const char** strs, int len)
{
    PerfectHash h;
    Cell cells[259][256];

    int icurr=0;

    for(int i=0; i<259; i++)
        memset(cells[i], 0, sizeof(Cell)*256);

    List buckets[256];
    List slots;
    size_t bits[4] = {0,0,0,0};

    for(int i=0; i<256; i++)
        list_init_from(&(buckets[i]), cells[i], 0, 256);
        
    list_init_from(&(h.G), cells[256], 256, 256);
    list_init_from(&(h.V), cells[257], 256, 256);
    list_init_from(&(slots), cells[258], 0, 256);

    int idx;
    for(int i=0; i<len; i++)
    {
        idx = hash(0, strs[i]) % len;
        list_append(&(buckets[idx]), (Cell) {.i = i, .set = true});
    }
    heapSort(buckets, 256);
    int i=0, d, item, bsize, slot;
    uint8_t amt_i, amt;
    for(List* curr = &buckets[0]; i<256 && curr->size > 0; curr = &buckets[++i])
    {
        d = 1; item = 0; bsize = curr->size;
        while(item < bsize)
        {
            slot = hash(d, curr->array[item].str);
            amt_i = (uint8_t) (slot >> 6);
            amt = slot & 63;
            if(h.V.array[slot].set || bits[amt_i] & (1 << amt))
            {
                d++;
                item = 0;
                slots.size = 0;
                memset(bits, 0, 4*sizeof(size_t));
            }
            else
            {
                slots.array[slots.size++] = (Cell) {.set = true, .i=slot};
                bits[amt_i] |= (1 << amt);
                item++;
            }
        }
        h.G.array[hash(0, strs[curr->array[0].i]) % len] = 
            (Cell) {.set = true, .i = d};

        for(int j=0; j<bsize; j++)
            h.V.array[slots.array[j].i] = (Cell) { .set=true, .i=icurr++};
    }

        
        // list_append(&buckets, )

}

