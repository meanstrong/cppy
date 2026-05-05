#pragma once

#include <algorithm>
#include <numeric>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"
#include "cppy/internal/internal.h"

/*
 * Return True if bool(x) is True for all values x in the iterable.
 *
 * If the iterable is empty, return True.
 */
template <class Iterable, class Pred>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_all(Iterable first, Iterable last, Pred func, bool* const result)
{
    *result = std::all_of(first, last, func);
    return CPPY_ERROR_t::Ok;
}
template <class Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_all(Iterable first, Iterable last, bool* const result)
{
    return CPPY_BUILTINS_all(first, last, [](typename Iterable::value_type v) { return v; }, result);
}

/*
 * Return True if bool(x) is True for any x in the iterable.
 *
 * If the iterable is empty, return False.
 */
template <class Iterable, class Pred>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_any(Iterable first, Iterable last, Pred func, bool* const result)
{
    *result = std::any_of(first, last, func);
    return CPPY_ERROR_t::Ok;
}
template <class Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_any(Iterable first, Iterable last, bool* const result)
{
    return CPPY_BUILTINS_any(first, last, [](typename Iterable::value_type v) { return v; }, result);
}

/*
 * Return whether the object is callable (i.e., some kind of function).
 */
template <typename T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_callable(bool* const result)
{
    *result = cppy::internal::is_callable_impl<std::decay_t<T>>::value;
    return CPPY_ERROR_t::Ok;
}

/*
 * Return a Unicode string of one character with ordinal i; 0 <= i <= 0x10ffff.
 */
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_chr(uint32_t i, std::string* const result)
{
    result->clear();
    if (i > 0x10FFFF)
        return CPPY_ERROR_t::ValueError;
    if (i <= 0x7F)
    {
        *result += static_cast<char>(i);
    }
    else if (i <= 0x7FF)
    {
        *result += static_cast<char>(0xC0 | ((i >> 6) & 0x1F));
        *result += static_cast<char>(0x80 | (i & 0x3F));
    }
    else if (i <= 0xFFFF)
    {
        *result += static_cast<char>(0xE0 | ((i >> 12) & 0x0F));
        *result += static_cast<char>(0x80 | ((i >> 6) & 0x3F));
        *result += static_cast<char>(0x80 | (i & 0x3F));
    }
    else
    {
        *result += static_cast<char>(0xF0 | ((i >> 18) & 0x07));
        *result += static_cast<char>(0x80 | ((i >> 12) & 0x3F));
        *result += static_cast<char>(0x80 | ((i >> 6) & 0x3F));
        *result += static_cast<char>(0x80 | (i & 0x3F));
    }
    return CPPY_ERROR_t::Ok;
}

/*
 * Return the tuple (x//y, x%y).  Invariant: div*y + mod == x.
 */
template <typename T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_divmod(T x, T y, T* const div, T* const mod)
{
    *div = x / y;
    *mod = x % y;
    return CPPY_ERROR_t::Ok;
}

/*
 * Return an iterator yielding those items of iterable for which function(item) is true.
 */
template <class Iterable, class Pred, class OutputIter>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_filter(Iterable first, Iterable last, Pred func, OutputIter result)
{
    std::copy_if(first, last, result, func);
    return CPPY_ERROR_t::Ok;
}

/* Return evenly spaced numbers over a specified interval.
 *
 *  Returns `num` evenly spaced samples, calculated over the interval [`start`, `stop`].
 *  The endpoint of the interval can optionally be excluded.
 *
 *  start
 *    The starting value
 *  stop
 *    The end value
 *  num : int, optional
 *    Number of samples to generate. Must be non-negative.
 *  endpoint : bool, optional
 *    If True, `stop` is the last sample. Otherwise, it is not included.
 *    Default is True.
 *
 *  >>> np.linspace(2.0, 3.0, 5)
 *  array([2.  , 2.25, 2.5 , 2.75, 3.  ])
 *  >>> np.linspace(2.0, 3.0, 5, endpoint=False)
 *  array([2. ,  2.2,  2.4,  2.6,  2.8])
 */
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_linspace(double start, double end, int num, double result[], bool endpoint = true);

/*
 * max(iterable, *[, default=obj, key=func]) -> value
 * max(arg1, arg2, *args, *[, key=func]) -> value
 *
 * With a single iterable argument, return its biggest item. The
 * default keyword-only argument specifies an object to return if
 * the provided iterable is empty.
 * With two or more arguments, return the largest argument.
 */
template <class Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_max(Iterable first, Iterable last, Iterable* const result)
{
    *result = std::max_element(first, last);
    return CPPY_ERROR_t::Ok;
}

/*
 * min(iterable, *[, default=obj, key=func]) -> value
 * min(arg1, arg2, *args, *[, key=func]) -> value
 *
 * With a single iterable argument, return its smallest item. The
 * default keyword-only argument specifies an object to return if
 * the provided iterable is empty.
 * With two or more arguments, return the smallest argument.
 */
template <class Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_min(Iterable first, Iterable last, Iterable* const result)
{
    *result = std::min_element(first, last);
    return CPPY_ERROR_t::Ok;
}

/*
 * reverse iterator over the values of the given sequence.
 */
template <class Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_reversed(Iterable first, Iterable last)
{
    std::reverse(first, last);
    return CPPY_ERROR_t::Ok;
}

/*
 * Create a slice object.  This is used for extended slicing.
 */
template <class Iterable, class OutputIter>
CPPY_API CPPY_ERROR_t
CPPY_BUILTINS_slice(Iterable first, Iterable last, int start, int stop, int step, OutputIter result)
{
    if (step == 0)
        return CPPY_ERROR_t::ValueError;
    const int len = static_cast<int>(std::distance(first, last));
    if (step > 0)
    {
        if (start < 0)
            start += len;
        if (stop < 0)
            stop += len;
        if (start < 0)
            start = 0;
        if (stop > len)
            stop = len;
        if (start >= len || start >= stop)
            return CPPY_ERROR_t::Ok;
        for (int i = start; i < stop; i += step)
        {
            auto it = first;
            std::advance(it, i);
            *result = *it;
            ++result;
        }
    }
    else
    {
        if (start < 0)
            start += len;
        if (stop < 0)
            stop += len;
        if (start >= len)
            start = len - 1;
        if (stop < -1)
            stop = -1;
        if (start < 0 || start <= stop)
            return CPPY_ERROR_t::Ok;
        for (int i = start; i > stop; i += step)
        {
            auto it = first;
            std::advance(it, i);
            *result = *it;
            ++result;
        }
    }
    return CPPY_ERROR_t::Ok;
}

/*
 * Return a new list containing all items from the iterable in ascending order.
 *
 * A custom key function can be supplied to customize the sort order, and the
 * reverse flag can be set to request the result in descending order.
 */
template <typename Iterable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_sorted(Iterable first, Iterable last, bool reverse = false)
{
    std::sort(first, last);
    if (reverse)
        std::reverse(first, last);
    return CPPY_ERROR_t::Ok;
}

template <typename Iterable, typename Callable>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_sorted(Iterable first, Iterable last, Callable key, bool reverse = false)
{
    std::sort(first, last, [&](const auto& a, const auto& b) { return key(a) < key(b); });
    if (reverse)
        std::reverse(first, last);
    return CPPY_ERROR_t::Ok;
}

/*
 * Return the sum of a 'start' value (default: 0) plus an iterable of numbers
 *
 * When the iterable is empty, return the start value.
 * This function is intended specifically for use with numeric values and may
 * reject non-numeric types.
 */
template <class Iterable, typename AddableT>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_sum(Iterable first, Iterable last, AddableT start, AddableT* const result)
{
    *result = std::accumulate(first, last, start);
    return CPPY_ERROR_t::Ok;
}
