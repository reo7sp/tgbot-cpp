//
// Created by Konstantin Kukin on 26/12/16.
//


#ifndef TGBOT_INPUTVENUEMESSAGECONTENT_H
#define TGBOT_INPUTVENUEMESSAGECONTENT_H

#include <memory>
#include <string>

namespace TgBot {

/**
* Represents the content of a venue message to be sent as the result of an inline query.
* @ingroup types
*/
class InputVenueMessageContent : public InputMessageContent {
public:
	typedef std::shared_ptr<InputVenueMessageContent> Ptr;

	InputVenueMessageContent() :
		InputMessageContent("InputVenueMessageContent")
	{}

	/**
	* Latitude of the location in degrees
	*/
	float latitude;

	/**
	* Longitude of the location in degrees
	*/
	float longitude;

	/**
	 * Name of the venue
	 */
	std::string title; 

	/**
	* Address of the venue
	*/
	std::string address;

	/**
	* Optional. Foursquare identifier of the venue, if known
	*/
	std::string foursquareId;

	virtual ~InputVenueMessageContent() { }
};
}

#endif //TGBOT_INPUTVENUEMESSAGECONTENT_H
