#ifndef CONCRETEFORTIFY_H
#define CONCRETEFORTIFY_H
#include "decorator.h"
#include <string>
using namespace std;
class ConcreteFortify : public Decorator
{
public:
	ConcreteFortify(Component *c);
	~ConcreteFortify();
	void log();
	string getLog();
private :
	string fortify = "fortify phase\n";

};

#endif // CONCRETEFORTIFY_H
