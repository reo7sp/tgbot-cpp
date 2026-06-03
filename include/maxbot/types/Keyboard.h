#pragma once

#include <variant>
#include <vector>
#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief После нажатия на такую кнопку клиент отправляет на сервер полезную нагрузку, которая содержит
 */
class CallbackButton
{
public:
    typedef std::shared_ptr<CallbackButton> Ptr;

    /**
     * @brief Токен кнопки
     */
    std::string payload;
};

/**
 * @brief После нажатия на такую кнопку пользователь переходит по ссылке, которую она содержит
 */
class LinkButton
{
public:
    typedef std::shared_ptr<LinkButton> Ptr;

    /**
     * @brief URL для перехода
     */
    std::string url;
};

/**
 * @brief После нажатия на такую кнопку клиент отправляет новое сообщение с вложением текущего контакта пользователя
 */
class RequestContactButton
{
public:
    typedef std::shared_ptr<RequestContactButton> Ptr;
};

/**
 * @brief После нажатия на такую кнопку клиент отправляет новое сообщение с вложением текущего географического положения пользователя
 */
class RequestGeoLocationButton
{
public:
    typedef std::shared_ptr<RequestGeoLocationButton> Ptr;

    /**
     * @brief Если *true*, отправляет местоположение без запроса подтверждения пользователя
     */
    bool quick = false;
};

/**
 * @brief Кнопка, которая создает новый чат, как только первый пользователь на нее нажмёт.
 *        Бот будет добавлен в участники чата как администратор.
 *        Автор сообщения станет владельцем чата.
 */
class ChatButton
{
public:
    typedef std::shared_ptr<ChatButton> Ptr;

    /**
     * @brief Название чата, который будет создан
     */
    std::string chat_title;

    /**
     * @brief Описание чата
     */
    std::string chat_description;

    /**
     * @brief Стартовая полезная нагрузка будет отправлена боту, как только чат будет создан
     */
    std::string start_payload;

    /**
     * @brief Уникальный ID кнопки среди всех кнопок чата на клавиатуре.
     *        Если `uuid` изменён, новый чат будет создан при следующем нажатии.
     *        Сервер сгенерирует его в момент, когда кнопка будет впервые размещена.
     *        Используйте его при редактировании сообщения.
     */
    std::int64_t uuid;
};

/**
 * @brief Кнопка для запуска мини-приложения
 */
class OpenAppButton
{
public:
    typedef std::shared_ptr<OpenAppButton> Ptr;

    /**
     * @brief Публичное имя (username) бота или ссылка на него, чьё мини-приложение надо запустить
     */
    std::string web_app;

    /**
     * @brief Идентификатор бота, чьё мини-приложение надо запустить
     */
    std::int64_t contact_id;

    /**
     * @brief Параметр запуска, который будет передан в [initData](/docs/webapps/bridge#WebAppData) мини-приложения
     */
    std::string payload;
};

/**
 * @brief При нажатии на кнопку с типом `clipboard` текст, указанный в свойстве `payload`, копируется в буфер обмена
 */
class ClipboardButton
{
public:
    typedef std::shared_ptr<ClipboardButton> Ptr;

    /**
     * @brief Текст, который будет скопирован
     */
    std::string payload;
};

/**
 * @brief Кнопка для запуска мини-приложения
 */
class MessageButton
{
public:
    typedef std::shared_ptr<MessageButton> Ptr;

    /**
     * @brief Текст кнопки, который будет отправлен в чат от лица пользователя
     */
    // std::string text;
};

/**
 * @brief Базовый класс для кнопок с дискриминатором
 */
class Button
{
public:
    typedef std::shared_ptr<Button> Ptr;

    /**
     * @brief Тип кнопки
     */
    std::string type;

    /**
     * @brief Видимый текст кнопки. Чтобы он отображался полностью, рекомендуем не превышать заданное количество символов 
     *        в зависимости от размещения текста: `20` символов — при 1 кнопке в ряду, `10` — при 2, `5` — при 3, `3` — при 4
     */
    std::string text;

    /**
     * @brief Вариант, содержащий один из конкретных типов кнопок
     */
    std::variant<
        CallbackButton::Ptr,
        LinkButton::Ptr,
        RequestGeoLocationButton::Ptr,
        RequestContactButton::Ptr,
        OpenAppButton::Ptr,
        MessageButton::Ptr,
        ClipboardButton::Ptr
    > _data;
};

/**
 * @brief Клавиатура — это двумерный массив кнопок. Подробнее о типах кнопок и клавиатуре в ботах — 
 *        [в разделе «Клавиатура для чат-бота»](/docs-api#Клавиатура%20для%20чат-бота)
 */
class Keyboard
{
public:
    typedef std::shared_ptr<Keyboard> Ptr;

    /**
     * @brief Двумерный массив кнопок
     */
    std::vector<std::vector<Button::Ptr>> buttons;
};

} // namespace MaxBot
