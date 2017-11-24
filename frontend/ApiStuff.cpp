/*
 * API Code
 * https://www.developers.meethue.com/documentation/lights-api
 *
 * Lights, Groups, Schedule
 */
#include <sstream>
#include <Wt/Http/Client>

//
stringstream url_ = "/api/";

 /*
  * Lights
  */

//Get All Lights
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
url_ << username << "/lights/" << id;
get(url_);

//Set Light attributes (set name/rename)
url_ << username << "/lights/" << id;
put(url_, Message);
  //Body: {"name":"Bedroom Light"}

//Set Light state
url_ << username << "/lights/" << id << "/state";
put(url_, Message);
// Body:
// {
// 	"hue": 50000,
// 	"on": true,
// 	"bri": 200
//  }

//Delete Light
url_ << username << "/lights/" << id;
DELETE(url_);


/*
 * Groups
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
// {
//     "name": "Living room",
//     "type": "Room",
//     "class": "Living room",
//     "lights": [
//         "3",
//         "4"
//     ]
// }

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
DELETE(url_);


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
DELETE(url_);
