#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь будет добавлен в чат, где бот является администратором
 */
class UpdateUserAddedToChat
{
public:
    typedef std::shared_ptr<UpdateUserAddedToChat> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, добавленный в чат
     */
	User::Ptr user;

    /**
     * @brief Пользователь, который добавил нового пользователя в чат. Может быть `null`, если пользователь присоединился к чату по ссылке
     */
    std::int64_t inviter_id;

    /**
     * @brief Указывает, что пользователь добавлен в канал, а не в чат
     */
    bool is_channel;
};

} // namespace MaxBot
