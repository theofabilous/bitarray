#ifndef _BITSTREAM_H
#define _BITSTREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>

#include "bitarray.h"


/* ! ! ! ! */
/* ! ! ! ! */
/*   WIP   */
/* ! ! ! ! */
/* ! ! ! ! */


/*
Mostly just brainstorming.
Sometimes just defining some structs
and staring at the definitions is
productive.

Sometimes it isn't.
*/


typedef uint16_t field_entry_t;
typedef uint16_t packet_id_t;


const uint8_t USE_BUFFER_SIZE_BREAK = 1;


typedef struct PacketDescriptor
{
	packet_id_t id;
	field_entry_t num_fields;
} PacketDescriptor;


typedef struct FieldEntry
{
	uint8_t entry_type;
	void* entry;
} FieldEntry;


typedef struct BitPacket
{
	PacketDescriptor* packet_type;
	FieldEntry* table;
	void* context_info;
} BitPacket;


typedef struct BitContextContainer
{
	uint8_t context_type;
	void *data;
} BitContextContainer;


typedef struct BitContextValue
{
	BitContextContainer* source;
	char* id;
} BitContextValue;


typedef struct BitValueContainer
{
	uint8_t value_type;
	void *data;
} BitValueContainer;

/* no need */
// typedef struct BitUnaryConditional
// {
// 	BitValueContainer* predicate;
// } BitUnaryConditional;

typedef struct BitBinaryConditional
{
	BitValueContainer* op1;
	BitValueContainer* op2;
} BitBinaryConditional;


typedef struct BitConditionalContainer
{
	uint8_t condition_type;
	void *data;
} BitConditionalContainer;

// Missing a shitload of stuff
typedef struct BitStreamer
{
	BitArray* buffer;
	size_t pos;
	size_t curr;
	uint8_t flags;
	bool (*breaker)(struct BitStreamer* self);
	size_t (*reader)(struct BitStreamer* self);
} BitStreamer;


void bitstream_read(BitStreamer* self, size_t size)
{
	switch(self->flags & USE_BUFFER_SIZE_BREAK)
	{
		case USE_BUFFER_SIZE_BREAK:
			if(self->pos + size <= bitarray_size(self->buffer))
			{
				self->curr = bitarray_slice(self->buffer, self->pos, self->pos + size);
				self->pos += size;
			}
			else
			{
				self->curr = -1;
				self->pos = -1;
			}
		default:
			if(self->breaker(self))
			{
				self->curr = bitarray_slice(self->buffer, self->pos, self->pos + size);
				self->pos += size;
			}
			else
			{
				self->curr = -1;
				self->pos = -1;
			}
	}
}





#endif /* _BITSTREAM_H */