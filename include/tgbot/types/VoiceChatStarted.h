#ifndef TGBOT_CPP_VOICECHATSTARTED_H
#define TGBOT_CPP_VOICECHATSTARTED_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about a voice chat started in the chat.
 * Currently holds no information.
 *
 * @ingroup types
 */
class VoiceChatStarted {

public:
    typedef std::shared_ptr<VoiceChatStarted> Ptr;
};
}

#endif //TGBOT_CPP_VOICECHATSTARTED_H
