#pragma once

#include "maxbot/types/Message.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Вы получите это событие, как только пользователь отредактирует сообщение
 */
class UpdateMessageEdited
{
public:
    typedef std::shared_ptr<UpdateMessageEdited> Ptr;

    /**
     * @brief Отредактированное сообщение
     */
	Message::Ptr message;
};

} // namespace MaxBot
