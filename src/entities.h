#ifndef ENTITIES_H
#define ENTITIES_H

#include <math.h>

#include <GL/gl.h>

#include "camera.h"
#include "types.h"

#define ENTITIES_MAX 65536

typedef struct {
	vec3f size;
	vec3f offset;
} hitbox;

typedef struct {
	hitbox hitbox;
	// TODO: renderers
	void *defaultData;
} entityType;

typedef struct {
	GLshort type;
	camera_pos eye;
	vec3f speed;
	vec3f acceleration;
	void* data;
} entity;

entityType *entityTypes[ENTITIES_MAX];

void entity_new(void);

#endif
