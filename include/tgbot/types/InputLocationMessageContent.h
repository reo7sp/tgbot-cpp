#ifndef TGBOT_INPUTLOCATIONMESSAGECONTENT_H
#define TGBOT_INPUTLOCATIONMESSAGECONTENT_H

#include <memory>

namespace TgBot {

/**
 * @brief Represents the content of a location message to be sent as the result of an inline query.
 *
 * @ingroup types
 */
class InputLocationMessageContent : public InputMessageContent {
public:
    typedef std::shared_ptr<InputLocationMessageContent> Ptr;

    InputLocationMessageContent() :
        InputMessageContent("InputLocationMessageContent")
    {}

    /**
     * @brief Latitude of the location in degrees
     */
    float latitude;

    /**
     * @brief Longitude of the location in degrees
     */
    float longitude;

    virtual ~InputLocationMessageContent() { }
};
}

#endif //TGBOT_INPUTLOCATIONMESSAGECONTENT_H
