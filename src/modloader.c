#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "lua/lua.h"
#include "lua/lapi.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#include "main.h"
#include "log.h"

char* mods[512];

int modloader_countMods(void) {
	DIR *dp;
	struct dirent *ep;
	
	dp = opendir("./mods/");
	if (dp == NULL) {
		log_write(loggingLevel_error, "Couldn't open the './mods/' directory.");
		return 0;
	}
	int count = 0;
	for (int i=0;(ep=readdir(dp));i++) {
		if (ep->d_name[0] != '.') {
			mods[count] = malloc(strlen(ep->d_name)+1);
			strcpy(mods[count], ep->d_name);
			count++;
			log_write(loggingLevel_debug, "Found mod '%s'.", ep->d_name);
		}
	}
	closedir(dp);
	
	return count;
}

void modloader_loadMods(int count) {
	for (int i=0;i<count;i++) {
		log_write(loggingLevel_info, "Loading mod '%s'.", mods[i]);
		lua_pushstring(mainState, "./mods/");
		lua_pushstring(mainState, mods[i]);
		lua_pushstring(mainState, "/init.lua");
		lua_concat(mainState, 3);
		const char *modfile = luaL_checkstring(mainState, 1);
		
		int errcode = 0;
		if ((errcode = luaL_loadfile(mainState, modfile))) {
			error(errcode, "Mod loading error");
		}
		
		lua_pushstring(mainState, mods[i]); // push the mod name as first argument
		if ((errcode = lua_pcall(mainState, 1, 0, 0)) != LUA_OK) {
			printf("[%s]", mods[i]);
			switch (errcode) {
				case LUA_ERRRUN:
					printf("Runtime error: %s.\n", luaL_optstring(mainState, 3, "Unknow error"));
					break;
				
				case LUA_ERRMEM:
					printf("Memory allocation error.\n");
					break;
				
				case LUA_ERRERR:
					printf("Error while returning the message handler.\n");
					break;
				
				case LUA_ERRGCMM:
					printf("Error while running the garbage collector.\n");
					break;
				
				default:
					printf("Unknown error.\n");
					break;
			}
			error(errcode, "Error while executing init.lua");
		} else {
			log_write(loggingLevel_info, "Successfuly loaded mod '%s'.", mods[i]);
		}
	}
}
