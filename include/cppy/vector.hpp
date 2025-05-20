#pragma once

#include <vector>

#include "cppy/internal/declare.h"
#include "cppy/typing.hpp"
#include "cppy/exception.h"

/* Built-in mutable sequence.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_init(std::vector<T>* const self, int n, const T* elements) {
	CPPY_MutableSequence_clear(self);
	return CPPY_MutableSequence_extend(self, elements, elements + n);
}

template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_VECTOR_init(std::vector<T>* const self, Iteratable begin, Iteratable end) {
	CPPY_MutableSequence_clear(self);
	return CPPY_MutableSequence_extend(self, begin, end);;
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_contains(const std::vector<T>& self, const T& element, bool* const result) {
	return CPPY_Sequence_contains(self, element, result);
}

/* Append object to the end of the list
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_append(std::vector<T>* const self, const T& element) {
	return CPPY_MutableSequence_append(self, element);
}

/* Remove all items from list.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_clear(std::vector<T>* const self) {
	return CPPY_MutableSequence_clear(self);
}

/* Return a shallow copy of the list.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_copy(const std::vector<T>& self, std::vector<T>* const result) {
	CPPY_MutableSequence_clear(result);
	return CPPY_MutableSequence_extend(result, self.begin(), self.end());
}

/* Return number of occurrences of value.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_count(const std::vector<T>& self, const T& element, int* const count) {
	return CPPY_Sequence_count(self, element, count);
}

/* Extend list by appending elements from the iterable.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_VECTOR_extend(std::vector<T>* const self, Iteratable begin, Iteratable end) {
	return CPPY_MutableSequence_extend(self, begin, end);
}

/* Return first index of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_index(const std::vector<T>& self, const T& element, int* const index, int start = 0, int end = INT_MAX) {
	return CPPY_Sequence_index(self, element, index, start, end);

}

/* Insert object before index.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_insert(std::vector<T>* const self, int index, const T& element) {
	return CPPY_MutableSequence_insert(self, index, element);
}

/* Remove and return item at index (default last).
*
*  Raises IndexError if list is empty or index is out of range.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_pop(std::vector<T>* const self, T* const element, int index = -1) {
	return CPPY_MutableSequence_pop(self, element, index);
}

/* Remove first occurrence of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_remove(std::vector<T>* self, const T& element) {
	return CPPY_MutableSequence_remove(self, element);
}

/* Reverse *IN PLACE*.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_reverse(std::vector<T>* self) {
	return CPPY_MutableSequence_reverse(self);
}

/* Sort the list in ascending order and return None.
*/
template <typename T>
CPPY_ERROR_t CPPY_VECTOR_sort(std::vector<T>* self) {
	std::sort(self->begin(), self->end());
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_eq(const std::vector<T>& self, const std::vector<T>& other, bool* const result) {
	if (self.size() != other.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}
	for (size_t i = 0; i < self.size(); i++)
	{
		if (self[i] != other[i])
		{
			*result = false;
			return CPPY_ERROR_t::Ok;
		}
	}
	*result = true;
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_iter(const std::vector<T>& self, T result[]) {
	return CPPY_Iterable_iter(self, result);
}

template <typename T>
CPPY_ERROR_t CPPY_VECTOR_mul(const std::vector<T>& self, int n, std::vector<T>* result) {
	CPPY_MutableSequence_clear(result);
	if (n <= 0) return CPPY_ERROR_t::Ok;
	if (n == 1)
		return CPPY_MutableSequence_extend(result, self.begin(), self.end());

	for (int i = 0; i < n; ++i)
		CPPY_MutableSequence_extend(result, self.begin(), self.end());

	return CPPY_ERROR_t::Ok;
}
