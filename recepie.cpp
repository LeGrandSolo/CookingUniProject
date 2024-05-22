#include "recepie.h"

Recepie::Recepie(const MyString _title, unsigned prepareTime)
{
	title = _title;
	prepareTime = prepareTime;
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
//
//const char* Recepie::getTitle() const
//{
//	return title.getStr();
//}
//
//const bool* Recepie::getTypesOfFood() const
//{
//	return typesOfFood;
//}
//
//const char* Recepie::getStepsDesc() const
//{
//	return stepsDesc.getStr();
//}
//
//unsigned Recepie::getPrepareTime() const
//{
//	return prepareTime;
//}
//
//const MyVector<Product>& Recepie::getProdList() const
//{
//	return productList;
//}
//
//const MyVector<MyString>& Recepie::getImagesUrl() const
//{
//	return imagesUrl;
//}
//
//time_t Recepie::getDate()const 
//{
//	return date;
//}
//
//
//unsigned Recepie::GetRatingSumed()const
//{
//	return ratingSumed;
//}
//
//unsigned Recepie::GetRatesLength()const
//{
//	return ratesLength;
//}
//
//xg::Guid Recepie::getId()const
//{
//	return id;
//}
//
//
//void Recepie::setId(xg::Guid _id)
//{
//	id = _id;
//}
//
//void Recepie::setRatingSumed(unsigned _ratingSum)
//{
//	ratingSumed = _ratingSum;
//}
//
//void Recepie::setRatesLength(unsigned _ratingLength)
//{
//	ratesLength = _ratingLength;
//}

size_t Recepie::categoryStrToIndex(const char* str)
{
	size_t categoryIndex = 0;
	if (!strcmp(str, "vegetables"))
	{
		categoryIndex = 1;
	}
	else if (!strcmp(str, "fruits")) {
		categoryIndex = 2;
	}
	else if (!strcmp(str, "grains")) {
		categoryIndex = 2;
	}
	else if (!strcmp(str, "fruits")) {
		categoryIndex = 3;
	}
	else if (!strcmp(str, "meat")) {
		categoryIndex = 4;
	}
	else if (!strcmp(str, "seafood")) {
		categoryIndex = 5;
	}
	else if (!strcmp(str, "dairy")) {
		categoryIndex = 6;
	}
	else if (!strcmp(str, "eggs")) {
		categoryIndex = 7;
	}
	return categoryIndex;
}
