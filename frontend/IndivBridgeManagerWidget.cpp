//
// Created by Peter on 2017/11/21.
//
#define _GLIBCXX_USE_CXX11_ABI 1
#include "IndivBridgeManagerWidget.h"

//constructor
IndivBridgeManagerWidget::IndivBridgeManagerWidget(const std::string &name, Wt::WContainerWidget *parent) : WContainerWidget(parent){

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
    currentStatus="";
    connect(b, uName);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return currentStatus=="";
}

//private methods

/**
 * Try to connect to bridge using default URL (http://localhost:8000/api/newdeveloper)
 *
 */
void IndivBridgeManagerWidget::connect() {
    string url_=URL;
    url_<<USERNAME;

    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(5);
    client->setMaximumResponseSize(10*1024);
    client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    client->get(url_);
}
/**
 * Try to connect to provided Bridge with specified 'Bridge username'
 * @param b Bridge trying to connect to
 * @param uName Bridge username
 */
void IndivBridgeManagerWidget::connect(Bridge b, string uName) {
    string url_="http://";
    url_<<b.getHostName()<<":"<<b.getPort()<<"/api/"<<uName;

    Wt::Http::Client *client=new Wt::Http::Client(this);
    client->setTimeout(5);
    client->setMaximumResponseSize(10*1024);
    client->done().connect(boost::bind(&IndivBridgeManagerWidget::handleHttpResponse, this, client, _1, _2));
    client->get(url_);
}



/**
 * Handles Http Response from Bridge. Update currentstatus upon receiving successful response.
 * @param client HTTP client
 * @param err Error code
 * @param response HTTP message received
 *
 */
void IndivBridgeManagerWidget::handleHttpResponse(Wt::Http::Client *client, boost::system::error_code err,
                                                  const Wt::Http::Message &response) const {
    if(err||response.status()!=200) {
        cerr<<"Error: "<<err.message()<<" ,"<<response.status()<<endl;

    } else {
        currentStatus=response.body();
        cout<<currentStatus;
        cout<<"\n";
    }

    delete client;
}

//test main
int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<IndivBridgeManagerWidget>(env);
    });
}