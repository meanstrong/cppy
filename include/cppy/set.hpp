#pragma once

#include <algorithm>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* set(iterable) -> new set object
*
*  Build an unordered collection of unique elements.
*/
template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_init(Set* const this_set, int n, const Element* elements) {
	this_set->clear();
	for (int i = 0; i < n; i++)
		this_set->insert(elements[i]);
	return CPPY_ERROR_t::Ok;
}

template <typename Set, class Iteratable>
CPPY_ERROR_t CPPY_SET_init(Set* const this_set, Iteratable begin, Iteratable end) {
	this_set->clear();
	this_set->insert(begin, end);
	return CPPY_ERROR_t::Ok;
}

template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_iscontain(const Set& this_set, const Element& element, bool* const result) {
	*result = this_set.find(element) != this_set.end();
	return CPPY_ERROR_t::Ok;
}

/* Add an element to a set.
*
*  This has no effect if the element is already present.
*/
template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_add(Set* const this_set, const Element& element) {
	this_set->insert(element);
	return CPPY_ERROR_t::Ok;
}

/* Remove all elements from this set.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_clear(Set* const this_set) {
	this_set->clear();
	return CPPY_ERROR_t::Ok;
}

/* Return a shallow copy of a set.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_copy(const Set& this_set, Set* const result) {
	result->clear();
	result->insert(this_set.begin(), this_set.end());
	return CPPY_ERROR_t::Ok;
}

/* Return the difference of two or more sets as a new set.
*
*  (i.e. all elements that are in this set but not the others.)
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_difference(const Set& this_set, const Set& other_set, Set* const result) {
	result->clear();
	std::set_difference(
		this_set.begin(), this_set.end(), other_set.begin(), other_set.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Remove all elements of another set from this set.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_difference_update(Set* const this_set, const Set& other_set) {
	for (auto it = other_set.begin(); it != other_set.end(); ++it) this_set->erase(*it);
	return CPPY_ERROR_t::Ok;
}

/* Return the intersection of two sets as a new set.
*
*  (i.e. all elements that are in both sets.)
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_intersection(const Set& this_set, const Set& other_set, Set* const result) {
	result->clear();
	std::set_intersection(
		this_set.begin(), this_set.end(), other_set.begin(), other_set.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the intersection of itself and another.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_intersection_update(Set* const this_set, const Set& other_set) {
	Set difference;
	std::set_difference(
		this_set->begin(), this_set->end(), other_set.begin(), other_set.end(), std::inserter(difference, difference.begin()));
	for (auto it = difference.begin(); it != difference.end(); ++it) this_set->erase(*it);
	return CPPY_ERROR_t::Ok;
}

/* Return the symmetric difference of two sets as a new set.
*
*  (i.e. all elements that are in exactly one of the sets.)
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_symmetric_difference(const Set& this_set, const Set& other_set, Set* const result) {
	result->clear();
	std::set_symmetric_difference(this_set.begin(), this_set.end(), other_set.begin(), other_set.end(),
		std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the symmetric difference of itself and another.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_symmetric_difference_update(Set* const this_set, const Set& other_set) {
	Set intersection_result;
	std::set_intersection(
		this_set->begin(), this_set->end(), other_set.begin(), other_set.end(), std::inserter(intersection_result, intersection_result.begin()));
	for (auto it = intersection_result.begin(); it != intersection_result.end(); ++it) this_set->erase(*it);
	for (auto it = other_set.begin(); it != other_set.end(); ++it) {
		if (intersection_result.find(*it) == intersection_result.end())
		{
			this_set->insert(*it);
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Return the union of sets as a new set.
*
*  (i.e. all elements that are in either set.)
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_union(const Set& this_set, const Set& other_set, Set* const result) {
	result->clear();
	std::set_union(this_set.begin(), this_set.end(), other_set.begin(), other_set.end(), std::inserter(*result, result->begin()));
	return CPPY_ERROR_t::Ok;
}

/* Update a set with the union of itself and others.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_update(Set* this_set, const Set& other_set) {
	this_set->insert(other_set.begin(), other_set.end());
	return CPPY_ERROR_t::Ok;
}

/* Remove and return an arbitrary set element.
*  Raises KeyError if the set is empty.
*/
template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_pop(Set* this_set, Element* element) {
	if (this_set->empty())
	{
		return CPPY_ERROR_t::KeyError;
	}
	*element = this_set->extract(this_set->begin()).value();
	return CPPY_ERROR_t::Ok;
}

/* Remove an element from a set; it must be a member.
*
*  If the element is not a member, raise a KeyError.
*/
template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_remove(Set* this_set, const Element& element) {
	auto size = this_set->erase(element);
	if (size == 0)
	{
		return CPPY_ERROR_t::KeyError;
	}
	return CPPY_ERROR_t::Ok;
}

/* Remove an element from a set if it is a member.
*
*  Unlike set.remove(), the discard() method does not raise
*  an exception when an element is missing from the set.
*/
template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_discard(Set* this_set, const Element& element) {
	this_set->erase(element);
	return CPPY_ERROR_t::Ok;
}

/* Return True if two sets have a null intersection.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_isdisjoint(const Set& this_set, const Set& other_set, bool* const result) {
	for (auto it = this_set.begin(); it != this_set.end(); ++it) {
		if (other_set.find(*it) != other_set.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Report whether another set contains this set.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_issubset(const Set& this_set, const Set& other_set, bool* const result) {
	if (this_set.size() > other_set.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}

	for (auto it = this_set.begin(); it != this_set.end(); ++it) {
		if (other_set.find(*it) == other_set.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

/* Report whether this set contains another set.
*/
template <typename Set>
CPPY_ERROR_t CPPY_SET_issuperset(const Set& this_set, const Set& other_set, bool* const result) {
	if (this_set.size() < other_set.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}

	for (auto it = other_set.begin(); it != other_set.end(); ++it) {
		if (this_set.find(*it) == this_set.end()) {
			*result = false;
			break;
		}
	}
	return CPPY_ERROR_t::Ok;
}

template <typename Set>
CPPY_ERROR_t CPPY_SET_isequal(const Set& this_set, const Set& other_set, bool* const result) {
	if (this_set.size() != other_set.size())
	{
		*result = false;
		return CPPY_ERROR_t::Ok;
	}
	for (auto it = this_set.begin(); it != this_set.end(); it++)
	{
		if (other_set.count(*it) == 0)
		{
			*result = false;
			return CPPY_ERROR_t::Ok;
		}
	}
	*result = true;
	return CPPY_ERROR_t::Ok;
}

template <typename Set, typename Element>
CPPY_ERROR_t CPPY_SET_iterator(const Set& this_set, Element result[]) {
	int i = 0;
	for (auto it = this_set.begin(); it != this_set.end(); it++)
	{
		result[i++] = *it;
	}
	return CPPY_ERROR_t::Ok;
}
