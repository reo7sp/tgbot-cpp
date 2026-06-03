#pragma once

#include "maxbot/types/User.h"
#include "maxbot/types/MessageBody.h"

namespace MaxBot {

/**
 * @brief Связанное сообщение
 */
class LinkedMessage
{
public:
    typedef std::shared_ptr<LinkedMessage> Ptr;

    /**
     * @brief Тип связанного сообщения
     */
	std::string type; // Enum: [forward, reply]

    /**
     * @brief Пользователь, отправивший сообщение
     */
    User::Ptr sender;

    /**
     * @brief Чат, в котором сообщение было изначально опубликовано. Только для пересланных сообщений
     */
    std::int64_t chat_id;

    /**
     * @brief Тело сообщения
     */
    MessageBody::Ptr message;
};

} // namespace MaxBot
