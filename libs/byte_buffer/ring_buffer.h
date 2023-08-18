#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

struct ring_buffer
{
	uint8_t* buffer;
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	bool full;
};
typedef struct ring_buffer ring_buffer_t;

ring_buffer_t* ring_buffer_initialize(ring_buffer_t* ring, uint8_t* buf, uint32_t size);

void ring_buffer_push(ring_buffer_t* ring, uint8_t const* buf, uint32_t size);

uint32_t ring_buffer_length_remaining(ring_buffer_t* ring);

uint32_t ring_buffer_count(ring_buffer_t* ring);

uint32_t ring_buffer_read(ring_buffer_t* ring, uint8_t* rBuf, uint32_t size);

uint32_t ring_buffer_remove(ring_buffer_t* ring, uint32_t size);

#endif
