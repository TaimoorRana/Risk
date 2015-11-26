#ifndef CONCRETEFORTIFY_H
#define CONCRETEFORTIFY_H
#include "decorator.h"
#include <string>
using namespace std;
class ConcreteFortify : public Decorator
{
public:
	ConcreteFortify();
	void log();
private :
	string fortify = "fortify phase";

};

#endif // CONCRETEFORTIFY_H
