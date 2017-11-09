#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>

using namespace Wt;
using namespace std;

/*
 * Phillips Hue
 */
class HelloApplication : public WApplication
{
public:
  HelloApplication(const WEnvironment& env);

private:
  WLineEdit *userName;
  WLineEdit *passWord;
  WLineEdit *signUpName;
  WLineEdit *signUpPassword;
  WLineEdit *signUpEmail;
  WText *greeting_;

  void greet();
  void registrationPage();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
HelloApplication::HelloApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Phillips Hue");                               // application title

//  root()->addWidget(new WText("Welcome "));  // show some text
  userName = new WLineEdit(root());                     // allow text input
  userName->setFocus();                                 // give focus

  passWord = new WLineEdit(root());
  passWord->setFocus();


  WPushButton *loginButton
    = new WPushButton("Login", root());              // create a button
  loginButton->setMargin(5, Top);                            // add 5 pixels margin
  loginButton->setStyleClass("btn-primary");

  WPushButton *signUpButton = new WPushButton("Sign Up", root());
  signUpButton->setMargin(10, Bottom);

  root()->addWidget(new WBreak());                       // insert a line break

  greeting_ = new WText(root());                         // empty text;
  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  loginButton->clicked().connect(this, &HelloApplication::greet);
  

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  userName->enterPressed().connect
    (boost::bind(&HelloApplication::greet, this));

  signUpButton->clicked().connect(this, &HelloApplication::registrationPage);

  /*
   * - using a c++0x lambda:
   */
  // button->clicked().connect(std::bind([=]() { 
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}

void HelloApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  root()->clear();
  setTitle("Landing Page");
  greeting_ = new WText(root());
  greeting_->setText("Welcome to the landing page, " + userName->text());

//  cout << "Welcome to the Registration Page.";
//  Wt::WApplication *app=Wt::WApplication::instance();
  //std::string path=app->internalPath();
 // app->setInternalPath("/regsitration");
//  app->setInternalPath(path,true);
}

void HelloApplication::registrationPage()
{
  root()->clear();
  setTitle("Registration Page");
  signUpName = new WLineEdit(root());
  signUpName->setFocus();
  signUpPassword = new WLineEdit(root());
  signUpPassword->setFocus();
  signUpEmail = new WLineEdit(root());
  signUpEmail->setFocus();
  WPushButton *registerMe = new WPushButton("Register Me!", root());
  registerMe->setMargin(10, Right);  
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new HelloApplication(env);
}

/*bool checkPassword(string passwordInput)
{
  
}
*/
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

