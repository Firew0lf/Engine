#ifndef BLOCKS_H
#define BLOCKS_H

#include <math.h>
#include <SDL2/SDL.h>

#include "types.h"

#define BAD_ID -1 // id < 0 or > MAX_BLOCKS
#define BLOCK_EXIST -2 // already a block here
#define NO_BLOCK -3 // no block here
#define BAD_FACE -4 // face < 0 or > 5

#define FACE_TOP 0
#define FACE_BOTTOM 1
#define FACE_RIGHT 2
#define FACE_FRONT 3
#define FACE_LEFT 4
#define FACE_BACK 5
#define FACE_ALL 6

typedef short blockID;
#define BLOCKS_MAX 65536

struct block_physicsFlags {
	bool physical:1; // false to be able to pass though
	bool aimable:1;  // false for the player to ignore the block
	bool fluid:1;    // true to use fluid data
};

typedef struct {
	char* name;
	blockID id;
	GLuint textures[6]; // top, bottom, x+, z+, x-, z-
	// Physic
	struct block_physicsFlags physicsFlags;
} block;

void blocks_init(void);
int blocks_new(int id);
block* blocks_get(int id);
int blocks_applyTexture(int id, int face, GLuint texture);

#endif
