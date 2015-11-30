#include "concrete_attack.h"

ConcreteAttack::ConcreteAttack(Component *comp)
{
	component = comp;
	log();
}

ConcreteAttack::~ConcreteAttack()
{
	delete component;
}

void ConcreteAttack::log()
{
	logging += component->getLog()+attack;
}

void ConcreteAttack::setLog(string s)
{
	logging += s;
}

string ConcreteAttack::getLog()
{
	return logging;
}

