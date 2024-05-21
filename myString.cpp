#include "myString.h"
#include <cstring>

MyString::MyString()
{
	str = nullptr;
	size = 0;
	capacity = 0;
}

MyString::MyString(const char* _str)
{
	if (_str == nullptr)
	{
		str = nullptr;
		size = 0;
		capacity = 0;
		return;
	}
	copy(str, _str);
	capacity = strlen(_str);
	size = capacity;
}

MyString::MyString(size_t length)
{
	str = new char[length];
	capacity = length;
	size = 0;
}

MyString::~MyString()
{
	delete[] str;
}

MyString::MyString(const MyString& other)
{
	if (!other.length())
	{
		str = nullptr;
		size = 0;
		capacity = 0;
		return;
	}
	copy(str, other.str);
	size = other.size;
	capacity = other.capacity;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		// copy() deletes if its nullptr
		if (other.str != nullptr)
		{
			delete[]str;
		}
		else {
			str = nullptr;
			size = 0;
			capacity = 0;
			return *this;
		}
		copy(str, other.str);
		size = other.size;
		capacity = other.capacity;
	}
	return *this;
}

MyString& MyString::operator=(const char* _str)
{
	// copy() deletes if its nullptr
	if (_str != nullptr)
	{
		delete[]str;
	}
	else {
		str = nullptr;
		size = 0;
		capacity = 0;
		return *this;
	}
	copy(str, _str);
	capacity = strlen(_str);
	size = capacity;
	return *this;
}

MyString::MyString(MyString&& other)
{
	str = other.str;
	size = other.size;
	capacity = other.capacity;
	other.str = nullptr;
}

MyString& MyString::operator=(MyString&& other)
{
	if (this != &other)
	{
		str = other.str;
		size = other.size;
		capacity = other.capacity;
		other.str = nullptr;
	}
	return *this;
}

bool MyString::isBetween(char arrOfPairsOfEndAndStartChars[][2], size_t length)const
{
	char* ptr = str;
	while (*ptr)
	{
		bool isInRange = false;
		char temp = *ptr;
		for (size_t i = 0; i < length; i++)
		{
			if (temp >= arrOfPairsOfEndAndStartChars[i][0] && temp <= arrOfPairsOfEndAndStartChars[i][1])
			{
				isInRange = true;
				break;
			}
		}
		if (!isInRange)
		{
			return false;
		}
		ptr++;
	}
	return true;
}

size_t MyString::length()const
{
	return strlen(str);
}

const char* MyString::getStr() const
{
	return str;
}

void MyString::append(const char* otherStr)
{
	size_t length = strlen(otherStr);
	enlargeIfNeeded(length);
	strcat_s(str, capacity, otherStr);
	size += length;
}



void MyString::enlargeIfNeeded(size_t catSize)
{
	if (size + catSize >= capacity)
	{
		if (!str || capacity == 0)
		{
			capacity = 5;
			str = new char[capacity];
			strcpy_s(str, 5, "\0");
		}
		else {
			capacity *= 2;
			char* temp = new char[capacity];
			strcpy_s(temp, capacity, str);
			delete[]str;
			str = new char[capacity];
			strcpy_s(str, capacity, temp);
			delete[]temp;
		}
	}
}

void MyString::copy(char*& dest, const char* src)
{
	if (src == nullptr)
	{
		delete[]dest;
		dest = nullptr;
		return;
	}
	size_t length = strlen(src) + 1;
	dest = new char[length];
	strcpy_s(dest, length, src);
}

std::istream& operator>>(std::istream& istream, MyString& obj)
{
	obj = "";
	while (istream.peek() != '\n' && istream.peek()!=' ')
	{
		// 1 for \0
		char c1[2];
		istream.get(c1,2);
		obj.append(c1);
	}
	istream.ignore(1);
	obj.enlargeIfNeeded(1);
	obj.str[obj.size] = '\0';
	obj.size++;
	return istream;
}
