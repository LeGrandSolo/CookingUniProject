#include "product.h"

Product::Product(): Product(nullptr,nullptr,0,0)
{
}

Product::Product(const MyString& _name, const MyString& _unit, unsigned _category = 0, double _quantity = 0)
{
	name = _name;
	unit = _unit;
	category = _category;
	quantity = _quantity;
}
