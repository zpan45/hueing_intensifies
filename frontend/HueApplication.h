#ifndef _hueapp_h_included
#define _hueapp_h_included

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WException>
#include <Wt/WServer>

#include "User.h"
#include "RegistrationWidget.h"

class HueApplication : public Wt::WApplication {
public:
    HueApplication(const Wt::WEnvironment& env);

private:
    User *curUser_ = nullptr;
    
    bool testLoggedInStatus();
    void goToLogIn();
    void goToRegister();
};

#endif