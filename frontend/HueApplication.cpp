/**
 * @file HueApplication.cpp
 * The HueApplication class is the backbone of our Application. It implements
 * the WApplication class. HueApplication functions as the landing page for the application.
 * It prompts the user to Log In or Register if they don't have an account.
 *
 * @brief HueApplication class functions as the backbone of the app.
 * @author Jacob Fryer (jfryer6)
 * @date November 09, 2017
 */

#include "HueApplication.h"

using namespace std;

/** Default constructor that creates the user-facing Hue Application's landing page.
* @param env - The WEnvironment variable.
*/
HueApplication::HueApplication(const Wt::WEnvironment& env) : Wt::WApplication(env) {
    setTitle("CS3307 - Team24 Hue Application");
    
    // add a new container widget for the "Logged In" dialogue / greeting
    Wt::WContainerWidget *cont = new Wt::WContainerWidget();
    root()->addWidget(cont);
    
    // test if the curUser_ pointer points to a User object
    if( testLoggedInStatus() == false ) {
        // if it does not, prompt the User to log in or register
        
        cont->addWidget(new Wt::WText("Please Log In."));
        cont->addWidget(new Wt::WBreak());
        
        Wt::WPushButton *loginButton = new Wt::WPushButton("Login", cont);
        loginButton->clicked().connect(this, &HueApplication::goToLogIn);
        
        Wt::WPushButton *registerButton = new Wt::WPushButton("Register", cont);
        registerButton->clicked().connect(this, &HueApplication::goToRegister);
    }
    else {
        // if the curUser_ pointer does point to a User, greet the User with a friendly hello!
        cont->addWidget(new Wt::WText("Hello, "));
        cont->addWidget(new Wt::WText( curUser_->getFirstName() ));
    }
}

/** Method that checks if the User is logged in by testing whether the curUser_ variable points
* to the nullptr. 
* @return bool - The status of whether there is a User logged into this session.
*/
bool HueApplication::testLoggedInStatus() {
    if( curUser_ == nullptr ) {
        return false;
    }
    else {
        return true;
    }
}

/** Method that displays the Log In Widget to the User.
* @todo - Needs to be properly implemented to take the User to the Log In Widget.
*/
void HueApplication::goToLogIn() {
    // Currently, method just sets the curUser_ pointer to point to a new User object.
    curUser_ = new User("jfryer6@uwo.ca", "pass123", "Jake", "Fryer");
    cout << curUser_->getFirstName() << endl;
}

/** Method that displays the Registration Widget to the User.
* @todo - Needs to be properly implemented to take the User to the Registration Widget.
*/
void HueApplication::goToRegister() {
    root()->clear();
    root()->addWidget(new RegistrationWidget("String"));
}

/** Function that is called in runRESTful() to create the HueApplication, which is made the 
* entry point for the website.
*/
Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
    return new HueApplication(env);
}

/** A replacement method for WRun()
* 
* Code modified from tutorial examples
* http://eduardo-lago.blogspot.ca/2013/05/creating-rest-web-service-using.html?m=1
* https://stackoverflow.com/questions/15956947/can-multiple-wt-applications-run-on-same-port?rq=1
* as listed in the Assignment 1 specifications
*/
int runRESTful(int argc, char *argv[], Wt::ApplicationCreator createApplication) {
    try {
        Wt::WServer server(argv[0]);
        
        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        
        
        server.addEntryPoint(Wt::Application, createApplication);
        
        if(server.start()) {
            int sig = Wt::WServer::waitForShutdown(argv[0]);

            std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
            server.stop();
        }
    }
    catch(Wt::WServer::Exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch(std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}

/** Main method that passes control to the runRESTful() function on launch.
*/
int main(int argc, char **argv) {    
    return runRESTful(argc, argv, &createApplication);
}
