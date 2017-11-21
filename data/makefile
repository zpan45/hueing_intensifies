app : User.o Bridge.o Group.o Light.o DBFileManager.o testDB.o
	g++ -std=c++11 User.o Bridge.o Group.o Light.o DBFileManager.o testDB.o -o app -lboost_system -lboost_filesystem

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

DBFileManager.o: DBFileManager.cpp DBFileManager.h User.h
	g++ -std=c++11 -Wall -c DBFileManager.cpp

clean:
	\rm *.o app
	\rm -r USERS
	\rm -r Test_Dir