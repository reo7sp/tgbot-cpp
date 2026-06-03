#ifndef MAXBOT_INPUTMESSAGECONTENT_H
#define MAXBOT_INPUTMESSAGECONTENT_H

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief This abstract class is base of all message contents.
 * 
 * This object represents the content of a message to be sent as a result of an inline query.
 * 
 * @ingroup types
 */
class InputMessageContent {
public:
    typedef std::shared_ptr<InputMessageContent> Ptr;

    InputMessageContent() {}

    virtual ~InputMessageContent() {}

    /**
     * @brief Type of the content
     */
    std::string type;
};
}

#endif //MAXBOT_INPUTMESSAGECONTENT_H
