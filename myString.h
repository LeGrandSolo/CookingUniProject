#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
class MyString {
public:
	MyString();
	MyString(const char* _str);
	MyString(size_t length);
	~MyString();
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString& operator=(const char* _str);

	friend std::istream& operator>>(std::istream& istream,MyString& obj);
	
	MyString(MyString&& other);
	MyString& operator=(MyString&& other);

	bool isBetween(char arrOfPairsOfEndAndStartChars[][2],size_t length)const;
	size_t length()const;
	const char* getStr()const;

private:
	void enlargeIfNeeded(size_t catSize);
	void copy(char*& dest, const char* src);
	size_t capacity;
	size_t size;
	char* str;
};

#endif // !MYSTRING_H