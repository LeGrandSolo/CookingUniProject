#ifndef RECEPIE_H
#define RECEPIE_H

#include <crossguid/guid.hpp>
#include <ctime>
#include "myString.h"

class Recepie {
public:

	Recepie();
	Recepie(const char* _title,unsigned _prepareTime, char** _productList, size_t prodListLength, const char* _stepsDesc,char** _imageLinks, size_t imageLinksLength, time_t date);
	~Recepie();
	Recepie(const Recepie& other);
	Recepie& operator=(const Recepie& other);

	Recepie(Recepie&& other);
	Recepie& operator=(Recepie&& other);
private:
	void copyObj(const Recepie& other);
	void move(Recepie* other);
	MyString title;
	/*Vegetables; Fruits; Grains; Meat; Seafood; Diary; Eggs; Other*/
	bool typesOfFood[8];
	unsigned prepareTime;
	MyString* productList;
	size_t prodLength;
	MyString stepsDesc;
	MyString* imageLinks;
	size_t imgLinksLength;
	time_t date;
	unsigned ratingSumed;
	unsigned ratesLength;
	xg::Guid id;
};

#endif // !RECEPIE_H
