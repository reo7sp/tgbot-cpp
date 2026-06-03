#pragma once

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Статистика сообщения. Возвращается только для постов в каналах
 */
class MessageStat
{                                               
public:
    typedef std::shared_ptr<MessageStat> Ptr;

    /**
     * @brief Количество пользователей, которые увидели пост в канале. Просмотр засчитывается, когда пост попадает в область видимости экрана
     */
    std::int64_t views;
};

} // namespace MaxBot
