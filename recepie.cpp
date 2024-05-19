#include "recepie.h"

Recepie::Recepie(const char* _title, unsigned _prepareTime, char** _productList, size_t prodListLength, const char* _stepsDesc, char** _imageLinks, size_t imageLinksLength, time_t date):title(_title),stepsDesc(_stepsDesc)
{
	prepareTime = _prepareTime;
	productList = new MyString[prodListLength];
	prodLength = prodListLength;
	for (size_t i = 0; i < prodListLength; i++)
	{
		productList[i] = _productList[i];
	}
	imageLinks = new MyString[imageLinksLength];
	imgLinksLength = imageLinksLength;
	for (size_t i = 0; i < imageLinksLength; i++)
	{
		imageLinks[i] = _imageLinks[i];
	}
	date = time(0);
	ratingSumed = 0;
	ratesLength = 0;
	id = xg::newGuid();
}

Recepie::~Recepie()
{
	delete[] productList;
	delete[] imageLinks;
}

Recepie::Recepie(const Recepie& other):title(other.title), stepsDesc(other.stepsDesc)
{
	copyObj(other);
	id = xg::newGuid();
}

Recepie& Recepie::operator=(const Recepie& other)
{
	if (this != &other)
	{
		title = other.title;
		stepsDesc = other.stepsDesc;
		id = xg::newGuid();
		copyObj(other);
	}
	return *this;
}

Recepie::Recepie(Recepie&& other):title(std::move(other.title)),stepsDesc(std::move(other.stepsDesc))
{
	move(&other);
	id = xg::newGuid();
}

Recepie& Recepie::operator=(Recepie&& other)
{
	if (this != &other)
	{
		title = std::move(other.title);
		stepsDesc = std::move(other.stepsDesc);
		move(&other);
		id = xg::newGuid();
	}
	return *this;
}

void Recepie::copyObj(const Recepie& other)
{
	prepareTime = other.prepareTime;
	prodLength = other.prodLength;
	imgLinksLength = other.imgLinksLength;
	date = time(0);
	productList = new MyString[prodLength];
	for (size_t i = 0; i < prodLength; i++)
	{
		productList[i] = other.productList[i];
	}
	imageLinks = new MyString[imgLinksLength];
	for (size_t i = 0; i < imgLinksLength; i++)
	{
		imageLinks[i] = other.imageLinks[i];
	}
	ratingSumed = other.ratingSumed;
	ratesLength = other.ratesLength;
}

void Recepie::move(Recepie* other)
{
	prepareTime = other->prepareTime;
	prodLength = other->prodLength;
	imgLinksLength = other->imgLinksLength;
	date = time(0);
	productList = other->productList;
	other->productList = nullptr;
	imageLinks = other->imageLinks;
	other->imageLinks = nullptr;
	ratingSumed = other->ratingSumed;
	ratesLength = other->ratesLength;
}
