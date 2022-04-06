#ifndef BINARYMAP_H
#define BINARYMAP_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

struct BitArray;

extern uint8_t Map_Bits;
extern uint8_t Keep_Bits;
extern uint8_t Ignore_Bits;
extern uint8_t Callback_Bits;

typedef struct BinaryMapContext
{
	struct BitArray const * src;
	struct BitArray const * target;
	size_t index;
	char* acc;
} BinaryMapContext;

typedef void (*binary_map_callback_t)(BinaryMapContext* ctx);

typedef struct BinaryMapEntry
{
	const char* k;
	union 
	{
		const char *v;
		uint32_t    skip;
		void       *raw;
		binary_map_callback_t cb;
	};
	uint8_t flags;
	
} BinaryMapEntry;

extern uint8_t MAPNODE_HAS_RIGHT;
extern uint8_t MAPNODE_HAS_LEFT;
extern uint8_t MAPNODE_MAPPED;
extern uint8_t MAPNODE_ROOT;
extern uint8_t MAPNODE_KEEP_TYPE;
extern uint8_t MAPNODE_IGNORE_TYPE;
extern uint8_t MAPNODE_CALLBACK_TYPE;

typedef struct _MapNode
{
	uint8_t flags;
	struct _MapNode* children[2];
	union 
	{
		const char *result;
		uint32_t    skip;
		void       *raw;
		binary_map_callback_t cb;
	};
} MapNode;

typedef struct _MapTreeNav
{
	MapNode* root;
	size_t current_depth;
	MapNode* curr;
} MapTreeNav;

static inline void 
mapnode_set_root(MapNode* node)
{
	node->flags |= MAPNODE_ROOT;
}

static inline bool 
mapnode_is_root(MapNode* node)
{
	return node->flags & MAPNODE_ROOT;
}

static inline bool 
mapnode_has_left(MapNode* node)
{
	return node->flags & MAPNODE_HAS_LEFT;
}

static inline bool 
mapnode_has_right(MapNode* node)
{
	return node->flags & MAPNODE_HAS_RIGHT;
}

static inline bool 
mapnode_is_leaf(MapNode* node)
{
	return !(node->flags & MAPNODE_HAS_RIGHT) && !(node->flags & MAPNODE_HAS_LEFT);
}

static inline void 
mapnode_set_mapped(MapNode* node)
{
	node->flags |= MAPNODE_MAPPED;
}

static inline bool 
mapnode_is_mapped(MapNode* node)
{
	return node->flags & MAPNODE_MAPPED;
}

static inline void
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


#endif

