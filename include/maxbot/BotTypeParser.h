#ifndef TGBOT_TGTYPEPARSER_H
#define TGBOT_TGTYPEPARSER_H

#include "maxbot/export.h"
#include "maxbot/types/Update.h"
#include "maxbot/types/WebhookInfo.h"
#include "maxbot/types/User.h"
#include "maxbot/types/Chat.h"
#include "maxbot/types/Message.h"
#include "maxbot/types/MessageId.h"
#include "maxbot/types/InaccessibleMessage.h"
#include "maxbot/types/MessageEntity.h"
#include "maxbot/types/TextQuote.h"
#include "maxbot/types/ExternalReplyInfo.h"
#include "maxbot/types/ReplyParameters.h"
#include "maxbot/types/MessageOrigin.h"
#include "maxbot/types/MessageOriginUser.h"
#include "maxbot/types/MessageOriginHiddenUser.h"
#include "maxbot/types/MessageOriginChat.h"
#include "maxbot/types/MessageOriginChannel.h"
#include "maxbot/types/PhotoSize.h"
#include "maxbot/types/Animation.h"
#include "maxbot/types/Audio.h"
#include "maxbot/types/Document.h"
#include "maxbot/types/Story.h"
#include "maxbot/types/Video.h"
#include "maxbot/types/VideoNote.h"
#include "maxbot/types/Voice.h"
#include "maxbot/types/Contact.h"
#include "maxbot/types/Dice.h"
#include "maxbot/types/PollOption.h"
#include "maxbot/types/PollAnswer.h"
#include "maxbot/types/Poll.h"
#include "maxbot/types/Location.h"
#include "maxbot/types/Venue.h"
#include "maxbot/types/WebAppData.h"
#include "maxbot/types/ProximityAlertTriggered.h"
#include "maxbot/types/MessageAutoDeleteTimerChanged.h"
#include "maxbot/types/ChatBoostAdded.h"
#include "maxbot/types/ForumTopicCreated.h"
#include "maxbot/types/ForumTopicClosed.h"
#include "maxbot/types/ForumTopicEdited.h"
#include "maxbot/types/ForumTopicReopened.h"
#include "maxbot/types/GeneralForumTopicHidden.h"
#include "maxbot/types/GeneralForumTopicUnhidden.h"
#include "maxbot/types/SharedUser.h"
#include "maxbot/types/UsersShared.h"
#include "maxbot/types/ChatShared.h"
#include "maxbot/types/WriteAccessAllowed.h"
#include "maxbot/types/VideoChatScheduled.h"
#include "maxbot/types/VideoChatStarted.h"
#include "maxbot/types/VideoChatEnded.h"
#include "maxbot/types/VideoChatParticipantsInvited.h"
#include "maxbot/types/GiveawayCreated.h"
#include "maxbot/types/Giveaway.h"
#include "maxbot/types/GiveawayWinners.h"
#include "maxbot/types/GiveawayCompleted.h"
#include "maxbot/types/LinkPreviewOptions.h"
#include "maxbot/types/UserProfilePhotos.h"
#include "maxbot/types/File.h"
#include "maxbot/types/WebAppInfo.h"
#include "maxbot/types/ReplyKeyboardMarkup.h"
#include "maxbot/types/KeyboardButton.h"
#include "maxbot/types/KeyboardButtonRequestUsers.h"
#include "maxbot/types/KeyboardButtonRequestChat.h"
#include "maxbot/types/KeyboardButtonPollType.h"
#include "maxbot/types/ReplyKeyboardRemove.h"
#include "maxbot/types/InlineKeyboardMarkup.h"
#include "maxbot/types/InlineKeyboardButton.h"
#include "maxbot/types/LoginUrl.h"
#include "maxbot/types/SwitchInlineQueryChosenChat.h"
#include "maxbot/types/CallbackQuery.h"
#include "maxbot/types/ForceReply.h"
#include "maxbot/types/ChatPhoto.h"
#include "maxbot/types/ChatInviteLink.h"
#include "maxbot/types/ChatAdministratorRights.h"
#include "maxbot/types/ChatMemberUpdated.h"
#include "maxbot/types/ChatMember.h"
#include "maxbot/types/ChatMemberOwner.h"
#include "maxbot/types/ChatMemberAdministrator.h"
#include "maxbot/types/ChatMemberMember.h"
#include "maxbot/types/ChatMemberRestricted.h"
#include "maxbot/types/ChatMemberLeft.h"
#include "maxbot/types/ChatMemberBanned.h"
#include "maxbot/types/ChatJoinRequest.h"
#include "maxbot/types/ChatPermissions.h"
#include "maxbot/types/Birthdate.h"
#include "maxbot/types/BusinessIntro.h"
#include "maxbot/types/BusinessLocation.h"
#include "maxbot/types/BusinessOpeningHoursInterval.h"
#include "maxbot/types/BusinessOpeningHours.h"
#include "maxbot/types/ChatLocation.h"
#include "maxbot/types/ReactionType.h"
#include "maxbot/types/ReactionTypeEmoji.h"
#include "maxbot/types/ReactionTypeCustomEmoji.h"
#include "maxbot/types/ReactionCount.h"
#include "maxbot/types/MessageReactionUpdated.h"
#include "maxbot/types/MessageReactionCountUpdated.h"
#include "maxbot/types/ForumTopic.h"
#include "maxbot/types/BotCommand.h"
#include "maxbot/types/BotCommandScope.h"
#include "maxbot/types/BotCommandScopeDefault.h"
#include "maxbot/types/BotCommandScopeAllPrivateChats.h"
#include "maxbot/types/BotCommandScopeAllGroupChats.h"
#include "maxbot/types/BotCommandScopeAllChatAdministrators.h"
#include "maxbot/types/BotCommandScopeChat.h"
#include "maxbot/types/BotCommandScopeChatAdministrators.h"
#include "maxbot/types/BotCommandScopeChatMember.h"
#include "maxbot/types/BotName.h"
#include "maxbot/types/BotDescription.h"
#include "maxbot/types/BotShortDescription.h"
#include "maxbot/types/MenuButton.h"
#include "maxbot/types/MenuButtonCommands.h"
#include "maxbot/types/MenuButtonWebApp.h"
#include "maxbot/types/MenuButtonDefault.h"
#include "maxbot/types/ChatBoostSource.h"
#include "maxbot/types/ChatBoostSourcePremium.h"
#include "maxbot/types/ChatBoostSourceGiftCode.h"
#include "maxbot/types/ChatBoostSourceGiveaway.h"
#include "maxbot/types/ChatBoost.h"
#include "maxbot/types/ChatBoostUpdated.h"
#include "maxbot/types/ChatBoostRemoved.h"
#include "maxbot/types/UserChatBoosts.h"
#include "maxbot/types/BusinessConnection.h"
#include "maxbot/types/BusinessMessagesDeleted.h"
#include "maxbot/types/ResponseParameters.h"
#include "maxbot/types/InputMedia.h"
#include "maxbot/types/InputMediaPhoto.h"
#include "maxbot/types/InputMediaVideo.h"
#include "maxbot/types/InputMediaAnimation.h"
#include "maxbot/types/InputMediaAudio.h"
#include "maxbot/types/InputMediaDocument.h"
#include "maxbot/types/Sticker.h"
#include "maxbot/types/StickerSet.h"
#include "maxbot/types/MaskPosition.h"
#include "maxbot/types/InputSticker.h"
#include "maxbot/types/InlineQuery.h"
#include "maxbot/types/InlineQueryResultsButton.h"
#include "maxbot/types/InlineQueryResult.h"
#include "maxbot/types/InlineQueryResultArticle.h"
#include "maxbot/types/InlineQueryResultPhoto.h"
#include "maxbot/types/InlineQueryResultGif.h"
#include "maxbot/types/InlineQueryResultMpeg4Gif.h"
#include "maxbot/types/InlineQueryResultVideo.h"
#include "maxbot/types/InlineQueryResultAudio.h"
#include "maxbot/types/InlineQueryResultVoice.h"
#include "maxbot/types/InlineQueryResultDocument.h"
#include "maxbot/types/InlineQueryResultLocation.h"
#include "maxbot/types/InlineQueryResultVenue.h"
#include "maxbot/types/InlineQueryResultContact.h"
#include "maxbot/types/InlineQueryResultGame.h"
#include "maxbot/types/InlineQueryResultCachedPhoto.h"
#include "maxbot/types/InlineQueryResultCachedGif.h"
#include "maxbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "maxbot/types/InlineQueryResultCachedSticker.h"
#include "maxbot/types/InlineQueryResultCachedDocument.h"
#include "maxbot/types/InlineQueryResultCachedVideo.h"
#include "maxbot/types/InlineQueryResultCachedVoice.h"
#include "maxbot/types/InlineQueryResultCachedAudio.h"
#include "maxbot/types/InputMessageContent.h"
#include "maxbot/types/InputTextMessageContent.h"
#include "maxbot/types/InputLocationMessageContent.h"
#include "maxbot/types/InputVenueMessageContent.h"
#include "maxbot/types/InputContactMessageContent.h"
#include "maxbot/types/InputInvoiceMessageContent.h"
#include "maxbot/types/ChosenInlineResult.h"
#include "maxbot/types/SentWebAppMessage.h"
#include "maxbot/types/LabeledPrice.h"
#include "maxbot/types/Invoice.h"
#include "maxbot/types/ShippingAddress.h"
#include "maxbot/types/OrderInfo.h"
#include "maxbot/types/ShippingOption.h"
#include "maxbot/types/SuccessfulPayment.h"
#include "maxbot/types/ShippingQuery.h"
#include "maxbot/types/PreCheckoutQuery.h"
#include "maxbot/types/PassportData.h"
#include "maxbot/types/PassportFile.h"
#include "maxbot/types/EncryptedPassportElement.h"
#include "maxbot/types/EncryptedCredentials.h"
#include "maxbot/types/PassportElementError.h"
#include "maxbot/types/PassportElementErrorDataField.h"
#include "maxbot/types/PassportElementErrorFrontSide.h"
#include "maxbot/types/PassportElementErrorReverseSide.h"
#include "maxbot/types/PassportElementErrorSelfie.h"
#include "maxbot/types/PassportElementErrorFile.h"
#include "maxbot/types/PassportElementErrorFiles.h"
#include "maxbot/types/PassportElementErrorTranslationFile.h"
#include "maxbot/types/PassportElementErrorTranslationFiles.h"
#include "maxbot/types/PassportElementErrorUnspecified.h"
#include "maxbot/types/Game.h"
#include "maxbot/types/CallbackGame.h"
#include "maxbot/types/GameHighScore.h"
#include "maxbot/types/GenericReply.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace MaxBot {

class TGBOT_API BotTypeParser {

public:
    template<typename T>
    using JsonToBotTypeFunc = std::shared_ptr<T> (BotTypeParser::*)(const boost::property_tree::ptree&) const;

    template<typename T>
    using BotTypeToJsonFunc = std::string (BotTypeParser::*)(const std::shared_ptr<T>&) const;

    Update::Ptr parseJsonAndGetUpdate(const boost::property_tree::ptree& data) const;
    std::string parseUpdate(const Update::Ptr& object) const;

    WebhookInfo::Ptr parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data) const;
    std::string parseWebhookInfo(const WebhookInfo::Ptr& object) const;

    User::Ptr parseJsonAndGetUser(const boost::property_tree::ptree& data) const;
    std::string parseUser(const User::Ptr& object) const;

    Chat::Ptr parseJsonAndGetChat(const boost::property_tree::ptree& data) const;
    std::string parseChat(const Chat::Ptr& object) const;

    Message::Ptr parseJsonAndGetMessage(const boost::property_tree::ptree& data) const;
    std::string parseMessage(const Message::Ptr& object) const;

    MessageId::Ptr parseJsonAndGetMessageId(const boost::property_tree::ptree& data) const;
    std::string parseMessageId(const MessageId::Ptr& object) const;

    InaccessibleMessage::Ptr parseJsonAndGetInaccessibleMessage(const boost::property_tree::ptree& data) const;
    std::string parseInaccessibleMessage(const InaccessibleMessage::Ptr& object) const;

    MessageEntity::Ptr parseJsonAndGetMessageEntity(const boost::property_tree::ptree& data) const;
    std::string parseMessageEntity(const MessageEntity::Ptr& object) const;

    TextQuote::Ptr parseJsonAndGetTextQuote(const boost::property_tree::ptree& data) const;
    std::string parseTextQuote(const TextQuote::Ptr& object) const;

    ExternalReplyInfo::Ptr parseJsonAndGetExternalReplyInfo(const boost::property_tree::ptree& data) const;
    std::string parseExternalReplyInfo(const ExternalReplyInfo::Ptr& object) const;

    ReplyParameters::Ptr parseJsonAndGetReplyParameters(const boost::property_tree::ptree& data) const;
    std::string parseReplyParameters(const ReplyParameters::Ptr& object) const;

    MessageOrigin::Ptr parseJsonAndGetMessageOrigin(const boost::property_tree::ptree& data) const;
    std::string parseMessageOrigin(const MessageOrigin::Ptr& object) const;

    MessageOriginUser::Ptr parseJsonAndGetMessageOriginUser(const boost::property_tree::ptree& data) const;
    std::string parseMessageOriginUser(const MessageOriginUser::Ptr& object) const;

    MessageOriginHiddenUser::Ptr parseJsonAndGetMessageOriginHiddenUser(const boost::property_tree::ptree& data) const;
    std::string parseMessageOriginHiddenUser(const MessageOriginHiddenUser::Ptr& object) const;

    MessageOriginChat::Ptr parseJsonAndGetMessageOriginChat(const boost::property_tree::ptree& data) const;
    std::string parseMessageOriginChat(const MessageOriginChat::Ptr& object) const;

    MessageOriginChannel::Ptr parseJsonAndGetMessageOriginChannel(const boost::property_tree::ptree& data) const;
    std::string parseMessageOriginChannel(const MessageOriginChannel::Ptr& object) const;

    PhotoSize::Ptr parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data) const;
    std::string parsePhotoSize(const PhotoSize::Ptr& object) const;

    Animation::Ptr parseJsonAndGetAnimation(const boost::property_tree::ptree& data) const;
    std::string parseAnimation(const Animation::Ptr& object) const;

    Audio::Ptr parseJsonAndGetAudio(const boost::property_tree::ptree& data) const;
    std::string parseAudio(const Audio::Ptr& object) const;

    Document::Ptr parseJsonAndGetDocument(const boost::property_tree::ptree& data) const;
    std::string parseDocument(const Document::Ptr& object) const;

    Story::Ptr parseJsonAndGetStory(const boost::property_tree::ptree& data) const;
    std::string parseStory(const Story::Ptr& object) const;

    Video::Ptr parseJsonAndGetVideo(const boost::property_tree::ptree& data) const;
    std::string parseVideo(const Video::Ptr& object) const;

    VideoNote::Ptr parseJsonAndGetVideoNote(const boost::property_tree::ptree& data) const;
    std::string parseVideoNote(const VideoNote::Ptr& object) const;

    Voice::Ptr parseJsonAndGetVoice(const boost::property_tree::ptree& data) const;
    std::string parseVoice(const Voice::Ptr& object) const;

    Contact::Ptr parseJsonAndGetContact(const boost::property_tree::ptree& data) const;
    std::string parseContact(const Contact::Ptr& object) const;

    Dice::Ptr parseJsonAndGetDice(const boost::property_tree::ptree& data) const;
    std::string parseDice(const Dice::Ptr& object) const;

    PollOption::Ptr parseJsonAndGetPollOption(const boost::property_tree::ptree& data) const;
    std::string parsePollOption(const PollOption::Ptr& object) const;

    PollAnswer::Ptr parseJsonAndGetPollAnswer(const boost::property_tree::ptree& data) const;
    std::string parsePollAnswer(const PollAnswer::Ptr& object) const;

    Poll::Ptr parseJsonAndGetPoll(const boost::property_tree::ptree& data) const;
    std::string parsePoll(const Poll::Ptr& object) const;

    Location::Ptr parseJsonAndGetLocation(const boost::property_tree::ptree& data) const;
    std::string parseLocation(const Location::Ptr& object) const;

    Venue::Ptr parseJsonAndGetVenue(const boost::property_tree::ptree& data) const;
    std::string parseVenue(const Venue::Ptr& object) const;

    WebAppData::Ptr parseJsonAndGetWebAppData(const boost::property_tree::ptree& data) const;
    std::string parseWebAppData(const WebAppData::Ptr& object) const;

    ProximityAlertTriggered::Ptr parseJsonAndGetProximityAlertTriggered(const boost::property_tree::ptree& data) const;
    std::string parseProximityAlertTriggered(const ProximityAlertTriggered::Ptr& object) const;

    MessageAutoDeleteTimerChanged::Ptr parseJsonAndGetMessageAutoDeleteTimerChanged(const boost::property_tree::ptree& data) const;
    std::string parseMessageAutoDeleteTimerChanged(const MessageAutoDeleteTimerChanged::Ptr& object) const;

    ChatBoostAdded::Ptr parseJsonAndGetChatBoostAdded(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostAdded(const ChatBoostAdded::Ptr& object) const;

    ForumTopicCreated::Ptr parseJsonAndGetForumTopicCreated(const boost::property_tree::ptree& data) const;
    std::string parseForumTopicCreated(const ForumTopicCreated::Ptr& object) const;

    ForumTopicClosed::Ptr parseJsonAndGetForumTopicClosed(const boost::property_tree::ptree& data) const;
    std::string parseForumTopicClosed(const ForumTopicClosed::Ptr& object) const;

    ForumTopicEdited::Ptr parseJsonAndGetForumTopicEdited(const boost::property_tree::ptree& data) const;
    std::string parseForumTopicEdited(const ForumTopicEdited::Ptr& object) const;

    ForumTopicReopened::Ptr parseJsonAndGetForumTopicReopened(const boost::property_tree::ptree& data) const;
    std::string parseForumTopicReopened(const ForumTopicReopened::Ptr& object) const;

    GeneralForumTopicHidden::Ptr parseJsonAndGetGeneralForumTopicHidden(const boost::property_tree::ptree& data) const;
    std::string parseGeneralForumTopicHidden(const GeneralForumTopicHidden::Ptr& object) const;

    GeneralForumTopicUnhidden::Ptr parseJsonAndGetGeneralForumTopicUnhidden(const boost::property_tree::ptree& data) const;
    std::string parseGeneralForumTopicUnhidden(const GeneralForumTopicUnhidden::Ptr& object) const;

    SharedUser::Ptr parseJsonAndGetSharedUser(const boost::property_tree::ptree& data) const;
    std::string parseSharedUser(const SharedUser::Ptr& object) const;

    UsersShared::Ptr parseJsonAndGetUsersShared(const boost::property_tree::ptree& data) const;
    std::string parseUsersShared(const UsersShared::Ptr& object) const;

    ChatShared::Ptr parseJsonAndGetChatShared(const boost::property_tree::ptree& data) const;
    std::string parseChatShared(const ChatShared::Ptr& object) const;

    WriteAccessAllowed::Ptr parseJsonAndGetWriteAccessAllowed(const boost::property_tree::ptree& data) const;
    std::string parseWriteAccessAllowed(const WriteAccessAllowed::Ptr& object) const;

    VideoChatScheduled::Ptr parseJsonAndGetVideoChatScheduled(const boost::property_tree::ptree& data) const;
    std::string parseVideoChatScheduled(const VideoChatScheduled::Ptr& object) const;

    VideoChatStarted::Ptr parseJsonAndGetVideoChatStarted(const boost::property_tree::ptree& data) const;
    std::string parseVideoChatStarted(const VideoChatStarted::Ptr& object) const;

    VideoChatEnded::Ptr parseJsonAndGetVideoChatEnded(const boost::property_tree::ptree& data) const;
    std::string parseVideoChatEnded(const VideoChatEnded::Ptr& object) const;

    VideoChatParticipantsInvited::Ptr parseJsonAndGetVideoChatParticipantsInvited(const boost::property_tree::ptree& data) const;
    std::string parseVideoChatParticipantsInvited(const VideoChatParticipantsInvited::Ptr& object) const;

    GiveawayCreated::Ptr parseJsonAndGetGiveawayCreated(const boost::property_tree::ptree& data) const;
    std::string parseGiveawayCreated(const GiveawayCreated::Ptr& object) const;

    Giveaway::Ptr parseJsonAndGetGiveaway(const boost::property_tree::ptree& data) const;
    std::string parseGiveaway(const Giveaway::Ptr& object) const;

    GiveawayWinners::Ptr parseJsonAndGetGiveawayWinners(const boost::property_tree::ptree& data) const;
    std::string parseGiveawayWinners(const GiveawayWinners::Ptr& object) const;

    GiveawayCompleted::Ptr parseJsonAndGetGiveawayCompleted(const boost::property_tree::ptree& data) const;
    std::string parseGiveawayCompleted(const GiveawayCompleted::Ptr& object) const;

    LinkPreviewOptions::Ptr parseJsonAndGetLinkPreviewOptions(const boost::property_tree::ptree& data) const;
    std::string parseLinkPreviewOptions(const LinkPreviewOptions::Ptr& object) const;

    UserProfilePhotos::Ptr parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) const;
    std::string parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) const;

    File::Ptr parseJsonAndGetFile(const boost::property_tree::ptree& data) const;
    std::string parseFile(const File::Ptr& object) const;

    WebAppInfo::Ptr parseJsonAndGetWebAppInfo(const boost::property_tree::ptree& data) const;
    std::string parseWebAppInfo(const WebAppInfo::Ptr& object) const;

    ReplyKeyboardMarkup::Ptr parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const;
    std::string parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const;

    KeyboardButton::Ptr parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data) const;
    std::string parseKeyboardButton(const KeyboardButton::Ptr& object) const;

    KeyboardButtonRequestUsers::Ptr parseJsonAndGetKeyboardButtonRequestUsers(const boost::property_tree::ptree& data) const;
    std::string parseKeyboardButtonRequestUsers(const KeyboardButtonRequestUsers::Ptr& object) const;

    KeyboardButtonRequestChat::Ptr parseJsonAndGetKeyboardButtonRequestChat(const boost::property_tree::ptree& data) const;
    std::string parseKeyboardButtonRequestChat(const KeyboardButtonRequestChat::Ptr& object) const;

    KeyboardButtonPollType::Ptr parseJsonAndGetKeyboardButtonPollType(const boost::property_tree::ptree& data) const;
    std::string parseKeyboardButtonPollType(const KeyboardButtonPollType::Ptr& object) const;

    ReplyKeyboardRemove::Ptr parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data) const;
    std::string parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object) const;

    InlineKeyboardMarkup::Ptr parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) const;
    std::string parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object) const;

    InlineKeyboardButton::Ptr parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) const;
    std::string parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) const;

    LoginUrl::Ptr parseJsonAndGetLoginUrl(const boost::property_tree::ptree& data) const;
    std::string parseLoginUrl(const LoginUrl::Ptr& object) const;

    SwitchInlineQueryChosenChat::Ptr parseJsonAndGetSwitchInlineQueryChosenChat(const boost::property_tree::ptree& data) const;
    std::string parseSwitchInlineQueryChosenChat(const SwitchInlineQueryChosenChat::Ptr& object) const;

    CallbackQuery::Ptr parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const;
    std::string parseCallbackQuery(const CallbackQuery::Ptr& object) const;

    ForceReply::Ptr parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const;
    std::string parseForceReply(const ForceReply::Ptr& object) const;

    ChatPhoto::Ptr parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data) const;
    std::string parseChatPhoto(const ChatPhoto::Ptr& object) const;

    ChatInviteLink::Ptr parseJsonAndGetChatInviteLink(const boost::property_tree::ptree& data) const;
    std::string parseChatInviteLink(const ChatInviteLink::Ptr& object) const;

    ChatAdministratorRights::Ptr parseJsonAndGetChatAdministratorRights(const boost::property_tree::ptree& data) const;
    std::string parseChatAdministratorRights(const ChatAdministratorRights::Ptr& object) const;

    ChatMemberUpdated::Ptr parseJsonAndGetChatMemberUpdated(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberUpdated(const ChatMemberUpdated::Ptr& object) const;

    ChatMember::Ptr parseJsonAndGetChatMember(const boost::property_tree::ptree& data) const;
    std::string parseChatMember(const ChatMember::Ptr& object) const;

    ChatMemberOwner::Ptr parseJsonAndGetChatMemberOwner(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberOwner(const ChatMemberOwner::Ptr& object) const;

    ChatMemberAdministrator::Ptr parseJsonAndGetChatMemberAdministrator(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberAdministrator(const ChatMemberAdministrator::Ptr& object) const;

    ChatMemberMember::Ptr parseJsonAndGetChatMemberMember(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberMember(const ChatMemberMember::Ptr& object) const;

    ChatMemberRestricted::Ptr parseJsonAndGetChatMemberRestricted(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberRestricted(const ChatMemberRestricted::Ptr& object) const;

    ChatMemberLeft::Ptr parseJsonAndGetChatMemberLeft(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberLeft(const ChatMemberLeft::Ptr& object) const;

    ChatMemberBanned::Ptr parseJsonAndGetChatMemberBanned(const boost::property_tree::ptree& data) const;
    std::string parseChatMemberBanned(const ChatMemberBanned::Ptr& object) const;

    ChatJoinRequest::Ptr parseJsonAndGetChatJoinRequest(const boost::property_tree::ptree& data) const;
    std::string parseChatJoinRequest(const ChatJoinRequest::Ptr& object) const;

    ChatPermissions::Ptr parseJsonAndGetChatPermissions(const boost::property_tree::ptree& data) const;
    std::string parseChatPermissions(const ChatPermissions::Ptr& object) const;

    Birthdate::Ptr parseJsonAndGetBirthdate(const boost::property_tree::ptree& data) const;
    std::string parseBirthdate(const Birthdate::Ptr& object) const;

    BusinessIntro::Ptr parseJsonAndGetBusinessIntro(const boost::property_tree::ptree& data) const;
    std::string parseBusinessIntro(const BusinessIntro::Ptr& object) const;

    BusinessLocation::Ptr parseJsonAndGetBusinessLocation(const boost::property_tree::ptree& data) const;
    std::string parseBusinessLocation(const BusinessLocation::Ptr& object) const;

    BusinessOpeningHoursInterval::Ptr parseJsonAndGetBusinessOpeningHoursInterval(const boost::property_tree::ptree& data) const;
    std::string parseBusinessOpeningHoursInterval(const BusinessOpeningHoursInterval::Ptr& object) const;

    BusinessOpeningHours::Ptr parseJsonAndGetBusinessOpeningHours(const boost::property_tree::ptree& data) const;
    std::string parseBusinessOpeningHours(const BusinessOpeningHours::Ptr& object) const;

    ChatLocation::Ptr parseJsonAndGetChatLocation(const boost::property_tree::ptree& data) const;
    std::string parseChatLocation(const ChatLocation::Ptr& object) const;

    ReactionType::Ptr parseJsonAndGetReactionType(const boost::property_tree::ptree& data) const;
    std::string parseReactionType(const ReactionType::Ptr& object) const;

    ReactionTypeEmoji::Ptr parseJsonAndGetReactionTypeEmoji(const boost::property_tree::ptree& data) const;
    std::string parseReactionTypeEmoji(const ReactionTypeEmoji::Ptr& object) const;

    ReactionTypeCustomEmoji::Ptr parseJsonAndGetReactionTypeCustomEmoji(const boost::property_tree::ptree& data) const;
    std::string parseReactionTypeCustomEmoji(const ReactionTypeCustomEmoji::Ptr& object) const;

    ReactionCount::Ptr parseJsonAndGetReactionCount(const boost::property_tree::ptree& data) const;
    std::string parseReactionCount(const ReactionCount::Ptr& object) const;

    MessageReactionUpdated::Ptr parseJsonAndGetMessageReactionUpdated(const boost::property_tree::ptree& data) const;
    std::string parseMessageReactionUpdated(const MessageReactionUpdated::Ptr& object) const;

    MessageReactionCountUpdated::Ptr parseJsonAndGetMessageReactionCountUpdated(const boost::property_tree::ptree& data) const;
    std::string parseMessageReactionCountUpdated(const MessageReactionCountUpdated::Ptr& object) const;

    ForumTopic::Ptr parseJsonAndGetForumTopic(const boost::property_tree::ptree& data) const;
    std::string parseForumTopic(const ForumTopic::Ptr& object) const;

    BotCommand::Ptr parseJsonAndGetBotCommand(const boost::property_tree::ptree& data) const;
    std::string parseBotCommand(const BotCommand::Ptr& object) const;

    BotCommandScope::Ptr parseJsonAndGetBotCommandScope(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScope(const BotCommandScope::Ptr& object) const;

    BotCommandScopeDefault::Ptr parseJsonAndGetBotCommandScopeDefault(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeDefault(const BotCommandScopeDefault::Ptr& object) const;

    BotCommandScopeAllPrivateChats::Ptr parseJsonAndGetBotCommandScopeAllPrivateChats(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeAllPrivateChats(const BotCommandScopeAllPrivateChats::Ptr& object) const;

    BotCommandScopeAllGroupChats::Ptr parseJsonAndGetBotCommandScopeAllGroupChats(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeAllGroupChats(const BotCommandScopeAllGroupChats::Ptr& object) const;

    BotCommandScopeAllChatAdministrators::Ptr parseJsonAndGetBotCommandScopeAllChatAdministrators(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeAllChatAdministrators(const BotCommandScopeAllChatAdministrators::Ptr& object) const;

    BotCommandScopeChat::Ptr parseJsonAndGetBotCommandScopeChat(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeChat(const BotCommandScopeChat::Ptr& object) const;

    BotCommandScopeChatAdministrators::Ptr parseJsonAndGetBotCommandScopeChatAdministrators(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeChatAdministrators(const BotCommandScopeChatAdministrators::Ptr& object) const;

    BotCommandScopeChatMember::Ptr parseJsonAndGetBotCommandScopeChatMember(const boost::property_tree::ptree& data) const;
    std::string parseBotCommandScopeChatMember(const BotCommandScopeChatMember::Ptr& object) const;

    BotName::Ptr parseJsonAndGetBotName(const boost::property_tree::ptree& data) const;
    std::string parseBotName(const BotName::Ptr& object) const;

    BotDescription::Ptr parseJsonAndGetBotDescription(const boost::property_tree::ptree& data) const;
    std::string parseBotDescription(const BotDescription::Ptr& object) const;

    BotShortDescription::Ptr parseJsonAndGetBotShortDescription(const boost::property_tree::ptree& data) const;
    std::string parseBotShortDescription(const BotShortDescription::Ptr& object) const;

    MenuButton::Ptr parseJsonAndGetMenuButton(const boost::property_tree::ptree& data) const;
    std::string parseMenuButton(const MenuButton::Ptr& object) const;

    MenuButtonCommands::Ptr parseJsonAndGetMenuButtonCommands(const boost::property_tree::ptree& data) const;
    std::string parseMenuButtonCommands(const MenuButtonCommands::Ptr& object) const;

    MenuButtonWebApp::Ptr parseJsonAndGetMenuButtonWebApp(const boost::property_tree::ptree& data) const;
    std::string parseMenuButtonWebApp(const MenuButtonWebApp::Ptr& object) const;

    MenuButtonDefault::Ptr parseJsonAndGetMenuButtonDefault(const boost::property_tree::ptree& data) const;
    std::string parseMenuButtonDefault(const MenuButtonDefault::Ptr& object) const;

    ChatBoostSource::Ptr parseJsonAndGetChatBoostSource(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostSource(const ChatBoostSource::Ptr& object) const;

    ChatBoostSourcePremium::Ptr parseJsonAndGetChatBoostSourcePremium(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostSourcePremium(const ChatBoostSourcePremium::Ptr& object) const;

    ChatBoostSourceGiftCode::Ptr parseJsonAndGetChatBoostSourceGiftCode(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostSourceGiftCode(const ChatBoostSourceGiftCode::Ptr& object) const;

    ChatBoostSourceGiveaway::Ptr parseJsonAndGetChatBoostSourceGiveaway(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostSourceGiveaway(const ChatBoostSourceGiveaway::Ptr& object) const;

    ChatBoost::Ptr parseJsonAndGetChatBoost(const boost::property_tree::ptree& data) const;
    std::string parseChatBoost(const ChatBoost::Ptr& object) const;

    ChatBoostUpdated::Ptr parseJsonAndGetChatBoostUpdated(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostUpdated(const ChatBoostUpdated::Ptr& object) const;

    ChatBoostRemoved::Ptr parseJsonAndGetChatBoostRemoved(const boost::property_tree::ptree& data) const;
    std::string parseChatBoostRemoved(const ChatBoostRemoved::Ptr& object) const;

    UserChatBoosts::Ptr parseJsonAndGetUserChatBoosts(const boost::property_tree::ptree& data) const;
    std::string parseUserChatBoosts(const UserChatBoosts::Ptr& object) const;

    BusinessConnection::Ptr parseJsonAndGetBusinessConnection(const boost::property_tree::ptree& data) const;
    std::string parseBusinessConnection(const BusinessConnection::Ptr& object) const;

    BusinessMessagesDeleted::Ptr parseJsonAndGetBusinessMessagesDeleted(const boost::property_tree::ptree& data) const;
    std::string parseBusinessMessagesDeleted(const BusinessMessagesDeleted::Ptr& object) const;

    ResponseParameters::Ptr parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data) const;
    std::string parseResponseParameters(const ResponseParameters::Ptr& object) const;

    InputMedia::Ptr parseJsonAndGetInputMedia(const boost::property_tree::ptree& data) const;
    std::string parseInputMedia(const InputMedia::Ptr& object) const;

    InputMediaPhoto::Ptr parseJsonAndGetInputMediaPhoto(const boost::property_tree::ptree& data) const;
    std::string parseInputMediaPhoto(const InputMediaPhoto::Ptr& object) const;

    InputMediaVideo::Ptr parseJsonAndGetInputMediaVideo(const boost::property_tree::ptree& data) const;
    std::string parseInputMediaVideo(const InputMediaVideo::Ptr& object) const;

    InputMediaAnimation::Ptr parseJsonAndGetInputMediaAnimation(const boost::property_tree::ptree& data) const;
    std::string parseInputMediaAnimation(const InputMediaAnimation::Ptr& object) const;

    InputMediaAudio::Ptr parseJsonAndGetInputMediaAudio(const boost::property_tree::ptree& data) const;
    std::string parseInputMediaAudio(const InputMediaAudio::Ptr& object) const;

    InputMediaDocument::Ptr parseJsonAndGetInputMediaDocument(const boost::property_tree::ptree& data) const;
    std::string parseInputMediaDocument(const InputMediaDocument::Ptr& object) const;

    Sticker::Ptr parseJsonAndGetSticker(const boost::property_tree::ptree& data) const;
    std::string parseSticker(const Sticker::Ptr& object) const;

    StickerSet::Ptr parseJsonAndGetStickerSet(const boost::property_tree::ptree& data) const;
    std::string parseStickerSet(const StickerSet::Ptr& object) const;

    MaskPosition::Ptr parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data) const;
    std::string parseMaskPosition(const MaskPosition::Ptr& object) const;

    InputSticker::Ptr parseJsonAndGetInputSticker(const boost::property_tree::ptree& data) const;
    std::string parseInputSticker(const InputSticker::Ptr& object) const;

    InlineQuery::Ptr parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const;
    std::string parseInlineQuery(const InlineQuery::Ptr& object) const;

    InlineQueryResultsButton::Ptr parseJsonAndGetInlineQueryResultsButton(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultsButton(const InlineQueryResultsButton::Ptr& object) const;

    InlineQueryResult::Ptr parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResult(const InlineQueryResult::Ptr& object) const;

    InlineQueryResultArticle::Ptr parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const;

    InlineQueryResultPhoto::Ptr parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) const;

    InlineQueryResultGif::Ptr parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) const;

    InlineQueryResultMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) const;

    InlineQueryResultVideo::Ptr parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) const;

    InlineQueryResultAudio::Ptr parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object) const;

    InlineQueryResultVoice::Ptr parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object) const;

    InlineQueryResultDocument::Ptr parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object) const;

    InlineQueryResultLocation::Ptr parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object) const;

    InlineQueryResultVenue::Ptr parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object) const;

    InlineQueryResultContact::Ptr parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object) const;

    InlineQueryResultGame::Ptr parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object) const;

    InlineQueryResultCachedPhoto::Ptr parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object) const;

    InlineQueryResultCachedGif::Ptr parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object) const;

    InlineQueryResultCachedMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object) const;

    InlineQueryResultCachedSticker::Ptr parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object) const;

    InlineQueryResultCachedDocument::Ptr parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object) const;

    InlineQueryResultCachedVideo::Ptr parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object) const;

    InlineQueryResultCachedVoice::Ptr parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object) const;

    InlineQueryResultCachedAudio::Ptr parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object) const;

    InputMessageContent::Ptr parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputMessageContent(const InputMessageContent::Ptr& object) const;

    InputTextMessageContent::Ptr parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputTextMessageContent(const InputTextMessageContent::Ptr& object) const;

    InputLocationMessageContent::Ptr parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object) const;

    InputVenueMessageContent::Ptr parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object) const;

    InputContactMessageContent::Ptr parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputContactMessageContent(const InputContactMessageContent::Ptr& object) const;

    InputInvoiceMessageContent::Ptr parseJsonAndGetInputInvoiceMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputInvoiceMessageContent(const InputInvoiceMessageContent::Ptr& object) const;

    ChosenInlineResult::Ptr parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) const;
    std::string parseChosenInlineResult(const ChosenInlineResult::Ptr& object) const;

    SentWebAppMessage::Ptr parseJsonAndGetSentWebAppMessage(const boost::property_tree::ptree& data) const;
    std::string parseSentWebAppMessage(const SentWebAppMessage::Ptr& object) const;

    LabeledPrice::Ptr parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data) const;
    std::string parseLabeledPrice(const LabeledPrice::Ptr& object) const;

    Invoice::Ptr parseJsonAndGetInvoice(const boost::property_tree::ptree& data) const;
    std::string parseInvoice(const Invoice::Ptr& object) const;

    ShippingAddress::Ptr parseJsonAndGetShippingAddress(const boost::property_tree::ptree& data) const;
    std::string parseShippingAddress(const ShippingAddress::Ptr& object) const;

    OrderInfo::Ptr parseJsonAndGetOrderInfo(const boost::property_tree::ptree& data) const;
    std::string parseOrderInfo(const OrderInfo::Ptr& object) const;

    ShippingOption::Ptr parseJsonAndGetShippingOption(const boost::property_tree::ptree& data) const;
    std::string parseShippingOption(const ShippingOption::Ptr& object) const;

    SuccessfulPayment::Ptr parseJsonAndGetSuccessfulPayment(const boost::property_tree::ptree& data) const;
    std::string parseSuccessfulPayment(const SuccessfulPayment::Ptr& object) const;

    ShippingQuery::Ptr parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data) const;
    std::string parseShippingQuery(const ShippingQuery::Ptr& object) const;

    PreCheckoutQuery::Ptr parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data) const;
    std::string parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object) const;

    PassportData::Ptr parseJsonAndGetPassportData(const boost::property_tree::ptree& data) const;
    std::string parsePassportData(const PassportData::Ptr& object) const;

    PassportFile::Ptr parseJsonAndGetPassportFile(const boost::property_tree::ptree& data) const;
    std::string parsePassportFile(const PassportFile::Ptr& object) const;

    EncryptedPassportElement::Ptr parseJsonAndGetEncryptedPassportElement(const boost::property_tree::ptree& data) const;
    std::string parseEncryptedPassportElement(const EncryptedPassportElement::Ptr& object) const;

    EncryptedCredentials::Ptr parseJsonAndGetEncryptedCredentials(const boost::property_tree::ptree& data) const;
    std::string parseEncryptedCredentials(const EncryptedCredentials::Ptr& object) const;

    PassportElementError::Ptr parseJsonAndGetPassportElementError(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementError(const PassportElementError::Ptr& object) const;

    PassportElementErrorDataField::Ptr parseJsonAndGetPassportElementErrorDataField(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorDataField(const PassportElementErrorDataField::Ptr& object) const;

    PassportElementErrorFrontSide::Ptr parseJsonAndGetPassportElementErrorFrontSide(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorFrontSide(const PassportElementErrorFrontSide::Ptr& object) const;

    PassportElementErrorReverseSide::Ptr parseJsonAndGetPassportElementErrorReverseSide(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorReverseSide(const PassportElementErrorReverseSide::Ptr& object) const;

    PassportElementErrorSelfie::Ptr parseJsonAndGetPassportElementErrorSelfie(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorSelfie(const PassportElementErrorSelfie::Ptr& object) const;

    PassportElementErrorFile::Ptr parseJsonAndGetPassportElementErrorFile(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorFile(const PassportElementErrorFile::Ptr& object) const;

    PassportElementErrorFiles::Ptr parseJsonAndGetPassportElementErrorFiles(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorFiles(const PassportElementErrorFiles::Ptr& object) const;

    PassportElementErrorTranslationFile::Ptr parseJsonAndGetPassportElementErrorTranslationFile(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorTranslationFile(const PassportElementErrorTranslationFile::Ptr& object) const;

    PassportElementErrorTranslationFiles::Ptr parseJsonAndGetPassportElementErrorTranslationFiles(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorTranslationFiles(const PassportElementErrorTranslationFiles::Ptr& object) const;

    PassportElementErrorUnspecified::Ptr parseJsonAndGetPassportElementErrorUnspecified(const boost::property_tree::ptree& data) const;
    std::string parsePassportElementErrorUnspecified(const PassportElementErrorUnspecified::Ptr& object) const;

    Game::Ptr parseJsonAndGetGame(const boost::property_tree::ptree& data) const;
    std::string parseGame(const Game::Ptr& object) const;

    CallbackGame::Ptr parseJsonAndGetCallbackGame(const boost::property_tree::ptree& data) const;
    std::string parseCallbackGame(const CallbackGame::Ptr& object) const;

    GameHighScore::Ptr parseJsonAndGetGameHighScore(const boost::property_tree::ptree& data) const;
    std::string parseGameHighScore(const GameHighScore::Ptr& object) const;

    GenericReply::Ptr parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const;
    std::string parseGenericReply(const GenericReply::Ptr& object) const;

    inline boost::property_tree::ptree parseJson(const std::string& json) const {
        boost::property_tree::ptree tree;
        std::istringstream input(json);
        boost::property_tree::read_json(input, tree);
        return tree;
    }

    template<typename T>
    std::shared_ptr<T> tryParseJson(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return std::shared_ptr<T>();
        }
        return (this->*parseFunc)(treeItem->second);
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data) const {
        std::vector<std::shared_ptr<T>> result;
        result.reserve(data.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : data) {
            result.push_back((this->*parseFunc)(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    std::vector<T> parseJsonAndGetArray(std::function<T(const boost::property_tree::ptree&)> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
        std::vector<T> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            result.push_back(parseFunc(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
        std::vector<std::shared_ptr<T>> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            result.push_back((this->*parseFunc)(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    std::vector<std::vector<std::shared_ptr<T>>> parseJsonAndGet2DArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
        std::vector<std::vector<std::shared_ptr<T>>> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            std::vector<std::shared_ptr<T>> innerResult;
            for (const std::pair<const std::string, boost::property_tree::ptree>& innerInnerTreeItem : innerTreeItem.second) {
                innerResult.push_back((this->*parseFunc)(innerInnerTreeItem.second));
            }
            result.push_back(innerResult);
        }
        return result;
    }

    template<typename T>
    std::string parseArray(BotTypeToJsonFunc<T> parseFunc, const std::vector<std::shared_ptr<T>>& objects) const {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const std::shared_ptr<T>& item : objects) {
            result += (this->*parseFunc)(item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    template<typename T>
    std::string parseArray(std::function<T(const T&)> parseFunc, const std::vector<T>& objects) const {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const T& item : objects) {
            result += parseFunc(item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    template<typename T>
    std::string parse2DArray(BotTypeToJsonFunc<T> parseFunc, const std::vector<std::vector<std::shared_ptr<T>>>& objects) const {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const std::vector<std::shared_ptr<T>>& item : objects) {
            result += parseArray(parseFunc, item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

private:
    inline void removeLastComma(std::string& input) const {
        input.erase(input.length() - 1);
    }

    template<typename T>
    inline void appendToJson(std::string& json, const std::string& varName, const std::shared_ptr<T>& value) const {
        if (value == nullptr) {
            return;
        }
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    template<typename T>
    inline void appendToJson(std::string& json, const std::string& varName, const T& value) const {
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    template<typename T>
    inline void appendToJsonNumber(std::string& json, const std::string& varName, const T& value) const {
        json += '"';
        json += varName;
        json += R"(":)";
        json += std::to_string(value);
        json += ',';
    }

    inline void appendToJson(std::string &json, const std::string &varName, const int &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const long &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const long long &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const unsigned &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const unsigned long &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const unsigned long long &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const float &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const double &value) const { appendToJsonNumber(json, varName, value); }
    inline void appendToJson(std::string &json, const std::string &varName, const long double &value) const { appendToJsonNumber(json, varName, value); }

    inline void appendToJson(std::string& json, const std::string& varName, const bool& value) const {
        json += '"';
        json += varName;
        json += R"(":)";
        json += (value ? "true" : "false");
        json += ',';
    }

    inline void appendToJson(std::string& json, const std::string& varName, const char* value) const {
        if (value != nullptr){
            std::string strValue(value);
            appendToJson(json, varName, strValue);
        }
    }

    void appendToJson(std::string& json, const std::string& varName, const std::string& value) const;
};
}

#endif //TGBOT_TGTYPEPARSER_H
