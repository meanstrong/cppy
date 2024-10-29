#ifndef CPPY_VECTOR_H
#define CPPY_VECTOR_H

#include <vector>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Built-in mutable sequence.
*/
template <typename T>
PyException CPPY_VECTOR_init(std::vector<T>* const this_vector, int n, const T* elements) {
	this_vector->clear();
	this_vector->reserve(n);
	this_vector->insert(this_vector->end(), elements, elements + n);
	return PyException::Ok;
}

template <typename T, class Iteratable>
PyException CPPY_VECTOR_init(std::vector<T>* const this_vector, Iteratable begin, Iteratable end) {
	this_vector->clear();
	this_vector->insert(this_vector->end(), begin, end);
	return PyException::Ok;
}

template <typename T>
PyException CPPY_VECTOR_iscontain(const std::vector<T>& this_vector, const T& element, bool* const result) {
	*result = std::find(this_vector.begin(), this_vector.end(), element) != this_vector.end();
	return PyException::Ok;
}

/* Append object to the end of the list
*/
template <typename T>
PyException CPPY_VECTOR_append(std::vector<T>* const this_vector, const T& element) {
	this_vector->push_back(element);
	return PyException::Ok;
}

/* Remove all items from list.
*/
template <typename T>
PyException CPPY_VECTOR_clear(std::vector<T>* const this_vector) {
	this_vector->clear();
	return PyException::Ok;
}

/* Return a shallow copy of the list.
*/
template <typename T>
PyException CPPY_VECTOR_copy(const std::vector<T>& this_vector, std::vector<T>* const result) {
	result->clear();
	result->reserve(this_vector.size());
	result->insert(result->end(), this_vector.begin(), this_vector.end());
	return PyException::Ok;
}

/* Return number of occurrences of value.
*/
template <typename T>
PyException CPPY_VECTOR_count(const std::vector<T>& this_vector, int* const count) {
	*count = (int)this_vector.size();
	return PyException::Ok;
}

/* Extend list by appending elements from the iterable.
*/
template <typename T, class Iteratable>
PyException CPPY_VECTOR_extend(std::vector<T>* const this_vector, Iteratable begin, Iteratable end) {
	this_vector->insert(this_vector->end(), begin, end);
	return PyException::Ok;
}

/* Return first index of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
PyException CPPY_VECTOR_index(const std::vector<T>& this_vector, const T& element, int* const index) {
	for (std::vector<T>::size_type i = 0; i != this_vector.size(); i++)
	{
		if (this_vector[i] == element)
		{
			*index = (int)i;
			return PyException::Ok;
		}
	}
	return PyException::ValueError;

}

/* Insert object before index.
*/
template <typename T>
PyException CPPY_VECTOR_insert(std::vector<T>* const this_vector, int index, const T& element) {
	int len = (int)this_vector->size();
	if (index > len) index = len;
	else if (index < 0) {
		index += len;
		if (index < 0) index = 0;
	}
	this_vector->insert(this_vector->begin() + index, element);
	return PyException::Ok;

}

/* Remove and return item at index (default last).
*
*  Raises IndexError if list is empty or index is out of range.
*/
template <typename T>
PyException CPPY_VECTOR_pop(std::vector<T>* this_vector, T* element, int index = -1) {
	if (this_vector->empty()) return PyException::IndexError;

	int len = (int)this_vector->size();
	if (index >= len || index < -len) return PyException::IndexError;

	index = index >= 0 ? index : index + len;
	*element = this_vector->at(index);
	this_vector->erase(this_vector->begin() + index);
	return PyException::Ok;
}

/* Remove first occurrence of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename T>
PyException CPPY_VECTOR_remove(std::vector<T>* this_vector, const T& element) {
	auto it = std::find(this_vector->begin(), this_vector->end(), element);
	if (it == this_vector->end()) return PyException::ValueError;

	this_vector->erase(it);
	return PyException::Ok;
}

/* Reverse *IN PLACE*.
*/
template <typename T>
PyException CPPY_VECTOR_reverse(std::vector<T>* this_vector) {
	std::reverse(this_vector->begin(), this_vector->end());
	return PyException::Ok;
}

/* Sort the list in ascending order and return None.
*/
template <typename T>
PyException CPPY_VECTOR_sort(std::vector<T>* this_vector) {
	std::sort(this_vector->begin(), this_vector->end());
	return PyException::Ok;
}

template <typename T>
PyException CPPY_VECTOR_isequal(const std::vector<T>& this_vector, const std::vector<T>& other_set, bool* const result) {
	if (this_vector.size() != other_set.size())
	{
		*result = false;
		return PyException::Ok;
	}
	for (size_t i = 0; i < this_vector.size(); i++)
	{
		if (this_vector[i] != other_set[i])
		{
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

template <typename T>
PyException CPPY_VECTOR_iterator(const std::vector<T>& this_vector, T result[]) {
	for (size_t i = 0; i < this_vector.size(); i++) result[i] = this_vector[i];
	return PyException::Ok;
}

template <typename T>
PyException CPPY_VECTOR_mul(const std::vector<T>& this_vector, int n, std::vector<T>* result) {
	result->clear();
	if (n <= 0) return PyException::Ok;
	if (n == 1) {
		result->insert(result->end(), this_vector.begin(), this_vector.end());
		return PyException::Ok;
	}
	for (int i = 0; i < n; ++i)
	{
		result->insert(result->end(), this_vector.begin(), this_vector.end());
	}
	return PyException::Ok;
}

#endif // CPPY_VECTOR_H
