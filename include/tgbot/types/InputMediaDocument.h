#ifndef TGBOT_INPUTMEDIADOCUMENT_H
#define TGBOT_INPUTMEDIADOCUMENT_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a general file to be sent.
 * 
 * @ingroup types
 */
class InputMediaDocument : public InputMedia {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputMediaDocument> Ptr;

    InputMediaDocument() {
        this->type = TYPE;
    }

    /**
     * @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
     * The thumbnail should be in JPEG format and less than 200 kB in size.
     * A thumbnail's width and height should not exceed 320.
     * Ignored if the file is not uploaded using multipart/form-data.
     * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * https://core.telegram.org/bots/api#sending-files
     */
    std::string thumbnail;

    /**
     * @brief Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data.
     * Always true, if the document is sent as part of an album.
     */
    bool disableContentTypeDetection;
};
}

#endif //TGBOT_INPUTMEDIADOCUMENT_H
