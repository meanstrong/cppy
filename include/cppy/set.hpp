#pragma once

#include <algorithm>
#include <set>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

/* set(iterable) -> new set object
 *
 *  Build an unordered collection of unique elements.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_SET_init(std::set<T>* const self, Iterable first, Iterable last)
{
    self->clear();
    self->insert(first, last);
    return CPPY_ERROR_t::Ok;
}

template <typename T>
CPPY_ERROR_t CPPY_SET_iscontain(const std::set<T>& self, const T& element, bool* const result)
{
    *result = self.find(element) != self.end();
    return CPPY_ERROR_t::Ok;
}

/* Add an element to a set.
 *
 *  This has no effect if the element is already present.
 */
template <typename T>
CPPY_ERROR_t CPPY_SET_add(std::set<T>* const self, const T& element)
{
    self->insert(element);
    return CPPY_ERROR_t::Ok;
}

/* Remove all elements from this set.
 */
template <typename T>
CPPY_ERROR_t CPPY_SET_clear(std::set<T>* const self)
{
    self->clear();
    return CPPY_ERROR_t::Ok;
}

/* Return a shallow copy of a set.
 */
template <typename T>
CPPY_ERROR_t CPPY_SET_copy(const std::set<T>& self, std::set<T>* const result)
{
    result->clear();
    result->insert(self.begin(), self.end());
    return CPPY_ERROR_t::Ok;
}

/* Return the difference of two or more sets as a new set.
 *
 *  (i.e. all elements that are in this set but not the others.)
 */
template <typename T, class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_difference(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, std::set<T>* const result)
{
    result->clear();
    std::set_difference(first_1, last_1, first_2, last_2, std::inserter(*result, result->begin()));
    return CPPY_ERROR_t::Ok;
}

/* Remove all elements of another set from this set.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_SET_difference_update(std::set<T>* const self, Iterable first, Iterable last)
{
    for (; first != last; ++first)
    {
        self->erase(*first);
    }
    return CPPY_ERROR_t::Ok;
}

/* Return the intersection of two sets as a new set.
 *
 *  (i.e. all elements that are in both sets.)
 */
template <typename T, class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_intersection(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, std::set<T>* const result)
{
    result->clear();
    std::set_intersection(first_1, last_1, first_2, last_2, std::inserter(*result, result->begin()));
    return CPPY_ERROR_t::Ok;
}

/* Update a set with the intersection of itself and another.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_SET_intersection_update(std::set<T>* const self, Iterable first, Iterable last)
{
    std::set<T> result;
    std::set_intersection(self->begin(), self->end(), first, last, std::inserter(result, result.begin()));
    self->swap(result);
    return CPPY_ERROR_t::Ok;
}

/* Return the symmetric difference of two sets as a new set.
 *
 *  (i.e. all elements that are in exactly one of the sets.)
 */
template <typename T, class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_symmetric_difference(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, std::set<T>* const result)
{
    result->clear();
    std::set_symmetric_difference(first_1, last_1, first_2, last_2, std::inserter(*result, result->begin()));
    return CPPY_ERROR_t::Ok;
}

/* Update a set with the symmetric difference of itself and another.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_SET_symmetric_difference_update(std::set<T>* const self, Iterable first, Iterable last)
{
    std::set<T> result;

    std::set_symmetric_difference(self->begin(), self->end(), first, last, std::inserter(result, result.begin()));

    self->swap(result);
    return CPPY_ERROR_t::Ok;
}

/* Return the union of sets as a new set.
 *
 *  (i.e. all elements that are in either set.)
 */
template <typename T, class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_union(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, std::set<T>* const result)
{
    result->clear();
    std::set_union(first_1, last_1, first_2, last_2, std::inserter(*result, result->begin()));
    return CPPY_ERROR_t::Ok;
}

/* Update a set with the union of itself and others.
 */
template <typename T, class Iterable>
CPPY_ERROR_t CPPY_SET_update(std::set<T>* self, Iterable first, Iterable last)
{
    self->insert(first, last);
    return CPPY_ERROR_t::Ok;
}

/* Remove and return an arbitrary set element.
 *  Raises KeyError if the set is empty.
 */
template <typename T>
CPPY_ERROR_t CPPY_SET_pop(std::set<T>* self, T* element)
{
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
CPPY_ERROR_t CPPY_SET_remove(std::set<T>* self, const T& element)
{
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
CPPY_ERROR_t CPPY_SET_discard(std::set<T>* self, const T& element)
{
    self->erase(element);
    return CPPY_ERROR_t::Ok;
}

/* Return True if two sets have a null intersection.
 */
template <class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_isdisjoint(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, bool* const result)
{
    *result = true;
    if ((first_1 == last_1) || (first_2 == last_2))
        return CPPY_ERROR_t::Ok;

    for (; first_1 != last_1; ++first_1)
    {
        if (std::find(first_2, last_2, *first_1) != last_2)
        {
            *result = false;
            break;
        }
    }
    return CPPY_ERROR_t::Ok;
}

/* Report whether another set contains this set.
 */
template <class Iterable1, class Iterable2>
CPPY_ERROR_t
CPPY_SET_issubset(Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, bool* const result)
{
    *result = std::includes(first_2, last_2, first_1, last_1);
    return CPPY_ERROR_t::Ok;
}

/* Report whether this set contains another set.
 */
template <class Iterable1, class Iterable2>
CPPY_ERROR_t CPPY_SET_issuperset(
    Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, bool* const result)
{
    *result = std::includes(first_1, last_1, first_2, last_2);
    return CPPY_ERROR_t::Ok;
}

template <class Iterable1, class Iterable2>
CPPY_ERROR_t
CPPY_SET_isequal(Iterable1 first_1, Iterable1 last_1, Iterable2 first_2, Iterable2 last_2, bool* const result)
{
    for (auto it = first_1; it != last_1; it++)
    {
        if (std::find(first_2, last_2, *it) == last_2)
        {
            *result = false;
            return CPPY_ERROR_t::Ok;
        }
    }
    for (auto it = first_2; it != first_2; it++)
    {
        if (std::find(first_1, last_1, *it) == last_1)
        {
            *result = false;
            return CPPY_ERROR_t::Ok;
        }
    }
    *result = true;
    return CPPY_ERROR_t::Ok;
}
