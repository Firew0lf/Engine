#ifndef LOG_H
#define LOG_H

typedef enum {
	loggingLevel_trace = 0,
	loggingLevel_debug,
	loggingLevel_info,
	loggingLevel_warn,
	loggingLevel_error
} loggingLevel;

void log_write(loggingLevel level, const char *text, ...);
void log_setLevel(loggingLevel level);
loggingLevel log_getLevel(void);

#endif
