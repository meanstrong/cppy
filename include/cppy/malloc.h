#pragma once

#include <cstdlib>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

template <typename T>
class CPPY_API CPPY_MEMORY_handler
{
public:
	using size_type = std::size_t;
	using value_type = T;
	using pointer = T*;
	using size_address_type = size_type*;
	using pointer_address_type = pointer*;

	CPPY_ERROR_t alloc(const size_type n)
	{
		m_size = n;
		m_ptr = static_cast<pointer>(std::malloc(n * sizeof(T)));
		if (!m_ptr)
			return CPPY_ERROR_t::MemoryError;
		return CPPY_ERROR_t::Ok;

	}

	void free()
	{
		if (m_size > 0)
		{
			std::free(m_ptr);
			m_size = 0;
			m_ptr = nullptr;
		}
	}

	size_type get_size() { return m_size; }

	pointer get_pointer() { return m_ptr; }

	T& operator[](const size_type i) { return m_ptr[i]; }

	size_address_type address_of_size() { return &m_size; }

	pointer_address_type address_of_pointer() { return &m_ptr; }

	~CPPY_MEMORY_handler()
	{
		free();
	}

private:
	size_type m_size;
	pointer m_ptr;
};

template <size_t N, typename T, typename... Types>
struct GetTypeAtIndex
{
	using type = typename GetTypeAtIndex<N - 1, Types...>::type;
};

template <typename T, typename... Types>
struct GetTypeAtIndex<0, T, Types...>
{
	using type = T;
};

template <typename... Types>
struct CPPY_MEMORY_array_handler
{
public:
	using size_type = std::size_t;
	using size_address_type = size_type*;

	template <std::size_t N>
	using value_type_at = typename GetTypeAtIndex<N, Types...>::type;

	template <std::size_t N>
	using pointer_type_at = value_type_at<N>*;
	
	template <std::size_t N>
	using pointer_address_type_at = pointer_type_at<N>*;

	static constexpr std::size_t NumTypes = sizeof...(Types);

	void alloc(const size_type n)
	{
		alloc_recursive<0>(n);
		m_size = n;
	}

	template <std::size_t Index>
	void alloc_recursive(const size_type n)
	{
		if constexpr (Index < NumTypes)
		{
			auto size = n * sizeof(value_type_at<Index>);
			m_pointers[Index] = std::malloc(size);
			alloc_recursive<Index + 1>(n);
		}
	}

	void free()
	{
		if (m_size > 0)
		{
			for (std::size_t i = 0; i < NumTypes; i++)
			{
				std::free(m_pointers[i]);
				m_pointers[i] = nullptr;
			}
		}
		m_size = 0;
	}

	size_type get_size() { return m_size; }

	template <std::size_t N>
	pointer_type_at<N> get_pointer()
	{
		return reinterpret_cast<pointer_type_at<N>>(m_pointers[N]);
	}

	size_address_type address_of_size() { return &m_size; }

	template <std::size_t N>
	pointer_address_type_at<N> address_of_pointer()
	{
		return reinterpret_cast<pointer_address_type_at<N>>(m_pointers + N);
	}

	~CPPY_MEMORY_array_handler()
	{
		free();
	}

private:
	size_type m_size;
	void* m_pointers[sizeof...(Types)];
};
