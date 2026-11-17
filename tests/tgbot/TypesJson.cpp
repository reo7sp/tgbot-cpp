#include <limits>
#include <memory>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "tgbot/Types.h"

TEST(TypesJson, NonnegativeQuantitiesRoundTripAndRejectNegativeValues) {
    static_assert(std::is_same_v<decltype(TgBot::MessageEntity::offset), std::uint32_t>);
    static_assert(std::is_same_v<decltype(TgBot::Video::duration), std::uint32_t>);
    static_assert(std::is_same_v<decltype(TgBot::File::fileSize), std::optional<std::uint64_t>>);
    static_assert(std::is_same_v<decltype(TgBot::BackgroundFillFreeformGradient::colors), std::vector<std::uint32_t>>);
    static_assert(std::is_same_v<decltype(TgBot::StoryAreaTypeWeather::backgroundColor), std::uint32_t>);

    nlohmann::json entity = { { "type", "bold" }, { "offset", 0 }, { "length", 3 } };
    nlohmann::json file = { { "file_id", "file" }, { "file_unique_id", "unique" }, { "file_size", (1ULL << 52) - 1 } };
    nlohmann::json colors = { { "type", "freeform_gradient" }, { "colors", { 0, 0x123456, 0xFFFFFF } } };
    nlohmann::json weather
        = { { "type", "weather" }, { "temperature", -12.5 }, { "emoji", "snow" }, { "background_color", 0xFFFFFFFFU } };
    EXPECT_EQ(nlohmann::json(entity.get<TgBot::MessageEntity>()), entity);
    EXPECT_EQ(nlohmann::json(file.get<TgBot::File>()), file);
    EXPECT_EQ(nlohmann::json(colors.get<TgBot::BackgroundFillFreeformGradient>()), colors);
    EXPECT_EQ(nlohmann::json(weather.get<TgBot::StoryAreaTypeWeather>()), weather);

    entity["offset"] = -1;
    file["file_size"] = -1;
    colors["colors"][0] = -1;
    weather["background_color"] = -1;
    EXPECT_THROW(entity.get<TgBot::MessageEntity>(), std::invalid_argument);
    EXPECT_THROW(file.get<TgBot::File>(), std::invalid_argument);
    EXPECT_THROW(colors.get<TgBot::BackgroundFillFreeformGradient>(), std::invalid_argument);
    EXPECT_THROW(weather.get<TgBot::StoryAreaTypeWeather>(), std::invalid_argument);
}

TEST(TypesJson, MonetaryAmountsPreserveLargeValuesAndSignedDiscounts) {
    static_assert(std::is_same_v<decltype(TgBot::SuggestedPostPrice::amount), std::uint64_t>);
    static_assert(std::is_same_v<decltype(TgBot::StarTransaction::amount), std::uint64_t>);
    static_assert(std::is_same_v<decltype(TgBot::StarTransaction::nanostarAmount), std::optional<std::uint32_t>>);
    static_assert(std::is_same_v<decltype(TgBot::LabeledPrice::amount), std::int64_t>);
    static_assert(std::is_same_v<decltype(TgBot::StarAmount::amount), std::int64_t>);

    nlohmann::json price = { { "currency", "TON" }, { "amount", 10000000000000ULL } };
    EXPECT_EQ(nlohmann::json(price.get<TgBot::SuggestedPostPrice>()), price);
    const nlohmann::json paid = { { "currency", "TON" }, { "amount", 10000000000000ULL } };
    EXPECT_EQ(nlohmann::json(paid.get<TgBot::SuggestedPostPaid>()), paid);
    const nlohmann::json discount = { { "label", "Discount" }, { "amount", -5000000000LL } };
    EXPECT_EQ(nlohmann::json(discount.get<TgBot::LabeledPrice>()), discount);
    const nlohmann::json balance = { { "amount", -5000000000LL }, { "nanostar_amount", -999999999 } };
    EXPECT_EQ(nlohmann::json(balance.get<TgBot::StarAmount>()), balance);
    const nlohmann::json refund = { { "affiliate_chat", { { "id", -1001234567890LL }, { "type", "channel" } } },
                                    { "commission_per_mille", 10 },
                                    { "amount", -5000000000LL },
                                    { "nanostar_amount", -999999999 } };
    EXPECT_EQ(nlohmann::json(refund.get<TgBot::AffiliateInfo>()), refund);
    nlohmann::json transaction
        = { { "id", "transaction" }, { "date", 1 }, { "amount", 5000000000ULL }, { "nanostar_amount", 999999999 } };
    EXPECT_EQ(nlohmann::json(transaction.get<TgBot::StarTransaction>()), transaction);
    price["amount"] = -1;
    transaction["nanostar_amount"] = -1;
    EXPECT_THROW(price.get<TgBot::SuggestedPostPrice>(), std::invalid_argument);
    EXPECT_THROW(transaction.get<TgBot::StarTransaction>(), std::invalid_argument);
}

TEST(TypesJson, RatingsAndGeneralUnixTimesRetainNegativeValues) {
    const nlohmann::json rating
        = { { "level", -2 }, { "rating", -100 }, { "current_level_rating", -150 }, { "next_level_rating", -50 } };
    EXPECT_EQ(nlohmann::json(rating.get<TgBot::UserRating>()), rating);
    const nlohmann::json entity = { { "type", "date_time" }, { "offset", 0 }, { "length", 4 }, { "unix_time", -1 } };
    EXPECT_EQ(nlohmann::json(entity.get<TgBot::MessageEntity>()), entity);
}

TEST(TypesJson, UnsignedIdentifiersRoundTripWithoutLosingBits) {
    static_assert(std::is_same_v<decltype(TgBot::User::id), std::uint64_t>);
    static_assert(std::is_same_v<decltype(TgBot::Contact::userId), std::optional<std::uint64_t>>);
    static_assert(std::is_same_v<decltype(TgBot::MessageId::messageId), std::uint32_t>);
    static_assert(std::is_same_v<decltype(TgBot::BusinessMessagesDeleted::messageIds), std::vector<std::uint32_t>>);
    static_assert(
        std::is_same_v<decltype(TgBot::SetManagedBotAccessSettingsArgs::addedUserIds), std::vector<std::uint64_t>>);

    const nlohmann::json userJson
        = { { "id", (std::uint64_t { 1 } << 52) - 1 }, { "is_bot", false }, { "first_name", "User" } };
    const auto user = userJson.get<TgBot::User>();
    EXPECT_EQ(nlohmann::json(user), userJson);

    for (const auto id : { std::uint32_t { 0 }, std::numeric_limits<std::uint32_t>::max() }) {
        const nlohmann::json messageJson = { { "message_id", id } };
        EXPECT_EQ(nlohmann::json(messageJson.get<TgBot::MessageId>()), messageJson);
    }
}

TEST(TypesJson, UnsignedIdentifiersRejectNegativeFractionalAndOverflowingValues) {
    for (const nlohmann::json id :
         { nlohmann::json(-1), nlohmann::json(1.5), nlohmann::json(std::uint64_t { 1 } << 32) }) {
        const nlohmann::json json = { { "message_id", id } };
        EXPECT_THROW(json.get<TgBot::MessageId>(), std::invalid_argument);
    }
    const nlohmann::json user = { { "id", -1 }, { "is_bot", false }, { "first_name", "User" } };
    EXPECT_THROW(user.get<TgBot::User>(), std::invalid_argument);
    const nlohmann::json reply = { { "message_id", -1 } };
    EXPECT_THROW(reply.get<TgBot::ReplyParameters>(), std::invalid_argument);
    const nlohmann::json answer
        = { { "poll_id", "poll" }, { "option_ids", { -1 } }, { "option_persistent_ids", { "option" } } };
    EXPECT_THROW(answer.get<TgBot::PollAnswer>(), std::invalid_argument);
}

TEST(TypesJson, CommunityAndPrivateChatIdentifiersRoundTripAndRejectNegativeValues) {
    static_assert(std::is_same_v<decltype(TgBot::Community::id), std::uint64_t>);
    static_assert(std::is_same_v<decltype(TgBot::BusinessConnection::userChatId), std::uint64_t>);
    static_assert(std::is_same_v<decltype(TgBot::ChatJoinRequest::userChatId), std::uint64_t>);

    const auto id = (std::uint64_t { 1 } << 52) - 1;
    const nlohmann::json user = { { "id", id }, { "is_bot", false }, { "first_name", "User" } };
    const nlohmann::json chat = { { "id", -1001234567890LL }, { "type", "supergroup" } };
    nlohmann::json community = { { "id", id }, { "name", "Community" } };
    nlohmann::json connection
        = { { "id", "connection" }, { "user", user }, { "user_chat_id", id }, { "date", 1 }, { "is_enabled", true } };
    nlohmann::json request = { { "chat", chat }, { "from", user }, { "user_chat_id", id }, { "date", 1 } };

    EXPECT_EQ(nlohmann::json(community.get<TgBot::Community>()), community);
    EXPECT_EQ(nlohmann::json(connection.get<TgBot::BusinessConnection>()), connection);
    EXPECT_EQ(nlohmann::json(request.get<TgBot::ChatJoinRequest>()), request);

    community["id"] = -1;
    connection["user_chat_id"] = -1;
    request["user_chat_id"] = -1;
    EXPECT_THROW(community.get<TgBot::Community>(), std::invalid_argument);
    EXPECT_THROW(connection.get<TgBot::BusinessConnection>(), std::invalid_argument);
    EXPECT_THROW(request.get<TgBot::ChatJoinRequest>(), std::invalid_argument);
}

TEST(TypesJson, SignedIdentifiersStillAcceptNegativeValues) {
    static_assert(std::is_same_v<decltype(TgBot::Chat::id), std::int64_t>);
    static_assert(std::is_same_v<decltype(TgBot::KeyboardButtonRequestUsers::requestId), std::int32_t>);
    static_assert(std::is_same_v<decltype(TgBot::SendMessageDraftArgs::draftId), std::int64_t>);
    const nlohmann::json chat = { { "id", -1001234567890LL }, { "type", "supergroup" } };
    EXPECT_EQ(nlohmann::json(chat.get<TgBot::Chat>()), chat);
    const nlohmann::json request = { { "request_id", -1 } };
    EXPECT_EQ(nlohmann::json(request.get<TgBot::KeyboardButtonRequestUsers>()), request);
}

TEST(TypesJson, SignedIdentifiersPreserveIntegerBoundaries) {
    for (const auto id :
         { std::numeric_limits<std::int32_t>::min(), -1, 0, std::numeric_limits<std::int32_t>::max() }) {
        const nlohmann::json request = { { "request_id", id } };
        EXPECT_EQ(nlohmann::json(request.get<TgBot::KeyboardButtonRequestUsers>()), request);
    }
    for (const auto id : { std::numeric_limits<std::int64_t>::min(), std::int64_t { -1 }, std::int64_t { 0 },
                           std::numeric_limits<std::int64_t>::max() }) {
        const nlohmann::json chat = { { "id", id }, { "type", "private" } };
        EXPECT_EQ(nlohmann::json(chat.get<TgBot::Chat>()), chat);
    }
    // Positive integers parsed from JSON use unsigned storage, even for signed fields.
    const auto chat = nlohmann::json::parse(R"({"id":9223372036854775807,"type":"private"})");
    EXPECT_EQ(nlohmann::json(chat.get<TgBot::Chat>()), chat);
    const auto request = nlohmann::json::parse(R"({"request_id":2147483647})");
    EXPECT_EQ(nlohmann::json(request.get<TgBot::KeyboardButtonRequestUsers>()), request);
}

TEST(TypesJson, SignedIdentifiersRejectNonintegersAndOverflow) {
    for (const nlohmann::json& id :
         { nlohmann::json(1.5), nlohmann::json(true), nlohmann::json("42"), nlohmann::json(nullptr),
           nlohmann::json(std::uint64_t { 1 } << 63), nlohmann::json(std::numeric_limits<std::uint64_t>::max()) }) {
        SCOPED_TRACE(id.dump());
        const nlohmann::json chat = { { "id", id }, { "type", "private" } };
        const nlohmann::json request = { { "request_id", id } };
        EXPECT_THROW(chat.get<TgBot::Chat>(), std::invalid_argument);
        EXPECT_THROW(request.get<TgBot::KeyboardButtonRequestUsers>(), std::invalid_argument);
    }
    for (const nlohmann::json& id : { nlohmann::json(-2147483649LL), nlohmann::json(2147483648LL),
                                      nlohmann::json(2147483648ULL), nlohmann::json(4294967303ULL) }) {
        SCOPED_TRACE(id.dump());
        const nlohmann::json request = { { "request_id", id } };
        EXPECT_THROW(request.get<TgBot::KeyboardButtonRequestUsers>(), std::invalid_argument);
        const nlohmann::json theme
            = { { "type", "emoji" }, { "emojis", nlohmann::json::array() }, { "background_backdrop_id", id } };
        EXPECT_THROW(theme.get<TgBot::ChatShareThemeEmoji>(), std::invalid_argument);
    }
}

TEST(TypesJson, ChatIdUnionsRejectNonintegersAndOverflow) {
    for (const nlohmann::json& id :
         { nlohmann::json(1.5), nlohmann::json(true), nlohmann::json(std::uint64_t { 1 } << 63),
           nlohmann::json(std::numeric_limits<std::uint64_t>::max()) }) {
        SCOPED_TRACE(id.dump());
        const nlohmann::json scope = { { "type", "chat" }, { "chat_id", id } };
        const nlohmann::json reply = { { "message_id", 1 }, { "chat_id", id } };
        EXPECT_THROW(scope.get<TgBot::BotCommandScopeChat>(), std::invalid_argument);
        EXPECT_THROW(reply.get<TgBot::ReplyParameters>(), std::invalid_argument);
    }
}

TEST(TypesJson, CommandScopesAcceptNumericChatIdsAndUsernames) {
    using ChatId = std::variant<std::int64_t, std::string>;
    static_assert(std::is_same_v<decltype(TgBot::BotCommandScopeChat::chatId), ChatId>);
    static_assert(std::is_same_v<decltype(TgBot::BotCommandScopeChatAdministrators::chatId), ChatId>);
    static_assert(std::is_same_v<decltype(TgBot::BotCommandScopeChatMember::chatId), ChatId>);

    const std::vector<nlohmann::json> chatIds = { 42, -1001234567890LL, (std::int64_t { 1 } << 52) - 1, "@example" };
    for (const auto& chatId : chatIds) {
        SCOPED_TRACE(chatId.dump());
        nlohmann::json json = { { "type", "chat" }, { "chat_id", chatId } };
        EXPECT_EQ(nlohmann::json(json.get<TgBot::BotCommandScopeChat>()), json);
        json["type"] = "chat_administrators";
        EXPECT_EQ(nlohmann::json(json.get<TgBot::BotCommandScopeChatAdministrators>()), json);
        json["type"] = "chat_member";
        json["user_id"] = 42;
        EXPECT_EQ(nlohmann::json(json.get<TgBot::BotCommandScopeChatMember>()), json);
    }
}

TEST(TypesJson, ReplyParametersAcceptOptionalNumericChatIdsAndUsernames) {
    using ChatId = std::variant<std::int64_t, std::string>;
    static_assert(std::is_same_v<decltype(TgBot::ReplyParameters::chatId), std::optional<ChatId>>);

    const std::vector<nlohmann::json> chatIds = { 42, -1001234567890LL, (std::int64_t { 1 } << 52) - 1, "@example" };
    for (const auto& chatId : chatIds) {
        SCOPED_TRACE(chatId.dump());
        const nlohmann::json json = { { "message_id", 1 }, { "chat_id", chatId } };
        EXPECT_EQ(nlohmann::json(json.get<TgBot::ReplyParameters>()), json);
    }
    const nlohmann::json omitted = { { "message_id", 1 } };
    const auto reply = omitted.get<TgBot::ReplyParameters>();
    EXPECT_FALSE(reply.chatId.has_value());
    EXPECT_EQ(nlohmann::json(reply), omitted);
    const nlohmann::json nullChat = { { "message_id", 1 }, { "chat_id", nullptr } };
    EXPECT_FALSE(nullChat.get<TgBot::ReplyParameters>().chatId.has_value());
}

TEST(TypesJson, RichTextPreservesExistingVariantIndicesAndDefault) {
    using Value = decltype(TgBot::RichText::value);
    static_assert(std::is_same_v<std::variant_alternative_t<0, Value>, std::shared_ptr<TgBot::RichTextBold>>);
    static_assert(std::is_same_v<std::variant_alternative_t<25, Value>, std::shared_ptr<TgBot::RichTextReferenceLink>>);
    static_assert(std::is_same_v<std::variant_alternative_t<26, Value>, std::string>);
    static_assert(std::is_same_v<std::variant_alternative_t<27, Value>, std::vector<TgBot::RichText::Ptr>>);
    const TgBot::RichText text;
    EXPECT_EQ(text.value.index(), 0);
}

TEST(TypesJson, StoryAreaPositionRemainsCompatibleWithAreaPosition) {
    static_assert(std::is_same_v<TgBot::StoryAreaPosition, TgBot::AreaPosition>);
    TgBot::StoryArea area;
    area.position = std::make_shared<TgBot::StoryAreaPosition>(TgBot::StoryAreaPosition { 10, 20, 30, 40, 50 });
    area.position->cornerRadiusPercentage = 5;
    const nlohmann::json json = *area.position;
    const auto position = json.get<TgBot::AreaPosition>();
    EXPECT_EQ(position.xPercentage, 10);
    EXPECT_EQ(position.cornerRadiusPercentage, 5);
}

TEST(TypesJson, ParsesWidgetQueryAndNewEntityTypes) {
    const auto json = nlohmann::json::parse(
        R"({"update_id":1,"widget_query":{"id":"query","from":{"id":2,"is_bot":false,"first_name":"User"},"chat_instance":"instance","type":{"type":"data"},"data":"payload"}})");
    const auto update = json.get<TgBot::Update>();
    ASSERT_TRUE(update.widgetQuery);
    ASSERT_TRUE(update.widgetQuery->type);
    EXPECT_TRUE(std::holds_alternative<TgBot::WidgetQueryTypeData::Ptr>(update.widgetQuery->type->value));
    EXPECT_EQ(nlohmann::json(update), json);

    for (const auto& type : { "ton_address", "bank_card_number" }) {
        const nlohmann::json entityJson = { { "type", type }, { "offset", 0 }, { "length", 10 } };
        EXPECT_EQ(nlohmann::json(entityJson.get<TgBot::MessageEntity>()), entityJson);
    }
}

TEST(TypesJson, RichTextRoundTripsPlainText) {
    for (const auto& text : { std::string(), std::string("plain text") }) {
        const nlohmann::json json = text;
        const auto richText = json.get<TgBot::RichText>();
        ASSERT_TRUE(std::holds_alternative<std::string>(richText.value));
        EXPECT_EQ(std::get<std::string>(richText.value), text);
        EXPECT_EQ(nlohmann::json(richText), json);
    }
}

TEST(TypesJson, RichTextRoundTripsRecursiveMixedArray) {
    const auto json = nlohmann::json::parse(R"(["plain text", {"type":"bold","text":"bold text"}, ["nested", []]])");
    const auto richText = json.get<TgBot::RichText>();
    const auto& items = std::get<std::vector<TgBot::RichText::Ptr>>(richText.value);
    ASSERT_EQ(items.size(), 3);
    ASSERT_TRUE(items[0]);
    EXPECT_EQ(std::get<std::string>(items[0]->value), "plain text");
    EXPECT_EQ(nlohmann::json(richText), json);
}

TEST(TypesJson, RichTextRoundTripsFormattedObjectAndParagraph) {
    const auto bold = nlohmann::json::parse(R"({"type":"bold","text":"plain text"})");
    const auto richText = bold.get<TgBot::RichText>();
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::RichTextBold>>(richText.value));
    EXPECT_EQ(nlohmann::json(richText), bold);

    const auto paragraph = nlohmann::json::parse(R"({"type":"paragraph","text":"plain text"})");
    EXPECT_EQ(nlohmann::json(paragraph.get<TgBot::RichBlockParagraph>()), paragraph);
}

TEST(TypesJson, RichTextRejectsInvalidRepresentations) {
    for (const auto& input :
         { "null", "42", "true", R"({"type":"unknown"})", "[null]", "[42]", R"({"type":"bold","text":false})" }) {
        SCOPED_TRACE(input);
        EXPECT_THROW(nlohmann::json::parse(input).get<TgBot::RichText>(), std::invalid_argument);
    }
}

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

TEST(TypesJson, ParsesMessageGenerationStoppedUpdate) {
    const nlohmann::json json = {
        { "update_id", 10 },
        { "stopped_message_generation",
          {
              { "chat", { { "id", 42 }, { "type", "private" } } },
              { "message_thread_id", 7 },
              { "draft_id", 9 },
          } },
    };

    const auto update = json.get<TgBot::Update>();

    ASSERT_TRUE(update.stoppedMessageGeneration);
    ASSERT_TRUE(update.stoppedMessageGeneration->chat);
    EXPECT_EQ(update.stoppedMessageGeneration->chat->id, 42);
    EXPECT_EQ(update.stoppedMessageGeneration->messageThreadId, 7);
    EXPECT_EQ(update.stoppedMessageGeneration->draftId, 9);
}

TEST(TypesJson, DraftIdentifiersAcceptSigned64BitNumbersAndStrings) {
    static_assert(std::is_same_v<decltype(TgBot::MessageGenerationStopped::draftId), std::int64_t>);
    const std::int64_t draftIds[] = {
        std::numeric_limits<std::int64_t>::min(), -2147483649LL, -1, 2147483648LL,
        std::numeric_limits<std::int64_t>::max(),
    };
    for (const auto draftId : draftIds) {
        const auto text = std::to_string(draftId);
        for (const auto& id : { nlohmann::json::parse(text), nlohmann::json(text) }) {
            SCOPED_TRACE(id.dump());
            const nlohmann::json json = {
                { "update_id", 1 },
                { "stopped_message_generation",
                  { { "chat", { { "id", 42 }, { "type", "private" } } }, { "draft_id", id } } },
            };
            const auto update = json.get<TgBot::Update>();
            ASSERT_TRUE(update.stoppedMessageGeneration);
            EXPECT_EQ(update.stoppedMessageGeneration->draftId, draftId);
            EXPECT_EQ(nlohmann::json(update).at("stopped_message_generation").at("draft_id"), draftId);
        }
    }
}

TEST(TypesJson, DraftIdentifiersRejectInvalidAndOutOfRangeValues) {
    const std::vector<nlohmann::json> invalidIds = {
        nullptr,
        true,
        1.5,
        "",
        "1.5",
        "1x",
        " 1",
        "1 ",
        "+1",
        "9223372036854775808",
        "-9223372036854775809",
        nlohmann::json(std::uint64_t { 1 } << 63),
        nlohmann::json::array(),
        nlohmann::json::object(),
    };
    for (const auto& id : invalidIds) {
        SCOPED_TRACE(id.dump());
        const nlohmann::json json = {
            { "chat", { { "id", 42 }, { "type", "private" } } },
            { "draft_id", id },
        };
        EXPECT_THROW(json.get<TgBot::MessageGenerationStopped>(), std::invalid_argument);
    }
}

TEST(TypesJson, ParsesRichMessageBlock) {
    const nlohmann::json json = {
        { "message_id", 1 },
        { "date", 2 },
        { "chat", { { "id", 3 }, { "type", "private" } } },
        { "rich_message", { { "blocks", { { { "type", "divider" } } } }, { "is_rtl", true } } },
    };

    const auto message = json.get<TgBot::Message>();

    ASSERT_TRUE(message.richMessage);
    ASSERT_EQ(message.richMessage->blocks.size(), 1);
    ASSERT_TRUE(message.richMessage->blocks.front());
    EXPECT_TRUE(
        std::holds_alternative<std::shared_ptr<TgBot::RichBlockDivider>>(message.richMessage->blocks.front()->value));
    EXPECT_EQ(message.richMessage->isRtl, true);
}

TEST(TypesJson, ParseGeneratedObjectRejectsWrongFieldType) {
    const std::string input = R"({
        "file_id": "photo-id",
        "file_unique_id": "photo-unique-id",
        "width": "wide",
        "height": 480
    })";

    EXPECT_THROW(nlohmann::json::parse(input).get<TgBot::PhotoSize>(), std::invalid_argument);
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
