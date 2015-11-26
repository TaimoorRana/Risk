#ifndef CONCRETEATTACK_H
#define CONCRETEATTACK_H
#include "decorator.h"
#include <string>
using  namespace std;

class ConcreteAttack : public Decorator
{
public:
	ConcreteAttack(Component *comp);
	void log();
	void setLog(string s);
	string getLog();

private:
	string attacking = "attacking phase";
};
#endif // CONCRETEATTACK_H
