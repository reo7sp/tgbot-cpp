#ifndef TGBOT_CPP_DOCUMENT_H
#define TGBOT_CPP_DOCUMENT_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a general file (as opposed to photos and audio files).
 *
 * @ingroup types
 */
class Document {

public:
    typedef std::shared_ptr<Document> Ptr;

    /**
     * @brief Unique file identifier.
     */
    std::string fileId;

    /**
     * @brief Optional. Document thumbnail as defined by sender.
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Original filename as defined by sender.
     */
    std::string fileName;

    /**
     * @brief Optional. MIME type of the file as defined by sender.
     */
    std::string mimeType;

    /**
     * @brief Optional. File size.
     */
    std::int32_t fileSize;
};

}

#endif //TGBOT_CPP_DOCUMENT_H
