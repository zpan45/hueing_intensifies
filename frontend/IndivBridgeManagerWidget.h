//
// Created by Peter on 2017/11/21.
//

#ifndef INDIVBRIDGEMANAGERWIDGET_H
#define INDIVBRIDGEMANAGERWIDGET_H

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

#include "Bridge.h"

#define USERNAME "newdeveloper"
#define HTML_CLIENT_TIMEOUT 5
#define HTML_MESSAGE_CHECK 10 //check if message received every 100ms * HTML_MESSAGE_CHECK times
#define URL "http://localhost:8000/api/"

class IndivBridgeManagerWidget: public Wt::WContainerWidget {

public:
    IndivBridgeManagerWidget(const std::string &name, Bridge *b, Wt::WContainerWidget *parent = 0);
    virtual ~IndivBridgeManagerWidget();
    bool checkBridge(Bridge b, std::string uName);


private:
    Bridge *b;
    Wt::WLineEdit *bridgeNameEdit_;
    Wt::WLineEdit *bridgeLocationEdit_;
    Wt::WLineEdit *hostNameEdit_;
    Wt::WLineEdit *portNumEdit_;
    
    void connect();
    void connect(Bridge b, std::string uName);
    void displayGroups(Bridge b);
    void update(Bridge *b);
    //bool handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,const Wt::Http::Message& response) const;
};

#endif
