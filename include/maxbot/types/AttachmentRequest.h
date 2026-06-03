#pragma once

#include "maxbot/types/Attachment.h"

#include <unordered_map>

namespace MaxBot {

/**
 * @brief Информация о загруженном изображении
 */
class PhotoToken
{
public:
    typedef std::shared_ptr<PhotoToken> Ptr;

    /**
     * @brief Закодированная информация загруженного изображения
     */
    std::string token;
};

/**
 * @brief Запрос на прикрепление изображения
 */
class PhotoAttachmentRequest
{
public:
    typedef std::shared_ptr<PhotoAttachmentRequest> Ptr;

    /**
     * @brief Полезная нагрузка запроса на прикрепление изображения
     */
    class Payload
    {
    public:
        typedef std::shared_ptr<Payload> Ptr;

        /**
         * @brief Любой внешний URL изображения, которое вы хотите прикрепить
         */
        std::string url;

        /**
         * @brief Токен существующего вложения
         */
        std::string token;

        /**
         * @brief Токены, полученные после загрузки изображений
         */
        std::unordered_map<std::string, PhotoToken::Ptr> photos;
    };

    Payload payload;
};

/**
 * @brief Это информация, которую вы получите, как только изображение будет загружено
 */
class PhotoTokens
{
public:
    typedef std::shared_ptr<PhotoTokens> Ptr;

    std::unordered_map<std::string, PhotoToken::Ptr> photos;
};

/**
 * @brief Это информация, которую вы получите, как только аудио/видео будет загружено
 */
class UploadedInfo
{
public:
    typedef std::shared_ptr<UploadedInfo> Ptr;

    /**
     * @brief Токен — уникальный ID загруженного медиафайла
     */
    std::string token;
};

/**
 * @brief Запрос на прикрепление видео к сообщению
 */
class VideoAttachmentRequest
{
public:
    typedef std::shared_ptr<VideoAttachmentRequest> Ptr;

	UploadedInfo::Ptr payload;
};

/**
 * @brief Запрос на прикрепление аудио к сообщению. ДОЛЖЕН быть единственным вложением в сообщении
 */
class AudioAttachmentRequest
{
public:
    typedef std::shared_ptr<AudioAttachmentRequest> Ptr;

	UploadedInfo::Ptr payload;
};

/**
 * @brief Запрос на прикрепление файла к сообщению. ДОЛЖЕН быть единственным вложением в сообщении
 */
class FileAttachmentRequest
{
public:
    typedef std::shared_ptr<FileAttachmentRequest> Ptr;

	UploadedInfo::Ptr payload;
};

/**
 * @brief Тип загружаемого файла
 */
enum class UploadType
{
    image,  ///< JPG, JPEG, PNG, GIF, TIFF, BMP, HEIC
    video,  ///< MP4, MOV, MKV, WEBM, MATROSKA
    audio,  ///< MP3, WAV, M4A и другие
    file    ///< любые типы файлов
};

/**
 * @brief Запрос на прикрепление карточки контакта к сообщению. ДОЛЖЕН быть единственным вложением в сообщении
 */
class ContactAttachmentRequest
{
public:
    typedef std::shared_ptr<ContactAttachmentRequest> Ptr;

    class Payload
    {
    public:
        typedef std::shared_ptr<Payload> Ptr;

        /**
         * @brief Имя контакта
         */
        std::string name;

        /**
         * @brief ID контакта, если он зарегистрирован в MAX
         */
        std::int64_t contact_id;

        /**
         * @brief Полная информация о контакте в формате VCF
         */
        std::string vcf_info;

        /**
         * @brief Телефон контакта в формате VCF
         */
        std::string vcf_phone;
    };

	Payload::Ptr payload;
};

/**
 * @brief Запрос на прикрепление стикера. ДОЛЖЕН быть единственным вложением в сообщении
 */
class StickerAttachmentRequest
{
public:
    typedef std::shared_ptr<StickerAttachmentRequest> Ptr;

    class Payload
    {
    public:
        typedef std::shared_ptr<Payload> Ptr;

        /**
         * @brief Код стикера
         */
        std::string code;
    };

	Payload::Ptr payload;
};

/**
 * @brief Запрос на прикрепление клавиатуры к сообщению
 */
class InlineKeyboardAttachmentRequest
{
public:
    typedef std::shared_ptr<InlineKeyboardAttachmentRequest> Ptr;

    class Payload
    {
    public:
        typedef std::shared_ptr<Payload> Ptr;

        /**
         * @brief Двумерный массив кнопок
         */
        std::vector<std::vector<Button::Ptr>> buttons;
    };

    Payload payload;
};

/**
 * @brief Request to attach reply keyboard to message
 */
class ReplyKeyboardAttachmentRequest
{
public:
    typedef std::shared_ptr<ReplyKeyboardAttachmentRequest> Ptr;

    /**
     * @brief Applicable only for chats. If `true` keyboard will be shown only for user bot mentioned or replied
     */
    bool direct = false;

    /**
     * @brief If set to `true`, reply keyboard will only be shown to this participant in chat
     */
    std::int64_t direct_user_id;

    /**
     * @brief Двумерный массив кнопок
     */
    std::vector<std::vector<ReplyButton::Ptr>> buttons;
};

/**
 * @brief Запрос на прикрепление клавиатуры к сообщению
 */
class LocationAttachmentRequest
{
public:
    typedef std::shared_ptr<LocationAttachmentRequest> Ptr;

    /**
     * @brief Широта
     */
    double latitude;

    /**
     * @brief Долгота
     */
    double longitude;
};

/**
 * @brief Запрос на прикрепление предпросмотра медиафайла по внешнему URL
 */
class ShareAttachmentRequest
{
public:
    typedef std::shared_ptr<ShareAttachmentRequest> Ptr;

	ShareAttachmentPayload::Ptr payload;
};

/**
 * @brief Запрос на прикрепление данных к сообщению (базовый тип с дискриминатором)
 */
class AttachmentRequest
{
public:
    typedef std::shared_ptr<AttachmentRequest> Ptr;

    /**
     * @brief Тип вложения
     */
    std::string type;

    using VariantType = std::variant<
        std::monostate, // для случая, если тип не задан
        PhotoAttachmentRequest::Ptr,
        VideoAttachmentRequest::Ptr,
        AudioAttachmentRequest::Ptr,
        FileAttachmentRequest::Ptr,
        StickerAttachmentRequest::Ptr,
        ContactAttachmentRequest::Ptr,
        InlineKeyboardAttachmentRequest::Ptr,
        LocationAttachmentRequest::Ptr,
        ShareAttachmentRequest::Ptr
    >;

    VariantType _data;
};

} // namespace MaxBot
