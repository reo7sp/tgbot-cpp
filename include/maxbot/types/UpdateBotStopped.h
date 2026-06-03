#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь остановит бота в его настройках в МАКС
 */
class UpdateBotStopped
{
public:
    typedef std::shared_ptr<UpdateBotStopped> Ptr;

    /**
     * @brief ID диалога, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который остановил бота
     */
	User::Ptr user;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
