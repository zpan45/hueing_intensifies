//
// Created by Peter on 2017/11/21.
//
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivBridgeManagerWidget.h"

using namespace std;

/** Constructor
* @param name - 
* @param parent -
* @param b - The Bridge object whose properties this Widget will allow the user to display and edit.
*/
IndivBridgeManagerWidget::IndivBridgeManagerWidget(const std::string &name, Bridge *bridge, Wt::WContainerWidget *parent) : Wt::WContainerWidget(parent){
    
    b = bridge; // b is a pointer to the current bridge object
    // It HAS to be a pointer because otherwise the changes from the update() method won't persist
    checkBridge();
    
    Group g;
    g.setName("new group1");
    
    b->addGroup(g);
    g.setName("newG2");
    b->addGroup(g);
    
    
    
    for(int i = 0; i < b->getNumberOfGroups(); i++) {
        cout << b->getGroup(i)->getName() << endl;
    }
    
    showInformation();
    
    Group *group;
    group = b->getGroup(0);
    
    this->addWidget(new IndivGroupManagerWidget("gmanager", group));
    
    // for testing purposes only -- in the future, the Bridge b will already have details associated with it when passed in
    /*
    b->setName("new bridge");
    b->setLocation("in a place");
    b->setHostName("255.255.255.0");
    b->setPort("8080");
    */
}


//destructor
IndivBridgeManagerWidget::~IndivBridgeManagerWidget() {

}


//public methods
/**
 * Check if the Bridge provided can be reached with specified username.
 * @return bool Bridge reached
 */
bool IndivBridgeManagerWidget::checkBridge() {
    //connect to Bridge
    connect();
    //if connection is successful, Bridge's status would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if Bridge's status isn't empty then connected successfully
        if(b->getStatus()!="") return true;
    }
    //connection timeout, return false
    return false;
}

//private methods

/**
 * Try to connect to provided Bridge
 */
void IndivBridgeManagerWidget::connect() {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/newdeveloper";
    //"<<b->getUsername();
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //TODO: here, do we pass a *Bridge to handleHttpResponse?
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    //send get request
    client->get(url_.str());
    
    cout << url_.str() << endl << endl;
}

/**
*/
void IndivBridgeManagerWidget::showInformation() {
    // set up the "Bridge Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Bridge Name: \t", this);
    bridgeNameEdit_ = new Wt::WLineEdit(b->getName(), this);
    nameLabel->setBuddy(bridgeNameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // set up the Location Name text entry field with a label
    Wt::WLabel *locLabel = new Wt::WLabel("Location: \t", this);
    bridgeLocationEdit_ = new Wt::WLineEdit(b->getLocation(), this);
    locLabel->setBuddy(bridgeLocationEdit_);
    this->addWidget(new Wt::WBreak());

    // set up the Host Name text entry field with a label
    Wt::WLabel *hostLabel = new Wt::WLabel("Hostname: \t", this);
    hostNameEdit_ = new Wt::WLineEdit(b->getHostName(), this);
    hostNameEdit_->setTextSize(15); // set the max length of this field
    hostNameEdit_->setInputMask("009.009.009.009;_"); // set the input mask to force IP address format
    hostLabel->setBuddy(hostNameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // set up the Port Number text entry field with a label
    Wt::WLabel *portLabel = new Wt::WLabel("Port #: \t", this);
    portNumEdit_ = new Wt::WLineEdit(b->getPort(), this);
    portNumEdit_->setTextSize(5); // set the max length of this field
    portLabel->setBuddy(portNumEdit_);
    this->addWidget(new Wt::WBreak());
    
    // add the "Update" button for changing a Bridge's information
    Wt::WPushButton *update_ = new Wt::WPushButton("Update", this);
    
    displayGroups();
    
    // the update_ button is bound to a lambda function that calls the update()
    // method. Done this way because you cannot pass parameters through Wt's connect()
    // method.
    update_->clicked().connect(bind([&]() {
        update();
    }));
}

/** Method that consults the current Bridge object for all associated groups, and displays them
* in a list with buttons that will allow the user to modify an individual Group.
* @param b - The Bridge object that contains the vector of Groups to be displayed.
*/
void IndivBridgeManagerWidget::displayGroups() {
    // ! TODO -- implement method that displays all Groups associated with the current Bridge
    // use Bridge.cpp's "getGroup()" method?? Iterate from 0 - size of the vector?
    
    // Add a new groupbox to display all the Groups associated with the current Bridge
    Wt::WGroupBox *groupbox = new Wt::WGroupBox(b->getName(), this);
    
    for(int i = 0; i < b->getNumberOfGroups(); i++) {
        groupbox->addWidget(new Wt::WText(b->getGroup(i)->getName() + " (" + to_string(b->getGroup(i)->getNumberOfLights()) + " Lights) "));
        
        // The "Click Here to Edit" button will be connected to a method that spawns the IndivBridgeManagerWidget, pass that Bridge as a parameter, and allow you to edit that Bridge's parameters through the new Widget. 
        
        //IDEA: Add buttons as links; use internalpath handling for /bridges for the main bridges widget and then /bridges/# for the subsequent bridges. use connect() to connect each button to a link?
        string s = "Edit " + to_string(i);
        Wt::WPushButton *button = new Wt::WPushButton(s, groupbox);
        
        //Wt::WApplication *app = Wt::WApplication::instance();
        //s = app->internalPath() + "/groups/" + to_string(i);
        s = "/groups/" + to_string(i);
        //delete app;
        
        button->setLink(Wt::WLink(Wt::WLink::InternalPath, s));
        
        groupbox->addWidget(new Wt::WBreak());
    }
    
    // add a remove button
    Wt::WComboBox *cb = new Wt::WComboBox(groupbox);
    
    // loop through all Groups associated with the current Bridge, adding them as selectable options
    for(int i = 0; i < b->getNumberOfGroups(); i++) {
        cb->addItem(b->getGroup(i)->getName());
    }
    
    groupbox->addWidget(new Wt::WBreak());
    
    Wt::WText *out = new Wt::WText(groupbox); // this is the "Delete?" text
    
    groupbox->addWidget(new Wt::WBreak());
    Wt::WPushButton *delButton_ = new Wt::WPushButton("Delete", groupbox);
    delButton_->setEnabled(false);
    
    // if the selected Group was changed:
    cb->changed().connect(std::bind([=] () {
        out->setText(Wt::WString::fromUTF8("Delete {1}?").arg(cb->currentText()));
        delButton_->setEnabled(true);
    }));
    
    // if the delete button is clicked, remove the option to remove the Group and the Group itself
    delButton_->clicked().connect(std::bind([=] () {
        b->removeGroup(cb->currentIndex()); // delete the Group with the current index 
        cb->removeItem(cb->currentIndex()); // remove the option to delete a button
        delButton_->setEnabled(false); // disable the delete button
        
        for(int i = 0; i < b->getNumberOfGroups(); i++) {
            cout << b->getGroup(i)->getName() << endl;
        }
        
        groupbox->refresh();
    }));
    
}

/** Method to update the current Bridge object with any changes from the text boxes.
* @param b - The Bridge object to be updated.
*/
void IndivBridgeManagerWidget::update() {
    this->addWidget(new Wt::WBreak());
    
    Wt::WHBoxLayout *change = new Wt::WHBoxLayout(this);
    //this->addWidget(change);
    
    Wt::WContainerWidget *old = new Wt::WContainerWidget();
    change->addWidget(old);
    old->addWidget(new Wt::WText("<b>Old Stuff:</b>"));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(b->getName()));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(b->getLocation()));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(b->getHostName()));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(b->getPort()));
    
    if( b->getName() != bridgeNameEdit_->text().toUTF8() ) {
        b->setName(bridgeNameEdit_->text().toUTF8());
    }
    
    if ( b->getLocation() != bridgeLocationEdit_->text().toUTF8() ) {
        b->setLocation(bridgeLocationEdit_->text().toUTF8());
    }
    
    if ( b->getHostName() != hostNameEdit_->text().toUTF8() ) {
        b->setHostName(hostNameEdit_->text().toUTF8());
    }
    
    if ( b->getPort() != portNumEdit_->text().toUTF8() ) {
        b->setPort(portNumEdit_->text().toUTF8());
    }
    
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    
    // didn't want to call the variable "new" so we named the display of things that have changed, "changed"
    Wt::WContainerWidget *changed = new Wt::WContainerWidget();
    change->addWidget(changed);
    changed->addWidget(new Wt::WText("<b>New Stuff:</b>"));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(b->getName()));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(b->getLocation()));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(b->getHostName()));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(b->getPort()));
    
}

/**
 * Handles Http Response from Bridge. Update Bridge status upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 * @param b pointer to current Bridge
 *
 */

void IndivBridgeManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message &response) const {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        b->setStatus(response.body());
        cout<< "current status:\t\t" << b->getStatus() <<endl;
    }

    delete client;
}
