#include"../react.h"
#include <fstream>
#include <map>
#include "Date.h"
#include "Event.h"
#include "Person.h"
using namespace std;

const char *get_day_of_week(long t_raw){
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%a", localtime(&t));
  return res;
}

const char *get_current_day(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%d", localtime(&t));
  return res;
}

const char *get_current_month(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%m", localtime(&t));
  return res;
}

const char *get_current_year(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%y", localtime(&t));
  return res;
}

void set_current_day(Date &today) {
  string e = (get_current_day(current_time()));
  stringstream d(e);
  short day; d >> day;
  string ee = (get_current_month(current_time()));
  stringstream m(ee);
  short month; m >> month;
  string eee = (get_current_year(current_time()));
  stringstream y(eee);
  short year; y >> year;
  today.setAll(month, day, year);
  string all = ee + '/' + e + '/' + eee;
}


// Main program

int main() {

  map<string,short>day_converter;
  day_converter["Sun"] = 0; day_converter["0"] = 0;
  day_converter["Mon"] = 1; day_converter["1"] = 1;
  day_converter["Tue"] = 2; day_converter["2"] = 2;
  day_converter["Wed"] = 3; day_converter["3"] = 3;
  day_converter["Thu"] = 4; day_converter["4"] = 4;
  day_converter["Fri"] = 5; day_converter["5"] = 5;
  day_converter["Sat"] = 6; day_converter["6"] = 6;
  Date today;
  set_current_day(today);
  Person test;
  test.read_events();
  init();

  if (just_starting()) {
    add_yaml("expandedOutput.yaml");
      print_at(0, "S");
      print_at(4, "M");
      print_at(8, "T");
      print_at(12, "W");
      print_at(16, "Th");
      print_at(20, "F");
      print_at(24, "S");
      print_at(30, "Today's Top 3:");
      print_at(50, "Exam");
      print_at(70, "Due: 11/18/19");
      print_at(90, "Work for 1 hour");
      print_at(110, "Homework");
      print_at(130, "Due: 11/22/19");
      print_at(150, "Work for 30 mins");
      print_at(170, "Paper");
      print_at(190, "Due: 11/25/19");
      print_at(210, "Work for 1 hour");
  }
        
  if(received_event()){
    
    for(int i = 0; i < test.sizeEvents(); ++i){
      cerr << test[i] -> getStartMonth() << "/" << test[i] -> getStartDay() << "/" << test[i] -> getStartYear() << "\t";
      test[i] -> subDays(1); 
      cerr << test[i] -> getStartMonth() << "/" << test[i] -> getStartDay() << "/" << test[i] -> getStartYear() << "\n";
    }
    add_yaml("expandedOutput.yaml");

  }
  test.write_events();
  quit();
}