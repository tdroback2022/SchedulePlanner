#include "Date.h"

void Date::operator+(int n) {
    day += n;
    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31 ) {
        month++;
        day -= 31;
    }else if (month == 2 && day > 28) {
        month++;
        day -= 28;
    }else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        month++;
        day -= 30;
    }
    if(month == 13){year++; month = 1;}
}
void Date::operator-(int n) {
    day -= n;
    if((month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11 || month == 1) && day == 0 ) {
        month--;
        day += 31;
    }else if (month == 3 && day == 0) {
        month--;
        day += 28;
    }else if ((month == 5 || month == 7 || month == 10 || month == 12) && day == 0) {
        month--;
        day += 30;
    }
    if(month == 0){year--; month = 12;}
}

Date & Date::operator=(const Date &d) {
    day = d.day;
    month = d.month;
    year = d.year;
    return *this;
}