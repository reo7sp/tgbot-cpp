#ifndef MAXBOT_WEBAPPINFO_H
#define MAXBOT_WEBAPPINFO_H

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief Describes a Web App.
 * 
 * https://core.telegram.org/bots/webapps
 *
 * @ingroup types
 */
class WebAppInfo {

public:
    typedef std::shared_ptr<WebAppInfo> Ptr;

    /**
     * @brief An HTTPS URL of a Web App to be opened with additional data as specified in Initializing Web Apps (https://core.telegram.org/bots/webapps#initializing-mini-apps)
     */
    std::string url;
};
}

#endif //MAXBOT_WEBAPPINFO_H
