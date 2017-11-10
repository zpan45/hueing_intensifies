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

/*This method is to create User after the user of programmer enters
 *their information.
*/
/*User RegistrationWidget::createUser(std::string &userName, std::string &firstName, std::string &lastName, std::string &password)
{
  User *newUser = new User(userName, password, firstName, lastName);
  
  return *newUser;
}

/** This method is to clear the widget after user has succesfully logged in.
*/
void RegistrationWidget::clearRegistration()
{
  std::cout << "Registration Widget Cleared" << std::endl;
}

