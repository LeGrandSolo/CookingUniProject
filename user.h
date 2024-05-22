#ifndef USER_H
#define USER_H
#include <crossguid/guid.hpp>
#include "myString.h"

class User {
public:
	User(const MyString& _name, const MyString& _pass);

	const char* getName()const;
	const char* getPass()const;
	xg::Guid getId()const;

	void print()const;
private:
	bool validateUsername(const MyString& username);
	bool validatePass(const MyString& pass);
	MyString name;
	MyString pass;
	xg::Guid id;
};
#endif // !USER_H
