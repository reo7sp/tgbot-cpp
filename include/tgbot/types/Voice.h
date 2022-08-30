#ifndef TGBOT_VOICE_H
#define TGBOT_VOICE_H

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a voice note.
 *
 * @ingroup types
 */
class Voice {
public:
    typedef std::shared_ptr<Voice> Ptr;

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
     * @brief Duration of the audio in seconds as defined by sender
     */
    std::int32_t duration;

    /**
     * @brief Optional. MIME type of the file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_VOICE_H
