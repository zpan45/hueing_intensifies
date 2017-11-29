// This may look like C code, but it's really -*- C++ -*-
/* 
 * Copyright (C) 2011 Emweb bvba, Heverlee, Belgium
 *
 * See the LICENSE file for terms of use.
 */

#ifndef REGISTRATION_WIDGET_H_
#define REGISTRATION_WIDGET_H_
#define _GLIBCXX_USE_CXX11_ABI 1
#include <vector>

#include <Wt/WContainerWidget>
#include "User.h"
#include "DBFileManager.h"
#include "HueApplication.h"

class RegistrationWidget: public Wt::WContainerWidget
{
public:
    RegistrationWidget(const std::string &name, Wt::WContainerWidget *parent = 0);

private:
    Wt::WText        *title;
    Wt::WPushButton  *registerButton;
    std::string 		name_;
    Wt::WLineEdit *usernameEdit;
    Wt::WLineEdit *passwordEdit;
    Wt::WLineEdit *firstNameEdit;
    Wt::WLineEdit *lastNameEdit;
    

    void createUser();
    void clearRegistration();
};

#endif //REGISTRATION_WIDGET_H_
