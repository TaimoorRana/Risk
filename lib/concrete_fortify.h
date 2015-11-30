#ifndef CONCRETEFORTIFY_H
#define CONCRETEFORTIFY_H
#include "decorator.h"
#include <string>
using namespace std;
/**
 * @brief The ConcreteFortify class extends Decorator
 */
class ConcreteFortify : public Decorator
{

public:
	/**
	 * @brief ConcreteFortify
	 * @param c we copy the component so that it can be decorated
	 */
	ConcreteFortify(Component *c);
	~ConcreteFortify();
	void log();
	string getLog();
private :
	string fortify = "fortify phase\n";

};

#endif // CONCRETEFORTIFY_H
