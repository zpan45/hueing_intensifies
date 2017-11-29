//
// Created by peter on 11/27/17.
//
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivLightManagerWidget.h"

//constructor
IndivLightManagerWidget::IndivLightManagerWidget(const std::string &name, Bridge *b, Light *l, Wt::WContainerWidget *parent) {

}

//destructor
IndivLightManagerWidget::~IndivLightManagerWidget() {

}

//public methods


//private methods

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
        //if Bridge's status isn't empty then connected successfully, change local Light name
        if(requestSuccess) {
            l->setName(newname);
            return true;
        }
    }
    //connection timeout, return false
    return false;
}


/**
 * Send a POST request to bridge to rename the Light
 * @param newname new name for the Light
 */
void IndivLightManagerWidget::connectRename(std::string newname) {
    //construct URL
    stringstream url_;
    url_<< "http://" <<b->getHostName()<<":"<<b->getPort()<<"/api/"<<b->getUsername()<<"/lights/"<<l->getID();
    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(HTML_CLIENT_TIMEOUT);
    client->setMaximumResponseSize(10*1024);
    //bind done signal with handling method
    client->done().connect(boost::bind(&IndivLightManagerWidget::handleHttpResponse, this, client, _1, _2));
    //send get request
    //client->get(url_.str());
    //build PUT message
    Wt::Http::Message message=new Wt::Http::Message();
    stringstream body= "{";
    //Set name
    body << "\"name\":\"" << newname << "\"}";
    message.addBodyText(body.str());
    //set header
    message.setHeader("Content-Type", "application/json");
    client->put(url_.str(), message);

}

/**
 * Handles Http Response from Bridge. Update requestSuccess flag upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 *
 */
void IndivLightManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,
                                                 const Wt::Http::Message &response) const {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        Wt::Json::Object result= new Wt::Json::Object;
        //try to parse response string to JSON object
        try {
            Wt::Json::parse(response.body(), result);
        } catch (exception e)
        {
            cout<<"JSON parse failure."<<endl;
            return false;
        }
        //if response contains "success" then request was successful, set requestSuccess to true
        requestSuccess=result.contains("success");
    }
    delete client;
}