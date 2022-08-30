#include "stringtree.h"
#include <string.h>


void init_char_maps()
{
	if(CHAR_MAP[256] || CHAR_IDX_MAP[256])
		return;

	CHAR_MAP[256] = 1;
	CHAR_IDX_MAP[256] = 1;
	uint16_t j=0;

	for(uint16_t i=0; i<256; i++)
	{
		if(i<=32)
		{
			CHAR_MAP[i] = CHAR_INVALID;
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 47)
		{
			CHAR_MAP[i] = CHAR_SYMBOL; 						// !"#$%&'()*+,-./
			CHAR_IDX_MAP[i] = j++;
		}
		else if(i <= 57)
		{
			CHAR_MAP[i] = CHAR_DIGIT | CHAR_HEX; 				// 0123456789
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 64)
		{
			CHAR_MAP[i] = CHAR_SYMBOL;						// :;<=>?@
			CHAR_IDX_MAP[i] = j++;
		}
		else if(i <= 70)
		{
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_UPPER | CHAR_HEX;	// ABCDEF
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 90)
		{
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_UPPER;			// GHIJKLMNOPQRSTUVWXYZ	
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 96)
		{
			CHAR_MAP[i] = CHAR_SYMBOL;						// [\]^_`
			CHAR_IDX_MAP[i] = j++;
		}
		else if(i <= 102)
		{
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_HEX;				// abcdef
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 122)
		{
			CHAR_MAP[i] = CHAR_ALPHA;							// ghijklmnopqrstuvwxyz
			CHAR_IDX_MAP[i] = 300;
		}
		else if(i <= 126)
		{
			CHAR_MAP[i] = CHAR_SYMBOL;						// {|}~
			CHAR_IDX_MAP[i] = j++;
		}
		else
		{
			CHAR_MAP[i] = CHAR_INVALID;
			CHAR_IDX_MAP[i] = 300;
		}
		// MAX: 126 (33+94)
	}
	// printf("j=%hu\n", j); // 32
}

FLAG8(IS_MAPPED, 0);
FLAG8(HAS_CHILDREN, 1);

static inline int get_char_small_index(char c)
{
	uint16_t idx = CHAR_IDX_MAP[(uint8_t) c];
	if(idx > 255)
		return -1;
	return idx;
}

static inline uint8_t get_char_index(char c)
{
	return ((uint8_t) c) - ((uint8_t) 33);
}

static inline bool node_is_mapped(SearchNode* node)
{
	return (node->priv_flags & IS_MAPPED) != 0;
}

static inline SearchNode* tree_get_node_idx(StringTree* tree, int idx)
{
	return &(tree->nodes[idx]);
}

static inline SearchNode* tree_get_node_chr(StringTree* tree, char c)
{
	return &(tree->nodes[get_char_index(c)]);
}

static inline SearchLeaf* node_get_leaf_chr(SearchNode* node, char c)
{
	return &(node->leaves[get_char_index(c)]);
}

static inline SearchLeaf node_get_leaf_chr_nop(SearchNode* node, char c)
{
	return node->leaves[get_char_index(c)];
}

static inline bool leaf_is_mapped(SearchLeaf leaf)
{
	return (leaf.priv_flags & IS_MAPPED) != 0;
}

static inline bool node_leaf_is_mapped(SearchNode* node, char c)
{
	return ((node_get_leaf_chr(node, c))->priv_flags & IS_MAPPED) != 0;
}

static inline void node_set_leaf_mapped(SearchNode* node, char c)
{
	node_get_leaf_chr(node, c)->priv_flags |= IS_MAPPED;
}

static inline void tree_clear_node_idx(StringTree* tree, int idx)
{
	tree->nodes[idx] = (SearchNode) {.priv_flags =0 , .flags =0, .value=0};
	memset((tree->nodes[idx]).leaves, 0, (94*sizeof(SearchLeaf)));
}

static inline bool tree_node_is_mapped(StringTree* tree, char c)
{
	return node_is_mapped(&(tree->nodes[get_char_index(c)]));
}

static inline void tree_set_node_mapped(StringTree* tree, char c)
{
	tree_get_node_chr(tree, c)->priv_flags |= IS_MAPPED;
}

static inline bool tree_set_leaf_mapped(StringTree* tree, const char* s)
{
	SearchNode* node = tree_get_node_chr(tree, *s);
	if(node_leaf_is_mapped(node, *(s+1)))
		return false;
	else
		node_set_leaf_mapped(node, *(s+1));
	return true;
}

// static inline

bool init_stringtree(
	StringTree* tree, 
	const char* tokens[],
	int num_tokens
	)
{
	for(int i=0; i<94; i++)
		tree_clear_node_idx(tree, i);

	const char* curr_token;
	for(int i=0; i<num_tokens; i++)
	{
		curr_token = tokens[i];
		if(curr_token[1] == '\0' && tree_node_is_mapped(tree, *curr_token))
			return false;
		else if(curr_token[1] == '\0')
		{
			tree_set_node_mapped(tree, *curr_token);
			return true;
		}
		else if(curr_token[2] != '\0')
			return false;
		else
		{
			if(!tree_set_leaf_mapped(tree, curr_token))
				return false;
		}
	}
	tree->init = true;
	return true;
}

SearchResult stringtree_find_str(StringTree* tree, const char* s)
{
	// if(*s < 33 || *s > 126 || *(s+1) < 33 || *(s+1) > 126)
	if(*s < 33 || *s > 126)
		return NO_RESULT();
	SearchNode* node = tree_get_node_chr(tree, *s);
	if(*(s+1) == '\0')
	{
		if(!node_is_mapped(node))
			return NO_RESULT();
		else
			return (SearchResult) {.valid=true, .flags=node->flags, .opaque=node->opaque};
	}
	else if(*(s+2) == '\0')
	{
		// printf("HERE! %s\n", s);
		SearchLeaf leaf = node_get_leaf_chr_nop(node, *(s+1));
		// printf("leaf: %hhu, %hhu, %hu\n", leaf.priv_flags, leaf.flags, leaf.value);
		if(!leaf_is_mapped(leaf))
			return NO_RESULT();
		else
			return (SearchResult) {.valid=true, .flags=leaf.flags, .opaque=leaf.opaque};
	}
	return NO_RESULT();
}

bool stringtree_add_str_u64(StringTree* tree, const char* s, uint16_t flags, uint64_t value)
{
	if(*s < 33 || *s > 126)
		return false;
	SearchNode* node = tree_get_node_chr(tree, *s);
	if(*(s+1) == '\0')
	{
		if(node_is_mapped(node))
			return false;
		node->priv_flags |= IS_MAPPED;
		node->flags = flags;
		node->value = value;
		return true;
	}
	else if(*(s+2) == '\0')
	{
		SearchLeaf *leaf = node_get_leaf_chr(node, *(s+1));
		if(leaf_is_mapped(*leaf))
			return false;
		leaf->priv_flags |= IS_MAPPED;
		leaf->flags = flags;
		leaf->value = value;
		return true;
	}
	return false;
}

bool 
stringtree_add_str_str(
	StringTree* tree, 
	const char* s, 
	uint16_t flags, 
	const char* strv
	)
{
	if(*s < 33 || *s > 126)
		return false;
	SearchNode* node = tree_get_node_chr(tree, *s);
	if(*(s+1) == '\0')
	{
		if(node_is_mapped(node))
			return false;
		node->priv_flags |= IS_MAPPED;
		node->flags = flags;
		node->str_val = strv;
		return true;
	}
	else if(*(s+2) == '\0')
	{
		SearchLeaf *leaf = node_get_leaf_chr(node, *(s+1));
		if(leaf_is_mapped(*leaf))
			return false;
		leaf->priv_flags |= IS_MAPPED;
		leaf->flags = flags;
		leaf->str_val = strv;
		return true;
	}
	return false;
}






