// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2011 Emweb bvba, Heverlee, Belgium
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LOGIN_WIDGET_H_
#define LOGIN_WIDGET_H_
#define _GLIBCXX_USE_CXX11_ABI 1
#include <vector>

#include <Wt/WContainerWidget>
#include "User.h"

class WLoginWidget: public Wt::WContainerWidget
{
public:
    WLoginWidget(const std::string &name, Wt::WContainerWidget *parent = 0);

private:
    Wt::WText        *title;
    Wt::WPushButton  *loginButton;
    Wt::WLineEdit *usernameEdit;
    Wt::WLineEdit *passwordEdit;


    void login();
};

#endif //REGISTRATION_WIDGET_H_
