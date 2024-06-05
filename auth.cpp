#include "auth.h"
#include <fstream>
#include <picosha2.h>
#include "recepie.h"
#include "user.h"
#include <cstring>
#include <string.h>

using namespace std;


Auth::Auth()
{
	fName = "recepies.txt";
}

void Auth::changeRecepie()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	fetchRecepies();
	MyString requestedName;
	cin >> requestedName;
	ofstream fout;
	fout.open("temp.txt", ios::out);
	if (!fout.is_open())
	{
		throw exception("File couldn't open for writing");
	}
	fout.seekp(0, fout.beg);
	bool succ = false;
	bool hasChanged = false;
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		succ = true;
		std::string usrId = allRecepies[i]->userId.str();
		if (!hasChanged)
		{
			if (id == usrId.c_str() && allRecepies[i]->title == requestedName)
			{
				cout << "entryToChange:name/stepsDescription/prepareTime/products/imageUrl" << endl;
				MyString entry;
				cin >> entry;
				if (entry.equalsInsensitive(std::move(MyString("name"))))
				{
					cout << "New name: " << endl;
					MyString name;
					cin >> name;
					allRecepies[i]->title = name;
				}
				if (entry.equalsInsensitive(std::move(MyString("stepsDescription"))))
				{
					cout << "New description: " << endl;
					char* newStepsDesc = new char[10000];
					cin.getline(newStepsDesc, 10000);
					allRecepies[i]->stepsDesc = newStepsDesc;
				}
				if (entry.equalsInsensitive(std::move(MyString("prepareTime"))))
				{
					cout << "New prepare time: " << endl;
					double newPrepareTime;
					cin >> newPrepareTime;
					allRecepies[i]->prepareTime = newPrepareTime;
				}
				if (entry.equalsInsensitive("products"))
				{
					cout << "'add' name unit category quantity\\'remove' index(starting from 1)" << endl;
					MyString command;
					cin >> command;
					if (command.equalsInsensitive(std::move(MyString("add"))))
					{
						MyString name;
						MyString unit;
						double quantity;
						MyString category;
						cin >> name >> unit >> category >> quantity;
						size_t categoryIndex = allRecepies[i]->categoryStrToIndex(category);
						Product prodEntry(name, unit, categoryIndex, quantity);
						allRecepies[i]->productList.add(prodEntry);
					}
					else if (command.equalsInsensitive("remove"))
					{
						size_t index;
						cin >> index;
						allRecepies[i]->productList.remove(index);
					}
				}
				if (entry.equalsInsensitive("imageUrl"))
				{
					cout << "'add' url\\'remove' index(starting from 1)" << endl;
					MyString command;
					cin >> command;
					if (command.equalsInsensitive("add"))
					{
						MyString url;
						cin >> url;
						allRecepies[i]->imagesUrl.add(url);
					}
					else if (command.equalsInsensitive("remove"))
					{
						size_t index;
						cin >> index;
						allRecepies[i]->imagesUrl.remove(index);
					}
				}
				hasChanged = true;
				cout << "Done! " << endl;
			}
		}
		allRecepies[i]->fWriteRecepie("temp.txt");
	}
	if (!hasChanged)
	{
		std::cout << "No such recepie found of this user!" << std::endl;
	}
	fout.close();
	if (succ)
	{
		std::remove(fName.getStr());
		bool succRen = std::rename("temp.txt", fName.getStr());
	}
}

////add_recepie title prepareTime desc
////product name unit category quantity

void Auth::addRecepie()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	if (id.getStr() != nullptr)
	{
		MyString title;
		unsigned prepareTime;
		cin >> title >> prepareTime;
		Recepie* recepieObj = new Recepie(title, prepareTime);
		cout << "Description: " << endl;
		cin.ignore(1);
		char desc[10000];
		cin.getline(desc, 10000);
		if (strchr(desc, '#'))
		{
			throw exception("Invalid character: #");
		}
		recepieObj->stepsDesc = desc;
		cout << "Enter: 'product' name unit category quantity || 'imageUrl' url" << endl;
		MyString command;
		cin >> command;

		while (command.equalsInsensitive("product") || command.equalsInsensitive("imageUrl"))
		{
			while (command.equalsInsensitive("product"))
			{
				MyString name;
				MyString unit;
				MyString categoryStr;
				double quantity;
				cin >> name >> unit >> categoryStr >> quantity;
				/*Other ;Vegetables; Fruits; Grains; Meat; Seafood; Dairy; Eggs*/
				size_t categoryIndex = recepieObj->categoryStrToIndex(categoryStr);
				recepieObj->addProduct(name, unit, categoryIndex, quantity);
				recepieObj->setCategory(categoryIndex);
				cin >> command;
			}
			while (command.equalsInsensitive("imageUrl"))
			{
				MyString imgUrl;
				cin >> imgUrl;
				recepieObj->addImgUrl(imgUrl.getStr());
				cin >> command;
			}
		}
		xg::Guid g(id.getStr());
		recepieObj->userId = g;
		recepieObj->fWriteRecepie(fName.getStr());
		allRecepies.add(recepieObj);
		userRecepies.add(recepieObj);
		std::cout << "Recepie added!" << std::endl;
	}
	else {
		cout << "Not logged in!" << endl;
	}
}
void Auth::fetchRecepies()
{
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		delete allRecepies[i];
	}
	allRecepies.clear();
	userRecepies.clear();
	ifstream fin;
	fin.open(fName.getStr(), ios::in);
	if (!fin.is_open())
	{
		throw exception("File couldn't open for reading");
	}
	fin.seekg(0, fin.beg);
	MyString line;
	stringstream strStream;
	while (line.getline(fin, '\n'))
	{

		const char* str = line.getStr();
		unsigned length = line.length();
		strStream.write(line.getStr(), line.length());
		MyString userId;
		MyString recepieId;
		MyString recepieName;
		strStream >> userId >> recepieId >> recepieName;
		Recepie elem(recepieName, 0);
		xg::Guid oldId(recepieId.getStr());
		elem.id = oldId;
		xg::Guid g(userId.getStr());
		elem.userId = g;
		getDetailedInfoForRecepie(elem, strStream);
		Recepie* cpy = new Recepie(elem);
		allRecepies.add(cpy);
		strStream.clear();
		strStream.str("");
	}
	selectUserRecepies();
	fin.close();
}

bool Auth::deleteRecepie()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return false;
	}
	fetchRecepies();
	MyString requestedID;
	cin >> requestedID;
	ofstream fout;
	fout.open("temp.txt", ios::out);
	if (!fout.is_open())
	{
		throw exception("File couldn't open for writing");
	}
	fout.seekp(0, fout.beg);
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		std::string usrId = allRecepies[i]->userId.str();
		std::string recepieID = allRecepies[i]->id;
		if (!(usrId.c_str() == id && requestedID == recepieID.c_str()))
		{
			allRecepies[i]->fWriteRecepie("temp.txt");
		}
		else {
			std::cout << "Done!" << std::endl;
		}
	}
	fout.close();
	bool succrem = std::remove(fName.getStr());
	bool succ = std::rename("temp.txt", fName.getStr());
	return true;
}

void Auth::viewRecepie()
{
	MyString requested;
	cin >> requested;
	fetchRecepies();
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		std::string recId = allRecepies[i]->id.str();
		if ((requested == recId.c_str()))
		{
			allRecepies[i]->print();
			break;
		}
	}
}

void Auth::searchByName()
{
	MyString requested;
	cin >> requested;
	fetchRecepies();
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		if (strstr(allRecepies[i]->title.getStr(), requested.getStr()))
		{
			cout << "Title: " << allRecepies[i]->title << " ID: " << allRecepies[i]->id << endl;
		}
	}
}

void Auth::rate()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	ofstream fout;
	fout.open("temp.txt", ios::out);
	if (!fout.is_open())
	{
		throw exception("File couldn't open for writing");
	}
	fout.seekp(0, fout.beg);
	MyString requested;
	unsigned rate;
	MyString rateId;
	cin >> requested >> rate;
	if (rate < 1 || rate>5)
	{
		throw std::exception("Invalid range of rate!");
	}
	fetchRecepies();
	bool hasRated = false;
	bool hasCurrRated = false;
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		hasCurrRated = false;
		if (!hasRated)
		{
			std::string recId = allRecepies[i]->id.str();
			for (size_t j = 0; j < allRecepies[i]->usersRated.getSize(); j++)
			{
				if (allRecepies[i]->usersRated[j] == id)
				{
					hasCurrRated = true;
					break;
				}
			}
			if ((recId.c_str() == requested) && !hasCurrRated)
			{
				std::string fetchedId = allRecepies[i]->id.str();
				MyString* recepieId = new MyString(fetchedId.c_str());
				allRecepies[i]->usersRated.add(id);
				allRecepies[i]->ratingSumed += rate;
				allRecepies[i]->ratesLength++;
				hasRated = true;
				rateId = recId.c_str();
				cout << "Done" << endl;
			}
		}
		allRecepies[i]->fWriteRecepie("temp.txt");
	}
	fout.close();
	bool succrem = std::remove(fName.getStr());
	bool succ = std::rename("temp.txt", fName.getStr());
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
		User newUser(username, password);
		const char* newUserName = newUser.getName();
		const char* newUserPass = newUser.getPass();
		std::string idStr = newUser.getId().str();
		const char* newUserId = idStr.c_str();
		ofstream fout;
		fout.open("users.txt", ios::out | ios::app);
		if (!fout.is_open()) {
			throw exception("File cannot open!");
		}
		fout << newUserName << ' ' << newUserPass << ' ' << newUserId << '\n';
		id = newUserId;
		selectUserRecepies();
		newUser.print();
		fout.close();
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
		fin.open("users.txt", ios::in);
		if (!fin.is_open())
		{
			throw exception("File cannot open!");
		}
		fin.seekg(0, fin.beg);
		cin >> username >> password;
		while (fin.good())
		{

			MyString fInputUsername;
			MyString fInputPass;
			MyString fInputId;
			fin >> fInputUsername >> fInputPass >> fInputId;
			if (username == fInputUsername && fInputPass == picosha2::hash256_hex_string(std::string(password.getStr())).c_str())
			{
				id = fInputId;
				selectUserRecepies();
				return;
			}
			id = nullptr;
		}
		id = nullptr;
		cout << "Username or password incorrect!" << endl;
	}
	else {
		cout << "Already logged in!" << endl;
	}
}

void Auth::logoff()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		delete allRecepies[i];
	}
	allRecepies.clear();
	userRecepies.clear();
	id = nullptr;
	cout << "Done!" << endl;
}

void Auth::topRecepies()
{
	unsigned num;
	cin >> num;
	if (num > 1000)
	{
		num = 1000;
	}

	Recepie* output = new Recepie[num];
	fetchRecepies();
	if (num > allRecepies.getSize())
	{
		num = allRecepies.getSize();
	}
	MyString criteria;
	cout << "<popular|rated|recent>" << endl;
	cin >> criteria;
	for (size_t i = 0; i < allRecepies.getSize() - 1; i++)
	{
		if (i >= num)
		{
			break;
		}
		size_t maxIndex = i;
		if (criteria.equalsInsensitive("popular"))
		{
			for (size_t j = i + 1; j < allRecepies.getSize(); j++)
			{
				if (allRecepies[j]->ratesLength > allRecepies[maxIndex]->ratesLength)
				{
					maxIndex = j;
				}
			}
		}
		else if (criteria.equalsInsensitive("rated")) {
			for (size_t j = i + 1; j < allRecepies.getSize(); j++)
			{
				if (allRecepies[j]->ratesLength != 0)
				{
					if (allRecepies[maxIndex]->ratesLength == 0)
					{
						maxIndex = j;
						continue;
					}
					else if (allRecepies[j]->ratingSumed / allRecepies[j]->ratesLength > allRecepies[maxIndex]->ratingSumed / allRecepies[maxIndex]->ratesLength)
					{
						maxIndex = j;
					}
				}
			}
		}
		else if (criteria.equalsInsensitive("recent")) {
			for (size_t j = i + 1; j < allRecepies.getSize(); j++)
			{
				if (allRecepies[j]->date > allRecepies[maxIndex]->date)
				{
					maxIndex = j;
				}
			}
		}
		Recepie* temp = allRecepies[i];
		allRecepies[i] = allRecepies[maxIndex];
		allRecepies[maxIndex] = temp;
	}
	for (size_t i = 0; i < num; i++)
	{
		cout << "Title: " << allRecepies[i]->title << " ID: " << allRecepies[i]->id;
		if (allRecepies[i]->ratesLength)
		{
			double rating = (double)allRecepies[i]->ratingSumed / (double)allRecepies[i]->ratesLength;
			cout << " Rating: " << rating << " People rated: "<< allRecepies[i]->ratesLength;
		}
		cout << endl;
	}
}

void Auth::myRecepies()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	fetchRecepies();
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		std::string recId = allRecepies[i]->userId.str();
		if (id == recId.c_str())
		{
			cout << "Title: " << allRecepies[i]->title << " ID: " << allRecepies[i]->id;
			if (allRecepies[i]->ratesLength)
			{
				double rating = (double)allRecepies[i]->ratingSumed / (double)allRecepies[i]->ratesLength;
				cout << " Rating: " << rating ;
			}
			cout << endl;
		}
	}
}

void Auth::ratedRecepies()
{
	if (!id.getStr())
	{
		throw std::exception("Not logged in!");
		return;
	}
	fetchRecepies();
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		for (size_t j = 0; j < allRecepies[i]->usersRated.getSize(); j++)
		{
			if (allRecepies[i]->usersRated[j] == id)
			{
				cout << "Title: " << allRecepies[i]->title << " ID: " << allRecepies[i]->id;
				if (allRecepies[i]->ratesLength)
				{
					double rating = (double)allRecepies[i]->ratingSumed / (double)allRecepies[i]->ratesLength;
					cout << " Rating: " << rating;
				}
				cout << endl;
				break;
			}
		}
	}
}

void Auth::setFName(const char* name)
{
	fName = name;
}


Recepie& Auth::getDetailedInfoForRecepie(Recepie& recepieObj, stringstream& strStream)
{
	char* stepsDesc = new char[10000];
	strStream.getline(stepsDesc, 10000, '#');

	unsigned prepareTime;
	time_t date;
	unsigned ratingSum;
	unsigned ratingLength;
	strStream >> prepareTime >> date >> ratingSum >> ratingLength;
	bool types[8];
	for (size_t i = 0; i < 8; i++)
	{
		char temp;
		strStream >> temp;
		int diff = temp - '0';
		types[i] = diff;
	}
	size_t prodLength = 0;
	strStream >> prodLength;
	MyVector<Product> products;
	for (size_t i = 0; i < prodLength; i++)
	{
		MyString name;
		MyString unit;
		double quantity;
		unsigned category;
		strStream >> name >> unit >> quantity >> category;
		Product prodEntry(name, unit, category, quantity);
		products.add(prodEntry);
	}
	size_t imgLength = 0;
	strStream >> imgLength;
	MyVector<MyString>imageUrls;
	for (size_t i = 0; i < imgLength; i++)
	{
		MyString url;
		strStream >> url;
		imageUrls.add(url);
	}
	size_t ratesLength = 0;
	strStream >> ratesLength;
	MyVector<MyString>usersRated;
	for (size_t i = 0; i < ratesLength; i++)
	{
		MyString usr;
		strStream >> usr;
		usersRated.add(usr);
	}
	recepieObj.prepareTime = prepareTime;
	recepieObj.stepsDesc = std::move(MyString(stepsDesc));
	recepieObj.ratesLength = ratingLength;
	recepieObj.ratingSumed = ratingSum;
	recepieObj.productList = products;
	recepieObj.imagesUrl = imageUrls;
	recepieObj.date = date;
	recepieObj.usersRated = usersRated;
	for (size_t i = 0; i < 8; i++)
	{
		recepieObj.typesOfFood[i] = types[i];
	}
	delete[]stepsDesc;
	return recepieObj;
}

Auth::~Auth()
{
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		delete allRecepies[i];
	}
}

void Auth::selectUserRecepies()
{
	for (size_t i = 0; i < allRecepies.getSize(); i++)
	{
		std::string userId = allRecepies[i]->userId.str();
		if (userId.c_str() == id)
		{
			userRecepies.add(allRecepies[i]);
		}
	}
}
