#ifndef CPPY_LIST_H
#define CPPY_LIST_H

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Built-in mutable sequence.
*/
template <typename List, typename Element>
PyException CPPY_LIST_init(List* const this_list, int n, const Element* elements) {
	this_list->clear();
	this_list->insert(this_list->end(), elements, elements + n);
	return PyException::Ok;
}

template <typename List, class Iteratable>
PyException CPPY_LIST_init(List* const this_list, Iteratable begin, Iteratable end) {
	this_list->clear();
	this_list->insert(this_list->end(), begin, end);
	return PyException::Ok;
}

template <typename List, typename Element>
PyException CPPY_LIST_iscontain(const List& this_list, const Element& element, bool* const result) {
	*result = std::find(this_list.begin(), this_list.end(), element) != this_list.end();
	return PyException::Ok;
}

/* Append object to the end of the list
*/
template <typename List, typename Element>
PyException CPPY_LIST_append(List* const this_list, const Element& element) {
	this_list->push_back(element);
	return PyException::Ok;
}

/* Remove all items from list.
*/
template <typename List>
PyException CPPY_LIST_clear(List* const this_list) {
	this_list->clear();
	return PyException::Ok;
}

/* Return a shallow copy of the list.
*/
template <typename List>
PyException CPPY_LIST_copy(const List& this_list, List* const result) {
	result->clear();
	result->insert(result->end(), this_list.begin(), this_list.end());
	return PyException::Ok;
}

/* Return number of occurrences of value.
*/
template <typename List>
PyException CPPY_LIST_count(const List& this_list, int* const count) {
	*count = (int)this_list.size();
	return PyException::Ok;
}

/* Extend list by appending elements from the iterable.
*/
template <typename List, class Iteratable>
PyException CPPY_LIST_extend(List* const this_list, Iteratable begin, Iteratable end) {
	this_list->insert(this_list->end(), begin, end);
	return PyException::Ok;
}

/* Return first index of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename List, typename Element>
PyException CPPY_LIST_index(const List& this_list, const Element& element, int* const index) {
	for (List::size_type i = 0; i != this_list.size(); i++)
	{
		if (this_list[i] == element)
		{
			*index = (int)i;
			return PyException::Ok;
		}
	}
	return PyException::ValueError;

}

/* Insert object before index.
*/
template <typename List, typename Element>
PyException CPPY_LIST_insert(List* const this_list, int index, const Element& element) {
	int len = (int)this_list->size();
	if (index > len) index = len;
	else if (index < 0) {
		index += len;
		if (index < 0) index = 0;
	}
	this_list->insert(this_list->begin() + index, element);
	return PyException::Ok;

}

/* Remove and return item at index (default last).
*
*  Raises IndexError if list is empty or index is out of range.
*/
template <typename List, typename Element>
PyException CPPY_LIST_pop(List* this_list, Element* element, int index = -1) {
	if (this_list->empty()) return PyException::IndexError;

	int len = (int)this_list->size();
	if (index >= len || index < -len) return PyException::IndexError;

	index = index >= 0 ? index : index + len;
	*element = this_list->at(index);
	this_list->erase(this_list->begin() + index);
	return PyException::Ok;
}

/* Remove first occurrence of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename List, typename Element>
PyException CPPY_LIST_remove(List* this_list, const Element& element) {
	auto it = std::find(this_list->begin(), this_list->end(), element);
	if (it == this_list->end()) return PyException::ValueError;

	this_list->erase(it);
	return PyException::Ok;
}

/* Reverse *IN PLACE*.
*/
template <typename List>
PyException CPPY_LIST_reverse(List* this_list) {
	std::reverse(this_list->begin(), this_list->end());
	return PyException::Ok;
}

/* Sort the list in ascending order and return None.
*/
template <typename List>
PyException CPPY_LIST_sort(List* this_list) {
	std::sort(this_list->begin(), this_list->end());
	return PyException::Ok;
}

template <typename List>
PyException CPPY_LIST_isequal(const List& this_list, const List& other_set, bool* const result) {
	if (this_list.size() != other_set.size())
	{
		*result = false;
		return PyException::Ok;
	}
	for (size_t i = 0; i < this_list.size(); i++)
	{
		if (this_list[i] != other_set[i])
		{
			*result = false;
			return PyException::Ok;
		}
	}
	*result = true;
	return PyException::Ok;
}

template <typename List, typename Element>
PyException CPPY_LIST_iterator(const List& this_list, Element result[]) {
	for (size_t i = 0; i < this_list.size(); i++) result[i] = this_list[i];
	return PyException::Ok;
}

template <typename List>
PyException CPPY_LIST_mul(const List& this_list, int n, List* result) {
	result->clear();
	if (n <= 0) return PyException::Ok;
	if (n == 1) {
		result->insert(result->end(), this_list.begin(), this_list.end());
		return PyException::Ok;
	}
	for (int i = 0; i < n; ++i)
	{
		result->insert(result->end(), this_list.begin(), this_list.end());
	}
	return PyException::Ok;
}

#endif // CPPY_LIST_H
