#pragma once

#include "maxbot/types/User.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только будет изменено название чата
 */
class UpdateChatTitleChanged
{
public:
    typedef std::shared_ptr<UpdateChatTitleChanged> Ptr;

    /**
     * @brief ID чата, где произошло событие
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, который изменил название
     */
	User::Ptr user;

    /**
     * @brief Новое название
     */
    std::string title;
};

} // namespace MaxBot
