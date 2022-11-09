#ifndef BINARYMAP_H
#define BINARYMAP_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include "util/bit_util.h"

struct BitArray;

extern uint8_t Map_Bits;
extern uint8_t Keep_Bits;
extern uint8_t Ignore_Bits;
extern uint8_t Callback_Bits;
extern uint8_t Custom_Bits;

typedef struct BinaryMapContext
{
	struct BitArray const * src;
	struct BitArray const * target;
	size_t index;
	char* acc;
} BinaryMapContext;

typedef void (*binary_map_callback_t)(BinaryMapContext* ctx);
typedef void (*bitstring_callback_t)(char* bits);
typedef void (*signal_callback_t)(uint32_t sig);

typedef struct BinaryMapEntry
{
	const char* k;
	union 
	{
		const char *v;
		uint32_t    skip;
		uint32_t    value;
		void       *raw;
		binary_map_callback_t cb;
		bitstring_callback_t str_cb;
		signal_callback_t sig_cb;
	};
	uint8_t flags;
	
} BinaryMapEntry;

typedef struct BinaryMapEntry VlcEntry;


extern uint8_t MAPNODE_HAS_RIGHT;
extern uint8_t MAPNODE_HAS_LEFT;
extern uint8_t MAPNODE_MAPPED;
extern uint8_t MAPNODE_ROOT;
extern uint8_t MAPNODE_KEEP_TYPE;
extern uint8_t MAPNODE_IGNORE_TYPE;
extern uint8_t MAPNODE_CALLBACK_TYPE;
extern uint8_t MAPNODE_OPAQUE_TYPE;

typedef struct MapNode
{
	uint8_t flags;
	struct MapNode* children[2];
	union 
	{
		const char *result;
		uint32_t    skip;
		uint32_t 	value;
		void       *raw;
		binary_map_callback_t cb;
	};
} MapNode;

typedef struct MapTreeNav
{
	MapNode* root;
	size_t current_depth;
	MapNode* curr;
} MapTreeNav;

typedef struct MapTreeNav VlcTable;

typedef struct VlcOutput
{
	MapNode* entry;
	char bits[100];
} VlcOutput;

// static inline
bitarray_force_inline 
void 
mapnode_set_root(MapNode* node)
{
	node->flags |= MAPNODE_ROOT;
}

// static inline
bitarray_force_inline
bool 
mapnode_is_root(MapNode* node)
{
	return node->flags & MAPNODE_ROOT;
}

// static inline
bitarray_force_inline
bool 
mapnode_has_left(MapNode* node)
{
	return node->flags & MAPNODE_HAS_LEFT;
}

// static inline
bitarray_force_inline
bool 
mapnode_has_right(MapNode* node)
{
	return node->flags & MAPNODE_HAS_RIGHT;
}

// static inline
bitarray_force_inline
bool 
mapnode_is_leaf(MapNode* node)
{
	return !(node->flags & MAPNODE_HAS_RIGHT) && !(node->flags & MAPNODE_HAS_LEFT);
}

// static inline
bitarray_force_inline
void 
mapnode_set_mapped(MapNode* node)
{
	node->flags |= MAPNODE_MAPPED;
}

// static inline
bitarray_force_inline
bool 
mapnode_is_mapped(MapNode* node)
{
	return node->flags & MAPNODE_MAPPED;
}

// static inline
bitarray_force_inline
void
mapnode_set_flag(MapNode* node, uint8_t flag)
{
	node->flags |= flag;
}

MapNode* new_root_node();

MapNode* new_node();

bool new_child(MapNode* parent, bool bit);

MapTreeNav* new_MapTreeNav();

bool mapnode_delete_all(MapNode* root);

bool del_MapTreeNav(MapTreeNav* tree);

MapTreeNav* 
build_binary_map(
	BinaryMapEntry entries[], 
	size_t num_entries);

VlcTable* 
build_vlc_table(
	VlcEntry entries[], 
	size_t num_entries);


#endif

