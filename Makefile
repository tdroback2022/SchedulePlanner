test: Date.o Event.o Test.o Person.o
	g++ -g -Wall -std=c++11 -o test Date.o Event.o Test.o Person.o

Test.o: Test.cpp
	g++ -g -Wall -std=c++11 -c Test.cpp

Date.o: Date.cpp Date.h
	g++ -g -Wall -std=c++11 -c Date.cpp

Event.o: Event.cpp Event.h
	g++ -g -Wall -std=c++11 -c Event.cpp

Person.o: Person.h Person.cpp
	g++ -g -Wall -std=c++11 -c Person.cpp

a.out: app.o Date.o Event.o Person.o
	g++ -g -Wall -std=c++11 -o a.out ~/react.o Date.o Event.o app.o Person.o -lcurl

app.o: app.cpp
	g++ -g -Wall -std=c++11 -c app.cpp