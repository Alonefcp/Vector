#pragma once

#include <iostream>

template<typename Vector>
class VectorIterator
{
public:

	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	VectorIterator(PointerType pointer) : m_Ptr(pointer) {}

	VectorIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr + index); // *(m_ptr[index])
	}

	PointerType operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const VectorIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const VectorIterator& other) const
	{
		return !(*this == other);
	}

private:

	PointerType m_Ptr;
};


template<typename T>
class Vector
{
public:

	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;


	Vector()
	{
		ReAllocate(2);
	}

	Vector(std::initializer_list<T> list) : m_size(list.size()), m_capacity(list.size())
	{
		m_data = (T*)::operator new(m_capacity * sizeof(T));

		size_t index = 0;
		for (auto& value : list)
		{
			new(&m_data[index]) T(std::move(value));
			index++;
		}
	}

	~Vector()
	{
		Clear();
		//delete[] m_data;
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	void PushBack(const T& value)
	{
		if (m_size >= m_capacity)
		{
			ReAllocate(m_capacity + m_capacity / 2);
		}

		m_data[m_size] = value;
		m_size++;
	}

	void PushBack(T&& value)
	{
		if (m_size >= m_capacity)
		{
			ReAllocate(m_capacity + m_capacity / 2);
		}

		m_data[m_size] = std::move(value);
		m_size++;
	}

	template <typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_size >= m_capacity)
		{
			ReAllocate(m_capacity + m_capacity / 2);
		}

		new(&m_data[m_size]) T(std::forward<Args>(args)...);

		//m_data[m_size] = T(std::forward<Args>()...);
		return m_data[m_size++];
	}

	void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}

		m_size = 0;
	}

	T& operator[] (size_t index)
	{
		if (index >= m_size)
		{
			//assert
		}

		return m_data[index];
	}

	const T& operator[] (size_t index) const
	{

		if (index >= m_size)
		{
			//assert
		}


		return m_data[index];
	}

	size_t Size() const { return m_size; }

	Iterator begin()
	{
		return Iterator(m_data);
	}

	Iterator end()
	{
		return Iterator(m_data + m_size);
	}




private:

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;


	void ReAllocate(size_t newCapacity)
	{
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T)); //new T[newCapacity];

		if (m_capacity < m_size)
		{
			m_size = newCapacity;
		}

		for (size_t i = 0; i < m_size; i++)
		{
			new(&newBlock[i]) T(std::move(m_data[i]));

			//newBlock[i] = std::move(m_data[i]);
		}

		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].~T();
		}
		//delete[] m_data;
		::operator delete(m_data, m_capacity * sizeof(T));

		m_data = newBlock;
		m_capacity = newCapacity;
	}

};

