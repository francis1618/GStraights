#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>

class Observer;

//subject interace
class Subject {
public:
	void subscribe(Observer*);
	void unsubscribe(Observer*);

protected:
	void notify();

private:
	typedef std::set<Observer*> ObserverSet;
	ObserverSet observers_;
};

#endif