#pragma once

#include "maxbot/types/Callback.h"
#include "maxbot/types/Message.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь нажмёт кнопку
 */
class UpdateMessageCallback
{
public:
    typedef std::shared_ptr<UpdateMessageCallback> Ptr;

    /**
     * @brief 
     */
	Callback::Ptr callback;

    /**
     * @brief Изначальное сообщение, содержащее встроенную клавиатуру. Может быть `null`, если оно было удалено к моменту, когда бот получил это событие
     */
	Message::Ptr message;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
