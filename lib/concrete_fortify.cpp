#include "concrete_fortify.h"





ConcreteFortify::ConcreteFortify(Component *c)
{
	component =c;
	log();
}

ConcreteFortify::~ConcreteFortify()
{
	delete component;
}

void ConcreteFortify::log()
{
	logging += component->getLog()+ fortify;
}

string ConcreteFortify::getLog(){
	return logging;
}
