#pragma once

#include <algorithm>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

template <typename Container, typename Element>
CPPY_ERROR_t CPPY_Container_iscontain(const Container& self, const Element& element, bool* const result) {
	*result = self.find(element) != self.end();
	return CPPY_ERROR_t::Ok;
}

template <typename Iterable, class Callable>
CPPY_ERROR_t CPPY_Iterable_iter(const Iterable& self, Callable call) {
	for (const auto& x : self) call(x);
	return CPPY_ERROR_t::Ok;
}

template <typename Sized>
CPPY_ERROR_t CPPY_Sized_len(const Sized& self, typename Sized::size_type* const len) {
	*len = self.size();
	return CPPY_ERROR_t::Ok;
}

// class Collection(Sized, Iterable, Container)

template <typename Reversible, typename Element>
CPPY_ERROR_t CPPY_Reversible_reversed(Reversible* const self) {
	std::reverse(self->begin(), self->end());
	return CPPY_ERROR_t::Ok;
}

template <typename Sequence, typename Element>
CPPY_ERROR_t CPPY_Sequence_at(const Sequence& self, int index, Element* const element) {
	*element = self[index];
	return CPPY_ERROR_t::Ok;
}

template <typename Sequence, typename Element>
CPPY_ERROR_t CPPY_Sequence_iscontain(const Sequence& self, const Element& element, bool* const result) {
	*result = std::find(self.begin(), self.end(), element) != self.end();
	return CPPY_ERROR_t::Ok;
}

template <typename Sequence>
CPPY_ERROR_t CPPY_Sequence_isequal(const Sequence& self, const Sequence& other, bool* const result) {
	using SizeType = typename Sequence::size_type;
	using ValueType = typename Sequence::value_type;
	SizeType n_self = self.size();
	SizeType n_other = other.size();
	if (n_self != n_other)
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}
	ValueType v_self, v_other;
	for (int i = 0; i < static_cast<int>(n_self); i++)
	{
		CPPY_Sequence_at(self, i, &v_self);
		CPPY_Sequence_at(other, i, &v_other);
		if (v_self != v_other)
		{
			*result = false;
			return CPPY_ERROR_t::Ok;
		}
	}
	*result = true;
	return CPPY_ERROR_t::Ok;
}

template <typename Sequence, typename Element>
CPPY_ERROR_t CPPY_Sequence_index(const Sequence& self, const Element& element, int* const index, int start = 0, int end = INT_MAX) {
	int len = static_cast<int>(self.size());

	int int_len = len;
	if (end > len) end = len;
	else if (end < 0) {
		end += len;
		if (end < 0) end = 0;
	}
	if (start < 0)
	{
		start += len;
		if (start < 0) start = 0;
	}

	int i = start;
	while (i < end)
	{
		Element e;
		CPPY_Sequence_at(self, i, &e);
		if (e == element)
		{
			*index = i;
			return CPPY_ERROR_t::Ok;
		}
		i++;
	}
	return CPPY_ERROR_t::ValueError;
}

template <typename Sequence, typename Element>
CPPY_ERROR_t CPPY_Sequence_count(const Sequence& self, const Element& element, int* const count) {
	*count = static_cast<int>(std::count(self.begin(), self.end(), element));
	return CPPY_ERROR_t::Ok;
}

// class Sequence(Reversible, Collection)

/* Insert object before index.
*/
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_insert(MutableSequence* const self, int index, const Element& element) {
	int len = static_cast<int>(self->size());

	if (index > len) index = len;
	else if (index < 0) {
		index += len;
		if (index < 0) index = 0;
	}
	self->insert(self->begin() + index, element);
	return CPPY_ERROR_t::Ok;

}

/* Append object to the end of the list
*/
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_append(MutableSequence* const self, const Element& element) {
	self->push_back(element);
	return CPPY_ERROR_t::Ok;
}

/* Remove all items from list.
*/
template <typename MutableSequence>
CPPY_ERROR_t CPPY_MutableSequence_clear(MutableSequence* const self) {
	self->clear();
	return CPPY_ERROR_t::Ok;
}

/* Reverse *IN PLACE*.
*/
template <typename MutableSequence>
CPPY_ERROR_t CPPY_MutableSequence_reverse(MutableSequence* self) {
	std::reverse(self->begin(), self->end());
	return CPPY_ERROR_t::Ok;
}

/* Extend list by appending elements from the iterable.
*/
template <typename MutableSequence, class Iterable>
CPPY_ERROR_t CPPY_MutableSequence_extend(MutableSequence* const self, Iterable begin, Iterable end) {
	self->insert(self->end(), begin, end);
	return CPPY_ERROR_t::Ok;
}

/* Remove and return item at index (default last).
*
*  Raises IndexError if list is empty or index is out of range.
*/
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_pop(MutableSequence* self, Element* const element, int index = -1) {
	if (self->empty()) return CPPY_ERROR_t::IndexError;

	int len = static_cast<int>(self->size());
	if (index >= len || index < -len) return CPPY_ERROR_t::IndexError;

	index = index >= 0 ? index : index + len;
	CPPY_Sequence_at(*self, index, element);
	self->erase(self->begin() + index);
	return CPPY_ERROR_t::Ok;
}

/* Remove first occurrence of value.
*
*  Raises ValueError if the value is not present.
*/
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_remove(MutableSequence* self, const Element& element) {
	auto it = std::find(self->begin(), self->end(), element);
	if (it == self->end()) return CPPY_ERROR_t::ValueError;

	self->erase(it);
	return CPPY_ERROR_t::Ok;
}
