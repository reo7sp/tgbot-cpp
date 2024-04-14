#ifndef TGBOT_WRITEACCESSALLOWED_H
#define TGBOT_WRITEACCESSALLOWED_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a service message about a user allowing a bot to write messages after adding the bot to the attachment menu or launching a Web App from a link.
 *
 * @ingroup types
 */
class WriteAccessAllowed {
public:
    typedef std::shared_ptr<WriteAccessAllowed> Ptr;

    /**
     * @brief Optional. Name of the Web App which was launched from a link
     */
    std::string webAppName;
};
}

#endif //TGBOT_WRITEACCESSALLOWED_H
