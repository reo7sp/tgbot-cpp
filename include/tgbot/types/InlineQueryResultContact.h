#ifndef TGBOT_INLINEQUERYRESULTCONTACT_H
#define TGBOT_INLINEQUERYRESULTCONTACT_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a contact with a phone number.
 *
 * By default, this contact will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the contact.
 *
 * @ingroup types
 */
class InlineQueryResultContact : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultContact> Ptr;

    InlineQueryResultContact() {
        this->type = TYPE;
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
     * @brief Optional. Additional data about the contact in the form of a [vCard](https://en.wikipedia.org/wiki/VCard), 0-2048 bytes
     */
    std::string vcard;

    /**
     * @brief Optional. Content of the message to be sent instead of the contact
     */
    InputMessageContent::Ptr inputMessageContent;

    /**
     * @brief Optional. Url of the thumbnail for the result
     */
    std::string thumbnailUrl;

    /**
     * @brief Optional. Thumbnail width
     */
    std::int32_t thumbnailWidth;

    /**
     * @brief Optional. Thumbnail height
     */
    std::int32_t thumbnailHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTCONTACT_H
