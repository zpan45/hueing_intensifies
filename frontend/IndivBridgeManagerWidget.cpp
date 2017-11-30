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
    connect();

    groupbox = new Wt::WGroupBox(b->getName()); // initialize area to display the list of groups associated with this Bridge -- Widget gets added in showInformation();
    
    showInformation();
}


//destructor
IndivBridgeManagerWidget::~IndivBridgeManagerWidget() {

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
    Wt::WLabel *nameLabel = new Wt::WLabel("Bridge Name: ", this);
    bridgeNameEdit_ = new Wt::WLineEdit(b->getName(), this);
    nameLabel->setBuddy(bridgeNameEdit_);
    this->addWidget(new Wt::WBreak());

    // set up the Location Name text entry field with a label
    Wt::WLabel *locLabel = new Wt::WLabel("Location: ", this);
    bridgeLocationEdit_ = new Wt::WLineEdit(b->getLocation(), this);
    locLabel->setBuddy(bridgeLocationEdit_);
    this->addWidget(new Wt::WBreak());

    // set up the Host Name text entry field with a label
    Wt::WLabel *hostLabel = new Wt::WLabel("Hostname: ", this);
    hostNameEdit_ = new Wt::WLineEdit(b->getHostName(), this);
    hostNameEdit_->setTextSize(15); // set the max length of this field
    hostNameEdit_->setInputMask("009.009.009.009;_"); // set the input mask to force IP address format
    hostLabel->setBuddy(hostNameEdit_);
    this->addWidget(new Wt::WBreak());

    // set up the Port Number text entry field with a label
    Wt::WLabel *portLabel = new Wt::WLabel("Port #: ", this);
    portNumEdit_ = new Wt::WLineEdit(b->getPort(), this);
    portNumEdit_->setTextSize(5); // set the max length of this field
    portLabel->setBuddy(portNumEdit_);
    this->addWidget(new Wt::WBreak());

    // add the "Update" button for changing a Bridge's information
    Wt::WPushButton *update_ = new Wt::WPushButton("Update", this);

    this->addWidget(new Wt::WBreak());
    Wt::WPushButton *showGroups_ = new Wt::WPushButton("Show Groups", this);

    Wt::WPushButton *addGroupButton = new Wt::WPushButton("Add Group", this);
    addGroupButton->clicked().connect(this, &IndivBridgeManagerWidget::addGroupToBridge);
    
    this->addWidget(groupbox);
    
    // the update_ button is bound to a lambda function that calls the update()
    // method. Done this way because you cannot pass parameters through Wt's connect()
    // method.
    update_->clicked().connect(bind([&]() {
        update();
    }));
    showGroups_->clicked().connect(bind([&]() {
        // Show all the current Groups associated with the Bridge
        displayGroups();
    }));
}

/** Method that consults the current Bridge object for all associated groups, and displays them
* in a list with buttons that will allow the user to modify an individual Group.
 *
*/
void IndivBridgeManagerWidget::displayGroups() {
    // ! TODO -- implement method that displays all Groups associated with the current Bridge
    // use Bridge.cpp's "getGroup()" method?? Iterate from 0 - size of the vector?
    updateGroups();

    // Add a new groupbox to display all the Groups associated with the current Bridge
    groupbox->clear();

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
        connectDeleteGroup(cb->currentIndex() + 1);
        
        cb->removeItem(cb->currentIndex()); // remove the option to delete a button
        delButton_->setEnabled(false); // disable the delete button

        for(int i = 0; i < b->getNumberOfGroups(); i++) {
            cout << b->getGroup(i)->getName() << endl;
        }

        displayGroups();
    }));
}

void IndivBridgeManagerWidget::addGroupToBridge() {
    Wt::WDialog dialogue("Add New Group...");

    // set up the "Group Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Group Name: ", dialogue.contents());
    Wt::WLineEdit *groupNameEdit_ = new Wt::WLineEdit(dialogue.contents());
    nameLabel->setBuddy(groupNameEdit_);
    dialogue.contents()->addWidget(new Wt::WBreak());

    Wt::WPushButton *confirm_ = new Wt::WPushButton( "Submit", dialogue.contents() );

    confirm_->clicked().connect(&dialogue, &Wt::WDialog::accept);

    dialogue.show();

    // On successful close of the dialogue, do the following:
    if (dialogue.exec() == Wt::WDialog::Accepted) {
        Group g;
        g.setName(groupNameEdit_->text().toUTF8());

        
        connectCreateGroup(g.getName());
        b->addGroup(g);
        displayGroups();
    }
}


/** Method to update the current Bridge object with any changes from the text boxes.
 *
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

/**
 * Connect to the bridge hardware and update the Lights objects stored in the bridge.
 * @return false if Bridge cannot be reached
 */
bool IndivBridgeManagerWidget::updateLights() {
    //drop all saved lights in the bridge
    b->clearLights();
    //try to connect to the Bridge; if connected, checkBridge returns true and bridge status is set
    connect();
    Wt::Json::Object result;
    //try to parse bridge status string to JSON object
    try {
        Wt::Json::parse(b->getStatus(), result);
    } catch (exception e)
    {
        cout<<"JSON parse failure."<<endl;
        return false;
    }
    //JSON object lightsJSON contains all the lights JSON
    Wt::Json::Object lightsJSON;
    lightsJSON=result.get("lights");
    //set<string> contains all the lightIDs
    std::set<std::string> lightIDs=lightsJSON.names();
    //for each lightID, get light status and store them in vector bridge.lights
    for (auto it=lightIDs.begin();it!=lightIDs.end();++it) {
        Light newlight;
        newlight.setID(*it);

        Wt::Json::Object lightJSON =lightsJSON.get(*it);
        newlight.setName(lightJSON.get("name"));
        Wt::Json::Object lightStateJSON =lightJSON.get("state");
        newlight.setIsActive(lightStateJSON.get("on"));
        newlight.setBrightness(lightStateJSON.get("bri"));
        newlight.setHue(lightStateJSON.get("hue"));
        newlight.setSat(lightStateJSON.get("sat"));

        //Wt::WString s = lightsJSON.get(*it);
        //cout << s << endl;

        //newlight.setName(lightsJSON.get(*it).get("name").toString().orIfNull("empty string");
        //newlight.setIsActive(lightsJSON.get(*it).get("state").get("on").toBool().orIfNull(false));
        //newlight.setBrightness(lightsJSON.get(*it).get("state").get("bri").toString().orIfNull(""));
        //newlight.setHue(lightsJSON.get(*it).get("state").get("hue"));
        //newlight.setSat(lightsJSON.get(*it).get("state").get("sat"));
        b->addLight(newlight);
    }
    return true;

}

/**
* Connect to the bridge hardware and update the Group objects stored in the bridge's vector.
* @return false if Bridge cannot be reached
*/
bool IndivBridgeManagerWidget::updateGroups() {
    //drop all saved groups in the bridge
    b->clearGroups();
    //try to connect to the Bridge; if connected, checkBridge returns true and bridge status is set
    connect();
    Wt::Json::Object result;
    //try to parse bridge status string to JSON object
    try {
        Wt::Json::parse(b->getStatus(), result);
    } catch (exception e)
    {
        cout<<"JSON parse failure (inside updateGroups())"<<endl;
        return false;
    }
    //JSON object groupsJSON contains all the groups JSON
    Wt::Json::Object groupsJSON;
    Wt::Json::Object lightsJSON;

    groupsJSON = result.get("groups");
    lightsJSON = result.get("lights");

    //set<string> contains all the groupIDs
    std::set<std::string> groupIDs=groupsJSON.names();
    //std::set<std::string> lightIDs = lightsJSON.names();

    //for each groupID, construct group with their lights, and store them in vector bridge.groups[groupID-1]
    for (auto it=groupIDs.begin();it!=groupIDs.end();it++) {
        Wt::Json::Object groupJSON =groupsJSON.get(*it);
        Group newgroup;
        //set Group name
        newgroup.setName(groupJSON.get("name"));


        const Wt::Json::Array& lightsInGroupJSONArray = groupJSON.get("lights");

        int i = 0; // loop counter
        vector<string> ary;
        //for every lightID in the Group
        for (auto itl=lightsInGroupJSONArray.begin();itl!=lightsInGroupJSONArray.end();itl++, i++) {
            ary.push_back(lightsInGroupJSONArray[i]);
        }

        for(int j = 0; j < ary.size(); j++) {
            Light newlight;
            Wt::Json::Object l = lightsJSON.get( ary[j] );

            newlight.setName(l.get("name"));

            Wt::Json::Object lightStateJSON =l.get("state");
            newlight.setIsActive(lightStateJSON.get("on"));
            newlight.setBrightness(lightStateJSON.get("bri"));
            newlight.setHue(lightStateJSON.get("hue"));
            newlight.setSat(lightStateJSON.get("sat"));

            newgroup.addLight(newlight);

            Wt::Json::Value val = l.get("name");
            string valStr = val.toString();
            cout << valStr << endl;

        }

        //add newgroup to Bridge
        b->addGroup(newgroup);
    }

    return true;
}

/**
 * Send a POST message to the bridge hardware to create a new group. Called by createGroup().
 * @param name new group's name
 * @param lightIDs lightIDs a vector of int containing the lightIDs in the group
 */
void IndivBridgeManagerWidget::connectCreateGroup(std::string name) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/newdeveloper";
    //"<<b->getUsername();
    url_<<"/groups";

    //build POST message
    Wt::Http::Message message;
    stringstream body;
    //set body
    body<< "{"<<"\"name\":\""<<name<<"\"}";

    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");

    Wt::Http::Client *clientPost=new Wt::Http::Client(this);
    clientPost->setTimeout(HTML_CLIENT_TIMEOUT);
    clientPost->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    clientPost->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponseGroup, this, clientPost, _1, _2));
    //send request
    if(clientPost->post(url_.str(), message)) {
        cout << "posted" << endl;
        Wt::WApplication::instance()->deferRendering();
    }
}

/**
 * Send a DELETE message to the bridge hardware to delete a specified group. Called by deleteGroup().
 * @param groupID the groupID of the group we want to delete as an int
 */
void IndivBridgeManagerWidget::connectDeleteGroup(int groupID) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/newdeveloper";
    //"<<b->getUsername();
    url_<<"/groups/"<<groupID;
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponseGroup, this, client, _1, _2));
    //send request
    Wt::Http::Message message;
    client->deleteRequest(url_.str(), message);
}


/**
 * Handles Http Response from Bridge. Update this->requestSuccess flag upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 *
 */
void IndivBridgeManagerWidget::handleHttpResponseGroup(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message &response) {
    Wt::WApplication::instance()->resumeRendering();

    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        Wt::Json::Array result;
        cout << response.body() << endl;
        //try to parse response string to JSON object
        try {

            Wt::Json::parse(response.body(), result);
            Wt::Json::Value val = result[0];

            Wt::Json::Object obj = val;
        }
        catch ( Wt::Json::TypeException t) {
            cerr << "type exception" << endl;
            return;
        }
        catch (exception e) {
            cout<<"JSON parse failure (inside handleHttpResponseGroup()).\n" << e.what() <<endl;
            return;
        }
    }

    delete client;
}
