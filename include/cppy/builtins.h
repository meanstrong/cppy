#pragma once

#include <algorithm>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

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
template <class Iterable, class T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_max(Iterable begin, Iterable end, T* const result)
{
	*result = *std::max_element(begin, end);
	return CPPY_ERROR_t::Ok;
};

template <class Iterable, class T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_max(Iterable iter, T* const result)
{
	return CPPY_BUILTINS_max(iter.begin(), iter.end(), result);
};

/*
* min(iterable, *[, default=obj, key=func]) -> value
* min(arg1, arg2, *args, *[, key=func]) -> value
*
* With a single iterable argument, return its smallest item. The
* default keyword-only argument specifies an object to return if
* the provided iterable is empty.
* With two or more arguments, return the smallest argument.
*/
template <class Iterable, class T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_min(Iterable begin, Iterable end, T* const result)
{
	*result = *std::min_element(begin, end);
	return CPPY_ERROR_t::Ok;
};

template <class Iterable, class T>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_min(Iterable iter, T* const result)
{
	return CPPY_BUILTINS_min(iter.begin(), iter.end(), result);
};

/*
* Return True if bool(x) is True for all values x in the iterable.
*
* If the iterable is empty, return True.
*/
template <class Iterable, class Pred>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_all(Iterable begin, Iterable end, Pred func, bool* const result)
{
	*result = std::all_of(begin, end, func);
	return CPPY_ERROR_t::Ok;
};

/*
* Return True if bool(x) is True for any x in the iterable.
*
* If the iterable is empty, return False.
*/
template <class Iterable, class Pred>
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_any(Iterable begin, Iterable end, Pred func, bool* const result)
{
	*result = std::any_of(begin, end, func);
	return CPPY_ERROR_t::Ok;
};