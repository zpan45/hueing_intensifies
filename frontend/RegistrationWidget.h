/**
 * @file RegistrationWidget.h
 * Head file for RegistrationWidget.cpp
 *
 * @brief Head file for RegistrationWidget.cpp
 * @author Jacob Fryer (jfryer6)
 */

#ifndef REGISTRATION_WIDGET_H_
#define REGISTRATION_WIDGET_H_
#define _GLIBCXX_USE_CXX11_ABI 1
#include <vector>

#include <Wt/WContainerWidget>
#include <Wt/WDialog>
#include "User.h"
#include "DBFileManager.h"
#include "HueApplication.h"

class RegistrationWidget: public Wt::WContainerWidget
{
public:
    RegistrationWidget(const std::string &name, User* current, Wt::WContainerWidget *parent = 0);

private:
    Wt::WText        *title;
    Wt::WPushButton  *registerButton;
    std::string 		name_;
    Wt::WLineEdit *usernameEdit;
    Wt::WLineEdit *passwordEdit;
    Wt::WLineEdit *passwordConf;
    Wt::WLineEdit *firstNameEdit;
    Wt::WLineEdit *lastNameEdit;

    void createUser();
    void showError(bool isError, std::string errorMessage);
    void clearRegistration();
};

#endif //REGISTRATION_WIDGET_H_
