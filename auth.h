#ifndef AUTH_H
#define AUTH_H
#include "myString.h"
#include "user.h"
#include "recepie.h"
#include "myVector.h"

class Auth {
private:
	MyString id;
public:
	void addRecepie();
	const char* getId()const;
	void registerUser();
	void login();
};
#endif // AUTH_H
