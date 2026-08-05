#pragma once

#include "tgbot/EventBroadcaster.h"
#include "tgbot/export.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/Update.h"

namespace TgBot {

class TGBOT_API EventHandler {

public:
    explicit EventHandler(const EventBroadcaster& broadcaster);

    void handleUpdate(const Update::Ptr& update) const;

private:
    const EventBroadcaster& _broadcaster;

    void handleMessage(const Message::Ptr& message) const;
};

} // namespace TgBot
