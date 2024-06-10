#ifndef TGBOT_GIVEAWAY_H
#define TGBOT_GIVEAWAY_H

#include "tgbot/types/Chat.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a message about a scheduled giveaway.
 *
 * @ingroup types
 */
class Giveaway {

public:
    typedef std::shared_ptr<Giveaway> Ptr;

    /**
     * @brief The list of chats which the user must join to participate in the giveaway
     */
    std::vector<Chat::Ptr> chats;

    /**
     * @brief Point in time (Unix timestamp) when winners of the giveaway will be selected
     */
    std::uint32_t winnersSelectionDate;

    /**
     * @brief The number of users which are supposed to be selected as winners of the giveaway
     */
    std::int32_t winnerCount;

    /**
     * @brief Optional. True, if only users who join the chats after the giveaway started should be eligible to win
     */
    bool onlyNewMembers;

    /**
     * @brief Optional. True, if the list of giveaway winners will be visible to everyone
     */
    bool hasPublicWinners;

    /**
     * @brief Optional. Description of additional giveaway prize
     */
    std::string prizeDescription;

    /**
     * @brief Optional. A list of two-letter [ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2) country codes indicating the countries from which eligible users for the giveaway must come.
     *
     * If empty, then all users can participate in the giveaway.
     * Users with a phone number that was bought on Fragment can always participate in giveaways.
     */
    std::vector<std::string> countryCodes;

    /**
     * @brief Optional. The number of months the Telegram Premium subscription won from the giveaway will be active for
     */
    std::int32_t premiumSubscriptionMonthCount;
};
}

#endif //TGBOT_GIVEAWAY_H
