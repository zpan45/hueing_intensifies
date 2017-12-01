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
    this->addWidget(new Wt::WText("Confirm Password: "));
    passwordConf = new WLineEdit(this);
    passwordConf->setEchoMode(Wt::WLineEdit::EchoMode::Password);
    this->addWidget(new Wt::WBreak());

    // add the first and last name entry text boxes
    this->addWidget(new Wt::WText("First Name: "));
    firstNameEdit = new WLineEdit(this);
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WText("\tLast Name: "));
    lastNameEdit = new WLineEdit(this);
    this->addWidget(new Wt::WBreak());

    // add the register button
    registerButton = new WPushButton("Register", this);
    registerButton->clicked().connect(this, &RegistrationWidget::createUser);
    
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    
    // set up a spot for an error message to be displayed
    //Wt::WText *errorText_ = new Wt::WText(this);
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
    

    if (usernameEdit->text().toUTF8() == "" || passwordEdit->text().toUTF8() == "" || passwordConf->text().toUTF8() == "" || firstNameEdit->text().toUTF8() == "" || lastNameEdit->text().toUTF8() == "" )
    {
        
        showError(true, "Can't register with an empty field! Make sure all fields are filled in and try again.");
        //errorText_->setText(Wt::WString("ERROR: Can't register with an empty field! Make sure all fields are filled in and try again."));
        //this->clearRegistration();
    }
    else
    {
        if( passwordEdit->text().toUTF8() != passwordConf->text().toUTF8() ) {
            showError(true, "The passwords entered do not match! Please try again.");
        }
        else{
            User newUser(usernameEdit->text().toUTF8(), passwordEdit->text().toUTF8(), firstNameEdit->text().toUTF8(), lastNameEdit->text().toUTF8());

            bool result = ::activeDB.DBFileManager::addNewUser(newUser);

            if(result)
            {
                showError(true, "User already exists. Please try with a different username.");
            }
            else
            {
                showError(false, newUser.constructGreetingString() + " Redirecting to Login screen...");
            }
        }
    }

}

/** Method that displays a dialogue box for errors (or successful registration).
* @brief Display an error message to the user.
* @param isError - a boolean to determine whether the message is an error or successful registration
* @param errorMessage - a string with which to construct the error message's body.
*/
void RegistrationWidget::showError(bool isError, string errorMessage) {
    Wt::WDialog errorText_;
    
    if(isError == true) {
        errorText_.setWindowTitle("ERROR");
    }
    else {
        errorText_.setWindowTitle("Hello!");
    }
    
    
    Wt::WText errMessage_(errorMessage, errorText_.contents());
    new Wt::WBreak(errorText_.contents());
    new Wt::WBreak(errorText_.contents());
    
    Wt::WPushButton confirm("Okay", errorText_.contents());
    
    confirm.clicked().connect(&errorText_, &Wt::WDialog::accept);
    
    if(errorText_.exec() == Wt::WDialog::Accepted) {
        
        if(isError == false) {
            Wt::WApplication::instance()->setInternalPath("/login", true);
        }
        
    }
}

/**
 * This method is to clear the widget after user has succesfully logged in.
 * @brief Clear Registration
 */
void RegistrationWidget::clearRegistration()
{
  std::cout << "Registration Widget Cleared" << std::endl;
}

