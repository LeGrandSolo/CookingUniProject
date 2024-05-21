#include "auth.h"
#include <fstream>
#include <picosha2.h>
#include <fstream>

using namespace std;


void Auth::addRecepie()
{
	if (id.getStr() != nullptr)
	{
		MyString title;
		unsigned prepareTime;
		cin >> title >> prepareTime;
		Recepie newRecepie(title, prepareTime);
		cout << "Description: " << endl;
		MyString desc;
		cin >> desc;
		newRecepie.setStepsDesc(desc);
		MyString command;
		cin >> command;
		
		while (!strcmp(command.getStr(), "product") || !strcmp(command.getStr(), "imageUrl"))
		{
			while (!strcmp(command.getStr(), "product"))
			{
				MyString name;
				MyString unit;
				MyString categoryStr;
				double quantity;
				cin >> name >> unit >> categoryStr >> quantity;
				/*Other ;Vegetables; Fruits; Grains; Meat; Seafood; Dairy; Eggs*/
				size_t categoryIndex = 0;
				if (!strcmp(categoryStr.getStr(), "vegetables"))
				{
					categoryIndex = 1;
				}
				else if (!strcmp(categoryStr.getStr(), "fruits")) {
					categoryIndex = 2;
				}
				else if (!strcmp(categoryStr.getStr(), "grains")) {
					categoryIndex = 2;
				}
				else if (!strcmp(categoryStr.getStr(), "fruits")) {
					categoryIndex = 3;
				}
				else if (!strcmp(categoryStr.getStr(), "meat")) {
					categoryIndex = 4;
				}
				else if (!strcmp(categoryStr.getStr(), "seafood")) {
					categoryIndex = 5;
				}
				else if (!strcmp(categoryStr.getStr(), "dairy")) {
					categoryIndex = 6;
				}
				else if (!strcmp(categoryStr.getStr(), "eggs")) {
					categoryIndex = 7;
				}
				newRecepie.addProduct(name, unit, categoryIndex, quantity);
				cin >> command;
			}
			while (!strcmp(command.getStr(), "imageUrl"))
			{
				MyString imgUrl;
				cin >> imgUrl;
				newRecepie.addImgUrl(imgUrl.getStr());
			}
		}
		/*const char* fTitle = newRecepie.getTitle();
		const bool* typesOfFood = newRecepie.getTypesOfFood();
		MyString typesOfFoodStr;
		for (size_t i = 0; i < 8; i++)
		{
			typesOfFoodStr.append((typesOfFood[i] - '0'));
		}
		const char* fStepsDesc = newRecepie.getStepsDesc();
		MyVector<Product> productList = newRecepie.getProdList();
		ofstream fout;
		fout.open("recepies.txt",ios::out|ios::app);
		fout << fTitle<< ' ' 
		for (size_t i = 0; i < productList.getSize(); i++)
		{
			
		}*/
		std::cout << "Recepie added!" << std::endl;
	}
	else {
		std::cout << "Not logged in!" << std::endl;
	}
}

const char* Auth::getId() const
{
	return id.getStr();
}

void Auth::registerUser()
{
	if (id.getStr() == nullptr)
	{
		MyString username;
		MyString password;
		cin >> username >> password;
		try
		{
			User newUser(username, password);
			const char* newUserName = newUser.getName();
			const char* newUserPass = newUser.getPass();
			const char* newUserId = newUser.getId();
			size_t newUserNameLength = strlen(newUser.getName());
			size_t newUserPassLength = strlen(newUser.getPass());
			size_t newUserIdLength = strlen(newUser.getId());
			ofstream fout;
			fout.open("users.bin", ios::out | ios::app | ios::binary);
			if (!fout.is_open()) {
				throw exception("File cannot open!");
			}
			fout.write((char*)&newUserNameLength, sizeof(size_t));
			fout.write(newUserName, newUserNameLength);
			fout.write((char*)&newUserPassLength, sizeof(size_t));
			fout.write(newUserPass, newUserPassLength);
			fout.write((char*)&newUserIdLength, sizeof(size_t));
			fout.write(newUserId, newUserIdLength);

			id = newUserId;
			newUser.print();
			fout.close();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Already logged in!";
	}
	
}

void Auth::login()
{
	if (id.getStr() == nullptr)
	{
		MyString username;
		MyString password;
		ifstream fin;
		fin.open("users.bin", ios::in | ios::binary);
		if (!fin.is_open())
		{
			throw exception("File cannot open!");
		}
		fin.seekg(0, fin.beg);
		cin >> username >> password;
		while (fin.good())
		{
			size_t nameLength;
			size_t passLength;
			size_t idLength;
			fin.read((char*)&nameLength, sizeof(nameLength));
			char* fInputUsername = new char[nameLength + 1];
			fin.read(fInputUsername, nameLength);
			fInputUsername[nameLength] = '\0';
			fin.read((char*)&passLength, sizeof(passLength));
			char* fInputPass = new char[passLength + 1];
			fin.read(fInputPass, passLength);
			fInputPass[passLength] = '\0';
			fin.read((char*)&idLength, sizeof(idLength));
			char* fInputId = new char[idLength + 1];
			fin.read(fInputId, idLength);
			fInputId[idLength] = '\0';
			if (!strcmp(username.getStr(), fInputUsername) && !strcmp(picosha2::hash256_hex_string(std::string(password.getStr())).c_str(), fInputPass))
			{
				id = fInputId;
				return;
			}
			id = nullptr;
			delete[]fInputUsername;
			delete[]fInputPass;
			delete[]fInputId;
		}
		id = nullptr;
	}
	else {
		std::cout << "Already logged in!";
	}
	
}
