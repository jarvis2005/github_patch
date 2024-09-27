#ifndef SYSLOG_H
#define SYSLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// 定义日志级别
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7

inline void syslog(int priority, const char* format, ...) {
    va_list args;
    char buffer[1024];
    time_t now;
    struct tm* timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    FILE* logfile = fopen("application.log", "a");
    if (logfile) {
        fprintf(logfile, "[%d-%02d-%02d %02d:%02d:%02d] [%d]: %s\n",
                timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
                priority, buffer);
        fclose(logfile);
    }
}

#define openlog(ident, option, facility)
#define closelog()

#endif // SYSLOG_H
