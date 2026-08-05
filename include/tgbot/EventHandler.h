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

    void handleUpdate(const Update::Ptr& update) const;

private:
    const EventBroadcaster& _broadcaster;

    void handleMessage(const Message::Ptr& message) const;
};

} // namespace TgBot
