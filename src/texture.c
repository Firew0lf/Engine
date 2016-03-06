#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "texture.h"
#include "log.h"

GLuint texture_load(const char* filename) {
	SDL_Surface* tmp;
	GLuint texture;
	if ((tmp = SDL_LoadBMP(filename))) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tmp->w, tmp->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tmp->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		log_write(loggingLevel_debug, "Loaded texture %d from '%s' (%d bytes)", texture, filename, (tmp->w*tmp->h*3));
		SDL_FreeSurface(tmp);
		return texture;
	} else {
		error(0, "Actually, that's not working.");
	}
	
	return 0;
}

GLuint texture_loadFromPixels16(Uint16* pixels, int w, int h) { // RGBA4
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	log_write(loggingLevel_debug, "Loaded texture %d from bitmap '%p' (%d bytes)", texture, pixels, (w*h*2));
	return texture;
}

void texture_unload(GLuint texture) {
	log_write(loggingLevel_debug, "Unloaded texture %d", texture);
	glDeleteTextures(1, &texture);
}

