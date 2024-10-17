
#ifndef TRINITYCORE_LOG_H
#define TRINITYCORE_LOG_H

#include <iostream>
#include "StringFormat.h"

#define TC_LOG_MESSAGE_BODY(filterType__, level__, ...)               \
        do {                                                          \
            std::cout << level__ << ":" <<                            \
                Trinity::StringFormat(__VA_ARGS__) << std::endl;      \
        } while (0)


#define TC_LOG_TRACE(filterType__, ...) \
    TC_LOG_MESSAGE_BODY(filterType__, "[TRACE]", __VA_ARGS__)

#define TC_LOG_DEBUG(filterType__, ...) \
    TC_LOG_MESSAGE_BODY(filterType__, "[DEBUG]", __VA_ARGS__)

#define TC_LOG_INFO(filterType__, ...)  \
    TC_LOG_MESSAGE_BODY(filterType__, "[INFO]", __VA_ARGS__)

#define TC_LOG_WARN(filterType__, ...)  \
    TC_LOG_MESSAGE_BODY(filterType__, "[WARN]", __VA_ARGS__)

#define TC_LOG_ERROR(filterType__, ...) \
    TC_LOG_MESSAGE_BODY(filterType__, "[ERROR]", __VA_ARGS__)

#define TC_LOG_FATAL(filterType__, ...) \
    TC_LOG_MESSAGE_BODY(filterType__, "[FATAL]", __VA_ARGS__)

#endif
