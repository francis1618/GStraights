#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(Observer* o) {
	observers_.insert(o);
}

void Subject::unsubscribe(Observer* o) {
	observers_.erase(0);
}

void Subject::notify() {
	ObserverSet::iterator iter;
	for(iter = observers_.begin(); iter!=observers_.end(); iter++)
		(*iter)->update();
}