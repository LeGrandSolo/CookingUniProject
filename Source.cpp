#include "user.h"
#include "myString.h"
#include <picosha2.h>
#include <limits>
#include "auth.h"
#include <fstream>
#include  "myVector.h"

using namespace std;

int main() {
	MyVector<MyString> vec;
	Auth state;
	cout << "Commands:" << endl;
	cout << "'login' name pass" << endl << "'register' name pass" << endl << "'search' recepieName" << "'view' recepieId" << "'top' numberOfRecepies" << endl;
	cout << "Commands with needed user loged in:" << endl;
	cout << "'logoff'" << endl << "'add_recepie' name prepareTimeInMin" << endl << "'change_recepie' recepieName" << "'delete' recepieID" << "'rate' recepieId" << "'my_recepies'" << "'rated_recepies'" << endl;
	cout << "WARNING: SPACES MATTER ONLY SPACES IN PRODUCT DESCRIPTION ARE ALLOWED! " << endl << endl;
	MyString command;
	cin >> command;
	while (!command.equalsInsensitive("exit"))
	{
		try
		{
			if (command.equalsInsensitive("register") && state.getId() == nullptr)
			{
				state.registerUser();
				cout << state.getId() << std::endl;
			}
			else if (command.equalsInsensitive("login"))
			{
				state.login();
				cout << state.getId() << std::endl;
			}
			else if (command.equalsInsensitive("logoff"))
			{
				state.logoff();
			}
			else if (command.equalsInsensitive("add_recepie"))
			{
				state.addRecepie();
			}
			else if (command.equalsInsensitive("change_recepie")) {
				state.changeRecepie();
			}
			else if (command.equalsInsensitive("delete")) {
				state.deleteRecepie();
			}
			else if (command.equalsInsensitive("view")) {
				state.viewRecepie();
			}
			else if (command.equalsInsensitive("search")) {
				state.searchByName();
			}
			else if (command.equalsInsensitive("rate")) {
				state.rate();
			}
			else if (command.equalsInsensitive("top")) {
				state.topRecepies();
			}
			else if (command.equalsInsensitive("my_recepies")) {
				state.myRecepies();
			}
			else if (command.equalsInsensitive("rated_recepies")) {
				state.ratedRecepies();
			}
		}
		catch (const std::exception&e)
		{
			std::cerr << e.what() << endl;
		}
		cin >> command;
	}
	return 0;
}