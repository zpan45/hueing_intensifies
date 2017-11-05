app : User.o Bridge.o Group.o Light.o
	g++ User.o Bridge.o Group.o Light.o -o app
    
User.o: User.cpp User.h Bridge.h
	g++ -Wall -c User.cpp

Bridge.o: Bridge.cpp Bridge.h Group.h
	g++ -Wall -c Bridge.cpp

Group.o: Group.cpp Group.h Light.h
	g++ -Wall -c Group.cpp

Light.o: Light.cpp Light.h
	g++ -Wall -c Light.cpp

clean:
	\rm *.o app