/*
 * API Code
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

//Selete Light
url_ << username << "/lights/" << id;
put(url_);
