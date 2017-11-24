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
IndivBridgeManagerWidget::IndivBridgeManagerWidget(const std::string &name, Bridge b, Wt::WContainerWidget *parent) : Wt::WContainerWidget(parent){
    
    
    // for testing purposes only -- in the future, the Bridge b will already have details associated with it when passed in
    b.setName("new bridge");
    b.setLocation("up ur butt");
    b.setHostName("255.255.255.0");
    b.setPort("8080");
    
    // set up the "Bridge Name" text entry field with a label
    Wt::WLabel *nameLabel = new Wt::WLabel("Bridge Name: \t", this);
    bridgeNameEdit_ = new Wt::WLineEdit(b.getName(), this);
    nameLabel->setBuddy(bridgeNameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // set up the Location Name text entry field with a label
    Wt::WLabel *locLabel = new Wt::WLabel("Location: \t", this);
    bridgeLocationEdit_ = new Wt::WLineEdit(b.getLocation(), this);
    locLabel->setBuddy(bridgeLocationEdit_);
    this->addWidget(new Wt::WBreak());

    // set up the Host Name text entry field with a label
    Wt::WLabel *hostLabel = new Wt::WLabel("Hostname: \t", this);
    hostNameEdit_ = new Wt::WLineEdit(b.getHostName(), this);
    hostLabel->setBuddy(hostNameEdit_);
    this->addWidget(new Wt::WBreak());
    
    // set up the Port Number text entry field with a label
    Wt::WLabel *portLabel = new Wt::WLabel("Port #: \t", this);
    portNumEdit_ = new Wt::WLineEdit(b.getPort(), this);
    portLabel->setBuddy(portNumEdit_);
    this->addWidget(new Wt::WBreak());
}


//destructor
IndivBridgeManagerWidget::~IndivBridgeManagerWidget() {

}

//TODO: Somebody please TEST/modify ALL THESE METHODS wrote by Peter    -Peter

//public methods
/**
 * Check if the Bridge provided can be reached with specified username.
 * @param b Bridge to be checked
 * @param uName username used for connection
 * @return bool Bridge reached
 */
bool IndivBridgeManagerWidget::checkBridge(Bridge b, string uName) {
    string currentStatus="";
    connect(b, uName);
    for(int i=0; i<HTML_MESSAGE_CHECK; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(currentStatus!="") return true;
    }
    return currentStatus=="";
}

//private methods

/**
 * Try to connect to bridge using default URL (http://localhost:8000/api/newdeveloper)
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
 * Try to connect to provided Bridge with specified 'Bridge username'
 * @param b Bridge trying to connect to
 * @param uName Bridge username
 */
void IndivBridgeManagerWidget::connect(Bridge b, string uName) {
    stringstream url_;
    url_<<"http://"<<b.getHostName()<<":"<<b.getPort()<<"/api/"<<uName;

    //Wt::Http::Client *client=new Wt::Http::Client(this);
    //client->setTimeout(HTML_CLIENT_TIMEOUT);
    //client->setMaximumResponseSize(10*1024);
    //client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    //client->get(url_.str());
    
    cout << url_.str() << endl << endl;
}



/**
 * Handles Http Response from Bridge. Update currentstatus upon receiving successful response.
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
        currentStatus=response.body();
        cout<<currentStatus<<endl;
    }

    delete client;
}
*/
