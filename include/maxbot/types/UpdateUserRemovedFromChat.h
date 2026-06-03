#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь будет удалён из чата, где бот является администратором
 */
class UpdateUserRemovedFromChat
{
public:
    typedef std::shared_ptr<UpdateUserRemovedFromChat> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, удалённый из чата
     */
	User::Ptr user;

    /**
     * @brief Администратор, который удалил пользователя из чата. Может быть `null`, если пользователь покинул чат сам
     */
    std::int64_t admin_id;

    /**
     * @brief Указывает, что пользователь удалён из канала, а не из чата
     */
    bool is_channel;
};

} // namespace MaxBot
