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
    
    showMainPage();
    
    Wt::WApplication *app = Wt::WApplication::instance();

    app->internalPathChanged().connect(std::bind([=] () {
        handleRequest();
    }));
    
}

void HueApplication::showMainPage() {    
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
        
        Wt::WPushButton *dispBridgeButton = new Wt::WPushButton("Bridges", cont);
        dispBridgeButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/bridges"));
        
        Wt::WPushButton *addBridgeButton = new Wt::WPushButton("Add Bridge", cont);
        addBridgeButton->clicked().connect(this, &HueApplication::addBridge);
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

/** This method displays a list of ALL bridges associated with the current 
* User object if the User is logged in. It will propagate a list of all the 
* current bridges, and create a button next to each one that will take us 
* to that Bridge's page. For example...
*
*        1. Bridge1 @ dummyLocation  [ Click Here to Edit ]
*        2. Bridge2 @ my house       [ Click Here to Edit ]
*        3. ..
*/
void HueApplication::displayBridges() {
    // Add a new groupbox to display all the Bridges associated with the current User
    Wt::WGroupBox *groupbox = new Wt::WGroupBox(curUser_->constructGreetingString(), root());
    
    for(int i = 0; i < curUser_->getNumberOfBridges(); i++) {
        groupbox->addWidget(new Wt::WText(curUser_->getBridge(i).getName() + " @ " + curUser_->getBridge(i).getLocation() + " "));
        
        // The "Click Here to Edit" button will be connected to a method that spawns the IndivBridgeManagerWidget, pass that Bridge as a parameter, and allow you to edit that Bridge's parameters through the new Widget. 
        
        //IDEA: Add buttons as links; use internalpath handling for /bridges for the main bridges widget and then /bridges/# for the subsequent bridges. use connect() to connect each button to a link?
        string s = "Edit " + to_string(i);
        Wt::WPushButton *button = new Wt::WPushButton(s, groupbox);
        
        s = "/bridges/" + to_string(i);
        button->setLink(Wt::WLink(Wt::WLink::InternalPath, s));
        
        groupbox->addWidget(new Wt::WBreak());
    }
}

void HueApplication::addBridge() {
    Wt::WDialog dialogue("Add New Bridge...");
    
    // set up the "Bridge Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Bridge Name: \t", dialogue.contents());
    Wt::WLineEdit *bridgeNameEdit_ = new Wt::WLineEdit(dialogue.contents());
    nameLabel->setBuddy(bridgeNameEdit_);
    dialogue.contents()->addWidget(new Wt::WBreak());
    
    // set up the Location Name text entry field with a label
    Wt::WLabel *locLabel = new Wt::WLabel("Location: \t", dialogue.contents());
    Wt::WLineEdit *bridgeLocationEdit_ = new Wt::WLineEdit(dialogue.contents());
    locLabel->setBuddy(bridgeLocationEdit_);
    dialogue.contents()->addWidget(new Wt::WBreak());

    // set up the Host Name text entry field with a label
    Wt::WLabel *hostLabel = new Wt::WLabel("Hostname: \t", dialogue.contents());
    Wt::WLineEdit *hostNameEdit_ = new Wt::WLineEdit(dialogue.contents());
    hostNameEdit_->setTextSize(15); // set the max length of this field
    hostNameEdit_->setInputMask("009.009.009.009;_"); // set the input mask to force IP address format
    hostLabel->setBuddy(hostNameEdit_);
    dialogue.contents()->addWidget(new Wt::WBreak());
    
    // set up the Port Number text entry field with a label
    Wt::WLabel *portLabel = new Wt::WLabel("Port #: \t", dialogue.contents());
    Wt::WLineEdit *portNumEdit_ = new Wt::WLineEdit(dialogue.contents());
    portNumEdit_->setTextSize(5); // set the max length of this field
    portLabel->setBuddy(portNumEdit_);
    dialogue.contents()->addWidget(new Wt::WBreak());
    
    Wt::WPushButton *confirm_ = new Wt::WPushButton( "Submit", dialogue.contents() );
    
    confirm_->clicked().connect(&dialogue, &Wt::WDialog::accept);
    
    dialogue.show();
    
    // On successful close of the dialogue, do the following:
    if (dialogue.exec() == Wt::WDialog::Accepted) {
        // ! TODO: Here is where we create the new Bridge object out of the details fed to the form.
        
        /*
        cout << "Name " << bridgeNameEdit_->text().toUTF8() << endl;
        cout << "Location " << bridgeLocationEdit_->text().toUTF8() << endl;
        cout << "Hostname " << hostNameEdit_->text().toUTF8() << endl;
        cout << "Port " << portNumEdit_->text().toUTF8() << endl;
        */
        
        Bridge b;
        
        b.setName(bridgeNameEdit_->text().toUTF8());
        b.setLocation(bridgeLocationEdit_->text().toUTF8());
        b.setHostName(hostNameEdit_->text().toUTF8());
        b.setPort(portNumEdit_->text().toUTF8());
        
        
        cout << "Name " << b.getName() << endl;
        cout << "Location " << b.getLocation() << endl;
        cout << "Hostname " << b.getHostName() << endl;
        cout << "Port " << b.getPort() << endl;
        
        curUser_->addBridge(b);
    }
}

void HueApplication::handleRequest() {
    Wt::WApplication *app = Wt::WApplication::instance();
    
    if(app->internalPath() == "/") {
        root()->clear();
        showMainPage();
    }
    else if(app->internalPath() == "/bridges") {
        root()->clear();
        displayBridges();
    }
    // handle the case with an integer number 'i' following "/bridges/i"
    else if(app->internalPath() == "/bridges/") {
        // LOL how2dothis
        
        /*
        // just a test bridge to pass as a parameter for the IndivBridgeManagerWidget
        Bridge *b = new Bridge;
        root()->addWidget(new IndivBridgeManagerWidget("bmanager", b));
        */
        
    }
    else {
        root()->clear();
    }
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
