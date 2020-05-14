#ifndef _Date_H_
#define _Date_H_
#include <iostream>
using namespace std;

class Date{
protected:
    short day, month, year;
public:
    // Constructors
    Date() { day = 0; month = 0; year = 0; }
    Date(short m, short d, short y) {day = d; month = m; year = y;}
    Date(short m, short d) {day = d; month = m;}
    
    // Get functions
    short getDay() {return day;}
    short getMonth() {return month;}
    short getYear() {return year;}

    // Set functions
    void setDay(short d) {day = d;}
    void setMonth(short m) {month = m;}
    void setYear(short y) {year = y;}
    void setAll(short m, short d, short y) {setDay(d); setMonth(m); setYear(y);}

    // Operator funcions
    void operator+(int n);
    void operator-(int n);
    Date &operator=(const Date &d);

};


#endif  // _DATE_H_