#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только бот будет удалён из чата
 */
class UpdateBotRemovedFromChat
{
public:
    typedef std::shared_ptr<UpdateBotRemovedFromChat> Ptr;

    /**
     * @brief ID чата, откуда был удалён бот
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, удаливший бота из чата
     */
	User::Ptr user;

    /**
     * @brief Указывает, что бот удалён из канала, а не из чата
     */
    bool is_channel;
};

} // namespace MaxBot
