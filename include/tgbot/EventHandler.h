#ifndef TGBOT_EVENTHANDLER_H
#define TGBOT_EVENTHANDLER_H

#include "tgbot/EventBroadcaster.h"
#include "tgbot/types/Update.h"
#include "tgbot/tools/StringTools.h"

namespace TgBot {

class TGBOT_API EventHandler {

public:
    explicit EventHandler(const EventBroadcaster& broadcaster) : _broadcaster(broadcaster) {
    }

    void handleUpdate(const Update::Ptr& update) const;

private:
    const EventBroadcaster& _broadcaster;

    void handleMessage(const Message::Ptr& message) const;
};

}

#endif //TGBOT_EVENTHANDLER_H
