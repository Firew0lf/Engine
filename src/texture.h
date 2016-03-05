#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLuint texture_load(const char* filename);
GLuint texture_loadFromPixels16(Uint16* pixels, int w, int h);
void texture_unload(GLuint texture);

#endif
