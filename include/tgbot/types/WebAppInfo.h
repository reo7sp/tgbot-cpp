#ifndef TGBOT_WEBAPPINFO_H
#define TGBOT_WEBAPPINFO_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Contains information about a Web App.
 *
 * @ingroup types
 */
class WebAppInfo {

public:
    typedef std::shared_ptr<WebAppInfo> Ptr;

    /**
     * @brief An HTTPS URL of a Web App to be opened with additional data as specified in https://core.telegram.org/bots/webapps#initializing-web-apps
     */
    std::string url;
};
}

#endif //TGBOT_WEBAPPINFO_H
