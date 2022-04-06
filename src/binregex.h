#ifndef BIN_REGEX_H
#define BIN_REGEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>


#define _ByteType 0b00000001
#define _StarMod 0b00000010
#define _RangeMod 0b00000100
#define _OrMod 0b00001000
#define _BitLiteralType 0b01000000
#define _HasNext 0b10000000

uint16_t CHAR_TO_FLAG_MAP[256];

#define MODIFIER_BEGIN 256
#define MODIFIER_END 512
#define BYTE_BEGIN 257 // MODIFIER_BEGIN | _ByteType
#define BYTE_END 513 // end | byte
#define STAR_BEGIN 258 // ...
#define STAR_END 514
#define RANGE_BEGIN 260
#define RANGE_END 516
#define OR_BEGIN 264
#define OR_END 520
#define _ESCAPE 1024
#define SEPARATOR 2048
#define OR_SEPARATOR 2056
#define RANGE_SEPARATOR 2052

void char_to_flag_map_init()
{
    memset(CHAR_TO_FLAG_MAP, 0, 512);
    CHAR_TO_FLAG_MAP[(size_t) '0'] = _BitLiteralType;
    CHAR_TO_FLAG_MAP[(size_t) '1'] = _BitLiteralType;
    CHAR_TO_FLAG_MAP[(size_t) '<'] = STAR_BEGIN;
    CHAR_TO_FLAG_MAP[(size_t) '>'] = STAR_END;
    CHAR_TO_FLAG_MAP[(size_t) '{'] = BYTE_BEGIN;
    CHAR_TO_FLAG_MAP[(size_t) '}'] = BYTE_BEGIN;
    CHAR_TO_FLAG_MAP[(size_t) '['] = RANGE_BEGIN;
    CHAR_TO_FLAG_MAP[(size_t) ':'] = RANGE_SEPARATOR;
    CHAR_TO_FLAG_MAP[(size_t) ']'] = RANGE_END;
    CHAR_TO_FLAG_MAP[(size_t) '\\'] = _ESCAPE;
    CHAR_TO_FLAG_MAP[(size_t) '('] = OR_BEGIN;
    CHAR_TO_FLAG_MAP[(size_t) '|'] = OR_SEPARATOR;
    CHAR_TO_FLAG_MAP[(size_t) ')'] = OR_END;
}

enum BinRegexFlags
{
    ByteType =       _ByteType,
    StarMod =        _StarMod,
    RangeMod =       _RangeMod,
    OrMod =          _OrMod,
    BitLiteralType = _BitLiteralType,
    HasNext =        _HasNext
};

typedef struct BinRegexItem BinRegexItem;

typedef struct RegexItemList
{
    uint8_t size;
    BinRegexItem** items;
} RegexItemList;

typedef struct BitLiteralItem
{
    uint8_t size;
    const char* bits;
} BitLiteralItem;

// typedef struct OrItem
// {
//    RegexItemList* items; 
// } OrItem;

typedef struct RangeItem
{
    uint8_t lo;
    uint8_t hi;
} RangeItem;

typedef struct BinRegexItem
{
    uint8_t item_type;
    union 
    {
        size_t match;
        BinRegexItem* sub_item; // star
        RegexItemList items; // or
        RangeItem range_item;
        BitLiteralItem bits_item;
    };
    BinRegexItem* next;
} BinRegexItem;


typedef struct BinRegexGraph
{
    BinRegexItem *start;
    BinRegexItem *curr;
    void *context;
} BinRegexGraph;


typedef struct CtxStack
{
    size_t size;
    BinRegexItem* item_stack[1000];
    BinRegexItem** stackp;
    BinRegexGraph* graph;
} CtxStack;

CtxStack init_CtxStack()
{
    CtxStack stack;
    stack.size = 0;
    stack.stackp = stack.item_stack;
    stack.graph = (BinRegexGraph*) malloc(sizeof(BinRegexGraph));
    stack.graph->start = NULL;
    stack.graph->curr = NULL;
    return stack;
}

inline void 
ctx_push(CtxStack* stack, BinRegexItem* item)
{
    *((stack->stackp)++) = item;
    stack->size++;
}

inline BinRegexItem* 
ctx_pop(CtxStack* stack)
{
    return *(--(stack->stackp));
}

inline BinRegexItem*
ctx_peek(CtxStack* stack)
{
    return *(stack->stackp - 1);
}

inline uint8_t
ctx_peek_type(CtxStack* stack)
{
    return (*(stack->stackp - 1))->item_type;
}

inline bool
ctx_empty(CtxStack* stack)
{
    return stack->size == 0;
}

inline void
ctx_push_next(CtxStack* stack, BinRegexItem* item)
{
    if(stack->graph->start == NULL)
        stack->graph->start = item;
    // else if(ctx_peek_type(stack) & _StarMod)
    //     stack->graph->curr->star_item.sub_item = item;
    else
    {
        switch(ctx_peek_type(stack))
        {
            case _StarMod:
               stack->graph->curr->sub_item = item;
               break;
        //     case _OrMod:

        }
    }
    // else
    //     stack->graph->curr->next = item;
    // stack->graph->curr = item;
    // ctx_push(stack, item);
}

// inline void
// ctx_add_next(CtxStack* stack, BinRegexItem* item)

inline BinRegexItem*
new_RegexItem(uint8_t item_type)
{
    BinRegexItem* new_item = 
        (BinRegexItem*) malloc(sizeof(BinRegexItem));
    if(new_item == NULL) return NULL;
    new_item->item_type = item_type;
    new_item->next = NULL;
    // switch(item_type)
    // {
    //     case 
    // }
    return new_item;
}

void
ctx_parse(CtxStack* stack, const char* str)
{
    BinRegexItem* item;
    uint16_t flags;
    char c;
    bool escape = false;
    while(c = *str++)
    {
        flags = CHAR_TO_FLAG_MAP[c];
        if(flags & MODIFIER_BEGIN)
        {
            item = new_RegexItem(flags & 0xFF);
            ctx_push_next(stack, item);
        }
        else if(flags & MODIFIER_END)
        {
            if(ctx_peek_type(stack) != (flags & 0xFF))
                return;
            ctx_pop(stack);
        }
        else if(flags & SEPARATOR)
        {
            if(ctx_peek_type(stack) != (flags & 0xFF))
                return;

        }
        
    }


    // BinRegexItem* item;
    // uint16_t flags = CHAR_TO_FLAG_MAP[c];
    // if(flags & MODIFIER_BEGIN)
    // {
    //     item = new_RegexItem(flags & 0xFF);
    //     ctx_push_next(stack, item);
    // }
    //     // switch(c)
    //     // {
    //     //     if()
    //     //     case '0':
    //     //     case '1':
    //     //         item = new_RegexItem(_BitLiteralType);
    //     //         if(item == NULL) return NULL;
    //     //         goto get_all_bits;

    //     // }

    // get_all_bits:
    // item->bits_item.size = 0;
    // item->bits_item.bits = str;
    // while(*str == '0' || *str == '1')
    // {
    //     str++;
    //     item->bits_item.size++;
    // }
    



}



// #define BIT_CTX 0
// #define BYTE_CTX 1
// #define OR_CTX 2
// BinRegexGraph* build_regex_graph(const char* regex)
// {
//     BinRegexGraph* graph = (BinRegexGraph*) malloc(sizeof(BinRegexGraph));
//     BinRegexItem* curr_item = NULL;
//     int stack[1000];
//     int* stackp = stack;
//     char bits[100];
//     char* bitp = bits;
//     #define push(x) *stackp++ = x
//     #define pop() *(--stackp)
//     #define peek() *(stackp-1)
//     #define bit_append(x) *(bitp++) = x; *bitp = '\0'
//     #define new_item() (BinRegexItem*) malloc(sizeof(BinRegexItem))
//     push(-1);
//     char c;
//     while(*regex)
//     {
//         c = (*regex++);
//         if(peek() == -1)
//         {
//             curr_item = new_item();
//             switch(c)
//             {
//                 case '0':
//                 case '1':
//                     push(BIT_CTX);
//                     bit_append(c);
//                     curr_item = (Bit)
//                 case '[':
//                     push(BYTE_CTX);
//             }
//         }
//     }
//     return NULL;
//     #undef pop
//     #undef push
//     #undef peek
// }



#endif /* binregex.h */