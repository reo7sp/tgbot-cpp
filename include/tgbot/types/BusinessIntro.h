#ifndef TGBOT_BUSINESSINTRO_H
#define TGBOT_BUSINESSINTRO_H

#include "tgbot/types/Sticker.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @ingroup types
 */
class BusinessIntro {

public:
    typedef std::shared_ptr<BusinessIntro> Ptr;

    /**
     * @brief Optional. Title text of the business intro
     */
    std::string title;

    /**
     * @brief Optional. Message text of the business intro
     */
    std::string message;

    /**
     * @brief Optional. Sticker of the business intro
     */
    Sticker::Ptr sticker;
};
}

#endif //TGBOT_BUSINESSINTRO_H
