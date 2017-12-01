/**
 * @file IndivLightManagerWidget.h
 * Head file for IndivLightManagerWidget.cpp
 *
 * @brief Head file for IndivLightManagerWidget.cpp
 * @author Zhengyang Pan (zpan45)
 */

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
#include <Wt/WComboBox>
#include <Wt/WHBoxLayout>

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
    Wt::WLineEdit *nameEdit_;
    Wt::WComboBox *onOffSwitch_;
    Wt::WLineEdit *brightnessEdit_;
    Wt::WLineEdit *hueEdit_;
    Wt::WLineEdit *satEdit_;
    
    
    void showInformation();
    
    bool rename(std::string newname);
    void update();
    void connectRename(std::string newname);
    void connectSwitchOnOff(bool active);
    void connectUpdate();
    void connectUpdate(int transTime);
    void handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response);

};
#endif //INDIVLIGHTMANAGERWIDGET_H
