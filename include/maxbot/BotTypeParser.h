#ifndef MAXBOT_TGTYPEPARSER_H
#define MAXBOT_TGTYPEPARSER_H

#include "maxbot/BotTypeParserUpdates.h"
#include "maxbot/types/WebhookInfo.h"
#include "maxbot/types/Chat.h"
#include "maxbot/types/Message.h"
#include "maxbot/types/CallbackAnswer.h"
#include "maxbot/types/MessageId.h"
#include "maxbot/types/AttachmentRequest.h"
#include "maxbot/types/NewMessageBody.h"
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
#include "maxbot/types/PollOption.h"
#include "maxbot/types/PollAnswer.h"
#include "maxbot/types/Poll.h"
#include "maxbot/types/Location.h"
#include "maxbot/types/WebAppData.h"
#include "maxbot/types/ProximityAlertTriggered.h"
#include "maxbot/types/MessageAutoDeleteTimerChanged.h"
#include "maxbot/types/ChatBoostAdded.h"
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
#include "maxbot/types/ChatLocation.h"
#include "maxbot/types/ReactionType.h"
#include "maxbot/types/ReactionTypeEmoji.h"
#include "maxbot/types/ReactionTypeCustomEmoji.h"
#include "maxbot/types/ReactionCount.h"
#include "maxbot/types/MessageReactionUpdated.h"
#include "maxbot/types/MessageReactionCountUpdated.h"
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
#include "maxbot/types/PreCheckoutQuery.h"
#include "maxbot/types/GenericReply.h"

namespace MaxBot {

class MAXBOT_API BotTypeParser : public BotTypeParserUpdates {

public:
    static WebhookInfo::Ptr parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data);
    static std::string parseWebhookInfo(const WebhookInfo::Ptr& object);

    static Chat::Ptr parseJsonAndGetChat(const boost::property_tree::ptree& data);

	static std::string parseNewMessageBody(const NewMessageBody::Ptr& msg);
    static std::string parseAttachmentRequest(const AttachmentRequest::Ptr& object);
    static std::string parseNewMessageLink(const NewMessageLink::Ptr& object);
	static std::string parseCallbackAnswer(const CallbackAnswer::Ptr& obj);

    static MessageId::Ptr parseJsonAndGetMessageId(const boost::property_tree::ptree& data);
    static std::string parseMessageId(const MessageId::Ptr& object);

    static InaccessibleMessage::Ptr parseJsonAndGetInaccessibleMessage(const boost::property_tree::ptree& data);

    static MessageEntity::Ptr parseJsonAndGetMessageEntity(const boost::property_tree::ptree& data);
    static std::string parseMessageEntity(const MessageEntity::Ptr& object);

    static TextQuote::Ptr parseJsonAndGetTextQuote(const boost::property_tree::ptree& data);
    static std::string parseTextQuote(const TextQuote::Ptr& object);

    static ExternalReplyInfo::Ptr parseJsonAndGetExternalReplyInfo(const boost::property_tree::ptree& data);

    static ReplyParameters::Ptr parseJsonAndGetReplyParameters(const boost::property_tree::ptree& data);
    static std::string parseReplyParameters(const ReplyParameters::Ptr& object);

    static MessageOrigin::Ptr parseJsonAndGetMessageOrigin(const boost::property_tree::ptree& data);

    static MessageOriginUser::Ptr parseJsonAndGetMessageOriginUser(const boost::property_tree::ptree& data);
    static std::string parseMessageOriginUser(const MessageOriginUser::Ptr& object);

    static MessageOriginHiddenUser::Ptr parseJsonAndGetMessageOriginHiddenUser(const boost::property_tree::ptree& data);
    static std::string parseMessageOriginHiddenUser(const MessageOriginHiddenUser::Ptr& object);

    static MessageOriginChat::Ptr parseJsonAndGetMessageOriginChat(const boost::property_tree::ptree& data);

    static MessageOriginChannel::Ptr parseJsonAndGetMessageOriginChannel(const boost::property_tree::ptree& data);

    static PhotoSize::Ptr parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data);
    static std::string parsePhotoSize(const PhotoSize::Ptr& object);

    static Animation::Ptr parseJsonAndGetAnimation(const boost::property_tree::ptree& data);
    static std::string parseAnimation(const Animation::Ptr& object);

    static Audio::Ptr parseJsonAndGetAudio(const boost::property_tree::ptree& data);
    static std::string parseAudio(const Audio::Ptr& object);

    static Document::Ptr parseJsonAndGetDocument(const boost::property_tree::ptree& data);
    static std::string parseDocument(const Document::Ptr& object);

    static Story::Ptr parseJsonAndGetStory(const boost::property_tree::ptree& data);

    static Video::Ptr parseJsonAndGetVideo(const boost::property_tree::ptree& data);
    static std::string parseVideo(const Video::Ptr& object);

    static VideoNote::Ptr parseJsonAndGetVideoNote(const boost::property_tree::ptree& data);
    static std::string parseVideoNote(const VideoNote::Ptr& object);

    static Voice::Ptr parseJsonAndGetVoice(const boost::property_tree::ptree& data);
    static std::string parseVoice(const Voice::Ptr& object);

    static Contact::Ptr parseJsonAndGetContact(const boost::property_tree::ptree& data);
    static std::string parseContact(const Contact::Ptr& object);

    static PollOption::Ptr parseJsonAndGetPollOption(const boost::property_tree::ptree& data);
    static std::string parsePollOption(const PollOption::Ptr& object);

    static PollAnswer::Ptr parseJsonAndGetPollAnswer(const boost::property_tree::ptree& data);

    static Poll::Ptr parseJsonAndGetPoll(const boost::property_tree::ptree& data);
    static std::string parsePoll(const Poll::Ptr& object);

    static Location::Ptr parseJsonAndGetLocation(const boost::property_tree::ptree& data);
    static std::string parseLocation(const Location::Ptr& object);

    static WebAppData::Ptr parseJsonAndGetWebAppData(const boost::property_tree::ptree& data);
    static std::string parseWebAppData(const WebAppData::Ptr& object);

    static ProximityAlertTriggered::Ptr parseJsonAndGetProximityAlertTriggered(const boost::property_tree::ptree& data);
    static std::string parseProximityAlertTriggered(const ProximityAlertTriggered::Ptr& object);

    static MessageAutoDeleteTimerChanged::Ptr parseJsonAndGetMessageAutoDeleteTimerChanged(const boost::property_tree::ptree& data);
    static std::string parseMessageAutoDeleteTimerChanged(const MessageAutoDeleteTimerChanged::Ptr& object);

    static ChatBoostAdded::Ptr parseJsonAndGetChatBoostAdded(const boost::property_tree::ptree& data);
    static std::string parseChatBoostAdded(const ChatBoostAdded::Ptr& object);

    static SharedUser::Ptr parseJsonAndGetSharedUser(const boost::property_tree::ptree& data);
    static std::string parseSharedUser(const SharedUser::Ptr& object);

    static UsersShared::Ptr parseJsonAndGetUsersShared(const boost::property_tree::ptree& data);
    static std::string parseUsersShared(const UsersShared::Ptr& object);

    static ChatShared::Ptr parseJsonAndGetChatShared(const boost::property_tree::ptree& data);
    static std::string parseChatShared(const ChatShared::Ptr& object);

    static WriteAccessAllowed::Ptr parseJsonAndGetWriteAccessAllowed(const boost::property_tree::ptree& data);
    static std::string parseWriteAccessAllowed(const WriteAccessAllowed::Ptr& object);

    static VideoChatScheduled::Ptr parseJsonAndGetVideoChatScheduled(const boost::property_tree::ptree& data);
    static std::string parseVideoChatScheduled(const VideoChatScheduled::Ptr& object);

    static VideoChatStarted::Ptr parseJsonAndGetVideoChatStarted(const boost::property_tree::ptree& data);
    static std::string parseVideoChatStarted(const VideoChatStarted::Ptr& object);

    static VideoChatEnded::Ptr parseJsonAndGetVideoChatEnded(const boost::property_tree::ptree& data);
    static std::string parseVideoChatEnded(const VideoChatEnded::Ptr& object);

    static VideoChatParticipantsInvited::Ptr parseJsonAndGetVideoChatParticipantsInvited(const boost::property_tree::ptree& data);
    static std::string parseVideoChatParticipantsInvited(const VideoChatParticipantsInvited::Ptr& object);

    static GiveawayCreated::Ptr parseJsonAndGetGiveawayCreated(const boost::property_tree::ptree& data);
    static std::string parseGiveawayCreated(const GiveawayCreated::Ptr& object);

    static Giveaway::Ptr parseJsonAndGetGiveaway(const boost::property_tree::ptree& data);

    static GiveawayWinners::Ptr parseJsonAndGetGiveawayWinners(const boost::property_tree::ptree& data);

    static GiveawayCompleted::Ptr parseJsonAndGetGiveawayCompleted(const boost::property_tree::ptree& data);

    static LinkPreviewOptions::Ptr parseJsonAndGetLinkPreviewOptions(const boost::property_tree::ptree& data);
    static std::string parseLinkPreviewOptions(const LinkPreviewOptions::Ptr& object);

    static UserProfilePhotos::Ptr parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data);
    static std::string parseUserProfilePhotos(const UserProfilePhotos::Ptr& object);

    static File::Ptr parseJsonAndGetFile(const boost::property_tree::ptree& data);
    static std::string parseFile(const File::Ptr& object);

    static WebAppInfo::Ptr parseJsonAndGetWebAppInfo(const boost::property_tree::ptree& data);
    static std::string parseWebAppInfo(const WebAppInfo::Ptr& object);

    static ReplyKeyboardMarkup::Ptr parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data);
    static std::string parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object);

    static KeyboardButton::Ptr parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data);
    static std::string parseKeyboardButton(const KeyboardButton::Ptr& object);

    static KeyboardButtonRequestUsers::Ptr parseJsonAndGetKeyboardButtonRequestUsers(const boost::property_tree::ptree& data);
    static std::string parseKeyboardButtonRequestUsers(const KeyboardButtonRequestUsers::Ptr& object);

    static KeyboardButtonRequestChat::Ptr parseJsonAndGetKeyboardButtonRequestChat(const boost::property_tree::ptree& data);
    static std::string parseKeyboardButtonRequestChat(const KeyboardButtonRequestChat::Ptr& object);

    static KeyboardButtonPollType::Ptr parseJsonAndGetKeyboardButtonPollType(const boost::property_tree::ptree& data);
    static std::string parseKeyboardButtonPollType(const KeyboardButtonPollType::Ptr& object);

    static ReplyKeyboardRemove::Ptr parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data);
    static std::string parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object);

    static InlineKeyboardMarkup::Ptr parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data);
    static std::string parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object);

    static InlineKeyboardButton::Ptr parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data);
    static std::string parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object);

    static LoginUrl::Ptr parseJsonAndGetLoginUrl(const boost::property_tree::ptree& data);
    static std::string parseLoginUrl(const LoginUrl::Ptr& object);

    static SwitchInlineQueryChosenChat::Ptr parseJsonAndGetSwitchInlineQueryChosenChat(const boost::property_tree::ptree& data);
    static std::string parseSwitchInlineQueryChosenChat(const SwitchInlineQueryChosenChat::Ptr& object);

    static CallbackQuery::Ptr parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data);

    static ForceReply::Ptr parseJsonAndGetForceReply(const boost::property_tree::ptree& data);
    static std::string parseForceReply(const ForceReply::Ptr& object);

    static ChatPhoto::Ptr parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data);
    static std::string parseChatPhoto(const ChatPhoto::Ptr& object);

    static ChatInviteLink::Ptr parseJsonAndGetChatInviteLink(const boost::property_tree::ptree& data);
    static std::string parseChatInviteLink(const ChatInviteLink::Ptr& object);

    static ChatAdministratorRights::Ptr parseJsonAndGetChatAdministratorRights(const boost::property_tree::ptree& data);
    static std::string parseChatAdministratorRights(const ChatAdministratorRights::Ptr& object);

    static ChatMemberUpdated::Ptr parseJsonAndGetChatMemberUpdated(const boost::property_tree::ptree& data);

    static ChatMember::Ptr parseJsonAndGetChatMember(const boost::property_tree::ptree& data);
    static std::string parseChatMember(const ChatMember::Ptr& object);

    static ChatMemberOwner::Ptr parseJsonAndGetChatMemberOwner(const boost::property_tree::ptree& data);
    static std::string parseChatMemberOwner(const ChatMemberOwner::Ptr& object);

    static ChatMemberAdministrator::Ptr parseJsonAndGetChatMemberAdministrator(const boost::property_tree::ptree& data);
    static std::string parseChatMemberAdministrator(const ChatMemberAdministrator::Ptr& object);

    static ChatMemberMember::Ptr parseJsonAndGetChatMemberMember(const boost::property_tree::ptree& data);
    static std::string parseChatMemberMember(const ChatMemberMember::Ptr& object);

    static ChatMemberRestricted::Ptr parseJsonAndGetChatMemberRestricted(const boost::property_tree::ptree& data);
    static std::string parseChatMemberRestricted(const ChatMemberRestricted::Ptr& object);

    static ChatMemberLeft::Ptr parseJsonAndGetChatMemberLeft(const boost::property_tree::ptree& data);
    static std::string parseChatMemberLeft(const ChatMemberLeft::Ptr& object);

    static ChatMemberBanned::Ptr parseJsonAndGetChatMemberBanned(const boost::property_tree::ptree& data);
    static std::string parseChatMemberBanned(const ChatMemberBanned::Ptr& object);

    static ChatJoinRequest::Ptr parseJsonAndGetChatJoinRequest(const boost::property_tree::ptree& data);

    static ChatPermissions::Ptr parseJsonAndGetChatPermissions(const boost::property_tree::ptree& data);
    static std::string parseChatPermissions(const ChatPermissions::Ptr& object);

    static Birthdate::Ptr parseJsonAndGetBirthdate(const boost::property_tree::ptree& data);
    static std::string parseBirthdate(const Birthdate::Ptr& object);

    static ChatLocation::Ptr parseJsonAndGetChatLocation(const boost::property_tree::ptree& data);
    static std::string parseChatLocation(const ChatLocation::Ptr& object);

    static ReactionType::Ptr parseJsonAndGetReactionType(const boost::property_tree::ptree& data);
    static std::string parseReactionType(const ReactionType::Ptr& object);

    static ReactionTypeEmoji::Ptr parseJsonAndGetReactionTypeEmoji(const boost::property_tree::ptree& data);
    static std::string parseReactionTypeEmoji(const ReactionTypeEmoji::Ptr& object);

    static ReactionTypeCustomEmoji::Ptr parseJsonAndGetReactionTypeCustomEmoji(const boost::property_tree::ptree& data);
    static std::string parseReactionTypeCustomEmoji(const ReactionTypeCustomEmoji::Ptr& object);

    static ReactionCount::Ptr parseJsonAndGetReactionCount(const boost::property_tree::ptree& data);
    static std::string parseReactionCount(const ReactionCount::Ptr& object);

    static MessageReactionUpdated::Ptr parseJsonAndGetMessageReactionUpdated(const boost::property_tree::ptree& data);

    static MessageReactionCountUpdated::Ptr parseJsonAndGetMessageReactionCountUpdated(const boost::property_tree::ptree& data);

    static BotCommand::Ptr parseJsonAndGetBotCommand(const boost::property_tree::ptree& data);
    static std::string parseBotCommand(const BotCommand::Ptr& object);

    static BotCommandScope::Ptr parseJsonAndGetBotCommandScope(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScope(const BotCommandScope::Ptr& object);

    static BotCommandScopeDefault::Ptr parseJsonAndGetBotCommandScopeDefault(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeDefault(const BotCommandScopeDefault::Ptr& object);

    static BotCommandScopeAllPrivateChats::Ptr parseJsonAndGetBotCommandScopeAllPrivateChats(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeAllPrivateChats(const BotCommandScopeAllPrivateChats::Ptr& object);

    static BotCommandScopeAllGroupChats::Ptr parseJsonAndGetBotCommandScopeAllGroupChats(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeAllGroupChats(const BotCommandScopeAllGroupChats::Ptr& object);

    static BotCommandScopeAllChatAdministrators::Ptr parseJsonAndGetBotCommandScopeAllChatAdministrators(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeAllChatAdministrators(const BotCommandScopeAllChatAdministrators::Ptr& object);

    static BotCommandScopeChat::Ptr parseJsonAndGetBotCommandScopeChat(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeChat(const BotCommandScopeChat::Ptr& object);

    static BotCommandScopeChatAdministrators::Ptr parseJsonAndGetBotCommandScopeChatAdministrators(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeChatAdministrators(const BotCommandScopeChatAdministrators::Ptr& object);

    static BotCommandScopeChatMember::Ptr parseJsonAndGetBotCommandScopeChatMember(const boost::property_tree::ptree& data);
    static std::string parseBotCommandScopeChatMember(const BotCommandScopeChatMember::Ptr& object);

    static BotName::Ptr parseJsonAndGetBotName(const boost::property_tree::ptree& data);
    static std::string parseBotName(const BotName::Ptr& object);

    static BotDescription::Ptr parseJsonAndGetBotDescription(const boost::property_tree::ptree& data);
    static std::string parseBotDescription(const BotDescription::Ptr& object);

    static BotShortDescription::Ptr parseJsonAndGetBotShortDescription(const boost::property_tree::ptree& data);
    static std::string parseBotShortDescription(const BotShortDescription::Ptr& object);

    static MenuButton::Ptr parseJsonAndGetMenuButton(const boost::property_tree::ptree& data);
    static std::string parseMenuButton(const MenuButton::Ptr& object);

    static MenuButtonCommands::Ptr parseJsonAndGetMenuButtonCommands(const boost::property_tree::ptree& data);
    static std::string parseMenuButtonCommands(const MenuButtonCommands::Ptr& object);

    static MenuButtonWebApp::Ptr parseJsonAndGetMenuButtonWebApp(const boost::property_tree::ptree& data);
    static std::string parseMenuButtonWebApp(const MenuButtonWebApp::Ptr& object);

    static MenuButtonDefault::Ptr parseJsonAndGetMenuButtonDefault(const boost::property_tree::ptree& data);
    static std::string parseMenuButtonDefault(const MenuButtonDefault::Ptr& object);

    static ChatBoostSource::Ptr parseJsonAndGetChatBoostSource(const boost::property_tree::ptree& data);
    static std::string parseChatBoostSource(const ChatBoostSource::Ptr& object);

    static ChatBoostSourcePremium::Ptr parseJsonAndGetChatBoostSourcePremium(const boost::property_tree::ptree& data);
    static std::string parseChatBoostSourcePremium(const ChatBoostSourcePremium::Ptr& object);

    static ChatBoostSourceGiftCode::Ptr parseJsonAndGetChatBoostSourceGiftCode(const boost::property_tree::ptree& data);
    static std::string parseChatBoostSourceGiftCode(const ChatBoostSourceGiftCode::Ptr& object);

    static ChatBoostSourceGiveaway::Ptr parseJsonAndGetChatBoostSourceGiveaway(const boost::property_tree::ptree& data);
    static std::string parseChatBoostSourceGiveaway(const ChatBoostSourceGiveaway::Ptr& object);

    static ChatBoost::Ptr parseJsonAndGetChatBoost(const boost::property_tree::ptree& data);
    static std::string parseChatBoost(const ChatBoost::Ptr& object);

    static ChatBoostUpdated::Ptr parseJsonAndGetChatBoostUpdated(const boost::property_tree::ptree& data);

    static ChatBoostRemoved::Ptr parseJsonAndGetChatBoostRemoved(const boost::property_tree::ptree& data);

    static UserChatBoosts::Ptr parseJsonAndGetUserChatBoosts(const boost::property_tree::ptree& data);
    static std::string parseUserChatBoosts(const UserChatBoosts::Ptr& object);

    static ResponseParameters::Ptr parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data);
    static std::string parseResponseParameters(const ResponseParameters::Ptr& object);

    static InputMedia::Ptr parseJsonAndGetInputMedia(const boost::property_tree::ptree& data);
    static std::string parseInputMedia(const InputMedia::Ptr& object);

    static InputMediaPhoto::Ptr parseJsonAndGetInputMediaPhoto(const boost::property_tree::ptree& data);
    static std::string parseInputMediaPhoto(const InputMediaPhoto::Ptr& object);

    static InputMediaVideo::Ptr parseJsonAndGetInputMediaVideo(const boost::property_tree::ptree& data);
    static std::string parseInputMediaVideo(const InputMediaVideo::Ptr& object);

    static InputMediaAnimation::Ptr parseJsonAndGetInputMediaAnimation(const boost::property_tree::ptree& data);
    static std::string parseInputMediaAnimation(const InputMediaAnimation::Ptr& object);

    static InputMediaAudio::Ptr parseJsonAndGetInputMediaAudio(const boost::property_tree::ptree& data);
    static std::string parseInputMediaAudio(const InputMediaAudio::Ptr& object);

    static InputMediaDocument::Ptr parseJsonAndGetInputMediaDocument(const boost::property_tree::ptree& data);
    static std::string parseInputMediaDocument(const InputMediaDocument::Ptr& object);

    static Sticker::Ptr parseJsonAndGetSticker(const boost::property_tree::ptree& data);
    static std::string parseSticker(const Sticker::Ptr& object);

    static StickerSet::Ptr parseJsonAndGetStickerSet(const boost::property_tree::ptree& data);
    static std::string parseStickerSet(const StickerSet::Ptr& object);

    static MaskPosition::Ptr parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data);
    static std::string parseMaskPosition(const MaskPosition::Ptr& object);

    static InputSticker::Ptr parseJsonAndGetInputSticker(const boost::property_tree::ptree& data);
    static std::string parseInputSticker(const InputSticker::Ptr& object);

    static InlineQuery::Ptr parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data);
    static std::string parseInlineQuery(const InlineQuery::Ptr& object);

    static InlineQueryResultsButton::Ptr parseJsonAndGetInlineQueryResultsButton(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultsButton(const InlineQueryResultsButton::Ptr& object);

    static InlineQueryResult::Ptr parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResult(const InlineQueryResult::Ptr& object);

    static InlineQueryResultArticle::Ptr parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object);

    static InlineQueryResultPhoto::Ptr parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object);

    static InlineQueryResultGif::Ptr parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object);

    static InlineQueryResultMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object);

    static InlineQueryResultVideo::Ptr parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object);

    static InlineQueryResultAudio::Ptr parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object);

    static InlineQueryResultVoice::Ptr parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object);

    static InlineQueryResultDocument::Ptr parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object);

    static InlineQueryResultLocation::Ptr parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object);

    static InlineQueryResultVenue::Ptr parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object);

    static InlineQueryResultContact::Ptr parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object);

    static InlineQueryResultGame::Ptr parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object);

    static InlineQueryResultCachedPhoto::Ptr parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object);

    static InlineQueryResultCachedGif::Ptr parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object);

    static InlineQueryResultCachedMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object);

    static InlineQueryResultCachedSticker::Ptr parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object);

    static InlineQueryResultCachedDocument::Ptr parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object);

    static InlineQueryResultCachedVideo::Ptr parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object);

    static InlineQueryResultCachedVoice::Ptr parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object);

    static InlineQueryResultCachedAudio::Ptr parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data);
    static std::string parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object);

    static InputMessageContent::Ptr parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputMessageContent(const InputMessageContent::Ptr& object);

    static InputTextMessageContent::Ptr parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputTextMessageContent(const InputTextMessageContent::Ptr& object);

    static InputLocationMessageContent::Ptr parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object);

    static InputVenueMessageContent::Ptr parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object);

    static InputContactMessageContent::Ptr parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputContactMessageContent(const InputContactMessageContent::Ptr& object);

    static InputInvoiceMessageContent::Ptr parseJsonAndGetInputInvoiceMessageContent(const boost::property_tree::ptree& data);
    static std::string parseInputInvoiceMessageContent(const InputInvoiceMessageContent::Ptr& object);

    static ChosenInlineResult::Ptr parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data);
    static std::string parseChosenInlineResult(const ChosenInlineResult::Ptr& object);

    static SentWebAppMessage::Ptr parseJsonAndGetSentWebAppMessage(const boost::property_tree::ptree& data);
    static std::string parseSentWebAppMessage(const SentWebAppMessage::Ptr& object);

    static LabeledPrice::Ptr parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data);
    static std::string parseLabeledPrice(const LabeledPrice::Ptr& object);

    static Invoice::Ptr parseJsonAndGetInvoice(const boost::property_tree::ptree& data);
    static std::string parseInvoice(const Invoice::Ptr& object);

    static PreCheckoutQuery::Ptr parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data);
    static std::string parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object);

    static GenericReply::Ptr parseJsonAndGetGenericReply(const boost::property_tree::ptree& data);
    static std::string parseGenericReply(const GenericReply::Ptr& object);
};

}

#endif //MAXBOT_TGTYPEPARSER_H
