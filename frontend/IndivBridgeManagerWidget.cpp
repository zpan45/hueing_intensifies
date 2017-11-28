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
    
    // for testing purposes only -- in the future, the Bridge b will already have details associated with it when passed in
    /*
    b->setName("new bridge");
    b->setLocation("in a place");
    b->setHostName("255.255.255.0");
    b->setPort("8080");
    */
    
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
    
    // the update_ button is bound to a lambda function that calls the update()
    // method. Done this way because you cannot pass parameters through Wt's connect()
    // method.
    update_->clicked().connect(bind([&]() {
        update(b);
    }));
}


//destructor
IndivBridgeManagerWidget::~IndivBridgeManagerWidget() {

}


//public methods
/**
 * Check if the Bridge provided can be reached with specified username.
 * @param b Bridge to be checked
 * @return bool Bridge reached
 */
bool IndivBridgeManagerWidget::checkBridge(Bridge b) {
    //connect to Bridge
    connect(b);
    //if connection is successful, Bridge's status would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if Bridge's status isn't empty then connected successfully
        if(b.getStatus()!="") return true;
    }
    //connection timeout, return false
    return false;
}

//private methods

/**
 * WILL BE REMOVED: Try to connect to bridge using default URL (http://localhost:8000/api/newdeveloper)
 *
 */
void IndivBridgeManagerWidget::connect() {
    stringstream url_;
    url_<< URL <<USERNAME;

    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    //client->get(url_.str());
}
/**
 * Try to connect to provided Bridge
 * @param b Bridge trying to connect to
 */
void IndivBridgeManagerWidget::connect(Bridge b) {
    stringstream url_="http://";
    url_<<b.getHostName()<<":"<<b.getPort()<<"/api/"<<b.getUsername();

    //Wt::Http::Client *client=new Wt::Http::Client(this);
    //client->setTimeout(HTML_CLIENT_TIMEOUT);
    //client->setMaximumResponseSize(10*1024);
    //TODO: here, do we pass a *Bridge to handleHttpResponse?
    //client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    //client->get(url_.str());
    
    cout << url_.str() << endl << endl;
}

/** Method that consults the current Bridge object for all associated groups, and displays them
* in a list with buttons that will allow the user to modify an individual Group.
* @param b - The Bridge object that contains the vector of Groups to be displayed.
*/
void IndivBridgeManagerWidget::displayGroups( Bridge b ) {
    // ! TODO -- implement method that displays all Groups associated with the current Bridge
    // use Bridge.cpp's "getGroup()" method?? Iterate from 0 - size of the vector?
}

/** Method to update the current Bridge object with any changes from the text boxes.
* @param b - The Bridge object to be updated.
*/
void IndivBridgeManagerWidget::update( Bridge *b ) {
    this->addWidget(new Wt::WBreak());
    
    Wt::WContainerWidget *old = new Wt::WContainerWidget(this);
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
    
    Wt::WContainerWidget *changed = new Wt::WContainerWidget(this);
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
 *
 */
 /*
void IndivBridgeManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,
                                                  const Wt::Http::Message &response) const {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
    //TODO: how do we bridge.setStatus(response.body())? Do we pass a *bridge to this method?
        currentStatus=response.body();
        cout<<currentStatus<<endl;
    }

    delete client;
}
*/
