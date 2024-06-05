#ifndef AUTH_H
#define AUTH_H
#include "myString.h"
#include <crossguid/guid.hpp>
#include "recepie.h"

class Auth {
public:
	Auth();
	~Auth();
	Auth(const Auth&) = delete;
	Auth& operator=(const Auth&) = delete;

	Auth( Auth&&) = delete;
	Auth& operator=( Auth&&) = delete;

	void viewRecepie();
	void searchByName();
	void rate();
	bool deleteRecepie();
	void changeRecepie();
	void addRecepie();
	void fetchRecepies();
	const char* getId()const;
	void registerUser();
	void login();
	void logoff();
	void topRecepies();
	void myRecepies();
	void ratedRecepies();
	void setFName(const char* name);
private:
	MyString id;
	MyString fName;
	MyVector<Recepie*> allRecepies;
	MyVector<Recepie*> userRecepies;
	Recepie& getDetailedInfoForRecepie(Recepie& recepieObj, stringstream& strStream);

	void selectUserRecepies();
};
#endif // AUTH_H
