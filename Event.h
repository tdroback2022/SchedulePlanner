#ifndef _Event_H_
#define _Event_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Date.h"
using namespace std;

class Event{
protected:
    string title;
    short priority;
    Date startDay;
    int startTime;
    int endTime;
    string description;
    string eventType;
    int timeSpend;
    /* Use this when displaying daily distribution
    Event
    ClassWork
    Work
    Sleep
    Eating
    Class
    Other
    */
    short repeats = 0;
    // if repeated is true, repeat every startDay + 7 until X amount of repeats
    short maxRepeats = 0;
public:
    // Constructors
    Event();
    Event(short m, short d, short y, int start, int end, short rank, const string type, const string name, const string desc, short rpts, short maxrepeats);
    Event(const Event &e);

    // Destructor
    ~Event() {;}

    // Get functions
    string &getTitle() {return title;}
    string &getDescription() {return description;}
    short getPriority() const {return priority;}
    int getStartTime() const {return startTime;}
    int getEndTime() const {return endTime;}
    string getEventType() const {return eventType;}
    short getStartDay() {return startDay.getDay();}
    short getStartMonth() {return startDay.getMonth();}
    short getStartYear() {return startDay.getYear();}
    short getRepeats() const {return repeats;}
    short getMaxRepeats() const {return maxRepeats;}
    int getTimeSpend() const {return (getEndTime() - getStartTime());}

    // These virtual functions only exist for Person.cpp's write_events() function
    virtual short getDueDay() {return 0;}
    virtual short getDueMonth() {return 0;}
    virtual short getDueYear() {return 0;}
    virtual bool getExam() {return 0;}

    // Set functions
    void setPriority(short val) {priority = val;}
    void setStartTime(short time) {startTime = time;}
    void setEndEtime(short time) {endTime = time;}
    void setStartDay(short m, short d, short y) {startDay.setAll(m,d,y);}
    void setTimeSpend(int time) {timeSpend = time;}

    // Set functions (definitions only)
    void setTitle(const string str);
    void setDescription(const string str);

    // Other functions
    void addDays(int n){startDay + n;}
    void subDays(int n){startDay - n;}
    void addWeeks(int n){startDay + (7*n);}
    void subWeeks(int n){startDay - (7*n);}
    
};

class ClassWork:public Event{
protected:
    bool exam;
    Date due;
    
public:
    // Constructors
    ClassWork();
    ClassWork(short m, short d, short y, int start, int end, short rank, const string type, const string name, const string desc, short rpts, short maxrepeats, short dueyear, short duemonth, short dueday, bool ex);
    ClassWork(const ClassWork &c);

    // Destructor
    ~ClassWork(){;}

    // Get functions
    bool getExam() {return exam;}

    // Get when the classwork is due
    short getDueDay() {return due.getDay();}
    short getDueMonth() {return due.getMonth();}
    short getDueYear() {return due.getYear();}

    // Set functions
    void setExam(bool e) {exam = e;}
    void setDue(short m, short d, short y) {due.setAll(m,d,y);}

    // Other functions
    void printDue(){cout << due.getMonth() << "/" << due.getDay() << "/20" << due.getYear() << endl;}

};

#endif  // _Event_H_