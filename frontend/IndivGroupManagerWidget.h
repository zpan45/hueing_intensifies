#ifndef INDIVGROUPMANAGERWIDGET_H
#define INDIVGROUPMANAGERWIDGET_H

#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>
#include <Wt/Http/Response>
#include <Wt/Http/Client>
#include <Wt/WLabel>
#include <Wt/WTemplate>
#include <Wt/WHBoxLayout>
#include <Wt/WGroupBox>
#include <Wt/WComboBox>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Array>

#include "Bridge.h"
#include "Group.h"

#define USERNAME "newdeveloper"
#define HTML_CLIENT_TIMEOUT 5
#define HTML_MESSAGE_CHECK 20 //check if message received every 100ms * HTML_MESSAGE_CHECK times
#define URL "http://localhost:8000/api/"

class IndivGroupManagerWidget: public Wt::WContainerWidget {

public:
    IndivGroupManagerWidget(const std::string &name, Bridge *b, Group *g, Wt::WContainerWidget *parent = 0);
    virtual ~IndivGroupManagerWidget();

private:
    Group *g;
    Bridge *b;
    Wt::WLineEdit *groupNameEdit_;
    bool requestSuccess;

    void showInformation();
    void displayLights();
    void update();
    bool updateGroup(int groupID);
    bool updateState(int groupID, bool on, int bri, int hue, int sat, int transTime);
    void connectUpdateGroup(int groupID);
    void connectUpdateState(int groupID, bool on, int bri, int hue, int sat, int transTime);
    void handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response);


};

#endif
