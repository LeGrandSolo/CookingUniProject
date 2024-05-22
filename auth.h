#ifndef AUTH_H
#define AUTH_H
#include "myString.h"
#include <crossguid/guid.hpp>
#include "recepie.h"

class Auth {
public:
	void changeRecepie();
	void addRecepie();
	const char* getId()const;
	void registerUser();
	void login();
private:
	void fWriteRecepie(Recepie& newRecepie, const char* filename)const;
	MyString id;
};
#endif // AUTH_H
