#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "../global.h"

#define MAX_PROCESSING_TIME 10


void appStart(void);

static void waitProcessing(uint32_t milliSeconds);

static inline void timeSleeping(uint32_t milliSeconds);

static void waitProcessing(uint32_t milliSeconds);

#endif