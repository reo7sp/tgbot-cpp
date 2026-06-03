#pragma once

#include <cstdint>
#include <memory>
#include <variant>

namespace MaxBot {

/// @brief Представляет ссылку в тексте
struct LinkMarkup
{
    typedef std::shared_ptr<LinkMarkup> Ptr;

    /**
     * @brief URL ссылки
     */
    std::string url;
};

/// @brief Представляет упоминание пользователя в тексте. Упоминание может быть как по имени пользователя, так и по ID, если у пользователя нет имени
struct UserMentionMarkup
{
    typedef std::shared_ptr<UserMentionMarkup> Ptr;

    /**
     * @brief `@username` упомянутого пользователя
     */
    std::string user_link;

    /**
     * @brief ID упомянутого пользователя без имени
     */
    std::int64_t user_id;
};

/**
 * @brief Базовый элемент разметки, использующий variant для хранения конкретных типов
 */
class MarkupElement {
public:
    typedef std::shared_ptr<MarkupElement> Ptr;

    /**
     * @brief Тип элемента разметки. Может быть **жирный**, *курсив*, ~зачеркнутый~, <ins>подчеркнутый</ins>, `моноширинный`, выделенный, цитата, заголовок, ссылка или упоминание пользователя
	 * Значения:
	 * strong
	 * emphasized
	 * monospaced
	 * link
	 * strikethrough
	 * underline
	 * user_mention
	 * heading
	 * highlighted
	 * quote
     */
    std::string type;

    /**
     * @brief Индекс начала элемента разметки в тексте. Нумерация с нуля
     */
    std::int32_t from;

    /**
     * @brief Длина элемента разметки
     */
    std::int32_t length;

    /**
     * @brief Данные конкретного типа разметки
     */
    std::variant<
        LinkMarkup::Ptr,
        UserMentionMarkup::Ptr
    > _data;
};

} // namespace MaxBot
