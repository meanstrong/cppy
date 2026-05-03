#pragma once

#include <climits>
#include <list>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"
#include "cppy/typing.hpp"

/* Built-in list.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_LIST_init(std::list<T>* const self, Iterable first, Iterable last)
{
    self->assign(first, last);
    return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_LIST_iscontain(const std::list<T>& self, const T& element, bool* const result)
{
    return CPPY_Container_iscontain(self.begin(), self.end(), element, result);
}

/* Append object to the end of the list
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_append(std::list<T>* const self, const T& element)
{
    self->push_back(element);
    return CPPY_ERROR_t::Ok;
}

/* Remove all items from list.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_clear(std::list<T>* const self)
{
    self->clear();
    return CPPY_ERROR_t::Ok;
}

/* Return a shallow copy of the list.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_copy(const std::list<T>& self, std::list<T>* const result)
{
    result->insert(result->end(), self.begin(), self.end());
    return CPPY_ERROR_t::Ok;
}

/* Return number of occurrences of value.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_count(const std::list<T>& self, const T& element, int* const count)
{
    return CPPY_Sequence_count(self.begin(), self.end(), element, count);
}

/* Extend list by appending elements from the iterable.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_LIST_extend(std::list<T>* const self, Iterable first, Iterable last)
{
    self->insert(self->end(), first, last);
    return CPPY_ERROR_t::Ok;
}

/* Return first index of value.
 *
 *  Raises ValueError if the value is not present.
 */
template <typename T>
CPPY_ERROR_t
CPPY_LIST_index(const std::list<T>& self, const T& element, int* const index, int start = 0, int end = INT_MAX)
{
    return CPPY_Sequence_index(self.begin(), self.end(), element, index, start, end);
}

/* Insert object before index.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_insert(std::list<T>* const self, int index, const T& element)
{
    self->insert(self->begin() + index, element);
    return CPPY_ERROR_t::Ok;
}

/* Remove and return item at index (default last).
 *
 *  Raises IndexError if list is empty or index is out of range.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_pop(std::list<T>* self, T* element, int index = -1)
{
    return CPPY_MutableSequence_pop(self, element, index);
}

/* Remove first occurrence of value.
 *
 *  Raises ValueError if the value is not present.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_remove(std::list<T>* self, const T& element)
{
    return CPPY_MutableSequence_remove(self, element);
}

/* Reverse *IN PLACE*.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_reverse(std::list<T>* self)
{
    return CPPY_MutableSequence_reverse(self->begin(), self->end());
}

/* Sort the list in ascending order and return None.
 */
template <typename T>
CPPY_ERROR_t CPPY_LIST_sort(std::list<T>* self)
{
    std::sort(self->begin(), self->end());
    return CPPY_ERROR_t::Ok;
}

template <typename T, typename Iterable>
CPPY_ERROR_t CPPY_LIST_isequal(const std::list<T>& self, Iterable other_first, Iterable other_last, bool* const result)
{
    return CPPY_Sequence_isequal(self.begin(), self.end(), other_first, other_last, result);
}

template <typename T>
CPPY_ERROR_t CPPY_LIST_mul(const std::list<T>& self, int n, std::list<T>* result)
{
    if (n <= 0)
        return CPPY_ERROR_t::Ok;
    if (n == 1)
        return CPPY_LIST_extend(result, self.begin(), self.end());

    for (int i = 0; i < n; ++i)
        CPPY_LIST_extend(result, self.begin(), self.end());

    return CPPY_ERROR_t::Ok;
}
