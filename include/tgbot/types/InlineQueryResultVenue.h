//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTVENUE_H
#define TGBOT_INLINEQUERYRESULTVENUE_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * Represents a venue. 
 * @ingroup types
 */
class InlineQueryResultVenue : public InlineQueryResult {
public:
	static const std::string TYPE;

	typedef std::shared_ptr<InlineQueryResultVenue> Ptr;

	InlineQueryResultVenue() {
		this->type = TYPE;
		this->thumbHeight = 0;
		this->thumbWidth = 0;
	}

	/**
	* Latitude of the venue location in degrees
	*/
	float latitude;

	/**
	* Longitude of the venue location in degrees
	*/
	float longitude;

	/**
	* Address of the venue
	*/
	std::string address;

	/**
	* Optional. Foursquare identifier of the venue if known
	*/
	std::string foursquareId;

	/**
	 * Optional. Url of the thumbnail for the result
	 */
	std::string thumbUrl;

	/**
	 * Optional. Thumbnail width.
	 */
	int32_t thumbWidth;

	/**
	 * Optinal. Thumbnail height
	 */
	int32_t thumbHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTVENUE_H
