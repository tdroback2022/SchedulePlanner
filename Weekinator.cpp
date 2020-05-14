#ifndef _WEEKINATOR_H_
#define _WEEKINATOR_H_
#include "Date.h"

class Weekinator {
    static Date today;
    Date week[7];
public:
    Weekinator() {
        for(int i = 0; i < 7; i++) {
            week[i] = today;
            week[i] + i;
        }
    }

    void weekinize() {
        for (int i = 0; i < 7; i++) {
            cout << week[i].getMonth() << "/" << week[i].getDay() << "/" << week[i].getYear() << endl;
        }
    }
};

#endif // _WEEKINATOR_H_