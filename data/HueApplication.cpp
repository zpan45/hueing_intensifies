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
#include "DBFileManager.h"

DBFileManager activeDB;

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
        loginButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/login"));

        Wt::WPushButton *registerButton = new Wt::WPushButton("Register", cont);
        registerButton->setLink(Wt::WLink(Wt::WLink::InternalPath, "/register"));


        // ------------------------------ TESTING FOR INDIVBRIDGEMANAGERWIDGET
        curUser_ = new User("jfryer6@uwo.ca", "pass123", "Jake", "Fryer");
        Bridge br;
        string bridgeString;

        for(int i = 0; i < 5; i++) {
            bridgeString = "bridge";
            bridgeString.std::string::append(std::to_string(i));
            br.setName(bridgeString);
            br.setLocation("dummyLocation");
            br.setHostName("127.0.0.1");
            br.setPort("8000");

            curUser_->addBridge(br);
        }

        for(int j = 0; j < 5; j++) {
            cout << curUser_->getBridge(j)->getName() << endl;
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

    //setInternalPath("/login", true);
    root()->clear();
    root()->addWidget(new LoginWidget("Login"));
}

/** Method that displays the Registration Widget to the User.
* @todo - Needs to be properly implemented to take the User to the Registration Widget.
*/
void HueApplication::goToRegister() {
    //setInternalPath("/register", true);
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

    else if(app->internalPath() == "/login") {
        goToLogIn();
    }
    // "/bridges" is a string of length 8. If the internal path is at least 8 characters, try to resolve the link as follows:
    else if (app->internalPath().size() >= 8) {
        // cout << "We found that the path was >= 8\n" << app->internalPath() << "\nIt is " << app->internalPath().size() << " characters long" << endl << endl;

        // if the internal path is just "/bridges", display a list of all bridges
        if(app->internalPath() == "/bridges") {
            root()->clear();
            displayBridges();
        }
        // handle go to "/register" internal link
        else if(app->internalPath() == "/register") {
            goToRegister();
        }
        // handle the case with an integer number 'i' following "/bridges/"
        else if(app->internalPath().size() > 9 && app->internalPath().substr(0, 9) == "/bridges/") {
            // cout << "We got to the substr stuff" << endl << endl;
            stringstream s;
            int bridgeNum;
            Bridge *b;

            //cout << "remaining curpath: " << app->internalPath().substr(9, app->internalPath().size()) << endl;

            s << app->internalPath().substr(9, app->internalPath().size());
            s >> bridgeNum;

            // !WARNING -- NEED to implement error handling here.

            b = curUser_->getBridge(bridgeNum);

            root()->clear();
            root()->addWidget(new IndivBridgeManagerWidget("bmanager", b));
        }
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
            ::activeDB.DBFileManager::saveUser(&HueApplication::curUser_);
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
