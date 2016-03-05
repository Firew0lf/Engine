#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "blocks.h"
#include "texture.h"
#include "log.h"

block* blocks[BLOCKS_MAX];
int newBlockId = 0;

Uint16 defaultTexturePixels[2*2] = {
	0xf0f0, 0x0007,
	0x0007, 0xf0f0,
};

GLuint defaultTexture;
block* defaultBlock;

void blocks_init(void) {
	log_write(loggingLevel_trace, "Block struct size: %lu", sizeof(block));
	log_write(loggingLevel_trace, "Max blocks: %i", BLOCKS_MAX);
	log_write(loggingLevel_trace, "Max RAM used for blocks: %i KiB", ((sizeof(block)+sizeof(void*))*BLOCKS_MAX)/1024);
	
	defaultTexture = texture_loadFromPixels16(defaultTexturePixels, 2, 2);
	defaultBlock = malloc(sizeof(block));
	defaultBlock->name = "missingno";
	defaultBlock->id = -1;
	for (int i=0;i<6;i++) {
		defaultBlock->textures[i] = defaultTexture;
	}
	
	blocks_new(0);
}

int blocks_new(int id) {
	if (id < 0 || id > (BLOCKS_MAX-1)) {
		return BAD_ID;
	}
	if (blocks[id] != NULL) { // already something here.
		return BLOCK_EXIST;
	}
	blocks[id] = malloc(sizeof(block));
	blocks[id]->id = id;
	
	for (int i=0;i<6;i++) {
		blocks[id]->textures[i] = defaultTexture;
	}
	
	return id;
}

block* blocks_get(int id) {
	if (blocks[id] == NULL) {
		return defaultBlock;
	}
	return blocks[id];
}

int blocks_applyTexture(int id, int face, GLuint texture) {
	if (blocks[id]->id != id) { // nothing here
		return NO_BLOCK;
	}
	if (face == FACE_ALL) {
		for (int i=0;i<6;i++) {
			blocks[id]->textures[i] = texture;
		}
	} else if (face >= 0 && face < 6) {
		blocks[id]->textures[face] = texture;
	} else {
		return BAD_FACE;
	}
	
	return 0;
}
