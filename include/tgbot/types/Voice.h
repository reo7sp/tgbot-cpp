#ifndef TGBOT_VOICE_H
#define TGBOT_VOICE_H

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
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Duration of the audio in seconds as defined by sender.
     */
    int32_t duration;

    /**
     * @brief Optional. MIME type of the file as defined by sender;
     */
    std::string mimeType;

    /**
     * @brief Optional. File size.
     */
    int32_t fileSize;
};
}

#endif //TGBOT_VOICE_H
