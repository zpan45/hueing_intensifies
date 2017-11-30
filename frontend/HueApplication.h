/**
 * @file HueApplication.h
 * Head file for HueApplication.cpp
 *
 * @brief Head file for HueApplication.cpp
 * @author Jacob Fryer (jfryer6)
 */

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
#include <Wt/WGroupBox>
#include <Wt/WDialog>
#include <Wt/WComboBox>
#include <vector>

#include "User.h"
#include "RegistrationWidget.h"
#include "LoginWidget.h"
#include "IndivBridgeManagerWidget.h"
#include "DBFileManager.h"

extern DBFileManager activeDB;

class HueApplication : public Wt::WApplication {
public:
    HueApplication(const Wt::WEnvironment& env);
    User* getCurrentUser();
    void setCurrentUser(User* u);
    void initialize();
    void finalize();
    
private:
    User *curUser_;
    
    void showMainPage();
    bool testLoggedInStatus();
    void goToLogIn();
    void loggedIn_(User u);
    void goToRegister();
    void signOut();
    
    void displayBridges();
    void addBridge();
    void dialogueDone(Wt::WDialog::DialogCode code);
    void handleRequest();
};

#endif