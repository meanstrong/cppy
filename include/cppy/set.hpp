#pragma once

#include <algorithm>
#include <set>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* set(iterable) -> new set object
*
*  Build an unordered collection of unique elements.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_init(std::set<T>* const self, int n, const T* elements) {
	self->clear();
	for (int i = 0; i < n; i++)
		self->insert(elements[i]);
	return CPPY_ERROR_t::Ok;
}

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
template <typename T>
CPPY_ERROR_t CPPY_SET_copy(const std::set<T>& self, std::set<T>* const result) {
	result->clear();
	result->insert(self.begin(), self.end());
	return CPPY_ERROR_t::Ok;
}

/* Return the difference of two or more sets as a new set.
*
*  (i.e. all elements that are in this set but not the others.)
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_difference(const std::set<T>& self, const std::set<T>& other, std::set<T>* const result) {
	result->clear();
	std::set_difference(
		self.begin(), self.end(), other.begin(), other.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Remove all elements of another set from this set.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_difference_update(std::set<T>* const self, const std::set<T>& other) {
	for (auto it = other.begin(); it != other.end(); ++it) self->erase(*it);
	return CPPY_ERROR_t::Ok;
}

/* Return the intersection of two sets as a new set.
*
*  (i.e. all elements that are in both sets.)
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_intersection(const std::set<T>& self, const std::set<T>& other, std::set<T>* const result) {
	result->clear();
	std::set_intersection(
		self.begin(), self.end(), other.begin(), other.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the intersection of itself and another.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_intersection_update(std::set<T>* const self, const std::set<T>& other) {
	std::set<T> difference;
	std::set_difference(
		self->begin(), self->end(), other.begin(), other.end(), std::inserter(difference, difference.begin()));
	for (auto it = difference.begin(); it != difference.end(); ++it) self->erase(*it);
	return CPPY_ERROR_t::Ok;
}

/* Return the symmetric difference of two sets as a new set.
*
*  (i.e. all elements that are in exactly one of the sets.)
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_symmetric_difference(const std::set<T>& self, const std::set<T>& other, std::set<T>* const result) {
	result->clear();
	std::set_symmetric_difference(self.begin(), self.end(), other.begin(), other.end(),
		std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the symmetric difference of itself and another.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_symmetric_difference_update(std::set<T>* const self, const std::set<T>& other) {
	std::set<T> intersection_result;
	std::set_intersection(
		self->begin(), self->end(), other.begin(), other.end(), std::inserter(intersection_result, intersection_result.begin()));
	for (auto it = intersection_result.begin(); it != intersection_result.end(); ++it) self->erase(*it);
	for (auto it = other.begin(); it != other.end(); ++it) {
		if (intersection_result.find(*it) == intersection_result.end())
		{
			self->insert(*it);
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Return the union of sets as a new set.
*
*  (i.e. all elements that are in either set.)
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_union(const std::set<T>& self, const std::set<T>& other, std::set<T>* const result) {
	result->clear();
	std::set_union(self.begin(), self.end(), other.begin(), other.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the union of itself and others.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_update(std::set<T>* self, const std::set<T>& other) {
	self->insert(other.begin(), other.end());
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
template <typename T>
CPPY_ERROR_t CPPY_SET_isdisjoint(const std::set<T>& self, const std::set<T>& other, bool* const result) {
	*result = true;
	for (auto it = self.begin(); it != self.end(); ++it) {
		if (other.find(*it) != other.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Report whether another set contains this set.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_issubset(const std::set<T>& self, const std::set<T>& other, bool* const result) {
	if (self.size() > other.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}

	*result = true;
	for (auto it = self.begin(); it != self.end(); ++it) {
		if (other.find(*it) == other.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Report whether this set contains another set.
*/
template <typename T>
CPPY_ERROR_t CPPY_SET_issuperset(const std::set<T>& self, const std::set<T>& other, bool* const result) {
	if (self.size() < other.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}

	*result = true;
	for (auto it = other.begin(); it != other.end(); ++it) {
		if (self.find(*it) == self.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_SET_eq(const std::set<T>& self, const std::set<T>& other, bool* const result) {
	if (self.size() != other.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}

	*result = true;
	for (auto it = self.begin(); it != self.end(); it++)
	{
		if (other.count(*it) == 0)
		{
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_SET_iter(const std::set<T>& self, T result[]) {
	int i = 0;
	for (auto it = self.begin(); it != self.end(); it++)
	{
		result[i++] = *it;
	}
	return CPPY_ERROR_t::Ok;
}
