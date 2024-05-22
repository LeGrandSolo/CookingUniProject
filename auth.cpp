#include "auth.h"
#include <fstream>
#include <picosha2.h>
#include "recepie.h"
#include "user.h"
#include <cstring>

using namespace std;


void Auth::changeRecepie()
{
	MyString requestedName;
	cin >> requestedName;
	ifstream fin;
	fin.open("recepies.txt", ios::in);
	if (!fin.is_open())
	{
		throw exception("File couldn't open for reading");
	}
	while (fin)
	{
		MyString userId;
		int objPosition = fin.tellg();
		fin >> userId;
		if (strcmp(userId.getStr(), id.getStr()))
		{
			cout << "entryToChange:name/stepsDescription/prepareTime/products/imageUrl" << endl;
			MyString entry;
			MyString recepieId;
			MyString recepieName;
			fin >> userId >> recepieName;

			if (recepieName.equalsInsensitive(requestedName))
			{
				char* stepsDesc = new char[10000];
				fin.getline(stepsDesc, 10000, '#');

				unsigned prepareTime;
				time_t date;
				unsigned ratingSum;
				unsigned ratingLength;
				fin >> prepareTime >> date >> ratingSum >> ratingLength;
				bool types[8];
				for (size_t i = 0; i < 8; i++)
				{
					char temp;
					fin >> temp;
					int diff = temp - '0';
					types[i] = diff;
				}
				size_t prodLength;
				fin >> prodLength;
				MyVector<Product> products;
				for (size_t i = 0; i < prodLength; i++)
				{
					MyString name;
					MyString unit;
					double quantity;
					unsigned category;
					fin >> name >> unit >> quantity >> category;
					Product prodEntry(name, unit, category, quantity);
					products.add(prodEntry);
				}
				size_t imgLength;
				fin >> imgLength;
				MyVector<MyString>imageUrls;
				for (size_t i = 0; i < imgLength; i++)
				{
					MyString url;
					fin >> url;
					imageUrls.add(url);
				}
				if (entry.equalsInsensitive(std::move(MyString("name"))))
				{
					cout << "New name: " << endl;
					MyString name;
					cin >> name;
					recepieName = name;
				}
				if (entry.equalsInsensitive(std::move(MyString("stepsDescription"))))
				{
					cout << "New description: " << endl;
					char* newStepsDesc = new char[10000];
					cin.getline(newStepsDesc, 10000);
					delete[]stepsDesc;
					stepsDesc = newStepsDesc;
				}
				if (entry.equalsInsensitive(std::move(MyString("prepareTime"))))
				{
					cout << "New prepare time: " << endl;
					double newPrepareTime;
					cin >> newPrepareTime;
					prepareTime = newPrepareTime;
				}
				Recepie updated(recepieName, prepareTime);
				if (entry.equalsInsensitive(std::move(MyString("products"))))
				{
					cout << products << endl;
					cout << "'add' name unit category quantity\\'remove' index(starting from 1)" << endl;
					MyString command;
					cin >> command;
					if (command.equalsInsensitive(std::move(MyString("add"))))
					{
						MyString name;
						MyString unit;
						double quantity;
						MyString category;
						cin >> name >> unit >> quantity >> category;
						size_t categoryIndex = updated.categoryStrToIndex(category.getStr());
						Product prodEntry(name, unit, categoryIndex, quantity);
						products.add(prodEntry);
					}
					else if (command.equalsInsensitive(std::move(MyString("remove"))))
					{
						size_t index;
						cin >> index;
						products.remove(index);
					}
				}
				if (entry.equalsInsensitive(std::move(MyString("imageUrl"))))
				{
					cout << products << endl;
					cout << "'add' url\\'remove' index(starting from 1)" << endl;
					MyString command;
					cin >> command;
					if (command.equalsInsensitive(std::move(MyString("add"))))
					{
						MyString url;
						cin >> url;
						imageUrls.add(url);
					}
					else if (command.equalsInsensitive(std::move(MyString("remove"))))
					{
						size_t index;
						cin >> index;
						imageUrls.remove(index);
					}
				}

				updated.stepsDesc = std::move(MyString(stepsDesc));
				updated.ratesLength = ratingSum;
				updated.ratingSumed = ratingLength;
				xg::Guid oldId(recepieId.getStr());
				updated.id = oldId;
				updated.productList = products;
				updated.imagesUrl = imageUrls;
				for (size_t i = 0; i < 8; i++)
				{
					updated.typesOfFood[i] = types[i];
				}
				fWriteRecepie(updated,"recepies.txt");
				int finalPosition = fin.tellg();
				//todo remove old
				delete[]stepsDesc;
				break;
			}
		}
	}
}

//add_recepie title prepareTime desc
//product name unit category quantity
void Auth::addRecepie()
{
	if (id.getStr() != nullptr)
	{
		MyString title;
		unsigned prepareTime;
		cin >> title >> prepareTime;
		Recepie newRecepie(title, prepareTime);
		cout << "Description: " << endl;
		cin.ignore(1);
		char desc[10000];
		cin.getline(desc, 10000);
		if (strchr(desc, '#'))
		{
			throw exception("Invalid character: #");
		}
		newRecepie.stepsDesc = std::move(MyString(desc));
		cout << "Enter: 'product' name unit category quantity || 'imageUrl' url" << endl;
		MyString command;
		cin >> command;

		while (!strcmp(command.getStr(), "product") || !strcmp(command.getStr(), "imageUrl"))
		{
			while (!strcmp(command.getStr(), "product"))
			{
				MyString name;
				MyString unit;
				MyString categoryStr;
				MyString clear;
				double quantity;
				cin >> name >> unit >> categoryStr >> quantity >> clear;
				/*Other ;Vegetables; Fruits; Grains; Meat; Seafood; Dairy; Eggs*/
				size_t categoryIndex = newRecepie.categoryStrToIndex(categoryStr.getStr());
				newRecepie.addProduct(name, unit, categoryIndex, quantity);
				newRecepie.setCategory(categoryIndex);
				cin >> command;
			}
			while (!strcmp(command.getStr(), "imageUrl"))
			{
				MyString imgUrl;
				cin >> imgUrl;
				newRecepie.addImgUrl(imgUrl.getStr());
				cin >> command;
			}
		}
		fWriteRecepie(newRecepie,"recepies.txt");
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
			const char* newUserId = newUser.getId().str().c_str();
			size_t newUserNameLength = strlen(newUser.getName());
			size_t newUserPassLength = strlen(newUser.getPass());
			size_t newUserIdLength = strlen(newUserId);
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

void Auth::fWriteRecepie(Recepie& newRecepie, const char* filename) const
{
	ofstream fout;
	fout.open(filename, ios::out | ios::app);
	fout << this->id << ' ' << newRecepie.id << ' ' << newRecepie.title << ' ' << newRecepie.stepsDesc << "# " << newRecepie.prepareTime << ' ' << newRecepie.date << ' ' << newRecepie.ratingSumed << ' ' << newRecepie.ratesLength << ' ';
	for (size_t i = 0; i < 8; i++)
	{
		fout << newRecepie.typesOfFood[i];
		fout << ' ';
	}
	fout << newRecepie.productList << newRecepie.imagesUrl << '\n';
	fout.close();
}

