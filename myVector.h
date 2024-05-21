#ifndef MY_VECTOR
#define MY_VECTOR
template<typename T>
class MyVector {
public:
	MyVector();
	~MyVector();
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);

	size_t getSize()const;

	void add(const T& elem);
	void ensure();

private:
	void copy(const MyVector& other);
	T* arr;
	size_t capacity;
	size_t size;
};
#endif // !MY_VECTOR

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
		copy(other)
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
inline void MyVector<T>::ensure()
{
	if (size + 1>= capacity)
	{
		capacity *= 2;
		temp = new T[capacity];
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
		arr[i] = other.arr[i]
	}
	size = other.size;
	capacity = other.capacity;
}
