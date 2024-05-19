#include <iostream>
#include "user.h"
#include "myString.h"
#include <fstream>

using namespace std;

void registerUser();
void login();
int main() {
	char command[10];
	std::cin.getline(command, 10 , ' ');
	if (!strcmp(command, "register"))
	{
		registerUser();
	}
	else if(strcmp(command, "login"))
	{
		login();
	}
	return 0;
}
void registerUser(){
	MyString username;
	MyString password;
	cin >> username >> password;
	try
	{
		User newUser(username, password);
		const char* newUserName = newUser.getName();
		const char* newUserPass = newUser.getPass();
		const char* newUserId = newUser.getId();
		ofstream of;
		of.open("users.txt", ios::out | ios::app);
		if (!of.is_open()) {
			throw exception("File cannot open");
		}
		of.write(newUserName, strlen(newUserName));
		of.write(" ", 1);
		of.write(newUserPass, strlen(newUserPass));
		of.write(" ", 1);
		of.write(newUserId, strlen(newUserId));
		of.write("\n", 1);
		newUser.print();
		of.close();
	}
	catch (const std::exception&e)
	{
		std::cerr << e.what();
	}

}
void login() {}