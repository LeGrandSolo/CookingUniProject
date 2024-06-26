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
	size = strlen(_str);
	capacity = size + 1;
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
		delete[]str;
		copy(str, other.str);
		size = other.size;
		capacity = other.capacity;
	}
	return *this;
}

MyString& MyString::operator=(const char* _str)
{
	// copy() deletes if its nullptr
	delete[]str;
	if (_str == nullptr)
	{
		str = nullptr;
		size = 0;
		capacity = 0;
		return *this;
	}
	copy(str, _str);
	size = strlen(_str);
	capacity = size + 1;
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

bool MyString::equalsInsensitive(const MyString& other) const
{
	if (other.size != size)
	{
		return false;
	}
	for (size_t i = 0; i < size; i++)
	{
		char own = 'a';
		char otherChr = 'b';
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			own = (str[i] - 'A') + 'a';
		}
		else {
			own = str[i];
		}
		if (other.str[i] >= 'A' && other.str[i] <= 'Z')
		{
			otherChr = (str[i] - 'A') + 'a';
		}
		else
		{
			otherChr = other.str[i];
		}
		if (otherChr != own) {
			return false;
		}
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
			capacity = capacity + catSize + size + 1;
			str = new char[capacity];
			strcpy_s(str, capacity, "\0");
		}
		else {
			capacity += catSize + size + 1;
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
	do
	{
		// 1 for \0
		char c1[2];
		istream >> c1;
		obj.append(c1);
	} while (istream.peek() != '\n' && istream.peek() != ' ');
	istream.ignore(1);
	return istream;
}

std::ostream& operator<<(std::ostream& ostrm, const MyString& obj)
{
	ostrm << obj.str;
	return ostrm;
}

bool MyString::operator==(const MyString& other)
{
	if (!str)
	{
		return false;
	}
	if (!other.str)
	{
		return false;
	}
	return !strcmp(str, other.str);
}

bool MyString::operator==(const char* other)
{
	if (!str)
	{
		return false;
	}
	if (!other)
	{
		return false;
	}
	return !strcmp(str, other);
}

bool MyString::getline(std::istream& istream, char delim = '\n')
{
	if (istream.eof())
	{
		return false;
	}
	delete[]str;
	str = nullptr;
	size = 0;
	capacity = 0;
	while (istream.peek() != delim && istream.good())
	{
		// 1 for \0
		char c1[100];
		istream.get(c1, 100, delim);
		append(c1);
	}
	if (str == nullptr)
	{
		return false;
	}
	istream.ignore(1);
	return true;
}
