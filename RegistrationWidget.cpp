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

/*
 * Registration Widget
 */


/*
 *Intializes and constructs the Registration Widget to be called by 
 *Hue main application. 
 */
RegistrationWidget::RegistrationWidget(const std::string& name)
: WContainerWidget(), name_(name)
{
  setContentAlignment(AlignmentFlag::Center);
  setTitle("Registration Widget");                              

  registerButton = addWidget(std::make_unique<WPushButton>(tr("Registration")));
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
User RegistrationWidget::createUser(string userName, string firstName, string lastName, string password)
{
  User *newUser = new User(userName, password, firstName, lastName);
  
  return User;
}

/*This method is to clear the widget after user has succesfully logged in.
*/
void clearRegistration
{
  root()->clear();
}

