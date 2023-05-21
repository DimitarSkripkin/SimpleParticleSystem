#pragma once

#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#define ENGINE_TRACE_SCOPE(scopeName) (void)0

#define ENGINE_MACRO(macro) macro
#define ENGINE_MACRO_AS_STRING(macro) #macro

#ifndef ENGINE_ENABLE_ASSERTS
    #define ENGINE_ENABLE_ASSERTS 1
#endif
#ifdef ENGINE_ENABLE_ASSERTS
    #include <cassert>

    #define ENGINE_ASSERT_WITH_MSG(expr, msg) assert(expr && msg)
    #define ENGINE_ASSERT_NO_MSG(expr) assert(expr)

    #define ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define ENGINE_INTERNAL_ASSERT_GET_MACRO(...) ENGINE_MACRO(ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ENGINE_ASSERT_WITH_MSG, ENGINE_ASSERT_NO_MSG))

    #define ENGINE_ASSERT(...) ENGINE_MACRO(ENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))
#else
    ENGINE_ASSERT(...)
#endif
