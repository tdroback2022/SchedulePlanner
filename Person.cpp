#include "Person.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


// ################
// ##Other things##
// ################

void read_stream(ifstream &f, char *array, int max_size) {
  int num_bytes;
  if (f.good()) {
    f.read(array, max_size);
    if (f) {
      cerr << "Warning in read_stream:  did not reach end of stream after " << max_size << " characters.";
      num_bytes = max_size - 1;
    } else {
      num_bytes = f.gcount();
      if (num_bytes >= max_size) num_bytes = max_size - 1;
    }
  } else {
    // cerr << "Warning in read_stream: unable to read anything\n";
    num_bytes = 0;
  }
  array[num_bytes] = 0;  // assign null at end
}

void read_file(const char *fname, char *array, int max_size) {
  ifstream f(fname);
  read_stream(f, array, max_size);
  f.close();
}

void Person::write_events(){

    // Create the fstream and get the vector size
    ofstream f("events.txt");
    int size = e.size();

    // Write event detials into a file, each event taking up <TO BE DETERMINED> bytes
    for(int i = 0; i < size; ++i){
        // The first 150 bytes of memory will be for general event details
        f.write(to_string(e[i]->getStartYear()).c_str(), 5);
        f.write(to_string(e[i]->getStartMonth()).c_str(), 5);
        f.write(to_string(e[i]->getStartDay()).c_str(), 5);
        f.write(to_string(e[i]->getStartTime()).c_str(),5);
        f.write(to_string(e[i]->getEndTime()).c_str(),5);
        f.write(to_string(e[i]->getPriority()).c_str(),5);
        f.write(e[i]->getEventType().c_str(), 10);
        f.write(e[i]->getTitle().c_str(), 20);
        f.write(e[i]->getDescription().c_str(), 80);
        f.write(to_string(e[i]->getRepeats()).c_str(),5);
        f.write(to_string(e[i]->getMaxRepeats()).c_str(),5);

        // 50 more bytes of either garbage or classwork values
        if(e[i]->getEventType() == "ClassWork" || e[i]->getEventType() == "Homework" || e[i]->getEventType() == "Exam"){
            f.write(to_string(e[i]->getDueYear()).c_str(), 5);
            f.write(to_string(e[i]->getDueMonth()).c_str(), 5);
            f.write(to_string(e[i]->getDueDay()).c_str(), 10);
            f.write(to_string(e[i]->getExam()).c_str(), 30);
        }
        else{
            string tildes = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            f.write(tildes.c_str(), 50);
        }
    }
    f.close();
}

// read_events will take all the information in events.txt and create a Person out of it
void Person::read_events(){
    char events[10000];
    read_file("events.txt", events, 10000);
    Event *temp;
    for(int i = 0; i < 10000; i += 200){
        char check = events[i];
        int int_check = check - '0';
        if(int_check >= 0 && int_check <= 9){ // Check if a valid year

        string sy = (events + i);           // Create temporary variables and reinterpret file data
        stringstream sys(sy);
        short startYear; sys >> startYear;

        string sm = (events + i + 5);
        stringstream sms(sm);
        short startMonth; sms >> startMonth;

        string sd = (events + i + 10);
        stringstream sds(sd);
        short startDay; sds >> startDay;

        string st = (events + i + 15);
        stringstream sts(st);
        int startTime; sts >> startTime;

        string et = (events + i + 20);
        stringstream ets(et);
        int endTime; ets >> endTime;

        string p = (events + i + 25);
        stringstream ps(p);
        short priority; ps >> priority;

        string eventType = (events + i + 30);

        string title = (events + i + 40); 

        string description = (events + i + 60);  
        
        string r = (events + i + 140);
        stringstream rs(r);
        short repeats; rs >> repeats;

        string mr = (events + i + 145);
        stringstream mrs(mr);
        short maxRepeats; mrs >> maxRepeats;
        
        if (events[i + 150] != '~') {       // Is this a classwork?
            
            string dy = (events + i + 150); // Create extra temporary variables and reinterpret file data
            stringstream dys(dy);
            short dueYear; dys >> dueYear;

            string dm = (events + i + 155);
            stringstream dms(dm);
            short dueMonth; dms >> dueMonth;

            string dd = (events + i + 160);
            stringstream dds(dd);
            short dueDay; dds >> dueDay;

            string e = (events + i + 170);
            stringstream es(e);
            bool exam; es >> exam;

            // Create a new ClassWork object and add it to person
            temp = new ClassWork(startMonth, startDay, startYear, startTime, endTime, priority, eventType, title, description, repeats, maxRepeats, dueYear, dueMonth, dueDay, exam);
            addEvent(temp);
        }

        else{
            // If just a regular event, create Event object and add it to person
            temp = new Event(startMonth, startDay, startYear, startTime, endTime, priority, eventType, title, description, repeats, maxRepeats);
            addEvent(temp);
        }
    }
    else{break;}  // If the next start index isn't valid, break out of for loop
  }
}