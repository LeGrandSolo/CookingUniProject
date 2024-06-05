#include "recepie.h"
#include <fstream>

Recepie::Recepie():Recepie(nullptr, 0)
{
}

Recepie::Recepie(const MyString _title, unsigned prepareTime)
{
	title = _title;
	this->prepareTime = prepareTime;
	ratingSumed = 0;
	ratesLength = 0;
	date = time(0);
	id = xg::newGuid();
}

void Recepie::addProduct(const MyString& name, const MyString& unit, unsigned category, double quantity)
{
	Product newProd(name, unit, category,quantity);
	productList.add(newProd);
}

void Recepie::addImgUrl(const MyString& url)
{
	MyString imgUrl = url;
	imagesUrl.add(imgUrl);
}

//void Recepie::setStepsDesc(const MyString& _stepsDesc)
//{
//	stepsDesc = _stepsDesc;
//}

void Recepie::setCategory(size_t index)
{
	if (index<8)
	{
		typesOfFood[index] = true;
	}
}

void Recepie::fWriteRecepie(const char* filename) const
{
	ofstream fout;
	fout.open(filename, ios::out | ios::app);
	fout << userId << ' ' << id << ' ' << title << ' ' << stepsDesc << "# " << prepareTime << ' ' << date << ' ' << ratingSumed << ' ' << ratesLength << ' ';
	for (size_t i = 0; i < 8; i++)
	{
		fout << typesOfFood[i];
		fout << ' ';
	}
	fout << productList << imagesUrl << usersRated<<'\n';
	fout.close();
}

void Recepie::print()
{
	char buffer[1024];
	cout << "Title: " << title << endl << " Prepare time: " << prepareTime << endl << " Product list: ";
	cout<< productList << endl << " Description: " << stepsDesc << endl << " Image urls: " << imagesUrl << endl;
	if (ratesLength)
	{
		double rating = (double)ratingSumed / (double)ratesLength;
		cout << " Rating: " << rating << endl;
	}
	ctime_s(buffer, 1024, &date);
	cout<< " Date: " << buffer << endl;
}

bool Recepie::operator==(const Recepie& other)
{
	return id == other.id;
}


size_t Recepie::categoryStrToIndex(const MyString& str)
{
	size_t categoryIndex = 0;
	if (str.equalsInsensitive("vegetables"))
	{
		categoryIndex = 1;
	}
	else if (str.equalsInsensitive("fruits")) {
		categoryIndex = 2;
	}
	else if (str.equalsInsensitive("grains")) {
		categoryIndex = 2;
	}
	else if (str.equalsInsensitive("meat")) {
		categoryIndex = 3;
	}
	else if (str.equalsInsensitive("seafood")) {
		categoryIndex = 4;
	}
	else if (str.equalsInsensitive("dairy")) {
		categoryIndex = 5;
	}
	else if (str.equalsInsensitive("eggs")) {
		categoryIndex = 6;
	}
	else {
		categoryIndex = 7;
	}
	return categoryIndex;
}
