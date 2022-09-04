#ifndef TGBOT_CPP_VOICECHATENDED_H
#define TGBOT_CPP_VOICECHATENDED_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about a voice chat ended in the chat.
 *
 * @ingroup types
 */
class VoiceChatEnded {

public:
    typedef std::shared_ptr<VoiceChatEnded> Ptr;

    /**
     * @brief This object represents a service message about a voice chat ended in the chat.
     */
    std::int32_t duration;
};
}

#endif //TGBOT_CPP_VOICECHATENDED_H
