/**
 * @file RegistrationWidget.h
 * Registration Widget head file.
 *
 * @brief Registration Widget head file.
 * @author Team 24
 * @date November 09, 2017
 */

#ifndef REGISTRATION_WIDGET_H_
#define REGISTRATION_WIDGET_H_
#define _GLIBCXX_USE_CXX11_ABI 1
#include <vector>

#include <Wt/WContainerWidget>
#include "User.h"

class RegistrationWidget: public Wt::WContainerWidget
{
public:
  RegistrationWidget(const std::string &name, Wt::WContainerWidget *parent = 0);

private:
  Wt::WText        *title;
  Wt::WPushButton  *registerButton;
  std::string 		name_;

//  User createUser(std::string &username, std::string &password, std::string &firstname, std::string &lastname);
  void clearRegistration();
};

#endif //REGISTRATION_WIDGET_H_
