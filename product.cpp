#include "product.h"

Product::Product() : Product(nullptr, nullptr, 0, 0)
{
}

Product::Product(const MyString& _name, const MyString& _unit, unsigned _category = 0, double _quantity = 0)
{
	name = _name;
	unit = _unit;
	category = _category;
	quantity = _quantity;
}

void Product::print()
{
	cout << " Product Name: " << name << " Unit: " << unit << " Quantity: " << quantity;
}

ostream& operator<<(ostream& ostream, const Product& product)
{
	if (&ostream == &std::cout)
	{
		cout << " Product Name: " << product.name << " Unit: " << product.unit << " Quantity: " << product.quantity;
	}
	else {
		ostream << product.name << ' ' << product.unit << ' ' << product.quantity << ' ' << product.category;
	}
	return ostream;
}
