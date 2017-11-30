/**
 * @class LoginWidget
 * Allows user to log in with his/her username and password.
 *
 * @brief Login Widget.
 * @author Team 24
 * @date November 09, 2017
 */

#define _GLIBCXX_USE_CXX11_ABI 1
#include "LoginWidget.h"

using namespace Wt;
using namespace std;

/**
 * Initializes and constructs the Login Widget to be called by
 * Hue main application.
 * @brief Login Widget
 */
LoginWidget::LoginWidget(const std::string &name, WContainerWidget *parent)
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

    // add the login button
    loginButton = new WPushButton("Login", this);

    // add a display area for login confirmation
    loginDisplay = new Wt::WContainerWidget;
    this->addWidget(loginDisplay);

    loginButton->clicked().connect(this, &LoginWidget::login);
}

/**
 * Return LoggedIn signal
 * @brief Logged In
 * @return W::Signal<User>& LoggedIn Signal
 */
Wt::Signal<User>& LoginWidget::loggedIn(){
    return loggedInSignal_;
}

/**
 * Gets a User object by its username.
 * @brief Get User by Username
 * @param username String username
 * @return User object with this username
 */
User LoginWidget::getUserByUsername(Wt::WString username) {
    //User testUser("mkatchab@csd.uwo.ca", "testPW", "Mike", "Katchabaw");
    User currentUser = ::activeDB.DBFileManager::getUser(username.toUTF8());
    // set the password to be the hashed version of the string "testPW"
    //testUser.setPassword( testUser.hashPassword( testUser.getPassword() ) );

    if( (username.toUTF8() == currentUser.getUsername()) ) {
        return currentUser;
    }
    else {
        User u;
        return u;
    }
}

/**
 * Method that takes an existing User object (as defined in getUserByUsername()) and a
 * password entered by the User and checks them (or rather, their hashes) against each other.
 * @brief Check Password
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

/**
 * This method is to clear the widget after user has succesfully logged in.
 * @brief Login
 */
void LoginWidget::login() {
    loginDisplay->clear();

    User u = getUserByUsername(usernameEdit->text());

    loginDisplay->addWidget(new Wt::WBreak());
    loginDisplay->addWidget(new Wt::WBreak());
    loginDisplay->addWidget(new Wt::WBreak());

    if(u.getUsername() != "") {
            std::cout << "Stored password: " << u.getPassword() << std::endl;
            std::cout << "Entered password: " << u.hashPassword(passwordEdit->text().toUTF8()) << std::endl;
            std::cout << "Entered and hashed: " << u.hashPassword(passwordEdit->text().toUTF8()) << std::endl;
        if(checkPassword(u, passwordEdit->text()) == true) {
            loginDisplay->addWidget(new Wt::WText(u.constructGreetingString()));
            loggedInSignal_.emit(u);
        }
        else {
            loginDisplay->addWidget(new Wt::WText("ERROR: The entered password did not match!"));
        }
    }
    else {
        loginDisplay->addWidget(new Wt::WText("ERROR: The entered Username was invalid!"));
    }
}
