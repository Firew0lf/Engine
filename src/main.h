#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include "lua/lua.h"
#include "lua/lapi.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

// version
#define MAJOR_VERSION "0"
#define MINOR_VERSION "ducks"
#define VERSION MAJOR_VERSION "." MINOR_VERSION

#define DEBUG

// error function/macro
#ifdef DEBUG
#define error(a, b) printf("FATAL ERROR: %s\nline: %i\nfile: %s\nError code: %i.\n", b, __LINE__, __FILE__, a); exit(a)
#else
void error(int code, const char *err);
#endif

// Lua
lua_State *mainState;

// engine state
typedef enum {
	state_undef,
	state_exiting,
} engineState;
engineState currentState;
void setState(engineState state);

#endif
