#include "ring_buffer.h"

ring_buffer_t*
ring_buffer_initialize(ring_buffer_t* ring, uint8_t* buf, uint32_t size)
{
	ring->buffer = buf;
	ring->head = 0;
	ring->tail = 0;
	ring->size = size;
	ring->full = false;

	return ring;
}

void
ring_buffer_push(ring_buffer_t* ring, uint8_t const* buf, uint32_t size)
{
	// uint32_t bytes_remaining = ring_buffer_length_remaining(ring);

	for( uint32_t i = 0; i < size; i++ )
	{
		ring->buffer[ring->head] = buf[i];
		ring->head = (ring->head + 1) % ring->size;

		if( ring->head == ring->tail )
		{
			ring->full = true;
		}

		if( ring->full )
		{
			ring->tail = ring->head;
		}
	}
}

uint32_t
ring_buffer_length_remaining(ring_buffer_t* ring)
{
	if( ring->full )
	{
		return 0;
	}
	else if( ring->tail <= ring->head )
	{
		return ring->size - (ring->head - ring->tail);
	}
	else
	{
		return ring->tail - ring->head;
	}
}

uint32_t
ring_buffer_count(ring_buffer_t* ring)
{
	return ring->size - ring_buffer_length_remaining(ring);
}

uint32_t
ring_buffer_read(ring_buffer_t* ring, uint8_t* rBuf, uint32_t size)
{
	uint32_t bytes_available = ring->size - ring_buffer_length_remaining(ring);
	uint32_t read_size = size <= bytes_available ? size : bytes_available;

	uint32_t read_head = ring->tail;
	for( uint32_t i = 0; i < read_size; i++ )
	{
		rBuf[i] = ring->buffer[read_head];
		read_head = (read_head + 1) % ring->size;
	}

	return read_size;
}

uint32_t
ring_buffer_remove(ring_buffer_t* ring, uint32_t size)
{
	uint32_t bytes_available = ring->size - ring_buffer_length_remaining(ring);
	uint32_t remove_size = size <= bytes_available ? size : bytes_available;

	for( uint32_t i = 0; i < remove_size; i++ )
	{
		ring->tail = (ring->tail + 1) % ring->size;

		if( ring->full )
		{
			ring->full = false;
		}
	}

	return remove_size;
}
