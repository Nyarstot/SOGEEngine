#ifndef SOGE_ENGINE_ASSERT_HPP
#define SOGE_ENGINE_ASSERT_HPP

#include "SOGE/Utils/Logger.hpp"

#ifdef SOGE_ENABLE_ASSERT
#define SOGE_ASSERT(x, ...) { if(!(x)) { SOGE_ERROR_LOG("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define SOGE_ASSERT(x, ...)
#endif // SOGE_ENABLE_ASSERT


#endif // !SOGE_ENGINE_ASSERT_HPP