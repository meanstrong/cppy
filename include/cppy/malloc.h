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
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;


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

	size_type* address_of_size() { return &m_size; }

	pointer* address_of_pointer() { return &m_ptr; }

	~CPPY_MEMORY_handler()
	{
		free();
	}

private:
	size_type m_size;
	pointer m_ptr;
};
