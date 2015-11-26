#include "concrete_attack.h"

ConcreteAttack::ConcreteAttack(Component *comp)
{
	component = comp;
}

void ConcreteAttack::log()
{
	component->log();
	//logString;
}

void ConcreteAttack::setLog(string s)
{
	logString = s;
}

