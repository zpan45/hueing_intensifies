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
        
        
        // ------------------------------ TESTING FOR INDIVBRIDGEMANAGERWIDGET
        curUser_ = new User("jfryer6@uwo.ca", "pass123", "Jake", "Fryer");
        Bridge br;
        string bridgeString;
        
        for(int i = 0; i < 5; i++) {
            bridgeString = "bridge";
            bridgeString.std::string::append(std::to_string(i+1));
            br.setName(bridgeString);
            br.setLocation("dummyLocation");
            br.setHostName("180.0.0.0");
            br.setPort("8080");
            
            curUser_->addBridge(br);
        }
        
        for(int j = 0; j < 5; j++) {
            cout << curUser_->getBridge(j).getName() << endl;
        }
        
        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());
        
        Wt::WPushButton *bridgeButton = new Wt::WPushButton("Bridges", cont);
        bridgeButton->clicked().connect(this, &HueApplication::displayBridges);
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
    //curUser_ = new User("jfryer6@uwo.ca", "pass123", "Jake", "Fryer");
    //cout << curUser_->getFirstName() << endl;
    
    setInternalPath("/login", true);
    root()->clear();
    root()->addWidget(new LoginWidget("Login"));
}

/** Method that displays the Registration Widget to the User.
* @todo - Needs to be properly implemented to take the User to the Registration Widget.
*/
void HueApplication::goToRegister() {
    setInternalPath("/register", true);
    root()->clear();
    root()->addWidget(new RegistrationWidget("Registration"));
}

void HueApplication::displayBridges() {
    // ---------------------------------------------------------
    
    // !TODO - We will display a list of ALL bridges associated with the current User object if the User is logged in.
    
    // For now, this is just a test to make sure we can connect the Individual Bridge Manager.
    
    // In the future, this method will display all the bridges. It will propagate a list of all the current bridges, and create a button next to each one that will take us to that Bridge's page. For example...
    
    /*
        1. Bridge1 @ dummyLocation  [ Click Here to Edit ]
        2. Bridge2 @ my house       [ Click Here to Edit ]
        3. ..
    */
    
    // The "Click Here to Edit" button will be connected to a method that spawns the IndivBridgeManagerWidget, pass that Bridge as a parameter, and allow you to edit that Bridge's parameters through the new Widget. 
    
    // ----------------------------------------------------------
    
    Wt::WGroupBox *groupbox = new Wt::WGroupBox(curUser_->constructGreetingString(), root());
    for(int i = 0; i < 5; i++) {
        groupbox->addWidget(new Wt::WText(curUser_->getBridge(i).getName() + " @ " + curUser_->getBridge(i).getLocation() + " "));
        groupbox->addWidget(new Wt::WPushButton("Edit"));
        groupbox->addWidget(new Wt::WBreak());
    }
    
    
    /*
    // just a test bridge to pass as a parameter for the IndivBridgeManagerWidget
    Bridge *b = new Bridge;
    root()->addWidget(new IndivBridgeManagerWidget("bmanager", b));
    */
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
