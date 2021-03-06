/**
 * @file IndivBridgeManagerWidget.h
 * Head file for IndivBridgeManagerWidget.cpp
 *
 * @brief Head file for IndivBridgeManagerWidget.cpp
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 */

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
#include <Wt/WHBoxLayout>
#include <Wt/WGroupBox>
#include <Wt/WComboBox>
#include <Wt/WDialog>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Array>
#include <Wt/WSelectionBox>

#include "Bridge.h"
#include "IndivGroupManagerWidget.h"

#define USERNAME "newdeveloper"
#define HTML_CLIENT_TIMEOUT 5
#define HTML_MESSAGE_CHECK 20 //check if message received every 100ms * HTML_MESSAGE_CHECK times
#define URL "http://localhost:8000/api/"

class IndivBridgeManagerWidget: public Wt::WContainerWidget {

public:
    IndivBridgeManagerWidget(const std::string &name, Bridge *b, Wt::WContainerWidget *parent = 0);
    virtual ~IndivBridgeManagerWidget();

private:
    Bridge *b;
    Wt::WLineEdit *bridgeNameEdit_;
    Wt::WLineEdit *bridgeLocationEdit_;
    Wt::WLineEdit *hostNameEdit_;
    Wt::WLineEdit *portNumEdit_;
    //bool requestSuccess;
    Wt::WGroupBox *groupbox; // display area
    
    
    void connect();
    void showInformation();
    void displayGroups();
    //void showAllLights();
    void addGroupToBridge();
    
    void update();
    void handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response) const;
    bool updateLights();
    bool updateGroups();
    void connectCreateGroup(std::string name);
    void connectDeleteGroup(int groupID);
    void handleHttpResponseGroup(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message& response);
};

#endif
