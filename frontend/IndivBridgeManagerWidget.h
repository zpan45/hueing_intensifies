//
// Created by Peter on 2017/11/21.
//

#ifndef INDIVBRIDGEMANAGERWIDGET_H
#define INDIVBRIDGEMANAGERWIDGET_H

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

#include "Bridge.h"

#define USERNAME "newdeveloper";
#define URL "http://localhost:8000/api/";

using namespace std;
using namespace Wt;

class IndivBridgeManagerWidget: public Wt::WContainerWidget {

public:
    IndivBridgeManagerWidget(const std::string &name, Wt::WContainerWidget *parent = 0);
    virtual ~IndivBridgeManagerWidget();
    bool checkBridge(Bridge b, string uName);


private:
    void connect();
    void connect(Bridge b, string uName);
    bool handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,const Wt::Http::Message& response) const;
    string currentStatus="";
};

#endif
