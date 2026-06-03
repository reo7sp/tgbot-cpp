#pragma once

#include "maxbot/types/AttachmentRequest.h"

namespace MaxBot {

/**
 * @brief Ссылка на сообщение
 */
class NewMessageLink
{
public:
    typedef std::shared_ptr<NewMessageLink> Ptr;

    /**
     * @brief Тип ссылки сообщения
	 * Enum: [forward, reply]
     */
	std::string type;

    /**
     * @brief ID сообщения исходного сообщения
     */
    std::string mid;
};

/**
 * @brief Тело нового сообщения
 */
class NewMessageBody
{
public:
    typedef std::shared_ptr<NewMessageBody> Ptr;

    /**
     * @brief Новый текст сообщения
     */
    std::string text;

    /**
     * @brief Вложения сообщения. Если пусто, все вложения будут удалены
     */
    std::vector<AttachmentRequest::Ptr> attachments;

    /**
     * @brief Ссылка на сообщение
     */
    NewMessageLink::Ptr link;

    /**
     * @brief Если false, участники чата не будут уведомлены (по умолчанию `true`)
     */
    bool notify = true;

    /**
     * @brief Если установлен, текст сообщения будет форматирован данным способом. 
     * Для подробной информации загляните в раздел [Форматирование](/docs-api#Форматирование%20текста%20в%20сообщениях)
	 * Enum: [markdown, html]
     */
	std::string format;
};

} // namespace MaxBot
