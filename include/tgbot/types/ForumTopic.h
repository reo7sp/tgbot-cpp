#ifndef TGBOT_FORUMTOPIC_H
#define TGBOT_FORUMTOPIC_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a forum topic.
 *
 * @ingroup types
 */
class ForumTopic {
public:
    typedef std::shared_ptr<ForumTopic> Ptr;

    /**
     * @brief Unique identifier of the forum topic
     */
    std::int32_t messageThreadId;

    /**
     * @brief Name of the topic
     */
    std::string name;

    /**
     * @brief Color of the topic icon in RGB format
     */
    std::int32_t iconColor;

    /**
     * @brief Optional. Unique identifier of the custom emoji shown as the topic icon
     */
    std::string iconCustomEmojiId;
};
}

#endif //TGBOT_FORUMTOPIC_H
