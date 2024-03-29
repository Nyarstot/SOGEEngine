#ifndef SOGE_ENGINE_ASSERT_HPP
#define SOGE_ENGINE_ASSERT_HPP

#include "SOGE/Utils/Logger.hpp"
#include <assert.h>

#ifdef SOGE_ENABLE_ASSERT
        #define SOGE_ASSERT(x, ...) { if(!(x)) { SOGE_ERROR_LOG("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
        #define SOGE_DELEGATE_STATIC_ASSERT(exp, msg) { SOGE_ERROR_LOG("Delegate assertion failed: {0}", msg); __debugbreak(); static_assert(exp, msg); }
#else
        #define SOGE_ASSERT(x, ...)
        #define SOGE_DELEGATE_STATIC_ASSERT(exp, msg)
#endif // SOGE_ENABLE_ASSERT

#endif // !SOGE_ENGINE_ASSERT_HPP