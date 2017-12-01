/**
 * @class IndivLightManagerWidget
 * A widget for managing a Light object, allows user to display and edit properties of a Light.
 * It has methods to rename a Light and
 * update the Light's state (on/off, Brightness, Hue, Saturation, Transition Time for switching states).
 *
 * @brief Individual Light Manager Widget
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 *
 */
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivLightManagerWidget.h"

using namespace std;

//constructor
/**
 * Constructor.
 * @brief Constructor
 * @param name String name of this widget
 * @param parent WContainerWidget pointer to parent container widget
 * @param bridge pointer to the Bridge object where the Light object belongs
 * @param light pointer to the Light object whose properties this Widget will allow the user to display and edit.
 */
IndivLightManagerWidget::IndivLightManagerWidget(const std::string &name, Bridge *bridge, Light *light, Wt::WContainerWidget *parent) {
    b = bridge;
    l = light;
    
    showInformation();
}

//destructor
IndivLightManagerWidget::~IndivLightManagerWidget() {

}

//public methods


//private methods

/**
 * Show the Light state attributes and allow user to update them
 * @brief Show Light Information
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
    
    Wt::WPushButton *update_ = new Wt::WPushButton("Update", this);
    
    // the update_ button is bound to a lambda function that calls the update()
    // method. Done this way because you cannot pass parameters through Wt's connect()
    // method.
    update_->clicked().connect(bind([&]() {
        update();
    }));
}

/**
 * Rename the Light to provided new name.
 * @brief Rename Light
 * @param newname new name for the Light.
 * @return true if renamed successfully
 * @author Zhengyang Pan (zpan45)
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
 * Method to update the current Light object with any changes from the text boxes.
 * @brief Update Light Object
 */
void IndivLightManagerWidget::update() {
    Wt::WDialog changedDialogue("Group Update");
    changedDialogue.setClosable(true);
    
    Wt::WHBoxLayout *change = new Wt::WHBoxLayout(changedDialogue.contents());
    
    Wt::WContainerWidget *old = new Wt::WContainerWidget();
    change->addWidget(old);
    old->addWidget(new Wt::WText("<b>Old Stuff:</b>"));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText(l->getName()));
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText( to_string( l->getIsActive()) ) );
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText( to_string( l->getBrightness() ) ) );
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText( to_string( l->getHue()) ) );
    old->addWidget(new Wt::WBreak());
    old->addWidget(new Wt::WText( to_string( l->getSat()) ) );
    old->addWidget(new Wt::WBreak());
    
    stringstream convertToInt;
    
    // call to turn the light on right away if needed in case the light is off (otherwise other update requests won't work)
    
    // off == false, but off == currentIndex of 1, so we flip it with a !
    if( !(bool)onOffSwitch_->currentIndex() == true ) {
        //cout << "onoff is: ON (" << !(bool)onOffSwitch_->currentIndex() << ")" << endl;
        l->setIsActive(true);
        connectSwitchOnOff(l->getIsActive());
    }
    
    if( l->getName() != nameEdit_->text().toUTF8() ) {
        l->setName(nameEdit_->text().toUTF8());
        connectRename(l->getName());
    }
    
    if( to_string(l->getBrightness()) != brightnessEdit_->text().toUTF8() ) {
        convertToInt << brightnessEdit_->text().toUTF8();
        int bri;
        convertToInt >> bri;
        
        l->setBrightness(bri);
        convertToInt.clear();
    }    
    
    if( to_string(l->getHue()) != hueEdit_->text().toUTF8() ) {
        convertToInt << hueEdit_->text().toUTF8();
        int hue;
        convertToInt >> hue;
        
        l->setHue(hue);
        convertToInt.clear();
    }
    
    if( to_string(l->getSat()) != satEdit_->text().toUTF8() ) {
        convertToInt << satEdit_->text().toUTF8();
        int sat;
        convertToInt >> sat;
        
        l->setSat(sat);
        convertToInt.clear();
    }
    
    connectUpdate();
    
    // if we're turning the light off, we do it at the end so as not to interrupt the other requests
    if( !(bool)onOffSwitch_->currentIndex() == false ) {
        //cout << "onoff is: OFF (" << (bool)onOffSwitch_->currentIndex() << ")" << endl;
        l->setIsActive(false);
        connectSwitchOnOff(l->getIsActive());
    }
    
    // didn't want to call the variable "new" so we named the display of things that have changed, "changed"
    Wt::WContainerWidget *changed = new Wt::WContainerWidget();
    change->addWidget(changed);
    changed->addWidget(new Wt::WText("<b>New Stuff:</b>"));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText(l->getName()));
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText( to_string( l->getIsActive()) ) );
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText( to_string( l->getBrightness() ) ) );
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText( to_string( l->getHue()) ) );
    changed->addWidget(new Wt::WBreak());
    changed->addWidget(new Wt::WText( to_string( l->getSat()) ) );
    changed->addWidget(new Wt::WBreak());
    
    new Wt::WBreak(changedDialogue.contents());
    new Wt::WBreak(changedDialogue.contents());
    
    Wt::WPushButton confirm("Okay", changedDialogue.contents());
    
    confirm.clicked().connect(&changedDialogue, &Wt::WDialog::accept);
    
    if(changedDialogue.exec() == Wt::WDialog::Accepted) {
    }
}

/**
 * Send a PUT request to bridge to rename the Light
 * @brief Connect Rename
 * @param newname new name for the Light
 * @author Zhengyang Pan (zpan45)
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
 * Send a PUT request to bridge to update the Light status to On or Off
 * @brief Connect Update for On/Off
 * @param active, boolean of whether the Light is on (true) or off (false)
 * @author Zhengyang Pan (zpan45)
 */
void IndivLightManagerWidget::connectSwitchOnOff(bool active) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<"newdeveloper"<<"/lights/"<<l->getID()<<"/state";
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //set on
    body<< "{" <<"\"on\":";
    
    if(l->getIsActive() == true) {
        body << "true";
    }
    else {
        body << "false";
    }
    body << "}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    //send request
    client->put(url_.str(), message);
}


/**
 * Send a PUT request to bridge to update the Light status using default transition time (bri, hue, sat)
 * @brief Connect Update
 * @author Zhengyang Pan (zpan45)
 */
void IndivLightManagerWidget::connectUpdate() {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<"newdeveloper"<<"/lights/"<<l->getID()<<"/state";
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //build PUT message
    Wt::Http::Message message;
    stringstream body;
    //set on
    body<< "{";
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
 * @brief Connect Update with TransTime
 * @param transTime * 100ms = transition time
 * @author Zhengyang Pan (zpan45)
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
 * @brief Handle HTTP Response
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 * @author Zhengyang Pan (zpan45)
 *
 */
void IndivLightManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err, const Wt::Http::Message &response) {
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