#pragma once

#include "maxbot/types/Attachment.h"
#include "maxbot/types/MarkupElement.h"

namespace MaxBot {

/**
 * @brief Схема, представляющая тело сообщения
 */
class MessageBody
{
public:
    typedef std::shared_ptr<MessageBody> Ptr;

    /**
     * @brief Уникальный ID сообщения
     */
    std::string mid;

    /**
     * @brief ID последовательности сообщения в чате
     */
    std::int64_t seq;

    /**
     * @brief Новый текст сообщения
     */
    std::string text;

    /**
     * @brief Вложения сообщения. Могут быть одним из типов `Attachment`. Смотрите описание схемы
     */
    std::vector<Attachment::Ptr> attachments;

    /**
     * @brief Разметка текста сообщения. Для подробной информации загляните в раздел [Форматирование](/docs-api#Форматирование%20текста%20в%20сообщениях)
     */
    std::vector<MarkupElement::Ptr> markup;
};

} // namespace MaxBot
