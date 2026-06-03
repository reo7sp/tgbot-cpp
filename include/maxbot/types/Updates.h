#pragma once

#include "maxbot/types/Update.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This [object](https://core.telegram.org/bots/api#available-types) represents an incoming update.
 *
 * At most one of the optional parameters can be present in any given update.
 *
 * @ingroup types
 */
class Updates {

public:
    typedef std::shared_ptr<Updates> Ptr;

    /**
     * @brief Указатель на следующую страницу данных
     */
    std::int64_t marker;

    /**
     * @brief Список обновлений о событиях в чатах и каналах, в которые добавлен бот. Обратите внимание, чтобы получать события из групповых чатов и каналов, бот должен быть администратором. Подробнее о возможных событиях — [в описании объекта Update](/docs-api/objects/Update)
     */
    std::vector<Update::Ptr> updates;
};
}
