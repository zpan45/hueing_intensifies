#define _GLIBCXX_USE_CXX11_ABI 1
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>

#include "User.h"
#include "RegistrationWidget.h"

using namespace Wt;
using namespace std;
/*
 * Registration Widget
 */


/** Initializes and constructs the Registration Widget to be called by
 * Hue main application.
 */
RegistrationWidget::RegistrationWidget(const std::string &name, WContainerWidget *parent)
: WContainerWidget(parent), name_(name) {
    setContentAlignment(AlignCenter);

    // add the Username entry textbox
    this->addWidget(new Wt::WText("Username: "));
    usernameEdit = new WLineEdit(this);
    usernameEdit->setFocus(); // set the focus to be on this textbox
    this->addWidget(new Wt::WBreak());

    // add the Password entry textbox
    this->addWidget(new Wt::WText("Password: "));
    passwordEdit = new WLineEdit(this);
    this->addWidget(new Wt::WBreak());

    // add the first and last name entry text boxes
    this->addWidget(new Wt::WText("First Name: "));
    firstNameEdit = new WLineEdit(this);
    this->addWidget(new Wt::WText("\tLast Name: "));
    lastNameEdit = new WLineEdit(this);
    this->addWidget(new Wt::WBreak());

    // add the register button
    registerButton = new WPushButton("Register", this);
    registerButton->clicked().connect(this, &RegistrationWidget::createUser);
}

/** This method is to create User after the user of program enters
* their information.
* @todo - Validate that the User has filled out all four fields
* @todo - Ensure that User has entered a valid email address as a username string
* @todo - Hide password string
* @todo - Return the User object somewhere for use in the rest of the app
*/
void RegistrationWidget::createUser() {
    User newUser(usernameEdit->text().toUTF8(), passwordEdit->text().toUTF8(), firstNameEdit->text().toUTF8(), lastNameEdit->text().toUTF8());

    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());

    ::activeDB.DBFileManager::addNewUser(newUser);
    ::activeDB.DBFileManager::saveUser(newUser);

    this->addWidget(new Wt::WText( newUser.constructGreetingString() ));
}

/** This method is to clear the widget after user has succesfully logged in.
*/
void RegistrationWidget::clearRegistration()
{
  std::cout << "Registration Widget Cleared" << std::endl;
}

