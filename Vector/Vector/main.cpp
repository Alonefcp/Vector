#include <iostream>
#include "Vector.h"

//template<typename T, size_t S>
//class Array
//{
//public:
//
//	constexpr size_t Size() const { return S; }
//
//	T& operator[] (size_t index) { return m_Data[index]; }
//	const T& operator[] (int index) const { return m_Data[index]; }
//
//	T* Data() { return m_Data; }
//	const T* Data() const { return m_Data; }
//
//
//private:
//
//	T m_Data[S];
//};
//

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_memoryBlock = nullptr;
	Vector3()
	{
		m_memoryBlock = new int[5];
	}

	Vector3(float scalar) : x(scalar), y(scalar), z(scalar)
	{
		m_memoryBlock = new int[5];
	}

	Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
		m_memoryBlock = new int[5];

	}

	Vector3(const Vector3& other) = delete;
	/*{
		std::cout << "Copy\n";
	}*/

	Vector3(Vector3&& other) noexcept
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		std::cout << "Move\n";
	}

	~Vector3()
	{
		std::cout << "Destroy\n";
		delete[] m_memoryBlock;
	}

	Vector3& operator= (const Vector3& other) = delete;
	/*{
		std::cout << "Copy\n";
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}*/

	Vector3& operator= (Vector3&& other) noexcept
	{
		std::cout << "Move\n";
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};


template<typename T>
void PrintVector(const T& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << "\n";
	}

	std::cout << "--------------------------------\n";
}

template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i].x << vector[i].y << vector[i].z << "\n";
	}

	std::cout << "--------------------------------\n";
}


int main()
{
	/*Array<int, 5> data;

	memset(data.Data(), 0, data.Size() * sizeof(int));

	for (size_t i = 0; i < data.Size(); i++)
	{
		std::cout << data[i]<< "\n";
	}*/




	//----------------- Using basic operations -----------------

	Vector<int> intVector = { 1, 4, 5 };
	intVector.PushBack(5);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	PrintVector(intVector);
	intVector.PopBack();
	PrintVector(intVector);
	intVector.Clear();

	/*Vector<Vector3> vector;
	vector.EmplaceBack(1.0f);
	vector.EmplaceBack(2, 3, 4);
	vector.EmplaceBack(1, 3, 4);
	vector.EmplaceBack();
	PrintVector(vector);

	vector.PopBack();
	vector.PopBack();
	PrintVector(vector);

	vector.EmplaceBack(5, 2, 0);
	vector.EmplaceBack(1, 7, 9);
	PrintVector(vector);

	vector.Clear();
	PrintVector(vector);

	vector.EmplaceBack(5, 2, 0);
	vector.EmplaceBack(1, 7, 9);
	PrintVector(vector);*/



	//----------------- Using iterators -----------------

	/*Vector<std::string> values;
	values.EmplaceBack("1");
	values.EmplaceBack("2");
	values.EmplaceBack("3");
	values.EmplaceBack("4");
	values.EmplaceBack("5");

	for (std::string value : values)
	{
		std::cout << value << "\n";
	}

	for (Vector<std::string>::Iterator it = values.begin(); it != values.end(); ++it)
	{
		std::cout << *it << "\n";
	}*/



	return 0;
}