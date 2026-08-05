#include <gtest/gtest.h>

#include "tgbot/HttpFormField.h"

#include <string>
#include <variant>

TEST(HttpFormField, StoresTextValue) {
    const TgBot::HttpFormField field { "chat_id", "42" };

    EXPECT_EQ(field.name, "chat_id");
    EXPECT_EQ(std::get<std::string>(field.value), "42");
}

TEST(HttpFormField, StoresFileValue) {
    const TgBot::HttpFormField field {
        "photo",
        TgBot::HttpFile { "contents", "image/jpeg", "photo.jpg" },
    };

    const auto& file = std::get<TgBot::HttpFile>(field.value);
    EXPECT_EQ(field.name, "photo");
    EXPECT_EQ(file.data, "contents");
    EXPECT_EQ(file.mimeType, "image/jpeg");
    EXPECT_EQ(file.fileName, "photo.jpg");
}
