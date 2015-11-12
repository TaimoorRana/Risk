#include "observable.h"
#include "observer.h"

Observable::Observable() {
	observers = std::list<Observer*>();
}

void Observable::attachObserver(Observer* observer){
  observers.push_back(observer);
};

void Observable::detachObserver(Observer* observer){
  observers.remove(observer);
};

void Observable::setNotificationsEnabled(bool enabled){
  this->notifyEnabled = enabled;
};

bool Observable::getNotificationsEnabled(){
  return this->notifyEnabled;
};

void Observable::notifyObservers(){
	if (!this->notifyEnabled) {
		return;
	}
  for (Observer* observer : observers) {
		observer->observedUpdated();
  }
};
