#ifndef TGBOT_TGTYPEPARSER_H
#define TGBOT_TGTYPEPARSER_H

#include <json/json.h>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "tgbot/types/Animation.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Birthdate.h"
#include "tgbot/types/BotCommand.h"
#include "tgbot/types/BotCommandScope.h"
#include "tgbot/types/BotCommandScopeAllChatAdministrators.h"
#include "tgbot/types/BotCommandScopeAllGroupChats.h"
#include "tgbot/types/BotCommandScopeAllPrivateChats.h"
#include "tgbot/types/BotCommandScopeChat.h"
#include "tgbot/types/BotCommandScopeChatAdministrators.h"
#include "tgbot/types/BotCommandScopeChatMember.h"
#include "tgbot/types/BotCommandScopeDefault.h"
#include "tgbot/types/BotDescription.h"
#include "tgbot/types/BotName.h"
#include "tgbot/types/BotShortDescription.h"
#include "tgbot/types/BusinessConnection.h"
#include "tgbot/types/BusinessIntro.h"
#include "tgbot/types/BusinessLocation.h"
#include "tgbot/types/BusinessMessagesDeleted.h"
#include "tgbot/types/BusinessOpeningHours.h"
#include "tgbot/types/BusinessOpeningHoursInterval.h"
#include "tgbot/types/CallbackGame.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/ChatAdministratorRights.h"
#include "tgbot/types/ChatBoost.h"
#include "tgbot/types/ChatBoostAdded.h"
#include "tgbot/types/ChatBoostRemoved.h"
#include "tgbot/types/ChatBoostSource.h"
#include "tgbot/types/ChatBoostSourceGiftCode.h"
#include "tgbot/types/ChatBoostSourceGiveaway.h"
#include "tgbot/types/ChatBoostSourcePremium.h"
#include "tgbot/types/ChatBoostUpdated.h"
#include "tgbot/types/ChatInviteLink.h"
#include "tgbot/types/ChatJoinRequest.h"
#include "tgbot/types/ChatLocation.h"
#include "tgbot/types/ChatMember.h"
#include "tgbot/types/ChatMemberAdministrator.h"
#include "tgbot/types/ChatMemberBanned.h"
#include "tgbot/types/ChatMemberLeft.h"
#include "tgbot/types/ChatMemberMember.h"
#include "tgbot/types/ChatMemberOwner.h"
#include "tgbot/types/ChatMemberRestricted.h"
#include "tgbot/types/ChatMemberUpdated.h"
#include "tgbot/types/ChatPermissions.h"
#include "tgbot/types/ChatPhoto.h"
#include "tgbot/types/ChatShared.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Dice.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/EncryptedCredentials.h"
#include "tgbot/types/EncryptedPassportElement.h"
#include "tgbot/types/ExternalReplyInfo.h"
#include "tgbot/types/File.h"
#include "tgbot/types/ForceReply.h"
#include "tgbot/types/ForumTopic.h"
#include "tgbot/types/ForumTopicClosed.h"
#include "tgbot/types/ForumTopicCreated.h"
#include "tgbot/types/ForumTopicEdited.h"
#include "tgbot/types/ForumTopicReopened.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/GeneralForumTopicHidden.h"
#include "tgbot/types/GeneralForumTopicUnhidden.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/Giveaway.h"
#include "tgbot/types/GiveawayCompleted.h"
#include "tgbot/types/GiveawayCreated.h"
#include "tgbot/types/GiveawayWinners.h"
#include "tgbot/types/InaccessibleMessage.h"
#include "tgbot/types/InlineKeyboardButton.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultAudio.h"
#include "tgbot/types/InlineQueryResultCachedAudio.h"
#include "tgbot/types/InlineQueryResultCachedDocument.h"
#include "tgbot/types/InlineQueryResultCachedGif.h"
#include "tgbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultCachedPhoto.h"
#include "tgbot/types/InlineQueryResultCachedSticker.h"
#include "tgbot/types/InlineQueryResultCachedVideo.h"
#include "tgbot/types/InlineQueryResultCachedVoice.h"
#include "tgbot/types/InlineQueryResultContact.h"
#include "tgbot/types/InlineQueryResultDocument.h"
#include "tgbot/types/InlineQueryResultGame.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultLocation.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultVenue.h"
#include "tgbot/types/InlineQueryResultVideo.h"
#include "tgbot/types/InlineQueryResultVoice.h"
#include "tgbot/types/InlineQueryResultsButton.h"
#include "tgbot/types/InputContactMessageContent.h"
#include "tgbot/types/InputInvoiceMessageContent.h"
#include "tgbot/types/InputLocationMessageContent.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/InputMediaAnimation.h"
#include "tgbot/types/InputMediaAudio.h"
#include "tgbot/types/InputMediaDocument.h"
#include "tgbot/types/InputMediaPhoto.h"
#include "tgbot/types/InputMediaVideo.h"
#include "tgbot/types/InputMessageContent.h"
#include "tgbot/types/InputSticker.h"
#include "tgbot/types/InputTextMessageContent.h"
#include "tgbot/types/InputVenueMessageContent.h"
#include "tgbot/types/Invoice.h"
#include "tgbot/types/KeyboardButton.h"
#include "tgbot/types/KeyboardButtonPollType.h"
#include "tgbot/types/KeyboardButtonRequestChat.h"
#include "tgbot/types/KeyboardButtonRequestUsers.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/LinkPreviewOptions.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/LoginUrl.h"
#include "tgbot/types/MaskPosition.h"
#include "tgbot/types/MenuButton.h"
#include "tgbot/types/MenuButtonCommands.h"
#include "tgbot/types/MenuButtonDefault.h"
#include "tgbot/types/MenuButtonWebApp.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/MessageAutoDeleteTimerChanged.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/MessageId.h"
#include "tgbot/types/MessageOrigin.h"
#include "tgbot/types/MessageOriginChannel.h"
#include "tgbot/types/MessageOriginChat.h"
#include "tgbot/types/MessageOriginHiddenUser.h"
#include "tgbot/types/MessageOriginUser.h"
#include "tgbot/types/MessageReactionCountUpdated.h"
#include "tgbot/types/MessageReactionUpdated.h"
#include "tgbot/types/OrderInfo.h"
#include "tgbot/types/PassportData.h"
#include "tgbot/types/PassportElementError.h"
#include "tgbot/types/PassportElementErrorDataField.h"
#include "tgbot/types/PassportElementErrorFile.h"
#include "tgbot/types/PassportElementErrorFiles.h"
#include "tgbot/types/PassportElementErrorFrontSide.h"
#include "tgbot/types/PassportElementErrorReverseSide.h"
#include "tgbot/types/PassportElementErrorSelfie.h"
#include "tgbot/types/PassportElementErrorTranslationFile.h"
#include "tgbot/types/PassportElementErrorTranslationFiles.h"
#include "tgbot/types/PassportElementErrorUnspecified.h"
#include "tgbot/types/PassportFile.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/Poll.h"
#include "tgbot/types/PollAnswer.h"
#include "tgbot/types/PollOption.h"
#include "tgbot/types/PreCheckoutQuery.h"
#include "tgbot/types/ProximityAlertTriggered.h"
#include "tgbot/types/ReactionCount.h"
#include "tgbot/types/ReactionType.h"
#include "tgbot/types/ReactionTypeCustomEmoji.h"
#include "tgbot/types/ReactionTypeEmoji.h"
#include "tgbot/types/ReplyKeyboardMarkup.h"
#include "tgbot/types/ReplyKeyboardRemove.h"
#include "tgbot/types/ReplyParameters.h"
#include "tgbot/types/ResponseParameters.h"
#include "tgbot/types/SentWebAppMessage.h"
#include "tgbot/types/SharedUser.h"
#include "tgbot/types/ShippingAddress.h"
#include "tgbot/types/ShippingOption.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/Story.h"
#include "tgbot/types/SuccessfulPayment.h"
#include "tgbot/types/SwitchInlineQueryChosenChat.h"
#include "tgbot/types/TextQuote.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/User.h"
#include "tgbot/types/UserChatBoosts.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/UsersShared.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/VideoChatEnded.h"
#include "tgbot/types/VideoChatParticipantsInvited.h"
#include "tgbot/types/VideoChatScheduled.h"
#include "tgbot/types/VideoChatStarted.h"
#include "tgbot/types/VideoNote.h"
#include "tgbot/types/Voice.h"
#include "tgbot/types/WebAppData.h"
#include "tgbot/types/WebAppInfo.h"
#include "tgbot/types/WebhookInfo.h"
#include "tgbot/types/WriteAccessAllowed.h"

namespace TgBot {

template <typename T>
using Matrix = std::vector<std::vector<T>>;
namespace detail {  // shared_ptr
template <typename T>
struct is_shared_ptr : std::false_type {};

template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {
    using type = T;
};

template <typename T>
constexpr bool is_shared_ptr_v = is_shared_ptr<T>::value;

// vector
template <typename T>
struct is_vector : std::false_type {};
template <typename T>
struct is_vector<std::vector<T>> : std::true_type {
    using type = T;
};
template <typename T>
constexpr bool is_vector_v = is_vector<T>::value;

// primitive
template <typename T>
struct is_primitive : std::false_type {};
template <>
struct is_primitive<std::string> : std::true_type {};
template <>
struct is_primitive<int> : std::true_type {};
template <>
struct is_primitive<bool> : std::true_type {};

template <typename T>
constexpr bool is_primitive_v = is_primitive<T>::value;

// Matrix
template <typename T>
struct is_matrix : std::false_type {};
template <typename T>
struct is_matrix<Matrix<T>> : std::true_type {
    using type = T;
};
template <typename T>
constexpr bool is_matrix_v = is_matrix<T>::value;

}  // namespace detail

// Parse function for shared_ptr<T>
template <typename T>
std::shared_ptr<T> parse(const Json::Value &data) = delete;

#define DECLARE_PARSER_FROM_JSON(TYPE) \
    template <>                         \
    TYPE::Ptr parse(const Json::Value &data)

// Grab array of T from JSON array.
template <typename T>
std::vector<std::shared_ptr<T>> parseArray(const Json::Value &data) {
    std::vector<std::shared_ptr<T>> result;
    for (const auto &item : data) {
        result.emplace_back(parse<T>(item));
    }
    return result;
}

// Parse array from a key.
template <typename T>
std::vector<std::shared_ptr<T>> parseArray(const Json::Value &data, const std::string &key) {
    if (!data.isMember(key)) {
        return {};
    }
    return parseArray<T>(data[key]);
}

// Parse 2D array of T from JSON.
template <typename T>
Matrix<std::shared_ptr<T>> parseMatrix(const Json::Value &data) {
    Matrix<std::shared_ptr<T>> result;
    for (const auto &item : data) {
        result.emplace_back(parseArray<T>(item));
    }
    return result;
}

template <typename T>
Matrix<std::shared_ptr<T>> parseMatrix(const Json::Value &data, const std::string &key) {
    if (!data.isMember(key)) {
        return {};
    }
    return parseMatrix<T>(data[key]);
}

// Parse an array of primitive types.
template <typename T>
std::vector<T> parsePrimitiveArray(const Json::Value &data, const std::string &key) {
    if (!data.isMember(key)) {
        return {};
    }
    std::vector<T> result;
    for (const auto &item : data[key]) {
        result.emplace_back(item.as<T>());
    }
    return result;
}

// Put function for objects to JSON
template <typename T>
Json::Value put(const T &value) = delete;

#define DECLARE_PARSER_TO_JSON(TYPE) \
    template <>                       \
    Json::Value put(const TYPE::Ptr &object)

// Helper to put base class shared_ptr to derived T.
template <typename T, typename V,
          std::enable_if_t<detail::is_shared_ptr_v<V> &&
                               !std::is_same_v<typename T::Ptr, V> &&
                               std::is_base_of_v<typename V::element_type, T>,
                           bool> = true>
Json::Value put(const V &data) {
    return put(std::static_pointer_cast<T>(data));
}

// Put vector to JSON.
template <typename T, std::enable_if_t<!detail::is_vector_v<T>, bool> = true>
Json::Value put(const std::vector<T> &vector) {
    Json::Value dataArray(Json::arrayValue);
    for (const auto &item : vector) {
        if constexpr (detail::is_primitive_v<T>) {
            dataArray.append(item);
        } else {
            dataArray.append(put(item));  // Recursively call put for non-primitives
        }
    }
    return dataArray;
}

// Put 2D array (Matrix) to JSON.
template <typename T>
Json::Value put(const Matrix<T> &matrix) {
    Json::Value dataMatrix(Json::arrayValue);
    for (const auto &row : matrix) {
        dataMatrix.append(put(row));  // Recursively call put for each row
    }
    return dataMatrix;
}

// Serialize object to JSON string.
template <typename T>
std::string putJSON(const T &object) {
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, put(object));
}


#define IMPLEMENT_PARSERS(type)      \
    DECLARE_PARSER_FROM_JSON(type); \
    DECLARE_PARSER_TO_JSON(type)
IMPLEMENT_PARSERS(Animation);
IMPLEMENT_PARSERS(Audio);
IMPLEMENT_PARSERS(Birthdate);
IMPLEMENT_PARSERS(BotCommand);
IMPLEMENT_PARSERS(BotCommandScope);
IMPLEMENT_PARSERS(BotCommandScopeAllChatAdministrators);
IMPLEMENT_PARSERS(BotCommandScopeAllGroupChats);
IMPLEMENT_PARSERS(BotCommandScopeAllPrivateChats);
IMPLEMENT_PARSERS(BotCommandScopeChat);
IMPLEMENT_PARSERS(BotCommandScopeChatAdministrators);
IMPLEMENT_PARSERS(BotCommandScopeChatMember);
IMPLEMENT_PARSERS(BotCommandScopeDefault);
IMPLEMENT_PARSERS(BotDescription);
IMPLEMENT_PARSERS(BotName);
IMPLEMENT_PARSERS(BotShortDescription);
IMPLEMENT_PARSERS(BusinessConnection);
IMPLEMENT_PARSERS(BusinessIntro);
IMPLEMENT_PARSERS(BusinessLocation);
IMPLEMENT_PARSERS(BusinessMessagesDeleted);
IMPLEMENT_PARSERS(BusinessOpeningHours);
IMPLEMENT_PARSERS(BusinessOpeningHoursInterval);
IMPLEMENT_PARSERS(CallbackGame);
IMPLEMENT_PARSERS(CallbackQuery);
IMPLEMENT_PARSERS(Chat);
IMPLEMENT_PARSERS(ChatAdministratorRights);
IMPLEMENT_PARSERS(ChatBoost);
IMPLEMENT_PARSERS(ChatBoostAdded);
IMPLEMENT_PARSERS(ChatBoostRemoved);
IMPLEMENT_PARSERS(ChatBoostSource);
IMPLEMENT_PARSERS(ChatBoostSourceGiftCode);
IMPLEMENT_PARSERS(ChatBoostSourceGiveaway);
IMPLEMENT_PARSERS(ChatBoostSourcePremium);
IMPLEMENT_PARSERS(ChatBoostUpdated);
IMPLEMENT_PARSERS(ChatInviteLink);
IMPLEMENT_PARSERS(ChatJoinRequest);
IMPLEMENT_PARSERS(ChatLocation);
IMPLEMENT_PARSERS(ChatMember);
IMPLEMENT_PARSERS(ChatMemberAdministrator);
IMPLEMENT_PARSERS(ChatMemberBanned);
IMPLEMENT_PARSERS(ChatMemberLeft);
IMPLEMENT_PARSERS(ChatMemberMember);
IMPLEMENT_PARSERS(ChatMemberOwner);
IMPLEMENT_PARSERS(ChatMemberRestricted);
IMPLEMENT_PARSERS(ChatMemberUpdated);
IMPLEMENT_PARSERS(ChatPermissions);
IMPLEMENT_PARSERS(ChatPhoto);
IMPLEMENT_PARSERS(ChatShared);
IMPLEMENT_PARSERS(ChosenInlineResult);
IMPLEMENT_PARSERS(Contact);
IMPLEMENT_PARSERS(Dice);
IMPLEMENT_PARSERS(Document);
IMPLEMENT_PARSERS(EncryptedCredentials);
IMPLEMENT_PARSERS(EncryptedPassportElement);
IMPLEMENT_PARSERS(ExternalReplyInfo);
IMPLEMENT_PARSERS(File);
IMPLEMENT_PARSERS(ForceReply);
IMPLEMENT_PARSERS(ForumTopic);
IMPLEMENT_PARSERS(ForumTopicClosed);
IMPLEMENT_PARSERS(ForumTopicCreated);
IMPLEMENT_PARSERS(ForumTopicEdited);
IMPLEMENT_PARSERS(ForumTopicReopened);
IMPLEMENT_PARSERS(Game);
IMPLEMENT_PARSERS(GameHighScore);
IMPLEMENT_PARSERS(GeneralForumTopicHidden);
IMPLEMENT_PARSERS(GeneralForumTopicUnhidden);
IMPLEMENT_PARSERS(GenericReply);
IMPLEMENT_PARSERS(Giveaway);
IMPLEMENT_PARSERS(GiveawayCompleted);
IMPLEMENT_PARSERS(GiveawayCreated);
IMPLEMENT_PARSERS(GiveawayWinners);
IMPLEMENT_PARSERS(InaccessibleMessage);
IMPLEMENT_PARSERS(InlineKeyboardButton);
IMPLEMENT_PARSERS(InlineKeyboardMarkup);
IMPLEMENT_PARSERS(InlineQuery);
IMPLEMENT_PARSERS(InlineQueryResult);
IMPLEMENT_PARSERS(InlineQueryResultArticle);
IMPLEMENT_PARSERS(InlineQueryResultAudio);
IMPLEMENT_PARSERS(InlineQueryResultCachedAudio);
IMPLEMENT_PARSERS(InlineQueryResultCachedDocument);
IMPLEMENT_PARSERS(InlineQueryResultCachedGif);
IMPLEMENT_PARSERS(InlineQueryResultCachedMpeg4Gif);
IMPLEMENT_PARSERS(InlineQueryResultCachedPhoto);
IMPLEMENT_PARSERS(InlineQueryResultCachedSticker);
IMPLEMENT_PARSERS(InlineQueryResultCachedVideo);
IMPLEMENT_PARSERS(InlineQueryResultCachedVoice);
IMPLEMENT_PARSERS(InlineQueryResultContact);
IMPLEMENT_PARSERS(InlineQueryResultDocument);
IMPLEMENT_PARSERS(InlineQueryResultGame);
IMPLEMENT_PARSERS(InlineQueryResultGif);
IMPLEMENT_PARSERS(InlineQueryResultLocation);
IMPLEMENT_PARSERS(InlineQueryResultMpeg4Gif);
IMPLEMENT_PARSERS(InlineQueryResultPhoto);
IMPLEMENT_PARSERS(InlineQueryResultVenue);
IMPLEMENT_PARSERS(InlineQueryResultVideo);
IMPLEMENT_PARSERS(InlineQueryResultVoice);
IMPLEMENT_PARSERS(InlineQueryResultsButton);
IMPLEMENT_PARSERS(InputContactMessageContent);
IMPLEMENT_PARSERS(InputInvoiceMessageContent);
IMPLEMENT_PARSERS(InputLocationMessageContent);
IMPLEMENT_PARSERS(InputMedia);
IMPLEMENT_PARSERS(InputMediaAnimation);
IMPLEMENT_PARSERS(InputMediaAudio);
IMPLEMENT_PARSERS(InputMediaDocument);
IMPLEMENT_PARSERS(InputMediaPhoto);
IMPLEMENT_PARSERS(InputMediaVideo);
IMPLEMENT_PARSERS(InputMessageContent);
IMPLEMENT_PARSERS(InputSticker);
IMPLEMENT_PARSERS(InputTextMessageContent);
IMPLEMENT_PARSERS(InputVenueMessageContent);
IMPLEMENT_PARSERS(Invoice);
IMPLEMENT_PARSERS(KeyboardButton);
IMPLEMENT_PARSERS(KeyboardButtonPollType);
IMPLEMENT_PARSERS(KeyboardButtonRequestChat);
IMPLEMENT_PARSERS(KeyboardButtonRequestUsers);
IMPLEMENT_PARSERS(LabeledPrice);
IMPLEMENT_PARSERS(LinkPreviewOptions);
IMPLEMENT_PARSERS(Location);
IMPLEMENT_PARSERS(LoginUrl);
IMPLEMENT_PARSERS(MaskPosition);
IMPLEMENT_PARSERS(MenuButton);
IMPLEMENT_PARSERS(MenuButtonCommands);
IMPLEMENT_PARSERS(MenuButtonDefault);
IMPLEMENT_PARSERS(MenuButtonWebApp);
IMPLEMENT_PARSERS(Message);
IMPLEMENT_PARSERS(MessageAutoDeleteTimerChanged);
IMPLEMENT_PARSERS(MessageEntity);
IMPLEMENT_PARSERS(MessageId);
IMPLEMENT_PARSERS(MessageOrigin);
IMPLEMENT_PARSERS(MessageOriginChannel);
IMPLEMENT_PARSERS(MessageOriginChat);
IMPLEMENT_PARSERS(MessageOriginHiddenUser);
IMPLEMENT_PARSERS(MessageOriginUser);
IMPLEMENT_PARSERS(MessageReactionCountUpdated);
IMPLEMENT_PARSERS(MessageReactionUpdated);
IMPLEMENT_PARSERS(OrderInfo);
IMPLEMENT_PARSERS(PassportData);
IMPLEMENT_PARSERS(PassportElementError);
IMPLEMENT_PARSERS(PassportElementErrorDataField);
IMPLEMENT_PARSERS(PassportElementErrorFile);
IMPLEMENT_PARSERS(PassportElementErrorFiles);
IMPLEMENT_PARSERS(PassportElementErrorFrontSide);
IMPLEMENT_PARSERS(PassportElementErrorReverseSide);
IMPLEMENT_PARSERS(PassportElementErrorSelfie);
IMPLEMENT_PARSERS(PassportElementErrorTranslationFile);
IMPLEMENT_PARSERS(PassportElementErrorTranslationFiles);
IMPLEMENT_PARSERS(PassportElementErrorUnspecified);
IMPLEMENT_PARSERS(PassportFile);
IMPLEMENT_PARSERS(PhotoSize);
IMPLEMENT_PARSERS(Poll);
IMPLEMENT_PARSERS(PollAnswer);
IMPLEMENT_PARSERS(PollOption);
IMPLEMENT_PARSERS(PreCheckoutQuery);
IMPLEMENT_PARSERS(ProximityAlertTriggered);
IMPLEMENT_PARSERS(ReactionCount);
IMPLEMENT_PARSERS(ReactionType);
IMPLEMENT_PARSERS(ReactionTypeCustomEmoji);
IMPLEMENT_PARSERS(ReactionTypeEmoji);
IMPLEMENT_PARSERS(ReplyKeyboardMarkup);
IMPLEMENT_PARSERS(ReplyKeyboardRemove);
IMPLEMENT_PARSERS(ReplyParameters);
IMPLEMENT_PARSERS(ResponseParameters);
IMPLEMENT_PARSERS(SentWebAppMessage);
IMPLEMENT_PARSERS(SharedUser);
IMPLEMENT_PARSERS(ShippingAddress);
IMPLEMENT_PARSERS(ShippingOption);
IMPLEMENT_PARSERS(ShippingQuery);
IMPLEMENT_PARSERS(Sticker);
IMPLEMENT_PARSERS(StickerSet);
IMPLEMENT_PARSERS(Story);
IMPLEMENT_PARSERS(SuccessfulPayment);
IMPLEMENT_PARSERS(SwitchInlineQueryChosenChat);
IMPLEMENT_PARSERS(TextQuote);
IMPLEMENT_PARSERS(Update);
IMPLEMENT_PARSERS(User);
IMPLEMENT_PARSERS(UserChatBoosts);
IMPLEMENT_PARSERS(UserProfilePhotos);
IMPLEMENT_PARSERS(UsersShared);
IMPLEMENT_PARSERS(Venue);
IMPLEMENT_PARSERS(Video);
IMPLEMENT_PARSERS(VideoChatEnded);
IMPLEMENT_PARSERS(VideoChatParticipantsInvited);
IMPLEMENT_PARSERS(VideoChatScheduled);
IMPLEMENT_PARSERS(VideoChatStarted);
IMPLEMENT_PARSERS(VideoNote);
IMPLEMENT_PARSERS(Voice);
IMPLEMENT_PARSERS(WebAppData);
IMPLEMENT_PARSERS(WebAppInfo);
IMPLEMENT_PARSERS(WebhookInfo);
IMPLEMENT_PARSERS(WriteAccessAllowed);

}  // namespace TgBot

#endif  // TGBOT_TGTYPEPARSER_H
