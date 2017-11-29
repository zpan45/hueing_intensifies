#ifndef LOGIN_WIDGET_H_
#define LOGIN_WIDGET_H_

#include <vector>
#include <iostream>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>
#include <Wt/WSignal>

#include "User.h"
#include "HueApplication.h"

class LoginWidget: public Wt::WContainerWidget
{
public:
    LoginWidget(const std::string &name, User* current, Wt::WContainerWidget *parent = 0);
    Wt::Signal<User>& loggedIn();

private:
    Wt::WText        *title;
    Wt::WPushButton  *loginButton;
    std::string 		name_;
    Wt::WContainerWidget *loginDisplay;
    Wt::WLineEdit *usernameEdit;
    Wt::WLineEdit *passwordEdit;
    User* cur;
    
    Wt::Signal<User> loggedInSignal_;

    User getUserByUsername(Wt::WString username);
    bool checkPassword(User u, Wt::WString passInput);
    void login();
};

#endif
