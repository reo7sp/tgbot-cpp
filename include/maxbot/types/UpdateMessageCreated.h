#pragma once

#include "maxbot/types/Message.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только сообщение будет создано
 */
class UpdateMessageCreated
{
public:
    typedef std::shared_ptr<UpdateMessageCreated> Ptr;

    /**
     * @brief Новое созданное сообщение
     */
	Message::Ptr message;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47. Доступно только в диалогах
     */
    std::string user_locale;
};

} // namespace MaxBot
