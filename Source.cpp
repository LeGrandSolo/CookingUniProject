#include <iostream>
#include "user.h"
#include "myString.h"
#include <fstream>
#include <picosha2.h>
#include <limits>
#include "auth.h"

using namespace std;

int main() {
	Auth state;
	MyString command;
	cin >> command;
	while (strcmp(command.getStr(), "exit"))
	{
		if (!strcmp(command.getStr(), "register") && state.getId() == nullptr)
		{
			state.registerUser();
			cout << state.getId() << std::endl;
		}
		else if (!strcmp(command.getStr(), "login"))
		{
			state.login();
			cout << state.getId()<<std::endl;
		}
		else if(!strcmp(command.getStr(), "add_recepie"))
		{
			state.addRecepie();
		}
		cin >> command;
	}
	return 0;
}