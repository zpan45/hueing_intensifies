/**
 * @file RegistrationWidget.cpp
 * Registration Widget.
 *
 * @brief Registration Widget.
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
<<<<<<< HEAD
using namespace std;
/*
 * Registration Widget
 */
=======

>>>>>>> 0adfd87997488bc2647c9f9beb13b39f65f6546d

/**
 * Initializes and constructs the Registration Widget to be called by Hue main application.
 * @param name Username used for registration as a String
 */
RegistrationWidget::RegistrationWidget(const std::string &name, WContainerWidget *parent)
: WContainerWidget(parent), name_(name)
{
  setContentAlignment(AlignCenter);
//  setTitle("Registration Widget");

  registerButton = new WPushButton("Registration", this);
  registerButton->clicked().connect(this, &RegistrationWidget::clearRegistration);
  // userNameEdit = new WLineEdit(root());                     // allow text input
  // userNameEdit->setFocus();                                 // give focus

  // passWordEdit = new WLineEdit(root());
  // passWordEdit->setFocus();


  // WPushButton *loginButton
  //   = new WPushButton("Login", root());              // create a button
  // loginButton->setMargin(5, Top);                            // add 5 pixels margin
  // loginButton->setStyleClass("btn-primary");

  // WPushButton *signUpButton = new WPushButton("Sign Up", root());
  // signUpButton->setMargin(100, Bottom);


  // loginButton->clicked().connect(this, &WLoginWidgetApplication::greet);
  // userNameEdit->enterPressed().connect
  //   (boost::bind(&WLoginWidgetApplication::greet, this));
}

<<<<<<< HEAD
/*This method is to create User after the user of programmer enters
 *their information.
*/
/*User RegistrationWidget::createUser(std::string &userName, std::string &firstName, std::string &lastName, std::string &password)
=======
/**
 * This method is to create User after the user of programmer enters their information.
 * @param userName Username used to create User as a String
 * @param firstName First name used to create User as a String
 * @param lastName Last name used to create User as a String
 * @param password Password used to create User as a String
 * @return the User object created.
 */
User RegistrationWidget::createUser(string userName, string firstName, string lastName, string password)
>>>>>>> 0adfd87997488bc2647c9f9beb13b39f65f6546d
{
  User *newUser = new User(userName, password, firstName, lastName);
  
  return *newUser;
}

<<<<<<< HEAD
/*This method is to clear the widget after user has succesfully logged in.
*/
void RegistrationWidget::clearRegistration()
{
  std::cout << "Registration Widget Cleared";
}
=======

/**
 * This method is to clear the widget after user has successfully logged in.
 */
void clearRegistration
{
  root()->clear()

};
>>>>>>> 0adfd87997488bc2647c9f9beb13b39f65f6546d

