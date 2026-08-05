#pragma once

#include "tgbot/EventBroadcaster.h"
#include "tgbot/Types.h"
#include "tgbot/export.h"

namespace TgBot {

/**
 * @ingroup general
 */
class TGBOT_API EventHandler {
public:
    explicit EventHandler(const EventBroadcaster& broadcaster);

    void handleUpdate(const std::shared_ptr<Update>& update) const;

private:
    const EventBroadcaster& _broadcaster;

    void handleMessage(const std::shared_ptr<Message>& message) const;
};

} // namespace TgBot
