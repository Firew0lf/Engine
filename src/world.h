#ifndef WORLD_H
#define WORLD_H

#include "blocks.h"

#define WORLD_HEIGHT 256
#define BLOCKS_PER_CHUNK 16*WORLD_HEIGHT*16

#define DIMENSION_SIZE_X 2 // in chunks
#define DIMENSION_SIZE_Z 2 // in chunks

typedef struct {
	blockID blocks[BLOCKS_PER_CHUNK];
	short metadatas[BLOCKS_PER_CHUNK];
	void* data[BLOCKS_PER_CHUNK];
} chunk;

typedef struct {
	chunk* chunks[DIMENSION_SIZE_X*DIMENSION_SIZE_Z];
} dimension;

typedef struct {
	dimension* dimensions[256];
} world;

void world_init(void);

#endif
