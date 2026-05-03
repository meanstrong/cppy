#pragma once

#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"
#include "cppy/typing.hpp"

/* Built-in vector.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_VECTOR_init(std::vector<T>* const self, Iterable first, Iterable last)
{
    self->assign(first, last);
    return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_iscontain(const std::vector<T>& self, const T& element, bool* const result)
{
    return CPPY_Container_iscontain(self.begin(), self.end(), element, result);
}

/* Append object to the end of the list
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_append(std::vector<T>* const self, const T& element)
{
    self->push_back(element);
    return CPPY_ERROR_t::Ok;
}

/* Remove all items from list.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_clear(std::vector<T>* const self)
{
    self->clear();
    return CPPY_ERROR_t::Ok;
}

/* Return a shallow copy of the list.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_copy(const std::vector<T>& self, std::vector<T>* const result)
{
    result->insert(result->end(), self.begin(), self.end());
    return CPPY_ERROR_t::Ok;
}

/* Return number of occurrences of value.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_count(const std::vector<T>& self, const T& element, int* const count)
{
    return CPPY_Sequence_count(self.begin(), self.end(), element, count);
}

/* Extend list by appending elements from the iterable.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_VECTOR_extend(std::vector<T>* const self, Iterable first, Iterable last)
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
CPPY_VECTOR_index(const std::vector<T>& self, const T& element, int* const index, int start = 0, int end = INT_MAX)
{
    return CPPY_Sequence_index(self.begin(), self.end(), element, index, start, end);
}

/* Insert object before index.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_insert(std::vector<T>* const self, int index, const T& element)
{
    int len = static_cast<int>(self->size());

    if (index >= len)
    {
        self->push_back(element);
        return CPPY_ERROR_t::Ok;
    }
    if (index < 0)
    {
        index += len;
        if (index < 0)
            index = 0;
    }
    self->insert(self->begin() + index, element);
    return CPPY_ERROR_t::Ok;
}

/* Remove and return item at index (default last).
 *
 *  Raises IndexError if list is empty or index is out of range.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_pop(std::vector<T>* const self, T* const element, int index = -1)
{
    return CPPY_MutableSequence_pop(self, element, index);
}

/* Remove first occurrence of value.
 *
 *  Raises ValueError if the value is not present.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_remove(std::vector<T>* self, const T& element)
{
    return CPPY_MutableSequence_remove(self, element);
}

/* Reverse *IN PLACE*.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_reverse(std::vector<T>* self)
{
    return CPPY_MutableSequence_reverse(self->begin(), self->end());
}

/* Sort the list in ascending order and return None.
 */
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_sort(std::vector<T>* self)
{
    std::sort(self->begin(), self->end());
    return CPPY_ERROR_t::Ok;
}

template <typename T, typename Iterable>
CPPY_ERROR_t
CPPY_VECTOR_isequal(const std::vector<T>& self, Iterable other_first, Iterable other_last, bool* const result)
{
    return CPPY_Sequence_isequal(self.begin(), self.end(), other_first, other_last, result);
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_mul(const std::vector<T>& self, int n, std::vector<T>* result)
{
    if (n <= 0)
        return CPPY_ERROR_t::Ok;
    if (n == 1)
        return CPPY_VECTOR_extend(result, self.begin(), self.end());

    for (int i = 0; i < n; ++i)
        CPPY_VECTOR_extend(result, self.begin(), self.end());

    return CPPY_ERROR_t::Ok;
}
