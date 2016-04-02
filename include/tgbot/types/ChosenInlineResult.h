//
// Created by Andrea Giove on 27/03/16.
//

#ifndef TGBOT_CHOSENINLINERESULT_H
#define TGBOT_CHOSENINLINERESULT_H

#include <string>
#include <memory>

#include "tgbot/types/User.h"

namespace TgBot {

/**
 * This object represents a result of an inline query that was chosen by the user and sent to their chat partner.
 * @ingroup types
 */
class ChosenInlineResult {
public:
	typedef std::shared_ptr<ChosenInlineResult> Ptr;

	/**
	 * The unique identifier for the result that was chosen.
	 */
	std::string resultId;

	/**
	 * The user that chose the result.
	 */
	User::Ptr from;

	/**
	 * The query that was used to obtain the result.
	 */
	std::string query;
};
}

#endif //TGBOT_CHOSENINLINERESULT_H
