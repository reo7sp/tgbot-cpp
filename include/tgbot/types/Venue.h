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
 * @brief This object represents a venue.
 * 
 * @ingroup types
 */
class Venue {
public:
	typedef std::shared_ptr<Venue> Ptr;

	/**
	 * @brief Venue location.
	 */
	Location::Ptr location;

	/**
	 * @brief Name of the venue.
	 */
	std::string title;

	/**
	 * @brief Address of the venue.
	 */
	std::string address;

	/**
	 * @brief Optional. Foursquare identifier of the venue.
	 */
	std::string foursquare_id;
};
}

#endif //TGBOT_VENUE_H
