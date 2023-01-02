#ifndef TGBOT_INPUTMEDIA_H
#define TGBOT_INPUTMEDIA_H

#include "tgbot/types/MessageEntity.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This abstract class is base of all input media.
 * 
 * This object represents the content of a media message to be sent.
 *
 * @ingroup types
 */
class InputMedia {
public:
    typedef std::shared_ptr<InputMedia> Ptr;

    InputMedia() {}

    virtual ~InputMedia() {}

    /**
     * @brief Type of the result
     */
    std::string type;

    /**
     * @brief File to send.
     * 
     * Pass a fileId to send a file that exists on the Telegram servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or pass “attach://<file_attach_name>” to upload a new one using multipart/form-data under <file_attach_name> name.
     * https://core.telegram.org/bots/api#sending-files
     */
    std::string media;

    /**
     * @brief Optional. Caption of the media to be sent, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the media caption.
     * 
     * See https://core.telegram.org/bots/api#formatting-options for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;
};
}

#endif //TGBOT_INPUTMEDIA_H
