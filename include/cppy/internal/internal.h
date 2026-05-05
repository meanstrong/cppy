#pragma once

#include <type_traits>

namespace cppy
{
namespace internal
{
template <typename T>
void format_helper(std::ostringstream& oss, std::string_view& str, const T& value)
{
    std::size_t open_bracket = str.find('{');
    std::size_t close_bracket = str.find('}', open_bracket + 1);
    if (open_bracket == std::string::npos || close_bracket == std::string::npos)
    {
        return;
    }
    oss << str.substr(0, open_bracket) << value;
    str = str.substr(close_bracket + 1);
}

template <size_t N, typename T, typename... Types>
struct GetTypeAtIndex
{
    using type = typename GetTypeAtIndex<N - 1, Types...>::type;
};

template <typename T, typename... Types>
struct GetTypeAtIndex<0, T, Types...>
{
    using type = T;
};

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
