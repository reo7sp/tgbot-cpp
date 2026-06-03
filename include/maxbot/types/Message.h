#pragma once

#include "maxbot/types/User.h"
#include "maxbot/types/Recipient.h"
#include "maxbot/types/LinkedMessage.h"
#include "maxbot/types/MessageBody.h"
#include "maxbot/types/MessageStat.h"

namespace MaxBot {

/**
 * @brief Сообщение в чате
 */
class Message
{
public:
    typedef std::shared_ptr<Message> Ptr;

    /**
     * @brief Пользователь, отправивший сообщение
     */
    User::Ptr sender;

    /**
     * @brief Получатель сообщения. Может быть пользователем или чатом
     */
    Recipient::Ptr recipient;

    /**
     * @brief Время создания сообщения в формате Unix-time
     */
    std::int64_t timestamp;

    /**
     * @brief Пересланное или ответное сообщение
     */
    LinkedMessage::Ptr link;

    /**
     * @brief Содержимое сообщения. Текст + вложения. Может быть `null`, если сообщение содержит только пересланное сообщение
     */
    MessageBody::Ptr body;

    /**
     * @brief Статистика сообщения. Возвращается только для постов в каналах
     */
    MessageStat::Ptr stat;

    /**
     * @brief Публичная ссылка на пост в канале. Отсутствует для диалогов и групповых чатов
     */
    std::string url;
};

} // namespace MaxBot
