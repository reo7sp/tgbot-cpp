#ifndef TGBOT_WRITEACCESSALLOWED_H
#define TGBOT_WRITEACCESSALLOWED_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about a user allowing a bot added to the attachment menu to write messages.
 * 
 * Currently holds no information.
 *
 * @ingroup types
 */
class WriteAccessAllowed {
public:
    typedef std::shared_ptr<WriteAccessAllowed> Ptr;
};
}

#endif //TGBOT_WRITEACCESSALLOWED_H
