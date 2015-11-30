#include "iattribute.h"


QLabel* IAttribute::getName()
{
	return name;
}

QLabel* IAttribute::getValue()
{
	observedUpdated();
	return value;
}

