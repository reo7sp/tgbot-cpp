#ifndef TGBOT_INPUTSTICKER_H
#define TGBOT_INPUTSTICKER_H

#include "tgbot/types/MaskPosition.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object describes a sticker to be added to a sticker set.
 *
 * @ingroup types
 */
class InputSticker {

public:
    typedef std::shared_ptr<InputSticker> Ptr;

    /**
     * @brief The added sticker.
     *
     * Pass a fileId as a String to send a file that already exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the Internet, upload a new one using multipart/form-data, or pass “attach://<file_attach_name>” to upload a new one using multipart/form-data under <file_attach_name> name.
     * Animated and video stickers can't be uploaded via HTTP URL.
     * [More information on Sending Files »](https://core.telegram.org/bots/api#sending-files)
     */
    std::string sticker;

    /**
     * @brief Format of the added sticker, must be one of “static” for a .WEBP or .PNG image, “animated” for a .TGS animation, “video” for a WEBM video
     */
    std::string format;

    /**
     * @brief List of 1-20 emoji associated with the sticker
     */
    std::vector<std::string> emojiList;

    /**
     * @brief Optional. Position where the mask should be placed on faces.
     *
     * For “mask” stickers only.
     */
    MaskPosition::Ptr maskPosition;

    /**
     * @brief Optional. List of 0-20 search keywords for the sticker with total length of up to 64 characters.
     *
     * For “regular” and “custom_emoji” stickers only.
     */
    std::vector<std::string> keywords;
};
}

#endif //TGBOT_INPUTSTICKER_H
