#ifndef PRODUCT_H
#define PRODUCT_H
#include "myString.h"
#include <iostream>

using namespace std;
class Product {
public:
	Product();
	Product(const MyString& _name, const MyString& _unit, unsigned _category, double _quantity);
	void print();
	
	friend ostream& operator<<(ostream& ostream, const Product& product);
private:
	MyString name;
	//0-8
	MyString unit;
	double quantity;
	unsigned category;
};
#endif // !PRODUCT_H
