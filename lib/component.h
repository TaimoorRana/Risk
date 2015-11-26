#ifndef COMPONENT
#define COMPONENT


#include <string>
using namespace std;

class Component {
public:
	virtual void log()=0;
	//virtual void setLog(string s)=0;
	virtual string getLog()=0;
	//virtual void setCurrentPlayer(string s)=0;
protected:
	string logString;
};

#endif // COMPONENT


