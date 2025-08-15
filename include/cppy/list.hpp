#pragma once

#include <list>

#include "cppy/internal/declare.h"
#include "cppy/typing.hpp"
#include "cppy/exception.h"

/* Built-in list.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_LIST_init(std::list<T>* const self, Iteratable begin, Iteratable end) {
	CPPY_MutableSequence_clear(self);
	return CPPY_MutableSequence_extend(self, begin, end);;
}

template <typename T>
CPPY_ERROR_t CPPY_LIST_iscontain(const std::list<T>& self, const T& element, bool* const result) {
	return CPPY_Sequence_iscontain(self, element, result);
}

/* Append object to the end of the list
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_append(std::list<T>* const self, const T& element) {
	return CPPY_MutableSequence_append(self, element);
}

/* Remove all items from list.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_clear(std::list<T>* const self) {
	return CPPY_MutableSequence_clear(self);
}

/* Return a shallow copy of the list.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_copy(const std::list<T>& self, std::list<T>* const result) {
	CPPY_MutableSequence_clear(result);
	return CPPY_MutableSequence_extend(result, self.begin(), self.end());
}

/* Return number of occurrences of value.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_count(const std::list<T>& self, const T& element, int* const count) {
	return CPPY_Sequence_count(self, element, count);
}

/* Extend list by appending elements from the iterable.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_LIST_extend(std::list<T>* const self, Iteratable begin, Iteratable end) {
	return CPPY_MutableSequence_extend(self, begin, end);
}

/* Return first index of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_index(const std::list<T>& self, const T& element, int* const index, int start = 0, int end = INT_MAX) {
	return CPPY_Sequence_index(self, element, index, start, end);

}

/* Insert object before index.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_insert(std::list<T>* const self, int index, const T& element) {
	return CPPY_MutableSequence_insert(self, index, element);
}

/* Remove and return item at index (default last).
*
*  Raises IndexError if list is empty or index is out of range.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_pop(std::list<T>* self, T* element, int index = -1) {
	return CPPY_MutableSequence_pop(self, element, index);
}

/* Remove first occurrence of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_remove(std::list<T>* self, const T& element) {
	return CPPY_MutableSequence_remove(self, element);
}

/* Reverse *IN PLACE*.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_reverse(std::list<T>* self) {
	return CPPY_MutableSequence_reverse(self);
}

/* Sort the list in ascending order and return None.
*/
template <typename T>
CPPY_ERROR_t CPPY_LIST_sort(std::list<T>* self) {
	std::sort(self->begin(), self->end());
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_LIST_isequal(const std::list<T>& self, const std::list<T>& other, bool* const result) {
	return CPPY_Sequence_isequal(self, other, result);
}

template <typename T, class Callable>
CPPY_ERROR_t CPPY_LIST_iter(const std::list<T>& self, Callable call) {
	return CPPY_Iterable_iter(self, call);
}

template <typename T>
CPPY_ERROR_t CPPY_LIST_mul(const std::list<T>& self, int n, std::list<T>* result) {
	CPPY_MutableSequence_clear(result);
	if (n <= 0) return CPPY_ERROR_t::Ok;
	if (n == 1)
		return CPPY_MutableSequence_extend(result, self.begin(), self.end());

	for (int i = 0; i < n; ++i)
		CPPY_MutableSequence_extend(result, self.begin(), self.end());

	return CPPY_ERROR_t::Ok;
}
