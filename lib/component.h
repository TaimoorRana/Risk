#ifndef COMPONENT
#define COMPONENT


#include <string>
using namespace std;

class Component {
public:
	virtual void log();
	virtual void setLog(string s);
	//virtual string getLog();
protected:
	string logString;
};

#endif // COMPONENT


