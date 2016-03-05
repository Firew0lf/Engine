#ifndef TYPE_H
#define TYPE_H

#include <GL/gl.h>

typedef GLbyte bool;
#define true 1
#define false 0

typedef struct {
	float x;
	float y;
	float z;
} vec3f;

typedef struct {
	double x;
	double y;
	double z;
} vec3d;

typedef struct {
	float w;
	float x;
	float y;
	float z;
} vec4f;

#endif
