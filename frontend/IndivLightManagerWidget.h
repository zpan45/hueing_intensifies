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

#include "Light.h"

class IndivLightManagerWidget: public Wt::WContainerWidget {

public:
    IndivLightManagerWidget(const std::string &name, Light *l, Wt::WContainerWidget *parent = 0);
    virtual ~IndivLightManagerWidget();



private:
    Light *l;

};
#endif //INDIVLIGHTMANAGERWIDGET_H
