/**
 * @class RegistrationWidget
 * Allows user to register with his/her username and password.
 *
 * @brief Login Widget.
 * @author Team 24
 * @date November 09, 2017
 */

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


/**
 * Initializes and constructs the Registration Widget to be called by
 * Hue main application.
 */
RegistrationWidget::RegistrationWidget(const std::string &name, User* current, WContainerWidget *parent)
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
    passwordEdit->setEchoMode(Wt::WLineEdit::EchoMode::Password);
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

/**
 * This method is to create User after the user of program enters
 * their information.
 * @brief Create User
 *
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

    User *u;

    u = &newUser;

    this->addWidget(new Wt::WText( newUser.constructGreetingString() ));
}

/**
 * This method is to clear the widget after user has succesfully logged in.
 * @brief Clear Registration
 */
void RegistrationWidget::clearRegistration()
{
  std::cout << "Registration Widget Cleared" << std::endl;
}

