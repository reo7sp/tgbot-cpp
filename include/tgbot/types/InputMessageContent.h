#ifndef TGBOT_INPUTMESSAGECONTENT_H
#define TGBOT_INPUTMESSAGECONTENT_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents the content of a message to be sent as a result of an inline query.
 * @ingroup types
 */
class InputMessageContent {
public:
    typedef std::shared_ptr<InputMessageContent> Ptr;

    InputMessageContent(const std::string &tType):
        type(tType)
    {}

    /**
     * May be
     * InputTextMessageContent
     * InputLocationMessageContent
     * InputVenueMessageContent
     * InputContactMessageContent
     */
    std::string type;

    virtual ~InputMessageContent() { }
};
}

#endif //TGBOT_INPUTMESSAGECONTENT_H
