#pragma once

extern bool enableLog;

#define LOG(format, ...)  do { if (enableLog) printf("[%s][%s][%d]||" format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); } while(0);

extern bool enableLogDebug;

#define LOG_DEBUG(format, ...)  do { if (enableLog && enableLogDebug) printf("[%s][%s][%d]||" format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); } while(0);