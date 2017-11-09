app : User.o Bridge.o Group.o Light.o testDB.o
	g++ -std=c++11 User.o Bridge.o Group.o Light.o testDB.o -o app
    
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

clean:
	\rm *.o app