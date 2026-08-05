#include <memory>
#include <string>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "tgbot/Types.h"

TEST(TypesJson, GeneratedDiscriminatorHasLegacyConstantAndDefault) {
    TgBot::InlineQueryResultCachedAudio result;

    EXPECT_EQ(TgBot::InlineQueryResultCachedAudio::TYPE, "audio");
    EXPECT_EQ(result.type, TgBot::InlineQueryResultCachedAudio::TYPE);
    EXPECT_EQ(nlohmann::json(result).at("type"), "audio");
}

TEST(TypesJson, PreservesLegacyEnums) {
    const auto chat = nlohmann::json { { "id", 1 }, { "type", "supergroup" } }.get<TgBot::Chat>();
    EXPECT_EQ(chat.type, TgBot::Chat::Type::Supergroup);
    EXPECT_EQ(nlohmann::json(chat).at("type"), "supergroup");

    const auto entity = nlohmann::json { { "type", "expandable_blockquote" }, { "offset", 0 }, { "length", 1 } }
                            .get<TgBot::MessageEntity>();
    EXPECT_EQ(entity.type, TgBot::MessageEntity::Type::ExpandableBlockquote);

    TgBot::Sticker sticker;
    sticker.type = TgBot::Sticker::Type::CustomEmoji;
    EXPECT_EQ(nlohmann::json(sticker).at("type"), "custom_emoji");
}

TEST(TypesJson, ParsesGeneratedObjectWithNestedObject) {
    const std::string input = R"({
        "file_id": "animation-id",
        "file_unique_id": "animation-unique-id",
        "width": 320,
        "height": 240,
        "duration": 5,
        "thumbnail": {
            "file_id": "thumbnail-id",
            "file_unique_id": "thumbnail-unique-id",
            "width": 32,
            "height": 24
        }
    })";

    const auto animation = nlohmann::json::parse(input).get<TgBot::Animation>();

    EXPECT_EQ(animation.fileId, "animation-id");
    ASSERT_TRUE(animation.thumbnail);
    EXPECT_EQ(animation.thumbnail->width, 32);
    EXPECT_FALSE(animation.fileSize.has_value());
}

TEST(TypesJson, SerializeGeneratedObjectPreservesJsonTypes) {
    TgBot::PhotoSize photo;
    photo.fileId = "photo-id";
    photo.fileUniqueId = "photo-unique-id";
    photo.width = 640;
    photo.height = 480;

    const nlohmann::json json = photo;

    EXPECT_TRUE(json.at("width").is_number_integer());
    EXPECT_EQ(json.at("width").get<int>(), 640);
    EXPECT_FALSE(json.contains("file_size"));
}

TEST(TypesJson, ParseGeneratedObjectRejectsMissingRequiredField) {
    const std::string input = R"({
        "file_id": "photo-id",
        "file_unique_id": "photo-unique-id",
        "height": 480
    })";

    EXPECT_THROW(nlohmann::json::parse(input).get<TgBot::PhotoSize>(), nlohmann::json::out_of_range);
}

TEST(TypesJson, ParseGeneratedObjectTreatsOptionalNullAsDefault) {
    const std::string input = R"({
        "file_id": "animation-id",
        "file_unique_id": "animation-unique-id",
        "width": 320,
        "height": 240,
        "duration": 5,
        "thumbnail": null,
        "file_size": null
    })";

    const auto animation = nlohmann::json::parse(input).get<TgBot::Animation>();

    EXPECT_FALSE(animation.thumbnail);
    EXPECT_FALSE(animation.fileSize.has_value());
}

TEST(TypesJson, RoundTripPreservesNestedObjectArray) {
    auto interval = std::make_shared<TgBot::BusinessOpeningHoursInterval>();
    interval->openingMinute = 60;
    interval->closingMinute = 120;

    TgBot::BusinessOpeningHours hours;
    hours.timeZoneName = "Europe/Moscow";
    hours.openingHours.push_back(interval);

    const nlohmann::json json = hours;
    const auto parsed = json.get<TgBot::BusinessOpeningHours>();

    ASSERT_TRUE(json.at("opening_hours").is_array());
    EXPECT_EQ(json.at("opening_hours").size(), 1);
    ASSERT_EQ(parsed.openingHours.size(), 1);
    ASSERT_TRUE(parsed.openingHours.front());
    EXPECT_EQ(parsed.openingHours.front()->openingMinute, 60);
    EXPECT_EQ(parsed.openingHours.front()->closingMinute, 120);
}

TEST(TypesJson, ParseGeneratedObjectRejectsWrongFieldType) {
    const std::string input = R"({
        "file_id": "photo-id",
        "file_unique_id": "photo-unique-id",
        "width": "wide",
        "height": 480
    })";

    EXPECT_THROW(nlohmann::json::parse(input).get<TgBot::PhotoSize>(), nlohmann::json::type_error);
}

TEST(TypesJson, ParseGeneratedObjectRejectsMalformedJson) {
    EXPECT_THROW(nlohmann::json::parse("{").get<TgBot::PhotoSize>(), nlohmann::json::parse_error);
}

TEST(TypesJson, ParsesUnionAsMatchingTelegramType) {
    const nlohmann::json json = {
        { "type", "custom_emoji" },
        { "custom_emoji_id", "emoji-id" },
    };

    const auto reaction = json.get<TgBot::ReactionType>();

    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::ReactionTypeCustomEmoji>>(reaction.value));
    const auto& customEmoji = std::get<std::shared_ptr<TgBot::ReactionTypeCustomEmoji>>(reaction.value);
    ASSERT_TRUE(customEmoji);
    EXPECT_EQ(customEmoji->customEmojiId, "emoji-id");
    EXPECT_EQ(nlohmann::json(reaction), json);
}

TEST(TypesJson, ParsesUnionMemberWithoutAdditionalFields) {
    const nlohmann::json json = { { "type", "paid" } };

    const auto reaction = json.get<TgBot::ReactionType>();

    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::ReactionTypePaid>>(reaction.value));
    const auto& paid = std::get<std::shared_ptr<TgBot::ReactionTypePaid>>(reaction.value);
    ASSERT_TRUE(paid);
    EXPECT_EQ(paid->type, TgBot::ReactionTypePaid::TYPE);
}

TEST(TypesJson, ParsesUnionUsingStatusDiscriminator) {
    const nlohmann::json json = {
        { "status", "member" },
        { "user", { { "id", 1 }, { "is_bot", false }, { "first_name", "User" } } },
    };

    const auto member = json.get<TgBot::ChatMember>();

    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::ChatMemberMember>>(member.value));
    const auto& regularMember = std::get<std::shared_ptr<TgBot::ChatMemberMember>>(member.value);
    ASSERT_TRUE(regularMember);
    EXPECT_EQ(regularMember->status, TgBot::ChatMemberMember::STATUS);
}

TEST(TypesJson, ParsesUnionUsingSourceDiscriminator) {
    const nlohmann::json json = {
        { "source", "premium" },
        { "user", { { "id", 1 }, { "is_bot", false }, { "first_name", "User" } } },
    };

    const auto source = json.get<TgBot::ChatBoostSource>();

    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::ChatBoostSourcePremium>>(source.value));
    const auto& premium = std::get<std::shared_ptr<TgBot::ChatBoostSourcePremium>>(source.value);
    ASSERT_TRUE(premium);
    EXPECT_EQ(premium->source, TgBot::ChatBoostSourcePremium::SOURCE);
}

TEST(TypesJson, RejectsUnionObjectWithUnknownDiscriminator) {
    const nlohmann::json json = {
        { "type", "unknown" },
        { "custom_emoji_id", "emoji-id" },
    };

    EXPECT_THROW(json.get<TgBot::ReactionType>(), std::invalid_argument);
}

TEST(TypesJson, RejectsStructurallyMatchingUnionMemberWithWrongDiscriminator) {
    const nlohmann::json json = {
        { "type", "custom_emoji" },
        { "emoji", "👍" },
    };

    EXPECT_THROW(json.get<TgBot::ReactionType>(), std::invalid_argument);
}

TEST(TypesJson, RejectsObjectUsedInsteadOfArray) {
    const nlohmann::json json = {
        { "time_zone_name", "Europe/Moscow" },
        { "opening_hours", { { "opening_minute", 60 }, { "closing_minute", 120 } } },
    };

    EXPECT_THROW(json.get<TgBot::BusinessOpeningHours>(), std::invalid_argument);
}

TEST(TypesJson, RejectsNullRequiredNestedObject) {
    const nlohmann::json json = {
        { "message_id", 1 },
        { "date", 2 },
        { "chat", nullptr },
    };

    EXPECT_THROW(json.get<TgBot::Message>(), std::invalid_argument);
}

TEST(TypesJson, MissingOptionalFieldsResetReusedObject) {
    TgBot::Animation animation;
    animation.thumbnail = std::make_shared<TgBot::PhotoSize>();
    animation.fileSize = 100;
    const nlohmann::json json = {
        { "file_id", "animation-id" },
        { "file_unique_id", "animation-unique-id" },
        { "width", 320 },
        { "height", 240 },
        { "duration", 5 },
    };

    json.get_to(animation);

    EXPECT_FALSE(animation.thumbnail);
    EXPECT_FALSE(animation.fileSize.has_value());
}
