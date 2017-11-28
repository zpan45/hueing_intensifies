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

#include "Group.h"

#define USERNAME "newdeveloper"
#define HTML_CLIENT_TIMEOUT 5
#define HTML_MESSAGE_CHECK 20 //check if message received every 100ms * HTML_MESSAGE_CHECK times
#define URL "http://localhost:8000/api/"

class IndivGroupManagerWidget: public Wt::WContainerWidget {

public:
    IndivGroupManagerWidget(const std::string &name, Group *g, Wt::WContainerWidget *parent = 0);
    virtual ~IndivGroupManagerWidget();

private:
    Group *g;
    Wt::WLineEdit *groupNameEdit_;
    
    void showInformation();
    void displayLights();
    void update();
    //void handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response, Group *g) const;
};

#endif
