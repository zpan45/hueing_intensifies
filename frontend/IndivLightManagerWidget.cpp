//
// Created by peter on 11/27/17.
//
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivLightManagerWidget.h"

using namespace std;

//constructor
IndivLightManagerWidget::IndivLightManagerWidget(const std::string &name, Bridge *bridge, Light *light, Wt::WContainerWidget *parent) {
    b = bridge;
    l = light;
    
    showInformation();
    
    Wt::WPushButton *update = new Wt::WPushButton("Update", this);
    update->clicked().connect(std::bind([=] () {
        rename("new string");
    }));
}

//destructor
IndivLightManagerWidget::~IndivLightManagerWidget() {

}

//public methods


//private methods

/**
*/
void IndivLightManagerWidget::showInformation() {
    // set up the "Light Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Light Name: ", this);
    nameEdit_ = new Wt::WLineEdit(l->getName(), this);
    nameLabel->setBuddy(nameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // Add a dropdown menu switch for on or off as a WComboBox
    Wt::WLabel *onOffLabel = new Wt::WLabel("Light State: ", this);
    onOffSwitch_ = new Wt::WComboBox(this);
    onOffSwitch_->addItem("On");
    onOffSwitch_->addItem("Off");
    onOffSwitch_->setCurrentIndex(1);
    this->addWidget(new Wt::WBreak());
    
    // brightness field
    Wt::WLabel *briLabel = new Wt::WLabel("Brightness: ", this);
    brightnessEdit_ = new Wt::WLineEdit(to_string(l->getBrightness()), this);
    briLabel->setBuddy(brightnessEdit_);
    this->addWidget(new Wt::WBreak());
    
    // set up a "Hue" text entry field with a label
    Wt::WLabel *hueLabel = new Wt::WLabel("Hue: ", this);
    hueEdit_ = new Wt::WLineEdit(to_string(l->getHue()), this);
    hueLabel->setBuddy(hueEdit_);
    this->addWidget(new Wt::WBreak());
    
    // saturation field
    Wt::WLabel *satLabel = new Wt::WLabel("Saturation: ", this);
    satEdit_ = new Wt::WLineEdit(to_string(l->getSat()), this);
    satLabel->setBuddy(satEdit_);
    this->addWidget(new Wt::WBreak());
}

/**
 * Rename the Light to provided new name.
 * @param newname new name for the Light.
 * @return true if renamed successfully
 */
bool IndivLightManagerWidget::rename(std::string newname) {
    //initialize request success flag
    requestSuccess=false;
    //connect to Bridge
    connectRename(newname);
    //if connection is successful, requestSuccess flag would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if flag's set then connected successfully, change local Light name
        if(requestSuccess) {
            l->setName(newname);
            return true;
        }
    }
    //connection timeout, return false
    return false;
}

/**
 * Update the Light status using default transition time(4). (on, bri, hue, sat)
 * @return true if updated successfully
 */
bool IndivLightManagerWidget::update() {
    //initialize request success flag
    requestSuccess=false;
    //connect to Bridge
    connectUpdate();
    //if connection is successful, requestSuccess flag would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if flag's set then connected successfully, change local Light name
        if(requestSuccess) {
            return true;
        }
    }
    //connection timeout, return false
    return false;
}

/**
 * Update the Light status with specified transition time. (on, bri, hue, sat)
 * @param transTime * 100ms = transition time
 * @return true if updated successfully
 */
bool IndivLightManagerWidget::update(int transTime) {
    //initialize request success flag
    requestSuccess=false;
    //connect to Bridge
    connectUpdate(transTime);
    //if connection is successful, requestSuccess flag would be updated by handleHttpResponse()
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        //check every 100ms for HTML_MESSAGE_CHECK times
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //if flag's set then connected successfully, change local Light name
        if(requestSuccess) {
            return true;
        }
    }
    //connection timeout, return false
    return false;
}


/**
 * Send a PUT request to bridge to rename the Light
 * @param newname new name for the Light
 */
void IndivLightManagerWidget::connectRename(std::string newname) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<"newdeveloper"<<"/lights/"<<l->getID();
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //Set name
    body << "{" << "\"name\":\"" << newname << "\"}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    client->put(url_.str(), message);

}


/**
 * Send a PUT request to bridge to update the Light status using default transition time (on, bri, hue, sat)
 *
 */
void IndivLightManagerWidget::connectUpdate() {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<b->getUsername()<<"/lights/"<<l->getID()<<"/state";
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //set on
    body<< "{" <<"\"on\":"<<boost::lexical_cast<std::string>(l->getIsActive())<< ",";
    body<<"\"bri\":"<<l->getBrightness()<<",";
    body<<"\"hue\":"<<l->getHue()<<",";
    body<<"\"sat\":"<<l->getSat()<<"}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    //send request
    client->put(url_.str(), message);

}

/**
 * Send a PUT request to bridge to update the Light status with specified transition time (on, bri, hue, sat)
 * @param transTime * 100ms = transition time
 */
void IndivLightManagerWidget::connectUpdate(int transTime) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<b->getUsername()<<"/lights/"<<l->getID()<<"/state";
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //set on
    body<< "{" <<"\"on\":"<<boost::lexical_cast<std::string>(l->getIsActive())<< ",";
    body<<"\"bri\":"<<l->getBrightness()<<",";
    body<<"\"hue\":"<<l->getHue()<<",";
    body<<"\"sat\":"<<l->getSat()<<",";
    body<<"\"transitiontime\":"<<transTime<<"}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    //send request
    client->put(url_.str(), message);

}

/**
 * Handles Http Response from Bridge. Update requestSuccess flag upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 *
 */
void IndivLightManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message &response) {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        Wt::Json::Object result;
        //try to parse response string to JSON object
        try {
            Wt::Json::parse(response.body(), result);
        } catch (exception e)
        {
            cout<<"JSON parse failure."<<endl;
            return;
        }
        //if response contains "success" then request was successful, set requestSuccess to true
        requestSuccess=result.contains("success");
    }
    delete client;
}