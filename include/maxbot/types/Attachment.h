#pragma once

#include "maxbot/types/User.h"
#include "maxbot/types/Keyboard.h"
#include "maxbot/types/ReplyButton.h"
#include <variant>
#include <vector>

namespace MaxBot {

/// @brief Базовая полезная нагрузка вложения
struct AttachmentPayload
{
    typedef std::shared_ptr<AttachmentPayload> Ptr;

    /// @brief URL медиа-вложения
    std::string url;
};

/// @brief Полезная нагрузка для PhotoAttachment
struct PhotoAttachmentPayload
{
    typedef std::shared_ptr<PhotoAttachmentPayload> Ptr;

    /// @brief Уникальный ID этого изображения
    std::int64_t photo_id;

    /// @brief Токен изображения
    std::string token;

    /// @brief URL изображения
    std::string url;
};

/// @brief Вложение изображения
struct PhotoAttachment
{
    typedef std::shared_ptr<PhotoAttachment> Ptr;

    /// @brief Полезная нагрузка изображения
	PhotoAttachmentPayload::Ptr payload;
};

/// @brief Миниатюра видео
struct VideoThumbnail
{
    typedef std::shared_ptr<VideoThumbnail> Ptr;

    /// @brief URL изображения
    std::string url;
};

/// @brief Полезная нагрузка медиа-вложения (видео/аудио)
struct MediaAttachmentPayload : public AttachmentPayload
{
    typedef std::shared_ptr<MediaAttachmentPayload> Ptr;

    /// @brief Используйте token, если вы пытаетесь повторно использовать одно и то же вложение в другом сообщении.
    std::string token;
};

/// @brief Вложение видео
struct VideoAttachment
{
    typedef std::shared_ptr<VideoAttachment> Ptr;

    /// @brief Полезная нагрузка видео
	MediaAttachmentPayload::Ptr payload;

    /// @brief Миниатюра видео
    VideoThumbnail::Ptr thumbnail;

    /// @brief Ширина видео
    std::int64_t width;

    /// @brief Высота видео
    std::int64_t height;

    /// @brief Длина видео в секундах
    std::int64_t duration;
};

/// @brief URL-ы видео в разных разрешениях
struct VideoUrls
{
    typedef std::shared_ptr<VideoUrls> Ptr;

    /// @brief URL видео в разрешении 1080p, если доступно
    std::string mp4_1080;

    /// @brief URL видео в разрешении 720p, если доступно
    std::string mp4_720;

    /// @brief URL видео в разрешении 480p, если доступно
    std::string mp4_480;

    /// @brief URL видео в разрешении 360p, если доступно
    std::string mp4_360;

    /// @brief URL видео в разрешении 240p, если доступно
    std::string mp4_240;

    /// @brief URL видео в разрешении 144p, если доступно
    std::string mp4_144;

    /// @brief URL трансляции, если доступна
    std::string hls;
};

/// @brief Детали видео-вложения (альтернативное представление)
struct VideoAttachmentDetails
{
    typedef std::shared_ptr<VideoAttachmentDetails> Ptr;

    /// @brief Токен видео-вложения
    std::string token;

    /// @brief URL-ы для скачивания или воспроизведения видео. Может быть null, если видео недоступно
    VideoUrls::Ptr urls;

    /// @brief Миниатюра видео
	PhotoAttachmentPayload::Ptr thumbnail;

    /// @brief Ширина видео
    std::int64_t width;

    /// @brief Высота видео
    std::int64_t height;

    /// @brief Длина видео в секундах
    std::int64_t duration;
};

/// @brief Вложение аудио
struct AudioAttachment
{
    typedef std::shared_ptr<AudioAttachment> Ptr;

    /// @brief Полезная нагрузка аудио
	MediaAttachmentPayload::Ptr payload;

    /// @brief Аудио транскрипция
    std::string transcription;
};

/// @brief Полезная нагрузка файлового вложения
struct FileAttachmentPayload : public AttachmentPayload
{
    typedef std::shared_ptr<FileAttachmentPayload> Ptr;

    /// @brief Используйте token, если вы пытаетесь повторно использовать одно и то же вложение в другом сообщении.
    std::string token;
};

/// @brief Вложение файла
struct FileAttachment
{
    typedef std::shared_ptr<FileAttachment> Ptr;

    /// @brief Полезная нагрузка файла
	FileAttachmentPayload::Ptr payload;

    /// @brief Имя загруженного файла
    std::string filename;

    /// @brief Размер файла в байтах
    std::int64_t size;
};

/// @brief Полезная нагрузка контакта
struct ContactAttachmentPayload
{
    typedef std::shared_ptr<ContactAttachmentPayload> Ptr;

    /// @brief Информация о пользователе в формате VCF
    std::string vcf_info;

    /// @brief Хеш информации о пользователе в формате VCF.
    std::string hash;

    /// @brief Информация о пользователе
	User::Ptr max_info;
};

/// @brief Вложение контакта
struct ContactAttachment
{
    typedef std::shared_ptr<ContactAttachment> Ptr;

    /// @brief Полезная нагрузка контакта
	ContactAttachmentPayload::Ptr payload;
};

/// @brief Полезная нагрузка стикера
struct StickerAttachmentPayload : public AttachmentPayload
{
    typedef std::shared_ptr<StickerAttachmentPayload> Ptr;

    /// @brief ID стикера
    std::string code;
};

/// @brief Вложение стикера
struct StickerAttachment
{
    typedef std::shared_ptr<StickerAttachment> Ptr;

    /// @brief Полезная нагрузка стикера
	StickerAttachmentPayload::Ptr payload;

    /// @brief Ширина стикера
    std::int64_t width;

    /// @brief Высота стикера
    std::int64_t height;
};

/// @brief Полезная нагрузка запроса ShareAttachment
struct ShareAttachmentPayload
{
    typedef std::shared_ptr<ShareAttachmentPayload> Ptr;

    /// @brief URL, прикрепленный к сообщению в качестве предпросмотра медиа
    std::string url;

    /// @brief Токен вложения
    std::string token;
};

/// @brief Вложение "поделиться"
struct ShareAttachment
{
    typedef std::shared_ptr<ShareAttachment> Ptr;

    /// @brief Полезная нагрузка
	ShareAttachmentPayload::Ptr payload;

    /// @brief Заголовок предпросмотра ссылки.
    std::string title;

    /// @brief Описание предпросмотра ссылки
    std::string description;

    /// @brief Изображение предпросмотра ссылки
    std::string image_url;
};

/// @brief Вложение геолокации
struct LocationAttachment
{
    typedef std::shared_ptr<LocationAttachment> Ptr;

    /// @brief Широта
    double latitude;

    /// @brief Долгота
    double longitude;
};

/// @brief Кнопки в сообщении (инлайн-клавиатура)
struct InlineKeyboardAttachment
{
    typedef std::shared_ptr<InlineKeyboardAttachment> Ptr;

    /// @brief Полезная нагрузка — клавиатура
	Keyboard::Ptr payload;
};

/// @brief Custom reply keyboard in message
struct ReplyKeyboardAttachment
{
    typedef std::shared_ptr<ReplyKeyboardAttachment> Ptr;

    /// @brief Матрица кнопок
    std::vector<std::vector<ReplyButton::Ptr>> buttons;
};

/// @brief Attachment contains payload sent through SendMessageButton
struct DataAttachment
{
    typedef std::shared_ptr<DataAttachment> Ptr;

    /// @brief Данные, переданные через кнопку
    std::string data;
};

/**
 * @brief Дискриминаторный класс для всех типов вложений.
 *        Использует std::variant для хранения конкретного типа вложения.
 */
class Attachment
{
public:
    typedef std::shared_ptr<Attachment> Ptr;

    /// @brief Тип вложения (текстовый дискриминатор)
    std::string type;

    /// @brief Вариант, содержащий одно из возможных вложений
    std::variant<
        PhotoAttachment::Ptr,
        VideoAttachment::Ptr,
        AudioAttachment::Ptr,
        FileAttachment::Ptr,
        StickerAttachment::Ptr,
        ContactAttachment::Ptr,
        InlineKeyboardAttachment::Ptr,
        ShareAttachment::Ptr,
        LocationAttachment::Ptr
    > _data;
};

} // namespace MaxBot
