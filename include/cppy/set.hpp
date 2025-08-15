#pragma once

#include <algorithm>
#include <set>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* set(iterable) -> new set object
*
*  Build an unordered collection of unique elements.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_init(std::set<T>* const self, Iteratable begin, Iteratable end) {
	self->clear();
	self->insert(begin, end);
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_SET_iscontain(const std::set<T>& self, const T& element, bool* const result) {
	*result = self.find(element) != self.end();
	return CPPY_ERROR_t::Ok;
}

/* Add an element to a set.
*
*  This has no effect if the element is already present.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_add(std::set<T>* const self, const T& element) {
	self->insert(element);
	return CPPY_ERROR_t::Ok;
}

/* Remove all elements from this set.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_clear(std::set<T>* const self) {
	self->clear();
	return CPPY_ERROR_t::Ok;
}

/* Return a shallow copy of a set.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_copy(Iteratable begin, Iteratable end, std::set<T>* const result) {
	result->clear();
	result->insert(begin, end);
	return CPPY_ERROR_t::Ok;
}

/* Return the difference of two or more sets as a new set.
*
*  (i.e. all elements that are in this set but not the others.)
*/
template <typename T, class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_difference(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, std::set<T>* const result) {
	result->clear();
	std::set_difference(
		this_begin, this_end, other_begin, other_end, std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Remove all elements of another set from this set.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_difference_update(std::set<T>* const self, Iteratable begin, Iteratable end) {
	for (; begin != end; ++begin)
	{
		self->erase(*begin);
	}
	return CPPY_ERROR_t::Ok;
}

/* Return the intersection of two sets as a new set.
*
*  (i.e. all elements that are in both sets.)
*/
template <typename T, class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_intersection(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, std::set<T>* const result) {
	result->clear();
	std::set_intersection(
		this_begin, this_end, other_begin, other_end, std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the intersection of itself and another.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_intersection_update(std::set<T>* const self, Iteratable begin, Iteratable end) {
	std::set<T> result;
	std::set_intersection(
		self->begin(), self->end(), begin, end, std::inserter(result, result.begin()));
	self->swap(result);
	return CPPY_ERROR_t::Ok;
}

/* Return the symmetric difference of two sets as a new set.
*
*  (i.e. all elements that are in exactly one of the sets.)
*/
template <typename T, class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_symmetric_difference(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, std::set<T>* const result) {
	result->clear();
	std::set_symmetric_difference(this_begin, this_end, other_begin, other_end,
		std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the symmetric difference of itself and another.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_symmetric_difference_update(std::set<T>* const self, Iteratable begin, Iteratable end) {
	std::set<T> result;

	std::set_symmetric_difference(self->begin(), self->end(), begin, end,
		std::inserter(result, result.begin())
	);

	self->swap(result);
	return CPPY_ERROR_t::Ok;
}

/* Return the union of sets as a new set.
*
*  (i.e. all elements that are in either set.)
*/
template <typename T, class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_union(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, std::set<T>* const result) {
	result->clear();
	std::set_union(this_begin, this_end, other_begin, other_end, std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the union of itself and others.
*/
template <typename T, class Iteratable>
CPPY_ERROR_t CPPY_SET_update(std::set<T>* self, Iteratable begin, Iteratable end) {
	self->insert(begin, end);
	return CPPY_ERROR_t::Ok;
}

/* Remove and return an arbitrary set element.
*  Raises KeyError if the set is empty.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_pop(std::set<T>* self, T* element) {
	if (self->empty())
		return CPPY_ERROR_t::KeyError;

	*element = self->extract(self->begin()).value();
	return CPPY_ERROR_t::Ok;
}

/* Remove an element from a set; it must be a member.
*
*  If the element is not a member, raise a KeyError.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_remove(std::set<T>* self, const T& element) {
	auto size = self->erase(element);
	if (size == 0)
		return CPPY_ERROR_t::KeyError;

	return CPPY_ERROR_t::Ok;
}

/* Remove an element from a set if it is a member.
*
*  Unlike set.remove(), the discard() method does not raise
*  an exception when an element is missing from the set.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_discard(std::set<T>* self, const T& element) {
	self->erase(element);
	return CPPY_ERROR_t::Ok;
}

/* Return True if two sets have a null intersection.
*/
template <class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_isdisjoint(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, bool* const result) {
	*result = true;
	if ((this_begin == this_end) || (other_begin == other_end))
		return CPPY_ERROR_t::Ok;

	for (; this_begin != this_end; ++this_begin) {
		if (std::find(other_begin, other_end, *this_begin) != other_end) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Report whether another set contains this set.
*/
template <class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_issubset(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, bool* const result) {
	*result = std::includes(other_begin, other_end, this_begin, this_end);
	return CPPY_ERROR_t::Ok;
}

/* Report whether this set contains another set.
*/
template <class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_issuperset(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, bool* const result) {
	*result = std::includes(this_begin, this_end, other_begin, other_end);
	return CPPY_ERROR_t::Ok;
}

template <class Iteratable1, class Iteratable2>
CPPY_ERROR_t CPPY_SET_isequal(Iteratable1 this_begin, Iteratable1 this_end, Iteratable2 other_begin, Iteratable2 other_end, bool* const result) {
	for (auto it = this_begin; it != this_end; it++)
	{
		if (std::find(other_begin, other_end, *it) == other_end) {
			*result = false;
			return CPPY_ERROR_t::Ok;
		}
	}
	for (auto it = other_begin; it != other_begin; it++)
	{
		if (std::find(this_begin, this_end, *it) == this_end) {
			*result = false;
			return CPPY_ERROR_t::Ok;
		}
	}
	*result = true;
	return CPPY_ERROR_t::Ok;
}

template <typename T, class Callable>
CPPY_ERROR_t CPPY_SET_iter(const std::set<T>& self, Callable call) {
	return CPPY_Iterable_iter(self, call);
}
