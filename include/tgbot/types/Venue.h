//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_VENUE_H
#define TGBOT_VENUE_H

#include <memory>
#include <string>

#include "tgbot/types/Location.h"

namespace TgBot {

/**
 * This object represents a venue.
 * @ingroup types
 */
class Venue {
public:
	typedef std::shared_ptr<Venue> Ptr;

	/**
	 * Venue location.
	 */
	Location::Ptr location;

	/**
	 * Name of the venue.
	 */
	std::string title;

	/**
	 * Address of the venue.
	 */
	std::string address;

	/**
	 * Optional. Foursquare identifier of the venue.
	 */
	std::string foursquare_id;
};
}

#endif //TGBOT_VENUE_H
