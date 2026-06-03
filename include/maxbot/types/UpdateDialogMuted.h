#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь отключит уведомления о новых сообщениях в диалоге с ботом
 */
class UpdateDialogMuted
{
public:
    typedef std::shared_ptr<UpdateDialogMuted> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который отключил уведомления
     */
	User::Ptr user;

    /**
     * @brief Время в формате Unix, до наступления которого диалог был отключён
     */
    std::int64_t muted_until;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
