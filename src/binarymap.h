#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct _BinaryMapEntry
{
	const char* k;
	const char* v;
} BinaryMapEntry;

uint8_t MAPNODE_HAS_RIGHT = 0b00000001;
uint8_t MAPNODE_HAS_LEFT =  0b00000010;
uint8_t MAPNODE_MAPPED =    0b00000100;
uint8_t MAPNODE_ROOT =      0b10000000;

typedef struct _MapNode
{
	uint8_t flags;
	struct _MapNode* children[2];
	const char* result;
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

MapNode* new_root_node()
{
	MapNode* root = (MapNode*) malloc(sizeof(MapNode));
	if(root == NULL) return NULL;
	root->flags = MAPNODE_ROOT;
	return root;
}

MapNode* new_node()
{
	MapNode* node = (MapNode*) malloc(sizeof(MapNode));
	if(node == NULL) return NULL;
	node->flags = 0;
	return node;
}

bool new_child(MapNode* parent, bool bit)
{
	MapNode* child = new_node();
	if(child==NULL)
		return false;
	if(bit) // 1, right
	{
		parent->flags |= MAPNODE_HAS_RIGHT;
		parent->children[1] = child;
	}
	else
	{
		parent->flags |= MAPNODE_HAS_LEFT;
		parent->children[0] = child;
	}
	return true;
}

MapTreeNav* new_MapTreeNav()
{
	MapTreeNav* tree = (MapTreeNav*) malloc(sizeof(MapTreeNav));
	if(tree == NULL) return tree;
	tree->root = new_root_node();
	if(tree->root == NULL)
	{
		free(tree);
		return NULL;
	}
	tree->curr = tree->root;
	tree->current_depth = 0;
	return tree;
}

bool mapnode_delete_all(MapNode* root)
{
	bool status;
	if(mapnode_has_left(root))
		status = mapnode_delete_all(root->children[0]);
	if(mapnode_has_right(root))
		status = status && mapnode_delete_all(root->children[1]);
	free(root);
	return status;
}

bool del_MapTreeNav(MapTreeNav* tree)
{
	bool status = mapnode_delete_all(tree->root);
	free(tree);
	return status;
}


MapTreeNav* 
build_binary_map(
	BinaryMapEntry entries[], 
	size_t num_entries)
{
	MapTreeNav* tree = new_MapTreeNav();
	if(tree == NULL) return tree;
	BinaryMapEntry* entry;
	bool _continue;
	// For every entry in BinaryMap...
	for(size_t i=0; i<num_entries; i++)
	{
		_continue = true;
		// First, set current to root
		tree->curr = tree->root;
		// Get the entry pointer
		entry = &(entries[i]);
		
		// If the "key" is the empty string, error
		if(!(entry->k[0]))
			goto map_err;
		// For every character in "key"
		for(size_t j=0;_continue;j++)
		{
			switch(entry->k[j])
			{
				case '0':
					if(!mapnode_has_left(tree->curr)) // If no left node yet
					{
						// Create a new left child and error if memory error
						if(!new_child(tree->curr, 0)) goto map_err;
					}
					tree->curr = tree->curr->children[0]; // set current to new child
					break;
				case '1': 
					if(!mapnode_has_right(tree->curr)) // If no right node yet
					{
						// Create a new right child and error if memory error
						if(!new_child(tree->curr, 1)) goto map_err;
					}
					tree->curr = tree->curr->children[1]; // set current to new child
					break;
				case '\0': // If null char (end of string)
					mapnode_set_mapped(tree->curr); // set current node as being mapped
					tree->curr->result = entry->v; // set resulting map to corresponding "value"
					_continue = false; // break the loop
					break;
				default:
					goto map_err; // If not '1', '0' or '\0' format error
			}
		}
	}
	tree->curr = tree->root;
	return tree;

	map_err:
	tree->curr = tree->root;
	del_MapTreeNav(tree);
	return NULL;
}


