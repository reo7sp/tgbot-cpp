#ifndef TGBOT_VIDEOCHATPARTICIPANTSINVITED_H
#define TGBOT_VIDEOCHATPARTICIPANTSINVITED_H

#include "tgbot/types/User.h"

#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a service message about new members invited to a video chat.
 *
 * @ingroup types
 */
class VideoChatParticipantsInvited {

public:
    typedef std::shared_ptr<VideoChatParticipantsInvited> Ptr;

    /**
     * @brief New members that were invited to the video chat
     */
    std::vector<User::Ptr> users;
};
}

#endif //TGBOT_VIDEOCHATPARTICIPANTSINVITED_H
