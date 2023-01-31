#pragma once
#include "src/Log.h"

#define LOGGING_ACTIVE

#ifdef LOGGING_ACTIVE
#define	LOGE(a) LOGGING::Log::e(a)
#define LOGD(a) LOGGING::Log::d(a)
#define LOGI(a) LOGGING::Log::i(a)
#else
#define	LOGE(a) //LOGGING::Log::e(a)
#define LOGD(a) //LOGGING::Log::d(a)
#define LOGI(a) //LOGGING::Log::i(a)
#endif // LOGGING_ACTIVE
