//
// Created by peter on 11/27/17.
//

#ifndef INDIVLIGHTMANAGERWIDGET_H
#define INDIVLIGHTMANAGERWIDGET_H

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
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "Bridge.h"
#include "Light.h"

#define HTML_CLIENT_TIMEOUT 5
#define HTML_MESSAGE_CHECK 20 //check if message received every 100ms * HTML_MESSAGE_CHECK times

class IndivLightManagerWidget: public Wt::WContainerWidget {

public:
    IndivLightManagerWidget(const std::string &name, Bridge *b, Light *l, Wt::WContainerWidget *parent = 0);
    virtual ~IndivLightManagerWidget();



private:
    Bridge *b;
    Light *l;
    bool requestSuccess;
    bool rename(std::string newname);
    bool update();
    void connectRename(std::string newname);
    void connectUpdate();
    void handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response);

};
#endif //INDIVLIGHTMANAGERWIDGET_H
