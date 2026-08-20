#include <gtest/gtest.h>

#include "tgbot/HttpFormField.h"
#include "tgbot/InputFile.h"

#include <filesystem>
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
    EXPECT_FALSE(file.filePath);
}

TEST(InputFile, CreatesFromBinaryDataInMemory) {
    const std::string data("a\0b", 3);

    const auto file = TgBot::InputFile::fromData(data, "application/octet-stream", "data.bin");

    EXPECT_EQ(file->data, data);
    EXPECT_EQ(file->mimeType, "application/octet-stream");
    EXPECT_EQ(file->fileName, "data.bin");
    EXPECT_FALSE(file->filePath);
}

TEST(InputFile, CreatesStreamingFileWithoutReadingContents) {
    const std::filesystem::path path = std::filesystem::path("files") / "data.bin";

    const auto file = TgBot::InputFile::fromFile(path.string(), "application/octet-stream");

    EXPECT_TRUE(file->data.empty());
    EXPECT_EQ(file->mimeType, "application/octet-stream");
    EXPECT_EQ(file->fileName, "data.bin");
    EXPECT_EQ(file->filePath, path.string());
}
