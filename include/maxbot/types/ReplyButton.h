#pragma once

#include <variant>
#include <memory>

namespace MaxBot {

/**
 * @brief After pressing this type of button client will send a message on behalf of user with given payload
 */
class SendMessageButton
{
public:
    typedef std::shared_ptr<SendMessageButton> Ptr;

    /**
     * @brief Видимый текст кнопки
     */
    std::string text;

    /**
     * @brief Токен кнопки
     */
    std::string payload;
};

/**
 * @brief После нажатия на такую кнопку клиент отправляет новое сообщение с вложением текущего географического положения пользователя
 */
class SendGeoLocationButton
{
public:
    typedef std::shared_ptr<SendGeoLocationButton> Ptr;

    /**
     * @brief Видимый текст кнопки
     */
    std::string text;

    /**
     * @brief Токен кнопки
     */
    std::string payload;

    /**
     * @brief Если *true*, отправляет местоположение без запроса подтверждения пользователя
     */
    bool quick = false;
};

/**
 * @brief AПосле нажатия на такую кнопку клиент отправляет новое сообщение с вложением текущего контакта пользователя
 */
class SendContactButton
{
public:
    typedef std::shared_ptr<SendContactButton> Ptr;

    /**
     * @brief Видимый текст кнопки
     */
    std::string text;

    /**
     * @brief Токен кнопки
     */
    std::string payload;
};

/**
 * @brief After pressing this type of button client will send a message on behalf of user with given payload
 */
class ReplyButton
{
public:
    typedef std::shared_ptr<ReplyButton> Ptr;

    /**
     * @brief Видимый текст кнопки
     */
    std::string text;

    /**
     * @brief Токен кнопки
     */
    std::string payload;

    /**
     * @brief Дискриминатор типа кнопки
     */
    std::string type;

    /**
     * @brief Вариант с конкретным типом кнопки (message, user_geo_location, user_contact)
     */
    std::variant<
		SendMessageButton::Ptr,
		SendGeoLocationButton::Ptr,
		SendContactButton::Ptr
	> _data;
};

} // namespace MaxBot
