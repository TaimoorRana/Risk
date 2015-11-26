#ifndef DECORATOR_H
#define DECORATOR_H
#include "component.h"
#include <string>

using namespace std;
class Decorator : public Component
{
public:
	Decorator();
	virtual void log();
	string getLog();
protected:
	Component *component = nullptr ;
	string logging;
};

#endif // DECORATOR_H
