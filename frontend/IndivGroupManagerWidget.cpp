#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivGroupManagerWidget.h"

using namespace std;

/** Constructor
* @param name - 
* @param parent -
* @param g - The Group object whose properties this Widget will allow the user to display and edit.
*/
IndivGroupManagerWidget::IndivGroupManagerWidget(const std::string &name, Group *group, Wt::WContainerWidget *parent) : Wt::WContainerWidget(parent){
    
    g = group; // g is a pointer to the current group object
    // It HAS to be a pointer because otherwise the changes from the update() method won't persist
    
    Light l;
    l.setName("new light1");
    
    g->addLight(l);
    l.setName("newL2");
    g->addLight(l);
    
    for(int i = 0; i < g->getNumberOfLights(); i++) {
        cout << g->getLight(i)->getName() << endl;
    }
    
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
/**
 */

//private methods

/**
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

/** Method that consults the current Bridge object for all associated groups, and displays them
* in a list with buttons that will allow the user to modify an individual Group.
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
        
        button->setLink(Wt::WLink(Wt::WLink::InternalPath, s));
        
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

/** Method to update the current Bridge object with any changes from the text boxes.
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
    
    // didn't want to call the variable "new" so we named the display of things that have changed, "changed"
    Wt::WContainerWidget *changed = new Wt::WContainerWidget();
    change->addWidget(changed);
    changed->addWidget(new Wt::WText("<b>New Stuff:</b>"));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(g->getName()));
}

/**
 * Handles Http Response from Bridge. Update Bridge status upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 * @param b pointer to current Bridge
 *


void IndivGroupManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,
                                                  const Wt::Http::Message &response, Bridge *b) const {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        b->setStatus(response.body());
        cout<< "current status:\t\t" << b->getStatus() <<endl;
    }

    delete client;
}
*/
