frontend : User.o Bridge.o Group.o Light.o HueApplication.o RegistrationWidget.o LoginWidget.o IndivBridgeManagerWidget.o
	g++ -std=c++11 User.o Bridge.o Group.o Light.o HueApplication.o RegistrationWidget.o LoginWidget.o IndivBridgeManagerWidget.o -o frontend -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time

User.o: User.cpp User.h Bridge.h
	g++ -std=c++11 -Wall -c User.cpp

Bridge.o: Bridge.cpp Bridge.h Group.h
	g++ -std=c++11 -Wall -c Bridge.cpp

Group.o: Group.cpp Group.h Light.h
	g++ -std=c++11 -Wall -c Group.cpp

Light.o: Light.cpp Light.h
	g++ -std=c++11 -Wall -c Light.cpp

HueApplication.o: HueApplication.cpp HueApplication.h User.h RegistrationWidget.h LoginWidget.h
	g++ -std=c++11 -Wall -c HueApplication.cpp

RegistrationWidget.o: RegistrationWidget.cpp RegistrationWidget.h User.h
	g++ -std=c++11 -Wall -c RegistrationWidget.cpp

LoginWidget.o: LoginWidget.cpp LoginWidget.h User.h
	g++ -std=c++11 -Wall -c LoginWidget.cpp

IndivBridgeManagerWidget.o: IndivBridgeManagerWidget.cpp IndivBridgeManagerWidget.h Bridge.h
	g++ -std=c++11 -Wall -c IndivBridgeManagerWidget.cpp

clean:
	\rm *.o frontend