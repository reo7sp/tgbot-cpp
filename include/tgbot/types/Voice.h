//
// Created by Andrea Giove on 17/04/16.
//

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
    std::string file_id;

    /**
     * @brief Duration of the audio in seconds as defined by sender.
     */
    int32_t duration;

    /**
     * @brief Optional. MIME type of the file as defined by sender;
     */
    std::string mime_type;

    /**
     * @brief Optional. File size.
     */
    int32_t file_size;
};
}

#endif //TGBOT_VOICE_H
