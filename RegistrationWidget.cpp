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


RegistrationWidget::RegistrationWidget(const std::string &name)
  :WContainerWidget(), name_(name) 
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

User RegistrationWidget::createUser(string userName, string firstName, string lastName, string password)
{
  User *newUser = new User();
  newUser->setUsername(userName);
  newUser->setFirstName(firstName);
  newUser->setLastName(lastName);
  newUser->setPassword(password);
  
  return User;
}

void clearRegistration
{
  root()->clear();
}

