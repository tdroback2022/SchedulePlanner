#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"
#include "Event.h"
#include "Person.h"
#include <sstream>
// #include"../react.h"
using namespace std;

const char *get_current_day(long t_raw)
{
  time_t t = t_raw/1000;
  static char res[100];
  strftime(res, sizeof(res), "%d", localtime(&t));
  return res;
}


int main() {

  Person dude;
  dude.write_events();

}

