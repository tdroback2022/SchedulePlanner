#ifndef _Person_H_
#define _Person_H_
#include "Event.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Person{
protected:
    vector<Event *>e;

public:
    // Constructors
    Person() {;}

    void addEvent(Event *m) {e.push_back(m);}
    void deleteEvent(int i){e.erase(e.begin() + i);}

    short sizeEvents() {
        return e.size();
    }

    Event *&operator[](short index) {return e[index];}

    void write_events();
    void read_events();
};


#endif  // _Person_H_