#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь удалит чат
 */
class UpdateDialogRemoved
{
public:
    typedef std::shared_ptr<UpdateDialogRemoved> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который удалил чат
     */
	User::Ptr user;

    /**
     * @brief Текущий язык пользователя в формате IETF BCP 47
     */
    std::string user_locale;
};

} // namespace MaxBot
