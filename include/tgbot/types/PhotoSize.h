#ifndef TGBOT_CPP_PHOTOSIZE_H
#define TGBOT_CPP_PHOTOSIZE_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents one size of a photo or a file / sticker thumbnail.
 *
 * @ingroup types
 */
class PhotoSize {

public:
    typedef std::shared_ptr<PhotoSize> Ptr;

    /**
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Photo width.
     */
    std::int32_t width;

    /**
     * @brief Photo height.
     */
    std::int32_t height;

    /**
     * @brief Optional. File size.
     */
    std::int32_t fileSize;
};

}

#endif //TGBOT_CPP_PHOTOSIZE_H
