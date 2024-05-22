#ifndef RECEPIE_H
#define RECEPIE_H

#include <crossguid/guid.hpp>
#include <ctime>
#include "myString.h"
#include "product.h"
#include "myVector.h"

class Recepie {
public:


	Recepie(const MyString _title, unsigned prepareTime);

	void addProduct(const MyString& name, const MyString& unit, unsigned category, double quantity);
	void addImgUrl(const MyString& url);

	void setCategory(size_t index);
	/*void setStepsDesc(const MyString& stepsDesc);
	void setId(xg::Guid _id);
	void setRatingSumed(unsigned _ratingSum);
	void setRatesLength(unsigned _ratingLength);*/

	/*const char* getTitle()const;
	const bool* getTypesOfFood()const;
	const char* getStepsDesc()const;
	unsigned getPrepareTime()const;
	const MyVector<Product>& getProdList()const;
	const MyVector<MyString>& getImagesUrl()const;
	time_t getDate()const;
	unsigned GetRatingSumed()const;
	unsigned GetRatesLength()const;
	xg::Guid getId()const;*/
	friend class Auth;
private:
	size_t categoryStrToIndex(const char* str);
	MyVector<Product> productList;
	MyVector<MyString> imagesUrl;
	xg::Guid id;
	MyString title;
	MyString stepsDesc;
	/*Other ;Vegetables; Fruits; Grains; Meat; Seafood; Dairy; Eggs*/
	bool typesOfFood[8];
	time_t date;
	unsigned prepareTime;
	unsigned ratingSumed;
	unsigned ratesLength;
};

#endif // !RECEPIE_H
