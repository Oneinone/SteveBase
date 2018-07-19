#pragma once

#undef interface

#define $(expr) { return (expr); }
#define lazy(expr) []() -> decltype((expr)) $(expr)

#define lazy_once(expr) []() -> decltype((expr)) { static auto value = (expr); return value; }

#define GenCombine(x, y, z, i) x ## y ## z ## i
#define Combine(x, y, z, i) GenCombine(x, y, z, i)

#define Pad(bytes) char Combine( __pad_, __COUNTER__, _, __LINE__ ) [bytes]

// extends all super data
#define extends \
  : public

// hacky, cause c++ do not have an idea of interface (more likely a full pure virtual class mappings)
#define implements extends

// All abstract, default, and static methods in an interface are implicitly public
#define interface struct 

#define FORCEINLINE __forceinline

template<class Fn>
class ScopeGuardDetails {
    const Fn m_fn;
public:
    constexpr ScopeGuardDetails(Fn &&fn) : m_fn(fn) {}
    __forceinline ~ScopeGuardDetails() { m_fn(); }
};


#define ScopeGuardNameGenApply(a, b) __scope_guard_ ## a ## b
#define ScopeGuardNameGen(a, b) ScopeGuardNameGenApply(a, b)

#define ScopeGuardName ScopeGuardNameGen(__LINE__, __COUNTER__)
#define defer(stmt) const auto ScopeGuardName = [](const auto _fn) { \
    return ScopeGuardDetails<decltype(_fn)> { std::move(_fn) }; \
}([&] { stmt ; })