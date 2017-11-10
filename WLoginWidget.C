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

using namespace Wt;

/**
 * Phillips Hue
 */
class WLoginWidgetApplication : public WApplication
{
public:
  WLoginWidgetApplication(const WEnvironment& env);

private:
  WLineEdit *userNameEdit;
  WLineEdit *passWordEdit;
  WText *greeting_;

  void greet();
};


/**
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
 * @param env information about the new session, and the initial request.
 */
WLoginWidgetApplication::WLoginWidgetApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Phillips Hue Login");                               // application title
  // show some text

  root()->addWidget(new WText("Enter your user name"));
  userNameEdit = new WLineEdit(root());
  userNameEdit->setFocus();

  root()->addWidget(new WText("Enter your password"));
  passWordEdit = new WLineEdit(root());
  passWordEdit->setFocus();


  WPushButton *loginButton
    = new WPushButton("Login", root());              // create a button
  loginButton->setMargin(5, Top);                            // add 5 pixels margin
  loginButton->setStyleClass("btn-primary");

  WPushButton *signUpButton = new WPushButton("Sign Up", root());
  signUpButton->setMargin(100, Bottom);


  loginButton->clicked().connect(this, &WLoginWidgetApplication::greet);


  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  userNameEdit->enterPressed().connect
    (boost::bind(&WLoginWidgetApplication::greet, this));

  /*
   * - using a c++0x lambda:
   */
  // button->clicked().connect(std::bind([=]() {
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}


/**
 * Update text to greet user.
 */
void WLoginWidgetApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  greeting_->setText("Hello there, " + userNameEdit->text());
}


/**
 * Read information from the environment to decide whether the user has permission to start a new application.
 * @param env environment
 * @return new application
 */
WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new WLoginWidgetApplication(env);
}

int main(int argc, char **argv)
{
  /*
   * Your main method may set up some shared resources, but should then
   * start the server application (FastCGI or httpd) that starts listening
   * for requests, and handles all of the application life cycles.
   *
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  return WRun(argc, argv, &createApplication);
}
