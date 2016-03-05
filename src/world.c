#include <stdio.h>
#include <stdlib.h>

#include "all.h"

world worldMain;

void utos(int x, int xmax, int *rx) { // convert [0;...] to [-(.../2);(.../2)-1]
	*rx = x-(xmax/2);
}

void stou(int x, int xmax, int *rx) { // convert [-(.../2);(.../2)-1] to [0;...]
	*rx = x+(xmax/2);
}

// Lib
void world_init(void) {
	log_write(loggingLevel_trace, "Chunk size: %lu KiB", sizeof(chunk)/1024);
}

void world_loadChunk(int x, int y) {
	
}
