/**
 * @class IndivGroupManagerWidget
 * A widget for managing a Group object, allows user to display and edit properties of a Group.
 * It has methods to rename a Group; display and update the Lights in the Group and
 * update the Group's all containing Lights' state (on/off, Brightness, Hue, Saturation, Transition Time for switching states).
 *
 * @brief Individual Group Manager Widget
 * @author Jacob Fryer (jfryer6)
 *
 */

#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivGroupManagerWidget.h"

using namespace std;

//constructor
/**
 * Constructor.
 * @brief Constructor
 * @param name String name of this widget
 * @param parent WContainerWidget pointer to parent container widget
 * @param bridge pointer to the Bridge object where the Light object belongs
 * @param group pointer to the Group object whose properties this Widget will allow the user to display and edit.
 */
IndivGroupManagerWidget::IndivGroupManagerWidget(const std::string &name, Bridge *bridge, Group *group, Wt::WContainerWidget *parent) : Wt::WContainerWidget(parent){
    b = bridge; // b is a pointer to the current bridge object
    g = group; // g is a pointer to the current group object
    // It HAS to be a pointer because otherwise the changes from the update() method won't persist
    
    showInformation();
    
    // for testing purposes only -- in the future, the Bridge b will already have details associated with it when passed in
    /*
    b->setName("new bridge");
    b->setLocation("in a place");
    b->setHostName("255.255.255.0");
    b->setPort("8080");
    */
}


//destructor
IndivGroupManagerWidget::~IndivGroupManagerWidget() {

}


//public methods


//private methods

/**
 * Show user and allow user to modify the properties of a Group.
 * @brief Show Group Information
 */
void IndivGroupManagerWidget::showInformation() {
    // set up the "Group Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Group Name: \t", this);
    groupNameEdit_ = new Wt::WLineEdit(g->getName(), this);
    nameLabel->setBuddy(groupNameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // add the "Update" button for changing a Bridge's information
    Wt::WPushButton *update_ = new Wt::WPushButton("Update", this);
    
    displayLights();
    
    // the update_ button is bound to a lambda function that calls the update()
    // method. Done this way because you cannot pass parameters through Wt's connect()
    // method.
    update_->clicked().connect(bind([&]() {
        update();
    }));
}

/**
 * Method that consults the current Bridge object for all associated groups, and displays them
 * in a list with buttons that will allow the user to modify an individual Group.
 * @brief Display Lights In Group
 */
void IndivGroupManagerWidget::displayLights() {
    // ! TODO -- implement method that displays all Groups associated with the current Bridge
    // use Bridge.cpp's "getGroup()" method?? Iterate from 0 - size of the vector?
    
    // Add a new groupbox to display all the Lights associated with the current Group
    Wt::WGroupBox *groupbox = new Wt::WGroupBox(g->getName(), this);
    
    for(int i = 0; i < g->getNumberOfLights(); i++) {
        groupbox->addWidget(new Wt::WText(g->getLight(i)->getName() + " (ID: " + g->getLight(i)->getID() + ") "));
        
        //IDEA: Add buttons as links; use internalpath handling for /bridges for the main bridges widget and then /bridges/# for the subsequent bridges. use connect() to connect each button to a link?
        string s = "Edit " + to_string(i);
        Wt::WPushButton *button = new Wt::WPushButton(s, groupbox);
        
        s = "/lights/" + to_string(i);
        
        button->setLink(Wt::WLink(Wt::WLink::InternalPath, Wt::WApplication::instance()->internalPath() + s));
        
        groupbox->addWidget(new Wt::WBreak());
    }
    
    // add a remove button
    Wt::WComboBox *cb = new Wt::WComboBox(groupbox);
    
    // loop through all Groups associated with the current Bridge, adding them as selectable options
    for(int i = 0; i < g->getNumberOfLights(); i++) {
        cb->addItem(g->getLight(i)->getName());
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
        g->removeLight(cb->currentIndex()); // delete the Group with the current index 
        cb->removeItem(cb->currentIndex()); // remove the option to delete a button
        delButton_->setEnabled(false); // disable the delete button
        
        for(int i = 0; i < g->getNumberOfLights(); i++) {
            cout << g->getLight(i)->getName() << endl;
        }
        
        groupbox->refresh();
    }));
    
}

/**
 * Method to update the current Bridge object with any changes from the text boxes.
 * @brief Update Group Object
 */
void IndivGroupManagerWidget::update() {
    this->addWidget(new Wt::WBreak());
    
    Wt::WHBoxLayout *change = new Wt::WHBoxLayout(this);
    //this->addWidget(change);
    
    Wt::WContainerWidget *old = new Wt::WContainerWidget();
    change->addWidget(old);
    old->addWidget(new Wt::WText("<b>Old Stuff:</b>"));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(g->getName()));
    
    if( g->getName() != groupNameEdit_->text().toUTF8() ) {
        g->setName(groupNameEdit_->text().toUTF8());
    }
    
    this->addWidget(new Wt::WBreak());
    this->addWidget(new Wt::WBreak());
    
    connectUpdateGroup();
    
    // didn't want to call the variable "new" so we named the display of things that have changed, "changed"
    Wt::WContainerWidget *changed = new Wt::WContainerWidget();
    change->addWidget(changed);
    changed->addWidget(new Wt::WText("<b>New Stuff:</b>"));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(g->getName()));
}

/**
 * Update the state of Lights belong to this Group. (on, bri, hue, sat, transTime)
 * @brief Update State of Group
 * @param groupID the groupID of the group being updated
 * @param on bool state of Lights: on/off
 * @param bri int brightness of Lights
 * @param hue int hue of Lights
 * @param sat int sat of Lights
 * @param transTime int transition time specified (*100ms)
 * @return true on state successfully set
 */
bool IndivGroupManagerWidget::updateState(int groupID, bool on, int bri, int hue, int sat, int transTime) {
    //initialize request success flag
    requestSuccess=false;
    //connect to Bridge
    connectUpdateState(groupID, on, bri, hue, sat, transTime);
    //if connection is successful, requestSuccess flag would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if flag's set then connected successfully, update groups stored in the vector
        if(requestSuccess) {
            return true;
        }
    }
    //connection timeout, return false
    return false;
}

/**
 * Send a PUT request to bridge to update the Group attributes (Group name and consisting LightIDs). Called by updateGroup().
 * @brief Connect Update Group
 * @param groupID the groupID of the group being updated
 */
void IndivGroupManagerWidget::connectUpdateGroup() {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<"newdeveloper"<<"/groups/"<<g->getID();
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivGroupManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //Set name
    body << "{" << "\"name\":\"" << g->getName() << "\",";
    //for each consisting light, add to message body
    body<<"\"lights\": [";
    for(int i=0; i<g->getNumberOfLights(); i++) {
        body<<"\""<<g->getLight(i)->getID()<<"\"";
        if(i<(g->getNumberOfLights()-1)) body<<",";
    }
    body<<"]}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    //send request
    client->put(url_.str(), message);
}

/**
 * Send a PUT request to bridge to update the state of Lights belong to this Group. Called by updateState().
 * @brief Connect Update State
 * @param groupID the groupID of the group being updated
 * @param on bool state of Lights: on/off
 * @param bri int brightness of Lights
 * @param hue int hue of Lights
 * @param sat int sat of Lights
 * @param transTime int transition time specified (*100ms)
 */
void IndivGroupManagerWidget::connectUpdateState(int groupID, bool on, int bri, int hue, int sat, int transTime) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<"newdeveloper"<<"/groups/"<<g->getID()<<"/action";
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivGroupManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    body<< "{" <<"\"on\":"<<boost::lexical_cast<std::string>(on)<< ",";
    body<<"\"bri\":"<<bri<<",";
    body<<"\"hue\":"<<hue<<",";
    body<<"\"sat\":"<<sat<<",";
    body<<"\"transitiontime\":"<<transTime<<"}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    //send request
    client->put(url_.str(), message);
}

/**
 * Handles Http Response from Bridge. Update requestSuccess flag upon receiving successful response.
 * @brief Handle HTTP Response
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 *
 */
void IndivGroupManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message &response) {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        Wt::Json::Object result;
        //try to parse response string to JSON object
        try {
            Wt::Json::parse(response.body(), result);
        }
        catch (exception e) {
            cout<<"JSON parse failure."<<endl;
            return;
        }
        //if response contains "success" then request was successful, set requestSuccess to true
        requestSuccess=result.contains("success");
    }
    delete client;
}