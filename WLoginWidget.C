/**
 * @file WLoginWidget.cpp
 * Login Widget.
 *
 * @brief Login Widget.
 * @author Team 24
 * @date November 09, 2017
 */

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
 * Login Widget
 */


/*
 *Intializes and constructs the Login Widget to be called by
 *Hue main application.
 */
WLoginWidget::WLoginWidget(const std::string &name, WContainerWidget *parent)
: WContainerWidget(parent), name_(name)
{
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

  // add the register button
  loginButton = new WPushButton("Login", this);
  loginButton->clicked().connect(this, &RegistrationWidget::login);

}

/*This method is to create User after the user of programmer enters
 *their information.
 */

/*This method is to clear the widget after user has succesfully logged in.
*/
void WLoginWidget::login()
{
  std::cout << "Login Widget Cleared";
}
