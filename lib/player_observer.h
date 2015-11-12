#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <set>
#include <string>
class PlayerObserver{

public:
	/**
	 * @brief update updates this observer values
	 */
    virtual void update() = 0;
};

#endif // PLAYEROBSERVER

