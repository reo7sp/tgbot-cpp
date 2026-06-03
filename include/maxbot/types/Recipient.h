#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief Новый получатель сообщения. Может быть пользователем или чатом
 */
class Recipient
{
public:
    typedef std::shared_ptr<Recipient> Ptr;

    /**
     * @brief ID чата
     */
    std::int64_t chat_id;

    /**
     * @brief Тип чата
     */
	std::string chat_type; // Enum: [chat, dialog, channel]

    /**
     * @brief ID пользователя, если сообщение было отправлено пользователю
     */
    std::int64_t user_id;
};

} // namespace MaxBot
