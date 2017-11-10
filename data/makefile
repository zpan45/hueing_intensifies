app : User.o Bridge.o Group.o Light.o HueApplication.o
	g++ -std=c++11 User.o Bridge.o Group.o Light.o HueApplication.o -o app -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time

User.o: User.cpp User.h Bridge.h
	g++ -std=c++11 -Wall -c User.cpp

Bridge.o: Bridge.cpp Bridge.h Group.h
	g++ -std=c++11 -Wall -c Bridge.cpp

Group.o: Group.cpp Group.h Light.h
	g++ -std=c++11 -Wall -c Group.cpp

Light.o: Light.cpp Light.h
	g++ -std=c++11 -Wall -c Light.cpp

testDB.o: testDB.cpp
	g++ -std=c++11 -Wall -c testDB.cpp

HueApplication.o: HueApplication.cpp HueApplication.h User.h
	g++ -std=c++11 -Wall -c HueApplication.cpp

clean:
	\rm *.o app