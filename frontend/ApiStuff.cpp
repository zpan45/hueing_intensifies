/*
 * API Code
 * https://www.developers.meethue.com/documentation/lights-api
 *
 * Lights, Groups, Schedule
 */
#include <sstream>
#include <Wt/WString.h>
#include <Wt/Http/Client>
#include <Wt/HTTP/Message.h> //Pack the JSONs into Message to send to api

//
stringstream url_ = "/api/";

/*
 * Handling API Requests and Response
 */

auto client = addChild(std::make_unique<Http::Client>());
client->setTimeout(std::chrono::seconds{15});
client->setMaximumResponseSize(10 * 1024);
client->done().connect(std::bind(&MyWidget::handleHttpResponse, this, _1, _2));
if (client->//GET/POST/PUT/requestDelete Method here)
{
  WApplication::instance()->deferRendering();
  else {
    // in case of an error in the %URL/client could not schedule request
  }
}
void handleHttpResponse(std::system::error_code err, const Http::Message& response)
{
  WApplication::instance()->resumeRendering();
  if (!err && response.status() == 200) {
    //result holds the response JSON
    Json::Object result;
    //body() returns the JSON Text body of the response as a string
    Json::parse(response.body(), result);
    //example: stores name of the light in WString s
    WString s = result.get("name");
  }
}



 /*
  * Lights
  */

//Get All Lights
//Returns JSON with ALL light Name, state(on, bri, hue, etc.)
url_ << username << "/lights";
get(url_);

//Get NEW Lights
url_ << username << "/lights/new";
get(url_);

//Search for new Lights
//Provides a list of lights available for get NEW lights
url_ << username << "/lights";
post(url_);
  //Optional body: {"deviceid":["45AF34","543636","34AFBE"]}

//Get light attribute and state
//Returns JSON with Name, state(on, bri, hue, etc.)
url_ << username << "/lights/" << id;
get(url_);

int hue = result.get("hue");
bool on = result.get("on");
WString effect = result.get("effect");
WString alert = result.get("alert");
int brightness = result.get("bri");
int saturation = result.get("sat");
int ct = result.get("ct");
idktype xy = result.get("xy");
bool reachable = result.get("reachable");
WString colourMode = result.get("colormode");

WString name = result.get("name");
WString type = result.get("type");
WString modelID = result.get("modelid");


//Set Light attributes (set name/rename)
url_ << username << "/lights/" << id;
put(url_, Message);
  //Body: {"name":"Bedroom Light"}
stringstream msg = "{";
//Set name
msg << ""name":" << """ << lightName << ""}";
Message.addBodyText(msg.str());


//Set Light state
//See documentation for JSON attributes
url_ << username << "/lights/" << id << "/state";
put(url_, Message);
// Body:
// {
// 	"hue": 50000,
// 	"on": true,
// 	"bri": 200
//  }

stringstream msg = "{\n";
//Set "on" or anything, one at a time
msg << "\t"on":" << onBool << ",\n}";
Message.addBodyText(msg.str());


//Delete Light
url_ << username << "/lights/" << id;
deleteRequest(url_);


/*
 * Groups
 * https://www.developers.meethue.com/documentation/groups-api
 */

//Get all groups
url_ << username << "/groups";
get(url_);

//Create group
url_ << username << "/groups";
post(url_, Message);
// Body Example:
// {
// 	"lights": [
// 		"1",
// 		"2"
// 	],
// 	"name": "bedroom",
//         "type": "LightGroup"
// }
//
// {
//     "name": "Living room",
//     "type": "Room",
//     "class": "Living room",
//     "lights": [
//         "3",
//         "4"
//     ]
// }

stringstream msg = "{\n";
//Set name
msg << "\t"lights": [" << """ << uhhlightid? << "",\n}";
Message.addBodyText(msg.str());


//Get group attributes
url_ << username << "/groups" << id;
get(url_);

//Set group state
url_ << username << "/groups" << id << "/action";
put(url_, Message);
// Body Example
// {
// 	"on": true,
// 	"hue": 2000,
// 	"effect": "colorloop"
// }

//Delete group
url_ << username << "/groups" << id;
deleteRequest(url_);


/*
 * Schedule
 * https://www.developers.meethue.com/documentation/schedules-api-0
 */

//Get all schedules
url_ << username << "/schedules";
get(url_);

//Create schedule
url_ << username << "/schedules";
post(url_, Message);
// Body Example:
// {
// 	"name": "Wake up",
// 	"description": "My wake up alarm",
// 	"command": {
// 		"address": "/api/<username>/groups/1/action",
// 		"method": "PUT",
// 		"body": {
// 			"on": true
// 		}
// 	},
// 	"localtime": "2015-06-30T14:24:40"
// }

//Get schedule attributes
url_ << username << "/schedules" << id;
get(url_);

//Set Schedule attributes
url_ << username << "/schedules" << id;
put(url_, Message);
// Body Example:
// {
// 	"name": "Wake up"
// }

//Delete schedule
url_ << username << "/schedules" << id;
deleteRequest(url_);
