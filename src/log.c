#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "log.h"

int currentLoggingLevel = 2; // info

void log_write(loggingLevel level, const char *text, ...) {
	if (currentLoggingLevel > level) {
		return;
	}
	
	va_list args;
	va_start(args, text);
	
	time_t now;
	time(&now);
	struct tm *timeInfos;
	timeInfos = localtime(&now);
	char nowStr[9];
	strftime(nowStr, 9, "%H:%M:%S", timeInfos);
	
	if (level == loggingLevel_trace) {
		printf("[%s][TRACE]", nowStr);
	} else if (level == loggingLevel_debug) {
		printf("[%s][DEBUG]", nowStr);
	} else if (level == loggingLevel_info) {
		printf("[%s][INFO]", nowStr);
	} else if (level == loggingLevel_warn) {
		printf("[%s][WARN]", nowStr);
	} else if (level == loggingLevel_error) {
		printf("[%s][ERROR]", nowStr);
	}
	
	vprintf(text, args);
	printf("\n");
	
	va_end(args);
}

void log_setLevel(loggingLevel level) {
	currentLoggingLevel = level;
}

loggingLevel log_getLevel(void) {
	return currentLoggingLevel;
}

