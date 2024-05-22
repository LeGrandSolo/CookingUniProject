#pragma once
#include <iostream>
using namespace std;
template<typename T>
class MyVector {
public:
	MyVector();
	~MyVector();
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);

	size_t getSize()const;

	void add(const T& elem);
	void remove(size_t index);
	void ensure();

	template<typename U>
	friend ostream& operator<<(ostream& ostrm, const MyVector<U>& vector);

private:
	void copy(const MyVector& other);
	T* arr;
	size_t capacity;
	size_t size;
};

template<typename T>
inline MyVector<T>::MyVector()
{
	arr = nullptr;
	capacity = 0;
	size = 0;
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	delete[]arr;
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& other)
{
	copy(other);
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != & other)
	{
		delete[]arr;
		copy(other);
	}
	return *this;
}

template<typename T>
inline size_t MyVector<T>::getSize()const
{
	return size;
}

template<typename T>
inline void  MyVector<T>::add(const T& elem)
{
	if (arr == nullptr|| capacity == 0)
	{
		arr = new T[5];
		capacity = 5;
		size = 0;
	}
	ensure();
	arr[size] = elem;
	size++;
}

template<typename T>
inline void MyVector<T>::remove(size_t index)
{
	if (index < size)
	{
		for (size_t i = index; i < size-1; i++)
		{
			arr[i] = arr[i + 1];
		}
		size--;
	}
	else {
		cout << " Index too high! " << endl;
	}
}

template<typename T>
inline void MyVector<T>::ensure()
{
	if (size + 1>= capacity)
	{
		capacity *= 2;
		T* temp = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}
		delete[] temp;
	}
}

template<typename T>
inline void MyVector<T>::copy(const MyVector& other)
{
	if (other.arr != nullptr)
	{
		arr = nullptr;
		size = 0;
		capacity = 0;
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
	size = other.size;
	capacity = other.capacity;
}

template<typename U>
ostream& operator<<(ostream& ostrm, const MyVector<U>& vector)
{
	ostrm << vector.size<<' ';
	for (size_t i = 0; i < vector.size; i++)
	{
		ostrm << vector.arr[i]<<' ';
	}
	return ostrm;
}
