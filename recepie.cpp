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

void Recepie::setStepsDesc(const MyString& _stepsDesc)
{
	stepsDesc = _stepsDesc;
}

void Recepie::setCategory(size_t index)
{
	if (index<8)
	{
		typesOfFood[index] = true;
	}
}

const char* Recepie::getTitle() const
{
	return title.getStr();
}

const bool* Recepie::getTypesOfFood() const
{
	return typesOfFood;
}

const char* Recepie::getStepsDesc() const
{
	return stepsDesc.getStr();
}

unsigned Recepie::getPrepareTime() const
{
	return prepareTime;
}

const MyVector<Product>& Recepie::getProdList() const
{
	return productList;
}

const MyVector<MyString>& Recepie::getImagesUrl() const
{
	return imagesUrl;
}

time_t Recepie::getDate()
{
	return date;
}

unsigned Recepie::GetRatingSumed()
{
	return ratingSumed;
}

unsigned Recepie::GetRatesLength()
{
	return ratesLength;
}

const char* Recepie::getId()
{
	return id.str().c_str();
}

