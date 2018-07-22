//
// Created by Konstantin Kukin on 26/12/16.
//

#ifndef TGBOT_WEBHOOKINFO_H
#define TGBOT_WEBHOOKINFO_H

#include <string>
#include <vector>
#include <memory>

namespace TgBot {

/**
 * @brief Contains information about the current status of a webhook.
 * 
 * @ingroup types
 */
class WebhookInfo {
public:
    typedef std::shared_ptr<WebhookInfo> Ptr;

    /**
     * @brief Webhook URL, may be empty if webhook is not set up.
     */
    std::string url;

    /**
     * @brief True, if a custom certificate was provided for webhook certificate checks
     */
    bool hasCustomCertificate;

    /**
     * @brief Number of updates awaiting delivery
     */
    int32_t pendingUpdateCount;

    /**
     * @brief Optional. Unix time for the most recent error that happened when trying to deliver an update via webhook
     */
    int32_t lastErrorDate;

    /**
     * @brief Optional. Error message in human - readable format for the most recent error that happened when trying to deliver an update via webhook
     */
    std::string lastErrorMessage;

    /**
     * @brief Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery
     */
    int32_t maxConnections;

    /**
     * @brief Optional. A list of update types the bot is subscribed to. Defaults to all update types
     */
    std::vector<std::string> allowedUpdates;
};
}

#endif //TGBOT_WEBHOOKINFO_H
