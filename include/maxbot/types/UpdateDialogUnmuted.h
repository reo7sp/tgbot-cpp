#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь включит уведомления о новых сообщениях в диалоге с ботом
 */
class UpdateDialogUnmuted
{
public:
    typedef std::shared_ptr<UpdateDialogUnmuted> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который включил уведомления
     */
	User::Ptr user;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
