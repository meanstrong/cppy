#pragma once

#include <type_traits>

namespace cppy
{
namespace internal
{
template <typename U, typename = void>
struct is_callable_impl : std::false_type
{
};
template <typename U>
struct is_callable_impl<U, std::void_t<decltype(&U::operator())>> : std::true_type
{
};
template <typename R, typename... Args>
struct is_callable_impl<R (*)(Args...), void> : std::true_type
{
};
template <typename R, typename... Args>
struct is_callable_impl<R(Args...), void> : std::true_type
{
};
} // namespace internal
} // namespace cppy
