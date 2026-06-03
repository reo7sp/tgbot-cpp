#pragma once

#include "maxbot/types/NewMessageBody.h"

namespace MaxBot {

/**
 * @brief Отправьте этот объект, когда ваш бот хочет отреагировать на нажатие кнопки
 */
class CallbackAnswer
{
public:
    typedef std::shared_ptr<CallbackAnswer> Ptr;

    /**
     * @brief Заполните это, если хотите изменить текущее сообщение
     */
    NewMessageBody::Ptr message;

    /**
     * @brief Заполните это, если хотите просто отправить одноразовое уведомление пользователю
     */
	std::string notification;
};

} // namespace MaxBot
