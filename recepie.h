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
	void setStepsDesc(const MyString& stepsDesc);
	void setCategory(size_t index);

	const char* getTitle()const;
	const bool* getTypesOfFood()const;
	const char* getStepsDesc()const;
	unsigned getPrepareTime()const;
	const MyVector<Product>& getProdList()const;
	const MyVector<MyString>& getImagesUrl()const;
	time_t getDate();
	unsigned GetRatingSumed();
	unsigned GetRatesLength();
	const char* getId();
private:

	MyString title;
	/*Other ;Vegetables; Fruits; Grains; Meat; Seafood; Dairy; Eggs*/
	bool typesOfFood[8];
	unsigned prepareTime;
	MyVector<Product> productList;
	MyString stepsDesc;
	MyVector<MyString> imagesUrl;
	time_t date;
	unsigned ratingSumed;
	unsigned ratesLength;
	xg::Guid id;
};

#endif // !RECEPIE_H
