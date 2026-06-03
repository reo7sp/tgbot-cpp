#pragma once

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только сообщение будет удалено
 */
class UpdateMessageRemoved
{
public:
    typedef std::shared_ptr<UpdateMessageRemoved> Ptr;

    /**
     * @brief ID удалённого сообщения
     */
    std::string message_id;

    /**
     * @brief ID чата, где сообщение было удалено
     */
    std::int64_t chat_id;

    /**
     * @brief Пользователь, удаливший сообщение
     */
    std::int64_t user_id;
};

} // namespace MaxBot
