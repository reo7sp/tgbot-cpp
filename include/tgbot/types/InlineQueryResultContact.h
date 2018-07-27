//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTCONTACT_H
#define TGBOT_INLINEQUERYRESULTCONTACT_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a contact with a phone number
 * 
 * @ingroup types
 */
class InlineQueryResultContact : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultContact> Ptr;

    InlineQueryResultContact() {
        this->type = TYPE;
        this->thumbHeight = 0;
        this->thumbWidth = 0;
    }

    /**
     * @brief Contact's phone number
     */
    std::string phoneNumber;

    /**
     * @brief Contact's first name
     */
    std::string firstName;

    /**
     * @brief Optional. Contact's last name
     */
    std::string lastName;

    /**
     * @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
     */
    std::string vcard;

    /**
    * @brief Optional. Url of the thumbnail for the result
    */
    std::string thumbUrl;

    /**
    * @brief Optional. Thumbnail width.
    */
    int32_t thumbWidth;

    /**
    * @brief Optinal. Thumbnail height
    */
    int32_t thumbHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTCONTACT_H
