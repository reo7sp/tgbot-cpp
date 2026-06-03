#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только бот будет добавлен в чат или канал
 */
class UpdateBotAddedToChat
{
public:
    typedef std::shared_ptr<UpdateBotAddedToChat> Ptr;

    /**
     * @brief ID чата, куда был добавлен бот
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, добавивший бота в чат
     */
	User::Ptr user;

    /**
     * @brief Указывает, что бот добавлен в канал, а не в чат
     */
    bool is_channel;
};

} // namespace MaxBot
