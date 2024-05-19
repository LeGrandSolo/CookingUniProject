#include "user.h"
#include <picosha2.h>
User::User(const MyString& _name, const MyString& _pass)
{
	if (!validateUsername(_name)) {
		throw std::exception("Invalid username");
	}
	if (!validatePass(_pass))
	{
		throw std::exception("Invalid password");
	}
	name = std::move(_name);
	pass = picosha2::hash256_hex_string(std::string(_pass.getStr())).c_str();
	id = xg::newGuid();
}

const char* User::getName() const
{
	return name.getStr();
}

const char* User::getPass() const
{
	return pass.getStr();
}

const char* User::getId() const
{
	return id.str().c_str();
}

void User::print() const
{
	std::cout << name.getStr() << ' ' << pass.getStr() << std::endl;
}

bool User::validateUsername(const MyString& username)
{
	char fnArr[6][2] = { {'a','z'},{'A','Z'},{'1','9'},{'-','-'},{'_','_'} ,{'.','.'} };
	return username.isBetween(fnArr, 6);
}

bool User::validatePass(const MyString& pass)
{
	char fnArr[3][2] = { {'a','z'},{'A','Z'},{'1','9'}};
	return pass.isBetween(fnArr, 3) && (pass.length()>=8);
}



