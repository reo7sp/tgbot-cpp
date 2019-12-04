#ifndef TGBOT_CHATPHOTO_H
#define TGBOT_CHATPHOTO_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a chat photo.
 * @ingroup types
 */
class ChatPhoto {
public:
    typedef std::shared_ptr<ChatPhoto> Ptr;

    /**
     * @brief Unique file identifier of small (160x160) chat photo. This file_id can be used only for photo download.
     */
    std::string smallFileId;

    /**
     * @brief Unique file identifier of big (640x640) chat photo. This file_id can be used only for photo download.
     */
    std::string bigFileId;
};
}

#endif //TGBOT_CHATPHOTO_H
