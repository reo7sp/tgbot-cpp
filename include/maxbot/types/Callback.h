#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Объект, отправленный боту, когда пользователь нажимает кнопку
 */
class Callback
{
public:
    typedef std::shared_ptr<Callback> Ptr;

    /**
     * @brief Unix-время, когда пользователь нажал кнопку
     */
    std::int64_t timestamp;

    /**
     * @brief Текущий ID клавиатуры
     */
    std::string callback_id;

    /**
     * @brief Токен кнопки
     */
    std::string payload;

    /**
     * @brief Пользователь, нажавший на кнопку
     */
    User::Ptr user;
};

} // namespace MaxBot
