/**
 * @class IndivBridgeManagerWidget
 * A widget for managing a Bridge object, allows user to display and edit properties of a Bridge.
 * It has methods to try to connect to a Bridge hardware and confirm it is reachable;
 * update the Lights and Groups stored in the Bridge object;
 * create/delete Groups stored in the Bridge object and send API calls to the hardware for this purpose.
 *
 * @brief Individual Bridge Manager Widget
 * @author Zhengyang Pan (zpan45)
 *
 */
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivBridgeManagerWidget.h"

using namespace std;

//constructor
/**
 * Constructor.
 * @brief Constructor
 * @param name String name of this widget
 * @param parent WContainerWidget pointer to parent container widget
 * @param bridge pointer to the Bridge object whose properties this Widget will allow the user to display and edit.
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
 * Try to connect to provided Bridge.
 * @brief Connect to Bridge
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
}

/**
 * Show user and allow user to modify the properties of a Bridge.
 * @brief Show Bridge Information
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

/**
 * Method that consults the current Bridge object for all associated groups, and displays them
 * in a list with buttons that will allow the user to modify an individual Group.
 * @brief Show Bridge Groups
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

        button->setLink(Wt::WLink(Wt::WLink::InternalPath, Wt::WApplication::instance()->internalPath() + s));

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
        
        cb->removeItem(cb->currentIndex()); // remove the option to delete the current item
        delButton_->setEnabled(false); // disable the delete button

        displayGroups();
        displayGroups();
    }));
}

/**
 * Method that shows a dialogue box and allows user to add a new Group to the Bridge
 * @brief Add Group To Bridge
 */
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
        displayGroups();
    }
}


/**
 * Method to update the current Bridge object with any changes from the text boxes.
 * @brief Update Bridge
 */
void IndivBridgeManagerWidget::update() {
    Wt::WDialog changedDialogue("Bridge Update");
    changedDialogue.setClosable(true);
    
    Wt::WHBoxLayout *change = new Wt::WHBoxLayout(changedDialogue.contents());

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
    
    new Wt::WBreak(changedDialogue.contents());
    new Wt::WBreak(changedDialogue.contents());
    
    Wt::WPushButton confirm("Okay", changedDialogue.contents());
    
    confirm.clicked().connect(&changedDialogue, &Wt::WDialog::accept);
    
    if(changedDialogue.exec() == Wt::WDialog::Accepted) {
    }
}

/**
 * Handles Http Response from Bridge. Update Bridge status upon receiving successful response.
 * @brief Handle HTTP Response
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
    }

    delete client;
}

/**
 * Connect to the bridge hardware and update the Lights objects stored in the bridge.
 * @brief Update Bridge Lights
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
        
        b->addLight(newlight);
    }
    return true;
}

/**
 * Connect to the bridge hardware and update the Group objects stored in the bridge's vector.
 * @brief Update Bridge Groups
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
        cerr<<"JSON parse failure (inside updateGroups())"<<endl;
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
        newgroup.setID(*it);
        
        const Wt::Json::Array& n = {};
        
        const Wt::Json::Array& lightsInGroupJSONArray = groupJSON.get("lights").orIfNull(n);

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
            
            newlight.setID( ary[j] ); // set the id to match what was retrieved from the API

            newgroup.addLight(newlight);
        }

        //add newgroup to Bridge
        b->addGroup(newgroup);
    }

    return true;
}

/**
 * Send a POST message to the bridge hardware to create a new group. Called by createGroup().
 * @brief Connect Create Group
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
        Wt::WApplication::instance()->deferRendering();
    }
}

/**
 * Send a DELETE message to the bridge hardware to delete a specified group. Called by deleteGroup().
 * @brief Connect Delete Group
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
 * @brief Handle Http Response for Group
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
        //cout << response.body() << endl;
        //try to parse response string to JSON object
        try {

            Wt::Json::parse(response.body(), result);
            
            int successCount = 0;
            
            for(int i = 0; i < result.size(); i++) {
                Wt::Json::Value val = result[i];
                Wt::Json::Object obj = val;
                
                if( !(obj.isNull("success")) ) {
                    successCount++;
                }
            }
        }
        catch ( Wt::Json::TypeException t) {
            cerr << "type exception" << endl;
            return;
        }
        catch (exception e) {
            cerr<<"JSON parse failure (inside handleHttpResponseGroup()).\n" << e.what() <<endl;
            return;
        }
    }
    
    delete client;
}
