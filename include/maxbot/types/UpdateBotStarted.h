#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь начнёт или возобновит общение с ботом: нажмёт соответствующую кнопку в настройках бота в МАКС
 */
class UpdateBotStarted
{
public:
    typedef std::shared_ptr<UpdateBotStarted> Ptr;

    /**
     * @brief ID диалога, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который нажал кнопку `Start`
     */
	User::Ptr user;

    /**
     * @brief Дополнительные данные из диплинков, переданные при запуске бота
     */
    std::string payload;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
