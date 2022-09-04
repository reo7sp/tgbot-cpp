#ifndef TGBOT_CPP_VOICECHATPARTICIPANTSINVITED_H
#define TGBOT_CPP_VOICECHATPARTICIPANTSINVITED_H

#include "tgbot/types/User.h"

#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a service message about new members invited to a voice chat.
 *
 * @ingroup types
 */
class VoiceChatParticipantsInvited {

public:
    typedef std::shared_ptr<VoiceChatParticipantsInvited> Ptr;

    /**
     * @brief Optional. New members that were invited to the voice chat
     */
    std::vector<User::Ptr> users;
};
}

#endif //TGBOT_CPP_VOICECHATPARTICIPANTSINVITED_H
