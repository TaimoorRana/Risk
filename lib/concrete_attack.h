#ifndef CONCRETEATTACK_H
#define CONCRETEATTACK_H
#include "decorator.h"
#include <string>
using  namespace std;

/**
 * @brief The ConcreteAttack class extends Decorator
 */
class ConcreteAttack : public Decorator
{
public:
	/**
	 * @brief ConcreteAttack
	 * @param comp we copy this so that it can be decorated
	 */
	ConcreteAttack(Component *comp);
	~ConcreteAttack();
	void log();
	void setLog(string s);
	string getLog();

private:
	string attack = "attacking phase\n";
};
#endif // CONCRETEATTACK_H
