#ifndef TGBOT_DOCUMENT_H
#define TGBOT_DOCUMENT_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a general file (as opposed to photos, voice messages and audio files).
 *
 * @ingroup types
 */
class Document {

public:
    typedef std::shared_ptr<Document> Ptr;

    /**
     * @brief Identifier for this file, which can be used to download or reuse the file
     */
    std::string fileId;

    /**
     * @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
     * Can't be used to download or reuse the file.
     */
    std::string fileUniqueId;

    /**
     * @brief Optional. Document thumbnail as defined by sender
     */
    PhotoSize::Ptr thumbnail;

    /**
     * @brief Optional. Original filename as defined by sender
     */
    std::string fileName;

    /**
     * @brief Optional. MIME type of the file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size in bytes.
     * 
     * It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
     */
    std::int64_t fileSize;
};
}

#endif //TGBOT_DOCUMENT_H
