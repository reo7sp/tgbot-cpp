#ifndef MAXBOT_EVENTHANDLER_H
#define MAXBOT_EVENTHANDLER_H

#include "maxbot/EventBroadcaster.h"
#include "maxbot/types/Update.h"
#include "maxbot/tools/StringTools.h"

#include <algorithm>
#include <cstddef>
#include <string>

namespace MaxBot {

class MAXBOT_API EventHandler {

public:
    explicit EventHandler(const EventBroadcaster& broadcaster) : _broadcaster(broadcaster) {
    }

    void handleUpdate(const Update::Ptr& update) const;

private:
    const EventBroadcaster& _broadcaster;

    void handleMessage(const Message::Ptr& message) const;
};

}

#endif //MAXBOT_EVENTHANDLER_H
