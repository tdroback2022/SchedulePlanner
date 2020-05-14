#include "Event.h"
#include <map>
#include <string>
#include <vector>

// ########################### Event class #############################

// ################
// ##Constructors##
// ################

// Default constructor
Event::Event() {
    eventType = "Event";
    title = "Event";
    priority = 0;
    startDay.setAll(0, 0, 0);
    startTime = 0;
    endTime = 0;
    description = "Description";
    timeSpend = endTime - startTime;
}

// Regular constructor
Event::Event(short m, short d, short y, int start, int end, short rank, const string type, const string name, const string desc, short rpts, short maxrepeats){
    startDay.setAll(m, d, y);
    startTime = start; endTime = end;
    repeats = rpts;
    maxRepeats = maxrepeats;
    priority = rank;
    eventType = type;
    title = name;
    description = desc;
    timeSpend = endTime - startTime;
}

// Copy constructor
Event::Event(const Event &e) {
    // Copy title
    title = e.title;

    // Copy description
    description = e.description;

    // Copy everything else
    maxRepeats = e.maxRepeats;
    eventType = e.eventType;
    priority = e.priority;
    startDay = e.startDay;
    startTime = e.startTime;
    endTime = e.endTime;
    repeats = e.repeats;
}

// ################
// ##Set function##
// ################

void Event::setTitle(const string str) {
    title = str;
}

void Event::setDescription(const string str) {
    description = str;
}

// ######################### ClassWork class ###########################

// ################
// ##Constructors##
// ################

// Default constructor
ClassWork::ClassWork() : Event() {
    eventType = "ClassWork";
    exam = false;
    due.setAll(0, 0, 0);
    timeSpend = 1;
}

// Regular constructor
ClassWork::ClassWork(short m, short d, short y, int start, int end, short rank, const string type, const string name, const string desc, short rpts, short maxrepeats, short dueyear, short duemonth, short dueday, bool ex): Event(m, d, y, start, end, rank, type, name, desc, rpts, maxrepeats){
    eventType = type;
    due.setAll(duemonth, dueday, dueyear);
    exam = ex;
}

// Copy constructor
ClassWork::ClassWork(const ClassWork &c) : Event(c){
    due = c.due;
    timeSpend = c.timeSpend;
    exam = c.exam;
}

// ################
// ##Set function##
// ################
