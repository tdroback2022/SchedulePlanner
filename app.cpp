#include"../react.h"
#include <fstream>
#include <map>
#include "Date.h"
#include "Event.h"
#include "Person.h"
#include <sstream>
#include <bits/stdc++.h> 
using namespace std;

// Functions to get and set current date from system

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

const char *get_current_hour(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%H", localtime(&t));
  return res;
}

const char *get_current_min(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%M", localtime(&t));
  return res;
}

int current_time_in_mins() {
  string h = (get_current_hour(current_time()));
  stringstream s1(h);
  int hours; s1 >> hours;
  string m = (get_current_min(current_time()));
  stringstream s2(m);
  int mins; s2 >> mins;
  return hours * 60 + mins;
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
}

string convert_time(int time) {
  int hours = time / 60;
  int mins = time % 60;
  string tod;
  if (hours > 12 && hours < 24) {
    hours = hours - 12;
    tod = "PM";
  }else if (hours == 12) {
    tod = "PM";
  } else if (hours == 0 || hours == 24) {
    hours = 12;
    tod = "AM";
  } else {
    tod = "AM";
  }
  string m;
  if (mins < 10) {
    m = '0' + to_string(mins);
  }else {
    m = to_string(mins);
  }
  string h = to_string(hours);
  string clock = h + ":" + m + " " + tod;
  return clock;
}

Event &find_next_event(vector<Event>e) {
  Event &next = e[0];
  int limit = e.size();
  int i = 0;
  while((i < limit) && (next.getStartTime() <= current_time_in_mins())) {
    i++;
    next = e[i];
  }
  if (i == limit) {
    for (int k = 0; k < limit; k++) {
      if (e[k].getStartTime() > next.getStartTime()) {
        next = e[k];
      }
    }
  }else {
    for (int k = i + 1; k < limit; k++) {
      if ((e[k].getStartTime() > current_time_in_mins()) && (e[k].getStartTime() < next.getStartTime())) {
        next = e[k];
      }
    }
  }
  return next;
}

bool compareInterval(const Event &i1, const Event &i2) 
{ 
  return (i1.getStartTime() < i2.getStartTime()); 
} 

void Organize(vector<Event> &in) {
  sort(in.begin(), in.end(), compareInterval);
}

// Build Home Page
void build_home(Person &user, Date &today) {
  string td = to_string(today.getMonth()) + "/" + to_string(today.getDay()) + "/" + to_string(today.getYear());
  print_at(0, td);
  add_yaml("home1.yaml");
  double eventTime = 0; string sleep = "Sleep";
  double classWorkTime = 0; string event = "Event";
  double workTime = 0; string classwork = "ClassWork";
  double sleepTime = 0; string homework = "Homework";
  double eatingTime = 0; string exam = "Exam";
  double classTime = 0; string work = "Work";
  double otherTime = 0; string clas = "Class";
  double totalTime = 1440; string other = "Other";
  string bre = "Breakfast";
  string lunch = "Lunch";
  string dinner = "Dinner";
  
  vector<Event>thisDay;
  int r = 255;
  int g = 255;
  int b = 255;
  if (user.sizeEvents() > 0) {  // If there are any events that the user has at all
    for(short i = 0; i < user.sizeEvents(); i++) {
      if(user[i]->getStartDay() == today.getDay() && user[i]->getStartMonth() == today.getMonth() && user[i]->getStartYear() == today.getYear()) {
        thisDay.push_back(*user[i]); // Only add events that are the same as today
      }
    }

    if(thisDay.size() > 1){Organize(thisDay);}
    

    for(unsigned int i = 0; i < thisDay.size(); i++) {
      print_at(50 + 120 * (i + 1), thisDay[i].getTitle());
      string tchar = convert_time(thisDay[i].getStartTime()) + " - " + convert_time(thisDay[i].getEndTime());
      print_at(150 + 120 * (i + 1), tchar.c_str());
      print_at(70 + 120 * (i + 1), thisDay[i].getDescription());
      if(thisDay[i].getEventType() == event) {
        eventTime += (thisDay[i].getTimeSpend());
        
        add_yaml("todayEventBox.yaml", {{"r", 160}, {"g", 160}, {"b", 160}, {"title", 50 + 120 * (i + 1)}, {"time", 150 + 120 * (i + 1)}});
      }else if((thisDay[i].getEventType() == classwork) || (thisDay[i].getEventType() == homework) || (thisDay[i].getEventType() == exam)) {
        classWorkTime += (thisDay[i].getTimeSpend());
        add_yaml("todayEventBox.yaml", {{"r", 60}, {"g", 60}, {"b", 60}, {"title", 50 + 120 * (i + 1)}, {"time", 150 + 120 * (i + 1)}});
      }else if(thisDay[i].getEventType() == work ) {
        workTime += (thisDay[i].getTimeSpend());
        add_yaml("todayEventBox.yaml", {{"r", 200}, {"g", 50}, {"b", 50}, {"title", 50 + 120 * (i + 1)}, {"time", 150 + 120 * (i + 1)}});
      }else if(thisDay[i].getEventType() == sleep) {
        sleepTime += (thisDay[i].getTimeSpend());
      }else if(thisDay[i].getEventType() == bre || thisDay[i].getEventType() == lunch || thisDay[i].getEventType() == dinner) {
        eatingTime += (thisDay[i].getTimeSpend());
      }else if(thisDay[i].getEventType() == clas) {
        classTime += (thisDay[i].getTimeSpend());
        add_yaml("todayEventBox.yaml", {{"r", 130}, {"g", 200}, {"b", 50}, {"title", 50 + 120 * (i + 1)}, {"time", 150 + 120 * (i + 1)}});
      }else if(thisDay[i].getEventType() == other) {
        otherTime += (thisDay[i].getTimeSpend());
      }
    }
    print_at(50, find_next_event(thisDay).getTitle());
    if(find_next_event(thisDay).getTitle() == event || find_next_event(thisDay).getTitle() == other){
      r= 160; g = 160; b = 160;
    }else if(find_next_event(thisDay).getTitle() == classwork){
      r = 60; g = 60; b = 60;
    }else if(find_next_event(thisDay).getTitle() == work){
      r = 200; g = 50; b = 50;
    }else if(find_next_event(thisDay).getTitle() == sleep){
      r = 90; g = 90; b = 220;
    }else if(find_next_event(thisDay).getTitle() == bre || find_next_event(thisDay).getTitle() == lunch || find_next_event(thisDay).getTitle() == dinner){
      r = 220; g = 140; b = 0;
    }else if(find_next_event(thisDay).getTitle() == clas){
      r = 130; g = 200; b = 50;
    }else{
      r= 160; g = 160; b = 160;
    }
    string tchar = convert_time(find_next_event(thisDay).getStartTime()) + " - " + convert_time(find_next_event(thisDay).getEndTime());
    print_at(150, tchar.c_str());
    print_at(70, find_next_event(thisDay).getDescription());
  }

  print_at(12, "Up Next:");
  add_yaml("home2.yaml", {{"r", r}, {"g", g}, {"b", b}, {"title", 50}, {"time", 150}, {"description", 70}, {"s", (sleepTime/totalTime * 100)}, {"e", (eatingTime/totalTime) * 100}, {"c", (classTime/totalTime * 100)}, {"h", (classWorkTime/totalTime) * 100}, {"w", (workTime/totalTime) * 100}, {"o", (otherTime/totalTime) * 100}, {"v", (eventTime/totalTime) * 100}});
}

// Build add_event
void build_addEvent(){
  add_yaml("addEvent.yaml");
  print_at(0,"Event type");
  print_at(15,"Event");
  print_at(25,"Homework");
  print_at(35,"Exam");
  print_at(50,"Event title");
  print_at(65,"Enter title");
  print_at(80,"On");
  print_at(85,"MM");
  print_at(90,"DD");
  print_at(95,"YY");
  print_at(100,"From");
  print_at(105,"HR");
  print_at(108,":");
  print_at(110,"MN");
  print_at(115,"AM");
  print_at(120,"PM");
  print_at(125,"To");
  print_at(130,"HR");
  print_at(133,":");
  print_at(135,"MN");
  print_at(140,"AM");
  print_at(145,"PM");
  print_at(150, "Description");
  print_at(170, "Enter something here");
  print_at(270, "Create event");
  print_at(300, "# repeats");
  print_at(325, "00");
  print_at(335, "Due");
  print_at(355,"MM");
  print_at(360,"DD");
  print_at(365,"YY");
}

//  Build personalization
void build_personalization(Person &test){
  add_yaml("personalization.yaml");
  print_at(0, "On");
  print_at(4, "Sun");
  print_at(8, "Mon");
  print_at(12, "Tue");
  print_at(16, "Wed");
  print_at(20, "Thu");
  print_at(24, "Fri");
  print_at(28, "Sat");
  print_at(32, "How long do you usually spend");
  print_at(70, "When");
  print_at(75, "Sleeping");
  print_at(85, "HR");
  print_at(90, ":");
  print_at(92, "MN"); 
  print_at(96, "HR");
  print_at(100, ":");
  print_at(102, "MN");
  print_at(106, "AM");
  print_at(110, "PM");
  print_at(115, "Breakfast"); 
  print_at(125, "HR");
  print_at(130, ":");
  print_at(132, "MN");
  print_at(136, "HR");
  print_at(140, ":");
  print_at(142, "MN");
  print_at(146, "AM");
  print_at(150, "PM");
  print_at(155, "Lunch");
  print_at(165, "HR");
  print_at(170, ":");
  print_at(172, "MN");
  print_at(176, "HR");
  print_at(180, ":");
  print_at(182, "MN");
  print_at(186, "AM");
  print_at(190, "PM");
  print_at(195, "Dinner");
  print_at(205, "HR");
  print_at(210, ":");
  print_at(212, "MN");
  print_at(216, "HR");
  print_at(220, ":");
  print_at(222, "MN");
  print_at(226, "AM");
  print_at(230, "PM");
  print_at(235, "Work");
  print_at(245, "HR");
  print_at(250, ":");
  print_at(252, "MN");
  print_at(256, "HR");
  print_at(260, ":");
  print_at(262, "MN");
  print_at(266, "AM");
  print_at(270, "PM");
  print_at(275, "Other");
  print_at(285, "HR");
  print_at(290, ":");
  print_at(292, "MN");
  print_at(296, "HR");
  print_at(300, ":");
  print_at(302, "MN");
  print_at(306, "AM");
  print_at(310, "PM");
  print_at(315, "Class Name");
  print_at(330, "From");
  print_at(340, "HR");
  print_at(345, ":");
  print_at(347, "MN");
  print_at(350, "To");
  print_at(355, "HR");
  print_at(360, ":");
  print_at(362, "MN");
  print_at(366, "AM");
  print_at(370, "PM");
  print_at(375, "Add a Class");
  print_at(390, "Save");
  print_at(395, "AM");
  print_at(398, "PM");
}

// Create event button
void create(Person &test, Date &today){
  Event *temp;
  string sy = (global_mem + 95);           // Create temporary variables and reinterpret file data
  stringstream sys(sy);
  short startYear; sys >> startYear;

  string sm = (global_mem + 85);
  stringstream sms(sm);
  short startMonth; sms >> startMonth;

  string sd = (global_mem + 90);
  stringstream sds(sd);
  short startDay; sds >> startDay;

  string sth = (global_mem + 105);
  stringstream sths(sth);
  int startTimeh; sths >> startTimeh;
  if((global_mem[115] == 'P' || global_mem[115] == '1') && global_mem[106] != '2'){startTimeh += 12;} // Add 12 hours if PM and not 12:00 PM
  if((global_mem[115] == 'A' || global_mem[115] == '0') && global_mem[106] == '2'){startTimeh = 0;}   // 0 hours if AM and not 12:00 AM

  string stm = (global_mem + 110);
  stringstream stms(stm);
  int startTimem; stms >> startTimem;
  int startTime = startTimem + startTimeh*60;


  string eth = (global_mem + 130);
  stringstream eths(eth);
  int endTimeh; eths >> endTimeh;
  if((global_mem[140] == 'P' || global_mem[140] == '1') && global_mem[131] != '2'){endTimeh += 12;} // Add 12 hours if PM and not 12:00 PM
  if((global_mem[140] == 'A' || global_mem[140] == '0') && global_mem[131] == '2'){startTimeh = 0;}   // 0 hours if AM and not 12:00 AM

  string etm = (global_mem + 135);
  stringstream etms(etm);
  int endTimem; etms >> endTimem;
  int endTime = endTimem + endTimeh*60;

  short priority = test.sizeEvents(); // This needs to be changed in the future (or does it?)

  string title = (global_mem + 65); 

  string description = (global_mem + 170);  
  
  short repeats = 0;

  string mr = (global_mem + 325);
  stringstream mrs(mr);
  short maxRepeats; mrs >> maxRepeats;

  string eventType;                   // Getting event type and adding appropriate event
  if(global_mem[15] == 'E' || global_mem[15] == '0'){
      eventType = "Event";
      temp = new Event(startMonth, startDay, startYear, startTime, endTime, priority, eventType, title, description, repeats, maxRepeats);
      test.addEvent(temp);

  }else if (global_mem[15] == '1'){
      eventType = "Homework";
      string dy = (global_mem + 365);
      stringstream dys(dy);
      short dueYear; dys >> dueYear;

      string dm = (global_mem + 355);
      stringstream dms(dm);
      short dueMonth; dms >> dueMonth;

      string dd = (global_mem + 360);
      stringstream dds(sd);
      short dueDay; dds >> dueDay;
      bool exam = false;

      temp = new ClassWork(startMonth, startDay, startYear, startTime, endTime, priority, eventType, title, description, repeats, maxRepeats, dueYear, dueMonth, dueDay, exam);
      test.addEvent(temp);

  }else if (global_mem[15] == '2'){
      eventType = "Exam";
      string dy = (global_mem + 365);
      stringstream dys(dy);
      short dueYear; dys >> dueYear;

      string dm = (global_mem + 355);
      stringstream dms(dm);
      short dueMonth; dms >> dueMonth;

      string dd = (global_mem + 360);
      stringstream dds(sd);
      short dueDay; dds >> dueDay;
      bool exam = true;

      temp = new ClassWork(startMonth, startDay, startYear, startTime, endTime, priority, eventType, title, description, repeats, maxRepeats, dueYear, dueMonth, dueDay, exam);
      test.addEvent(temp);
  }
  add_yaml("addEvent.yaml");
  // build_home(test, today);
}

// Personalization Save Button
void save(Person &test, map<string,short>day_converter) {
  Event *temp;

  string sy = get_current_year(current_time());           // Create a new event of the appropriate type (x)
  stringstream sys(sy);
  short startYear; sys >> startYear;

  string sm = get_current_month(current_time());
  stringstream sms(sm);
  short startMonth; sms >> startMonth;
  
  string sd = get_current_day(current_time());
  stringstream sds(sd);
  short startDay; sds >> startDay;

  Date current(startMonth, startDay, startYear);

  string day = get_day_of_week(current_time());    // This is a fix that doesn't account for days in a month but I don't want to make it do that

  string chosen = (global_mem + 4);                // What day did the user choose? Start at the next instance of that day
  stringstream schosen(chosen);
  short selected;
  if(global_mem[4] == 'S') { selected = 0;}
  else{schosen >> selected;}
  
  if(selected - day_converter[day] < 0){
    current + (7 + (selected - day_converter[day]));
  }else{current + (selected - day_converter[day]);}

  vector<string> types = {"Sleep", "Breakfast", "Lunch", "Dinner", "Work" ,"Other"};
  int index = 75;
  for(auto x : types){
    for(int i = 0; i < test.sizeEvents(); ++i){                     // If that type of event already exists
      if(test[i] -> getEventType() == x){
        if(test[i] -> getStartDay() == current.getDay()){                
          test.deleteEvent(i);                                         // Erase the previous one
        }
      }
    }
    
    
    string sth = (global_mem + index + 21); // 75, +10 startHr, +17 startMn, +21 endHr, +27 endMn, +31AM/PM, +40 NEXT
    stringstream sths(sth);
    int startTimeh; sths >> startTimeh;
    if((global_mem[index + 31] == 'P' || global_mem[index + 31] == '1') && global_mem[index + 22] != '2'){startTimeh += 12;} // Add 12 hours if PM and not 12:00 PM
    if((global_mem[index + 31] == 'A' || global_mem[index + 31] == '0') && global_mem[index + 22] == '2'){startTimeh = 0;}   // 0 hours if AM and 12:00 AM

    string stm = (global_mem + index + 27);
    stringstream stms(stm);
    int startTimem; stms >> startTimem;
    int startTime = startTimem + startTimeh*60;

    string eth = (global_mem + index + 10);
    stringstream eths(eth);
    int endTimeh; eths >> endTimeh;

    string etm = (global_mem + index + 17);
    stringstream etms(etm);
    int endTimem; etms >> endTimem;
    int endTime = startTime + endTimem + endTimeh*60;

    short priority = test.sizeEvents(); // This needs to be changed in the future (or does it?)

    string title = x; 

    // Defaults
    string type = x;
    short repeats = 0;
    short maxRepeats = 99;
    string description = "This is a(n) " + x + " event";
    
    temp = new Event(current.getMonth(), current.getDay(), current.getYear(), startTime, endTime, priority, type, title, description, repeats, maxRepeats);
    test.addEvent(temp);

    index += 40;
  }
  add_yaml("personalization.yaml");
}

// Personalization Add a Class Button
void add(map<string,short>day_converter, Person &test) {
  Event * temp;
  string sy = get_current_year(current_time());           // Create temporary variables and reinterpret file data
  stringstream sys(sy);
  short startYear; sys >> startYear;

  string sm = get_current_month(current_time());
  stringstream sms(sm);
  short startMonth; sms >> startMonth;

  string sd = get_current_day(current_time());
  stringstream sds(sd);
  short startDay; sds >> startDay;

  string day = get_day_of_week(current_time());    // This is a fix that doesn't account for days in a month but I don't want to make it do that

  string chosen = (global_mem + 4);                // What day did the user choose? Start at the next instance of that day
  startDay += (day_converter[chosen] - day_converter[day]);
  
  string sth = (global_mem + 340);
  stringstream sths(sth);
  int startTimeh; sths >> startTimeh;
  if((global_mem[395] == 'P' || global_mem[395] == '1') && global_mem[341] != '2'){startTimeh += 12;} // Add 12 hours if PM and not 12:00 PM
  if((global_mem[395] == 'A' || global_mem[395] == '0') && global_mem[341] == '2'){startTimeh = 0;}   // 0 hours if AM and not 12:00 AM

  string stm = (global_mem + 347);
  stringstream stms(stm);
  int startTimem; stms >> startTimem;
  int startTime = startTimem + startTimeh*60;


  string eth = (global_mem + 355);
  stringstream eths(eth);
  int endTimeh; eths >> endTimeh;
  if((global_mem[366] == 'P' || global_mem[366] == '1') && global_mem[356] != '2'){endTimeh += 12;}   // Add 12 hours if PM and not 12:00 PM
  if((global_mem[366] == 'A' || global_mem[366] == '0') && global_mem[356] == '2'){endTimeh = 0;}     // 0 hours if AM and 12:00 AM

  string etm = (global_mem + 362);
  stringstream etms(etm);
  int endTimem; etms >> endTimem;
  int endTime = endTimem + endTimeh*60;

  short priority = test.sizeEvents(); // This needs to be changed in the future (or does it?)

  string title = (global_mem + 315); 

  // Defaults
  string type = "Class";
  short repeats = 0;
  short maxRepeats = 20;
  string description = "This is a class";
  
  temp = new Event(startMonth, startDay, startYear, startTime, endTime, priority, type, title, description, repeats, maxRepeats);
  test.addEvent(temp);
  add_yaml("personalization.yaml");
}

// Build Expanded Output
void build_expanded(Person &user, Date &today, map<string,short>day_converter, map<short, string>num_converter) {
  string sleep = "Sleep";
  string event = "Event";
  string classwork = "ClassWork";
  string homework = "Homework";
  string exam = "Exam";
  string work = "Work";
  string clas = "Class";
  string other = "Other";
  string bre = "Breakfast";
  string lunch = "Lunch";
  string dinner = "Dinner";
  int k = 0;
  short m = day_converter[get_day_of_week(current_time())];
  for (int i = day_converter[get_day_of_week(current_time())]; i < (day_converter[get_day_of_week(current_time())] + 7); i++) {
    print_at(0 + 5 * k, num_converter[m].c_str());
    k = k + 1;
    m = m + 1;
    if (m > 6) {
      m = m - 7;
    }
  }
  add_yaml("expanded1.yaml");
  for(int j = 0; j < 7; j++) {
    if (j > 0) {
      today + 1;
    }

    add_yaml("expandedCalendarDay.yaml"); // adds the column into the larger box
    double eventTime = 0;
    double classWorkTime = 0;
    double workTime = 0;
    double sleepTime = 0;
    double eatingTime = 0;
    double classTime = 0;
    double otherTime = 0;
    double totalTime = 1440;
    for (int i = 0; i < user.sizeEvents(); i++){
      if((user[i]->getStartDay() == today.getDay()) && user[i]->getStartMonth() == today.getMonth() && user[i]->getStartYear() == today.getYear()) {
        double top_calc = user[i]->getStartTime();
        if(user[i]->getEventType() == event) {
          eventTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (eventTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 160}, {"g", 160}, {"b", 160}});
        }
        if((user[i]->getEventType() == classwork) || (user[i]->getEventType() == homework) || (user[i]->getEventType() == exam)) {
          classWorkTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (classWorkTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 60}, {"g", 60}, {"b", 60}});
        }
        if(user[i]->getEventType() == work) {
          workTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (workTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 200}, {"g", 50}, {"b", 50}});
        }
        if(user[i]->getEventType() == sleep) {
          sleepTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (sleepTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 90}, {"g", 90}, {"b", 220}});
        }
        if(user[i]->getEventType() == bre) {
          eatingTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (eatingTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 220}, {"g", 140}, {"b", 0}});
        }
        if(user[i]->getEventType() == lunch) {
          eatingTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (eatingTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 220}, {"g", 140}, {"b", 0}});
        }
        if(user[i]->getEventType() == dinner) {
          eatingTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (eatingTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 220}, {"g", 140}, {"b", 0}});
        }
        if(user[i]->getEventType() == clas) {
          classTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (classTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 130}, {"g", 200}, {"b", 50}});
        }
        if(user[i]->getEventType() == other) {
          otherTime += user[i]->getTimeSpend();
          add_yaml("expandedCalendarEvent.yaml", {{"h", (otherTime/totalTime * 100)}, {"t", (top_calc/1440) * 100}, {"r", 160}, {"g", 160}, {"b", 160}});
        }
      }
    }
  } 
}


// Main program

int main() {
    init();

    Date today;
    set_current_day(today);

    Person user;
    user.read_events();

    map<string,short>day_converter;
    day_converter["Sun"] = 0; day_converter["0"] = 0;
    day_converter["Mon"] = 1; day_converter["1"] = 1;
    day_converter["Tue"] = 2; day_converter["2"] = 2;
    day_converter["Wed"] = 3; day_converter["3"] = 3;
    day_converter["Thu"] = 4; day_converter["4"] = 4;
    day_converter["Fri"] = 5; day_converter["5"] = 5;
    day_converter["Sat"] = 6; day_converter["6"] = 6;

    map<short, string>num_converter;
    num_converter[0] = "Sun";
    num_converter[1] = "Mon";
    num_converter[2] = "Tue";
    num_converter[3] = "Wed";
    num_converter[4] = "Thu";
    num_converter[5] = "Fri";
    num_converter[6] = "Sat";

    if(just_starting()) {
      build_home(user, today);
    }else if (received_event()) {
      if(event_id_is("home")) {
        build_home(user, today);
      } else if(event_id_is("create")) {
        create(user, today);
      } else if(event_id_is("event")) {
        build_addEvent(); 
      } else if (event_id_is("person")) {
        build_personalization(user);
      } else if (event_id_is("add")) {
        add(day_converter, user);
      } else if (event_id_is("save")) {
        save(user, day_converter);
      } else if (event_id_is("picker")) {
        add_yaml("addEvent.yaml");
      } else if (event_id_is("picker1")) {
        add_yaml("personalization.yaml");
      }else if(event_id_is("expanded")) {
        build_expanded(user, today, day_converter, num_converter);
      }else if(event_id_is("priorities")) {
        build_home(user, today);
        print_at(0, "Big Brain");
      } else{build_home(user, today);}

    
    }
    user.write_events();
    quit();
}