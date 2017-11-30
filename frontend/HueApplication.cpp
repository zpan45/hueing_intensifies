/**
 * @class HueApplication
 * The HueApplication class is the backbone of our Application. It implements
 * the WApplication class. HueApplication functions as the landing page for the application.
 * It prompts the user to Log In or Register if they don't have an account.
 *
 * @brief HueApplication class functions as the backbone of the app.
 * @author Jacob Fryer (jfryer6)
 * @date November 09, 2017
 */

#include "HueApplication.h"
#include "DBFileManager.h"

DBFileManager activeDB;

using namespace std;

/**
 * Default constructor that creates the user-facing Hue Application's landing page.
 * @brief Hue Application
 * @param env - The WEnvironment variable.
 */
HueApplication::HueApplication(const Wt::WEnvironment& env) : Wt::WApplication(env) {
}

User* HueApplication::getCurrentUser() {
    return curUser_;
}

void HueApplication::setCurrentUser(User *u) {
    curUser_ = u;
}

void HueApplication::initialize() {
    curUser_ = new User();

    setTitle("CS3307 - Team24 Hue Application");
    
    
    // if the User is not logged in on session startup, force redirect to the root
    if(testLoggedInStatus() == false) {
        setInternalPath( "/", true );
    }
    
    showMainPage();
    
    Wt::WApplication::instance()->internalPathChanged().connect(std::bind([=] () {
        handleRequest();
    }));

}

/** Method that is called when the app is closed before the destructor is called. Finalizes any remaining details. In our case, calls the signOut() method to serialize User data to file at the end of a session.
 * @brief Finalize the application and serializes User data.
 * @author Jacob Fryer (jfryer6)
 */
void HueApplication::finalize() {
    if(curUser_->getUsername() != "") {
        signOut();
    }
}

/**
 *
 */
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
        loginButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/login"));

        Wt::WPushButton *registerButton = new Wt::WPushButton("Register", cont);
        registerButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/register"));
    }
    else {
        Wt::WPushButton *signOut_ = new Wt::WPushButton("Sign Out", cont);
        signOut_->clicked().connect(this, &HueApplication::signOut);
        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());
        
        // if the curUser_ pointer does point to a User, greet the User with a friendly hello!
        cont->addWidget(new Wt::WText( curUser_->constructGreetingString() ));
        cont->addWidget(new Wt::WBreak());

        Wt::WPushButton *dispBridgeButton = new Wt::WPushButton("Bridges", cont);
        dispBridgeButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/bridges"));

        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());
        cont->addWidget(new Wt::WBreak());

        Wt::WPushButton *addBridgeButton = new Wt::WPushButton("Add Bridge", cont);
        addBridgeButton->clicked().connect(this, &HueApplication::addBridge);
    }

}

/**
 * Method that checks if the User is logged in by testing whether the curUser_ variable points
 * to the nullptr.
 * @brief Test LoggedIn Status
 * @return bool - The status of whether there is a User logged into this session.
 */
bool HueApplication::testLoggedInStatus() {
    if( curUser_->getUsername() == "" ) {
        return false; // Not logged in
    }
    else {
        return true; // Logged in
    }
}

/**
 * Method that displays the Log In Widget to the User.
 * @brief Go To LogIn
 */
void HueApplication::goToLogIn() {
    root()->clear();
    LoginWidget *login = new LoginWidget("Login", root());

    login->loggedIn().connect( this, &HueApplication::loggedIn_ );
}

void HueApplication::loggedIn_(User u) {
    curUser_->setUsername(u.getUsername());
    curUser_->setPassword(u.getPassword());
    curUser_->setFirstName(u.getFirstName());
    curUser_->setLastName(u.getLastName());

    // extract all bridges from the User pulled from the database and attach them to curUser_
    for(int i = 0; i < u.getNumberOfBridges(); i++) {
        Bridge b( u.getBridge(i)->getName(), u.getBridge(i)->getLocation(), u.getBridge(i)->getHostName(), u.getBridge(i)->getPort(), u.getBridge(i)->getUsername(), u.getBridge(i)->getStatus() );

        curUser_->addBridge( b );
    }
}

/**
 * Method that displays the Registration Widget to the User.
 * @brief Go To Register
 */
void HueApplication::goToRegister() {
    root()->clear();
    root()->addWidget(new RegistrationWidget("Registration", curUser_));
}

void HueApplication::signOut() {
    ::activeDB.DBFileManager::saveBridges(curUser_);
    
    curUser_ = new User();
    setInternalPath("/#", true);
}

/**
 * This method displays a list of ALL bridges associated with the current
 * User object if the User is logged in. It will propagate a list of all the
 * current bridges, and create a button next to each one that will take us
 * to that Bridge's page. For example...
 *
 *        1. Bridge1 @ dummyLocation  [ Click Here to Edit ]
 *        2. Bridge2 @ my house       [ Click Here to Edit ]
 *        3. ..
 * @brief Display Bridges
 */
void HueApplication::displayBridges() {
    // Add a new groupbox to display all the Bridges associated with the current User
    Wt::WGroupBox *groupbox = new Wt::WGroupBox(curUser_->constructGreetingString(), root());

    for(int i = 0; i < curUser_->getNumberOfBridges(); i++) {
        groupbox->addWidget(new Wt::WText(curUser_->getBridge(i)->getName() + " @ " + curUser_->getBridge(i)->getLocation() + " "));

        // The "Click Here to Edit" button will be connected to a method that spawns the IndivBridgeManagerWidget, pass that Bridge as a parameter, and allow you to edit that Bridge's parameters through the new Widget.

        //IDEA: Add buttons as links; use internalpath handling for /bridges for the main bridges widget and then /bridges/# for the subsequent bridges. use connect() to connect each button to a link?
        string s = "Edit " + to_string(i);
        Wt::WPushButton *button = new Wt::WPushButton(s, groupbox);

        s = "/bridges/" + to_string(i);
        button->setLink(Wt::WLink(Wt::WLink::InternalPath, s));

        groupbox->addWidget(new Wt::WBreak());
    }

    // add a remove button
    Wt::WComboBox *cb = new Wt::WComboBox(groupbox);

    // loop through all Bridges associated with the current User, adding them as selectable options
    for(int i = 0; i < curUser_->getNumberOfBridges(); i++) {
        cb->addItem(curUser_->getBridge(i)->getName());
    }

    groupbox->addWidget(new Wt::WBreak());

    Wt::WText *out = new Wt::WText(groupbox); // this is the "Delete?" text

    groupbox->addWidget(new Wt::WBreak());
    Wt::WPushButton *delButton_ = new Wt::WPushButton("Delete", groupbox);
    delButton_->setEnabled(false);

    // if the selected Bridge was changed:
    cb->changed().connect(std::bind([=] () {
        out->setText(Wt::WString::fromUTF8("Delete {1}?").arg(cb->currentText()));
        delButton_->setEnabled(true);
    }));

    // if the delete button is clicked, remove the option to remove the Bridge and the Bridge itself
    delButton_->clicked().connect(std::bind([=] () {
        curUser_->removeBridge(cb->currentIndex()); // delete the Bridge with the current index
        cb->removeItem(cb->currentIndex()); // remove the option to delete a button
        delButton_->setEnabled(false); // disable the delete button

        for(int i = 0; i < curUser_->getNumberOfBridges(); i++) {
            cout << curUser_->getBridge(i)->getName() << endl;
        }

        groupbox->refresh();
    }));
}

/**
 * Allow user to enter information and add a Bridge to the system
 * @brief Add Bridge
 */
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
        // create the new Bridge object out of the details fed to the form.
        Bridge b;

        b.setName(bridgeNameEdit_->text().toUTF8());
        b.setLocation(bridgeLocationEdit_->text().toUTF8());
        b.setHostName(hostNameEdit_->text().toUTF8());
        b.setPort(portNumEdit_->text().toUTF8());

        
        /* ------------------------- TESTING 
        Bridge br;
        br.setName("bridgeString");
        br.setLocation("dummyLocation");
        br.setHostName("127.0.0.1");
        br.setPort("8000");
        
        curUser_->addBridge(br);
        */
        
        cout << "Name " << b.getName() << endl;
        cout << "Location " << b.getLocation() << endl;
        cout << "Hostname " << b.getHostName() << endl;
        cout << "Port " << b.getPort() << endl;

        curUser_->addBridge(b);
        ::activeDB.DBFileManager::saveBridges(curUser_); // save the bridges of the current user
    }
}

/**
 *
 */
void HueApplication::handleRequest() {
    Wt::WApplication *app = Wt::WApplication::instance();
    
    // internalPathNextPart returns the next "folder" of the URL if one exists
    // or "" if not.
    // If it doesn't return the empty string, we try to serve it the appropriate webpage
    
    //cout << "internalPathMatches(/login) = " << app->internalPathMatches( "/login" ) << "\n\nInternalPath = " << app->internalPath() << "\n\n\n";
    
    if(app->internalPathMatches("/") && app->internalPathNextPart( "/" ) == "") {
        root()->clear();
        showMainPage();
    }
    
    else if(app->internalPathMatches("/login")) {
        goToLogIn();
    }
    
    // handle go to "/register" internal link
    else if(app->internalPathMatches("/register")) {
        goToRegister();
    }
    
    // if the user is logged in and tries to navigate to the Bridges page
    else if( app->internalPathMatches("/bridges") ) {
        if(testLoggedInStatus() == true) {
            // if the internal path is just "/bridges" (i.e. doesn't have a "Next Part"), 
            // display a list of all bridges
            if( app->internalPathNextPart( "/bridges/" ) == "" ) {
                root()->clear();
                displayBridges();
            }
            // otherwise, there IS a next part, so we process it
            else {
                // construct a working URL to handle variability in bridge numbers
                // workingURL_ will contain "/bridges/#"
                string workingURL_ =  "/bridges/" + app->internalPathNextPart("/bridges/");
                
                stringstream s;
                int bridgeNum;
                Bridge *b;
                
                s << app->internalPathNextPart("/bridges/"); // strip the bridge number out of the string
                s >> bridgeNum;

                // !WARNING -- NEED to implement error handling here.
                b = curUser_->getBridge(bridgeNum);
                
                // if there is nothing after the "bridges/#/" part
                if( app->internalPathNextPart( workingURL_ + "/" ) == "" ) {
                    root()->clear();
                    root()->addWidget(new IndivBridgeManagerWidget("bmanager", b));
                }
                // there is more in the current internal path, so we construct the Group widget
                else {
                    //cout << "working url: " << workingURL_ << "\nnext part: " << app->internalPathNextPart( workingURL_ ) << "\n\n\n" << endl;
                    
                    workingURL_ += "/groups/";
                    int groupNum;
                    Group *g;
                    
                    s.clear();
                    s << app->internalPathNextPart(workingURL_); // strip the group number out of the string
                    
                    // update the workingURL_ to include variability of groupNum
                    workingURL_ += app->internalPathNextPart( workingURL_ );
                    
                    cout << "working url: " << workingURL_ << "\nnext part: " << app->internalPathNextPart( workingURL_ ) << "\n\n\n" << endl;
                    
                    s >> groupNum;
                    g = b->getGroup(groupNum);
                    
                    if( app->internalPathNextPart(workingURL_ + "/") == "" ) {
                        root()->clear();
                        root()->addWidget(new IndivGroupManagerWidget("groupManager", b, g));
                    }
                    else {
                        workingURL_ += "/lights/";
                        int lightNum;
                        Light *l;
                        
                        s.clear();
                        s << app->internalPathNextPart(workingURL_); // strip the light number out of the string
                        
                        workingURL_ += app->internalPathNextPart("/lights/");
                        
                        s >> lightNum;
                        l = g->getLight(lightNum);
                        
                        root()->clear();
                        root()->addWidget( new IndivLightManagerWidget("lightManager", b, l) );

                    }
                }
            }
        }
        
        // if the User is not logged in, redirect them to the home page
        else {
            setInternalPath("/", true);
        }
    }
    
    else {
        root()->clear();
        showMainPage();
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
