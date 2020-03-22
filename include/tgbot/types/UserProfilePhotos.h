#ifndef TGBOT_CPP_USERPROFILEPHOTOS_H
#define TGBOT_CPP_USERPROFILEPHOTOS_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <vector>
#include <memory>

namespace TgBot {

/**
 * @brief This object represent a user's profile pictures.
 *
 * @ingroup types
 */
class UserProfilePhotos {

public:
    typedef std::shared_ptr<UserProfilePhotos> Ptr;

    /**
     * @brief Total number of profile pictures the target user has.
     */
    std::int32_t totalCount;

    /**
     * @brief Requested profile pictures (in up to 4 sizes each).
     */
    std::vector<std::vector<PhotoSize::Ptr>> photos;
};

}

#endif //TGBOT_CPP_USERPROFILEPHOTOS_H
