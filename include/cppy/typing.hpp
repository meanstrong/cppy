#pragma once

#include <algorithm>
#include <climits>
#include <iterator>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

template <typename Container, typename Element>
CPPY_ERROR_t CPPY_Container_iscontain(const Container& self, const Element& element, bool* const result)
{
    *result = self.find(element) != self.end();
    return CPPY_ERROR_t::Ok;
}

template <typename Iterable, class Callable>
CPPY_ERROR_t CPPY_Iterable_iter(Iterable first, Iterable last, Callable call)
{
    std::for_each(first, last, call);
    return CPPY_ERROR_t::Ok;
}

template <typename InputIterable, typename OutputIterable, class Callable>
CPPY_ERROR_t
CPPY_Iterable_iter(InputIterable input_first, InputIterable input_last, OutputIterable output_first, Callable call)
{
    std::transform(input_first, input_last, output_first, call);
    return CPPY_ERROR_t::Ok;
}

template <typename Sized>
CPPY_ERROR_t CPPY_Sized_len(const Sized& self, typename Sized::size_type* const len)
{
    *len = self.size();
    return CPPY_ERROR_t::Ok;
}

// class Collection(Sized, Iterable, Container)

template <typename Iterable, typename Element>
CPPY_ERROR_t CPPY_Reversible_reversed(Iterable first, Iterable last)
{
    std::reverse(first, last);
    return CPPY_ERROR_t::Ok;
}

template <typename Sequence, typename Element>
CPPY_ERROR_t CPPY_Sequence_at(const Sequence& self, int index, Element* const element)
{
    auto it = self.begin();
    std::advance(it, index);
    *element = *it;
    return CPPY_ERROR_t::Ok;
}

template <typename Iterable, typename Element>
CPPY_ERROR_t CPPY_Sequence_iscontain(Iterable first, Iterable last, const Element& element, bool* const result)
{
    *result = std::find(first, last, element) != last;
    return CPPY_ERROR_t::Ok;
}

template <typename Iterable1, typename Iterable2>
CPPY_ERROR_t
CPPY_Sequence_isequal(Iterable1 first1, Iterable1 last1, Iterable2 first2, Iterable2 last2, bool* const result)
{
    *result = std::equal(first1, last1, first2, last2);
    return CPPY_ERROR_t::Ok;
}

template <typename Iterable, typename Element>
CPPY_ERROR_t CPPY_Sequence_index(
    Iterable first, Iterable last, const Element& element, int* const index, int start = 0, int end = INT_MAX)
{
    int len = static_cast<int>(std::distance(first, last));

    if (end > len)
        end = len;
    else if (end < 0)
    {
        end += len;
        if (end < 0)
            end = 0;
    }
    if (start < 0)
    {
        start += len;
        if (start < 0)
            start = 0;
    }

    if (start >= end)
        return CPPY_ERROR_t::ValueError;

    auto begin = first;
    std::advance(begin, start);
    auto end_it = first;
    std::advance(end_it, end);
    auto it = std::find(begin, end_it, element);
    if (it != end_it)
    {
        *index = static_cast<int>(std::distance(first, it));
        return CPPY_ERROR_t::Ok;
    }
    return CPPY_ERROR_t::ValueError;
}

template <typename Iterable, typename Element>
CPPY_ERROR_t CPPY_Sequence_count(Iterable first, Iterable last, const Element& element, int* const count)
{
    *count = static_cast<int>(std::count(first, last, element));
    return CPPY_ERROR_t::Ok;
}

// class Sequence(Reversible, Collection)

/* Insert object before index.
 */
template <typename Iterator, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_insert(Iterator inserter, const Element& element)
{
    *inserter = element;
    return CPPY_ERROR_t::Ok;
}

/* Append object to the end of the list
 */
template <typename Iterator, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_append(Iterator back_inserter, const Element& element)
{
    *back_inserter = element;
    return CPPY_ERROR_t::Ok;
}

/* Remove all items from list.
 */
template <typename MutableSequence>
CPPY_ERROR_t CPPY_MutableSequence_clear(MutableSequence* const self)
{
    self->clear();
    return CPPY_ERROR_t::Ok;
}

/* Reverse *IN PLACE*.
 */
template <typename Iterable>
CPPY_ERROR_t CPPY_MutableSequence_reverse(Iterable first, Iterable last)
{
    std::reverse(first, last);
    return CPPY_ERROR_t::Ok;
}

/* Extend list by appending elements from the iterable.
 */
template <typename BackInserter, class Iterable>
CPPY_ERROR_t CPPY_MutableSequence_extend(BackInserter inserter, Iterable first, Iterable last)
{
    std::copy(first, last, inserter);
    return CPPY_ERROR_t::Ok;
}

/* Remove and return item at index (default last).
 *
 *  Raises IndexError if list is empty or index is out of range.
 */
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_pop(MutableSequence* self, Element* const element, int index = -1)
{
    if (self->empty())
        return CPPY_ERROR_t::IndexError;

    int len = static_cast<int>(self->size());
    if (index >= len || index < -len)
        return CPPY_ERROR_t::IndexError;

    index = index >= 0 ? index : index + len;
    CPPY_Sequence_at(*self, index, element);
    auto it = self->begin();
    std::advance(it, index);
    self->erase(it);
    return CPPY_ERROR_t::Ok;
}

/* Remove first occurrence of value.
 *
 *  Raises ValueError if the value is not present.
 */
template <typename MutableSequence, typename Element>
CPPY_ERROR_t CPPY_MutableSequence_remove(MutableSequence* self, const Element& element)
{
    auto it = std::find(self->begin(), self->end(), element);
    if (it == self->end())
        return CPPY_ERROR_t::ValueError;

    self->erase(it);
    return CPPY_ERROR_t::Ok;
}
