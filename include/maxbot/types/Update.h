#pragma once

#include "maxbot/types/UpdateBotAddedToChat.h"
#include "maxbot/types/UpdateBotStarted.h"
#include "maxbot/types/UpdateBotStopped.h"
#include "maxbot/types/UpdateBotRemovedFromChat.h"
#include "maxbot/types/UpdateChatTitleChanged.h"
#include "maxbot/types/UpdateDialogCleared.h"
#include "maxbot/types/UpdateDialogMuted.h"
#include "maxbot/types/UpdateDialogUnmuted.h"
#include "maxbot/types/UpdateDialogRemoved.h"
#include "maxbot/types/UpdateMessageCallback.h"
#include "maxbot/types/UpdateMessageCreated.h"
#include "maxbot/types/UpdateMessageEdited.h"
#include "maxbot/types/UpdateMessageRemoved.h"
#include "maxbot/types/UpdateUserAddedToChat.h"
#include "maxbot/types/UpdateUserRemovedFromChat.h"
#include <variant>

namespace MaxBot {

/**
 * @brief Объект `Update` описывает возможные события в чате или канале. Может возвращаться в следующих случаях:
 * - Вы подписались на обновления через Webhook — при наступлении события МАКС пришлёт [POST-запрос `/subscriptions`](/docs-api/methods/POST/subscriptions), который содержит объект `Update`
 * - Вы отправили [GET-запрос /updates](/docs-api/methods/GET/updates) для получения обновлений через  Long Polling— в ответ вернётся объект `Update`
 *
 *  >! Получение обновлений с помощью [Long Polling](/docs-api/methods/GET/updates) ограничено по скорости и сроку хранения событий — этот способ не подходит для production-окружения. Рекомендуем на всех этапах работы использовать [Webhook](/docs-api/methods/POST/subscriptions)
 *
 * ## Типы событий
 *
 *- `bot_added` — бот добавлен в чат или канал
 *
 *- `bot_started` — пользователь впервые начал общение с ботом или возобновил после остановки — нажал соответствующую кнопку в настройках бота в МАКС
 *
 *- `bot_stopped` — пользователь остановил бота – выбрал соответствующее действие в настройках бота в МАКС
 *
 *- `bot_removed` — бот удалён из чата или канала 
 *
 *- `chat_title_changed` — пользователь изменил название чата или канала
 *
 *- `dialog_cleared` — пользователь очистил историю диалога с ботом
 *
 *- `dialog_muted` — пользователь отключил уведомления в диалоге с ботом
 *
 *- `dialog_unmuted` — пользователь включил уведомления в диалоге с ботом
 *
 *- `dialog_removed` — пользователь удалил диалог с ботом
 *
 *- `message_callback` — пользователь нажал на кнопку в чате или канале
 *
 *- `message_created` — пользователь отправил новое сообщение или опубликовал пост
 *
 *- `message_edited` — пользователь отредактировал сообщение в чате или канале
 *
 *- `message_removed` — пользователь удалил сообщение из чата или канала
 *
 *- `user_added` — в чат или канал добавлен или перешёл по ссылке новый пользователь
 *
 *- `user_removed` — пользователь удалён или покинул чат или канал
 *
 * ## Свойства объекта Update

 *
 * @ingroup types
 */
class Update {

public:
    typedef std::shared_ptr<Update> Ptr;

    /**
     * @brief Unix-время, когда произошло событие
     */
    std::int64_t timestamp;

    /**
     * @brief Тип события
     */
    std::string update_type;

    /**
     * @brief Данные события в зависимости от типа в update_type
     */
	std::variant<
		std::monostate,
		UpdateBotAddedToChat::Ptr,
		UpdateBotStarted::Ptr,
		UpdateBotStopped::Ptr,
		UpdateBotRemovedFromChat::Ptr,
		UpdateChatTitleChanged::Ptr,
		UpdateDialogCleared::Ptr,
		UpdateDialogMuted::Ptr,
		UpdateDialogUnmuted::Ptr,
		UpdateDialogRemoved::Ptr,
		UpdateMessageCallback::Ptr,
		UpdateMessageCreated::Ptr,
		UpdateMessageEdited::Ptr,
		UpdateMessageRemoved::Ptr,
		UpdateUserAddedToChat::Ptr,
		UpdateUserRemovedFromChat::Ptr
	> _data;
};

}
