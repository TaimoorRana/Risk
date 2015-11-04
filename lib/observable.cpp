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
void Observable::notifyObservers(){
  for (Observer* observer : observers) {
		observer->observedUpdated();
  }
};
