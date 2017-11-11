#define _GLIBCXX_USE_CXX11_ABI 1
/**
 * @file LoginWidget.cpp
 * Login Widget.
 *
 * @brief Login Widget.
 * @author Team 24
 * @date November 09, 2017
 */

#include "LoginWidget.h"

using namespace Wt;
using namespace std;
/*
 * Login Widget
 */


/**
 *Intializes and constructs the Login Widget to be called by
 *Hue main application.
 */
LoginWidget::LoginWidget(const std::string &name, WContainerWidget *parent)
: WContainerWidget(parent), name_(name) {
    setContentAlignment(AlignCenter);
    
    // ====================================== // 
    // !! NOTE: This is only for Stage 2!     //
    // ====================================== //
    this->addWidget(new Wt::WText("For the purposes of this stage, the 'valid' User information is as follows:"));
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WText("Username: mkatchab@csd.uwo.ca"));
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WText("Password: testPW"));
    // ====================================== //
    
    
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    
    // add the Username entry textbox
    this->addWidget(new Wt::WText("Username: "));
    usernameEdit = new WLineEdit(this);
    usernameEdit->setFocus(); // set the focus to be on this textbox
    this->addWidget(new Wt::WBreak());

    // add the Password entry textbox
    this->addWidget(new Wt::WText("Password: "));
    passwordEdit = new WLineEdit(this);
    this->addWidget(new Wt::WBreak());

    // add the login button
    loginButton = new WPushButton("Login", this);
    
    // add a display area for login confirmation
    loginDisplay = new Wt::WContainerWidget;
    this->addWidget(loginDisplay);
    
    loginButton->clicked().connect(this, &LoginWidget::login);
}

User LoginWidget::getUserByUsername(Wt::WString username) {
    User testUser("mkatchab@csd.uwo.ca", "testPW", "Mike", "Katchabaw");
    
    // set the password to be the hashed version of the string "testPW"
    testUser.setPassword( testUser.hashPassword( testUser.getPassword() ) );
    
    if( (username.toUTF8() == testUser.getUsername()) ) {
        return testUser;
    }
    else {
        User u;
        return u;
    }
}

/** Method that takes an existing User object (as defined in getUserByUsername()) and a
* password entered by the User and checks them (or rather, their hashes) against each other.
*
* @param u - A User object to test the password against.
* @param passInput - A string that contains the password to check against the User's password.
* @return boolean - Returns whether the input password is the same as the User's stored password.
*/
bool LoginWidget::checkPassword(User u, Wt::WString passInput) {
    if( u.hashPassword(passInput.toUTF8()) == u.getPassword() ) {
        return true;
    }
    else {
        return false;
    }
}

/**This method is to clear the widget after user has succesfully logged in.
*/
void LoginWidget::login() {
    loginDisplay->clear();
    
    //string uNameString = usernameEdit->text().value();
    //stringstream s(uNameString);
    
    User u = getUserByUsername(usernameEdit->text());
    
    loginDisplay->addWidget(new Wt::WBreak());
    loginDisplay->addWidget(new Wt::WBreak());
    loginDisplay->addWidget(new Wt::WBreak());
    
    if(u.getUsername() != "") {
        //string pwString = passwordEdit->text().toUTF8();
        //stringstream ss(pwString);
        if(checkPassword(u, passwordEdit->text()) == true) {
            loginDisplay->addWidget(new Wt::WText(u.constructGreetingString()));
        }
        else {
            loginDisplay->addWidget(new Wt::WText("ERROR: The entered password did not match!"));
        }
    }
    else {
        loginDisplay->addWidget(new Wt::WText("ERROR: The entered Username was invalid!"));
    }
}
