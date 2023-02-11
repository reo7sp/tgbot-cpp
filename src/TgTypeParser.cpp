#include "tgbot/TgTypeParser.h"

namespace TgBot {

Update::Ptr TgTypeParser::parseJsonAndGetUpdate(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Update>());
    result->updateId = data.get<std::int32_t>("update_id", 0);
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->editedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_message");
    result->channelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "channel_post");
    result->editedChannelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_channel_post");
    result->inlineQuery = tryParseJson<InlineQuery>(&TgTypeParser::parseJsonAndGetInlineQuery, data, "inline_query");
    result->chosenInlineResult = tryParseJson<ChosenInlineResult>(&TgTypeParser::parseJsonAndGetChosenInlineResult, data, "chosen_inline_result");
    result->callbackQuery = tryParseJson<CallbackQuery>(&TgTypeParser::parseJsonAndGetCallbackQuery, data, "callback_query");
    result->shippingQuery = tryParseJson<ShippingQuery>(&TgTypeParser::parseJsonAndGetShippingQuery, data, "shipping_query");
    result->preCheckoutQuery = tryParseJson<PreCheckoutQuery>(&TgTypeParser::parseJsonAndGetPreCheckoutQuery, data, "pre_checkout_query");
    result->poll = tryParseJson<Poll>(&TgTypeParser::parseJsonAndGetPoll, data, "poll");
    result->pollAnswer = tryParseJson<PollAnswer>(&TgTypeParser::parseJsonAndGetPollAnswer, data, "poll_answer");
    result->myChatMember = tryParseJson<ChatMemberUpdated>(&TgTypeParser::parseJsonAndGetChatMemberUpdated, data, "my_chat_member");
    result->chatMember = tryParseJson<ChatMemberUpdated>(&TgTypeParser::parseJsonAndGetChatMemberUpdated, data, "chat_member");
    result->chatJoinRequest = tryParseJson<ChatJoinRequest>(&TgTypeParser::parseJsonAndGetChatJoinRequest, data, "chat_join_request");
    return result;
}

std::string TgTypeParser::parseUpdate(const Update::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "update_id", object->updateId);
    appendToJson(result, "message", parseMessage(object->message));
    appendToJson(result, "edited_message", parseMessage(object->editedMessage));
    appendToJson(result, "channel_post", parseMessage(object->channelPost));
    appendToJson(result, "edited_channel_post", parseMessage(object->editedChannelPost));
    appendToJson(result, "inline_query", parseInlineQuery(object->inlineQuery));
    appendToJson(result, "chosen_inline_result", parseChosenInlineResult(object->chosenInlineResult));
    appendToJson(result, "callback_query", parseCallbackQuery(object->callbackQuery));
    appendToJson(result, "shipping_query", parseShippingQuery(object->shippingQuery));
    appendToJson(result, "pre_checkout_query", parsePreCheckoutQuery(object->preCheckoutQuery));
    appendToJson(result, "poll", parsePoll(object->poll));
    appendToJson(result, "poll_answer", parsePollAnswer(object->pollAnswer));
    appendToJson(result, "my_chat_member", parseChatMemberUpdated(object->myChatMember));
    appendToJson(result, "chat_member", parseChatMemberUpdated(object->chatMember));
    appendToJson(result, "chat_join_request", parseChatJoinRequest(object->chatJoinRequest));
    removeLastComma(result);
    result += '}';
    return result;
}

WebhookInfo::Ptr TgTypeParser::parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<WebhookInfo>());
    result->url = data.get<std::string>("url", "");
    result->hasCustomCertificate = data.get<bool>("has_custom_certificate", false);
    result->pendingUpdateCount = data.get<std::int32_t>("pending_update_count", 0);
    result->ipAddress = data.get<std::string>("ip_address", "");
    result->lastErrorDate = data.get<std::int32_t>("last_error_date", 0);
    result->lastErrorMessage = data.get<std::string>("last_error_message", "");
    result->lastSynchronizationErrorDate = data.get<std::int32_t>("last_synchronization_error_date", 0);
    result->maxConnections = data.get<std::int32_t>("max_connections", 0);
    result->allowedUpdates = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }
    , data, "allowed_updates");
    return result;
}

std::string TgTypeParser::parseWebhookInfo(const WebhookInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "url", object->url);
    appendToJson(result, "has_custom_certificate", object->hasCustomCertificate);
    appendToJson(result, "pending_update_count", object->pendingUpdateCount);
    appendToJson(result, "ip_address", object->ipAddress);
    appendToJson(result, "last_error_date", object->lastErrorDate);
    appendToJson(result, "last_error_message", object->lastErrorMessage);
    appendToJson(result, "last_synchronization_error_date", object->lastSynchronizationErrorDate);
    appendToJson(result, "max_connections", object->maxConnections);
    appendToJson(result, "allowed_updates",
                 parseArray<std::string>([] (const std::string& s)->std::string {
        return s;
    }
    , object->allowedUpdates));
    removeLastComma(result);
    result += '}';
    return result;
}

User::Ptr TgTypeParser::parseJsonAndGetUser(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<User>());
    result->id = data.get<std::int64_t>("id", 0);
    result->isBot = data.get<bool>("is_bot", false);
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->username = data.get<std::string>("username", "");
    result->languageCode = data.get<std::string>("language_code", "");
    result->isPremium = data.get<bool>("is_premium", false);
    result->addedToAttachmentMenu = data.get<bool>("added_to_attachment_menu", false);
    result->canJoinGroups = data.get<bool>("can_join_groups", false);
    result->canReadAllGroupMessages = data.get<bool>("can_read_all_group_messages", false);
    result->supportsInlineQueries = data.get<bool>("supports_inline_queries", false);
    return result;
}

std::string TgTypeParser::parseUser(const User::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "is_bot", object->isBot);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "username", object->username);
    appendToJson(result, "language_code", object->languageCode);
    appendToJson(result, "is_premium", object->isPremium);
    appendToJson(result, "added_to_attachment_menu", object->addedToAttachmentMenu);
    appendToJson(result, "can_join_groups", object->canJoinGroups);
    appendToJson(result, "can_read_all_group_messages", object->canReadAllGroupMessages);
    appendToJson(result, "supports_inline_queries", object->supportsInlineQueries);
    removeLastComma(result);
    result += '}';
    return result;
}

Chat::Ptr TgTypeParser::parseJsonAndGetChat(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Chat>());
    result->id = data.get<std::int64_t>("id", 0);
    std::string type = data.get<std::string>("type", "");
    if (type == "private") {
        result->type = Chat::Type::Private;
    } else if (type == "group") {
        result->type = Chat::Type::Group;
    } else if (type == "supergroup") {
        result->type = Chat::Type::Supergroup;
    } else if (type == "channel") {
        result->type = Chat::Type::Channel;
    }
    result->title = data.get<std::string>("title", "");
    result->username = data.get<std::string>("username", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->isForum = data.get<bool>("is_forum", false);
    result->photo = tryParseJson<ChatPhoto>(&TgTypeParser::parseJsonAndGetChatPhoto, data, "photo");
    result->activeUsernames = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "active_usernames");
    result->emojiStatusCustomEmojiId = data.get<std::string>("emoji_status_custom_emoji_id", "");
    result->bio = data.get<std::string>("bio", "");
    result->hasPrivateForwards = data.get<bool>("has_private_forwards", false);
    result->hasRestrictedVoiceAndVideoMessages = data.get<bool>("has_restricted_voice_and_video_messages", false);
    result->joinToSendMessages = data.get<bool>("join_to_send_messages", false);
    result->joinByRequest = data.get<bool>("join_by_request", false);
    result->description = data.get<std::string>("description", "");
    result->inviteLink = data.get<std::string>("invite_link", "");
    result->pinnedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "pinned_message");
    result->permissions = tryParseJson<ChatPermissions>(&TgTypeParser::parseJsonAndGetChatPermissions, data, "permissions");
    result->slowModeDelay = data.get<std::int32_t>("slow_mode_delay", 0);
    result->messageAutoDeleteTime = data.get<std::int32_t>("message_auto_delete_time", 0);
    result->hasProtectedContent = data.get<bool>("has_protected_content", false);
    result->hasAggressiveAntiSpamEnabled = data.get<bool>("has_aggressive_anti_spam_enabled", false);
    result->hasHiddenMembers = data.get<bool>("has_hidden_members", false);
    result->stickerSetName = data.get<std::string>("sticker_set_name", "");
    result->canSetStickerSet = data.get<bool>("can_set_sticker_set", false);
    result->linkedChatId = data.get<std::int64_t>("linked_chat_id", 0);
    result->location = tryParseJson<ChatLocation>(&TgTypeParser::parseJsonAndGetChatLocation, data, "location");
    return result;
}

std::string TgTypeParser::parseChat(const Chat::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    if (object->type == Chat::Type::Private) {
        appendToJson(result, "type", "private");
    } else if (object->type == Chat::Type::Group) {
        appendToJson(result, "type", "group");
    } else if (object->type == Chat::Type::Supergroup) {
        appendToJson(result, "type", "supergroup");
    } else if (object->type == Chat::Type::Channel) {
        appendToJson(result, "type", "channel");
    }
    appendToJson(result, "title", object->title);
    appendToJson(result, "username", object->username);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "is_forum", object->isForum);
    appendToJson(result, "photo", parseChatPhoto(object->photo));
    appendToJson(result, "active_usernames",
                 parseArray<std::string>([] (const std::string& s)->std::string {
        return s;
    }, object->activeUsernames));
    appendToJson(result, "emoji_status_custom_emoji_id", object->emojiStatusCustomEmojiId);
    appendToJson(result, "bio", object->bio);
    appendToJson(result, "has_private_forwards", object->hasPrivateForwards);
    appendToJson(result, "has_restricted_voice_and_video_messages", object->hasRestrictedVoiceAndVideoMessages);
    appendToJson(result, "join_to_send_messages", object->joinToSendMessages);
    appendToJson(result, "join_by_request", object->joinByRequest);
    appendToJson(result, "description", object->description);
    appendToJson(result, "invite_link", object->inviteLink);
    appendToJson(result, "pinned_message", parseMessage(object->pinnedMessage));
    appendToJson(result, "permissions", parseChatPermissions(object->permissions));
    appendToJson(result, "slow_mode_delay", object->slowModeDelay);
    appendToJson(result, "message_auto_delete_time", object->messageAutoDeleteTime);
    appendToJson(result, "has_aggressive_anti_spam_enabled", object->hasAggressiveAntiSpamEnabled);
    appendToJson(result, "has_hidden_members", object->hasHiddenMembers);
    appendToJson(result, "has_protected_content", object->hasProtectedContent);
    appendToJson(result, "sticker_set_name", object->stickerSetName);
    appendToJson(result, "can_set_sticker_set", object->canSetStickerSet);
    appendToJson(result, "linked_chat_id", object->linkedChatId);
    appendToJson(result, "location", parseChatLocation(object->location));
    removeLastComma(result);
    result += '}';
    return result;
}

Message::Ptr TgTypeParser::parseJsonAndGetMessage(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Message>());
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->messageThreadId = data.get<std::int32_t>("message_thread_id", 0);
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->senderChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "sender_chat");
    result->date = data.get<std::int32_t>("date", 0);
    result->chat = parseJsonAndGetChat(data.find("chat")->second);
    result->forwardFrom = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "forward_from");
    result->forwardFromChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "forward_from_chat");
    result->forwardFromMessageId = data.get<std::int32_t>("forward_from_message_id", 0);
    result->forwardSignature = data.get<std::string>("forward_signature", "");
    result->forwardSenderName = data.get<std::string>("forward_sender_name", "");
    result->forwardDate = data.get<std::int32_t>("forward_date", 0);
    result->isTopicMessage = data.get<bool>("is_topic_message", false);
    result->isAutomaticForward = data.get<bool>("is_automatic_forward", false);
    result->replyToMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "reply_to_message");
    result->viaBot = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "via_bot");
    result->editDate = data.get<std::int32_t>("edit_date", 0);
    result->hasProtectedContent = data.get<bool>("has_protected_content", false);
    result->mediaGroupId = data.get<std::string>("media_group_id", "");
    result->authorSignature = data.get<std::string>("author_signature", "");
    result->text = data.get<std::string>("text", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
    result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
    result->video = tryParseJson<Video>(&TgTypeParser::parseJsonAndGetVideo, data, "video");
    result->videoNote = tryParseJson<VideoNote>(&TgTypeParser::parseJsonAndGetVideoNote, data, "video_note");
    result->voice = tryParseJson<Voice>(&TgTypeParser::parseJsonAndGetVoice, data, "voice");
    result->caption = data.get<std::string>("caption", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->hasMediaSpoiler = data.get<bool>("has_media_spoiler", false);
    result->contact = tryParseJson<Contact>(&TgTypeParser::parseJsonAndGetContact, data, "contact");
    result->dice = tryParseJson<Dice>(&TgTypeParser::parseJsonAndGetDice, data, "dice");
    result->game = tryParseJson<Game>(&TgTypeParser::parseJsonAndGetGame, data, "game");
    result->poll = tryParseJson<Poll>(&TgTypeParser::parseJsonAndGetPoll, data, "poll");
    result->venue = tryParseJson<Venue>(&TgTypeParser::parseJsonAndGetVenue, data, "venue");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->newChatMembers = parseJsonAndGetArray<User>(&TgTypeParser::parseJsonAndGetUser, data, "new_chat_members");
    result->leftChatMember = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "left_chat_member");
    result->newChatTitle = data.get<std::string>("new_chat_title", "");
    result->newChatPhoto = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "new_chat_photo");
    result->deleteChatPhoto = data.get<bool>("delete_chat_photo", false);
    result->groupChatCreated = data.get<bool>("group_chat_created", false);
    result->supergroupChatCreated = data.get<bool>("supergroup_chat_created", false);
    result->channelChatCreated = data.get<bool>("channel_chat_created", false);
    result->messageAutoDeleteTimerChanged = tryParseJson<MessageAutoDeleteTimerChanged>(&TgTypeParser::parseJsonAndGetMessageAutoDeleteTimerChanged, data, "message_auto_delete_timer_changed");
    result->migrateToChatId = data.get<std::int64_t>("migrate_to_chat_id", 0);
    result->migrateFromChatId = data.get<std::int64_t>("migrate_from_chat_id", 0);
    result->pinnedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "pinned_message");
    result->invoice = tryParseJson<Invoice>(&TgTypeParser::parseJsonAndGetInvoice, data, "invoice");
    result->successfulPayment = tryParseJson<SuccessfulPayment>(&TgTypeParser::parseJsonAndGetSuccessfulPayment, data, "successful_payment");
    result->userShared = tryParseJson<UserShared>(&TgTypeParser::parseJsonAndGetUserShared, data, "user_shared");
    result->chatShared = tryParseJson<ChatShared>(&TgTypeParser::parseJsonAndGetChatShared, data, "chat_shared");
    result->connectedWebsite = data.get<std::string>("connected_website", "");
    result->writeAccessAllowed = tryParseJson<WriteAccessAllowed>(&TgTypeParser::parseJsonAndGetWriteAccessAllowed, data, "write_access_allowed");
    result->passportData = tryParseJson<PassportData>(&TgTypeParser::parseJsonAndGetPassportData, data, "passport_data");
    result->proximityAlertTriggered = tryParseJson<ProximityAlertTriggered>(&TgTypeParser::parseJsonAndGetProximityAlertTriggered, data, "proximity_alert_triggered");
    result->forumTopicCreated = tryParseJson<ForumTopicCreated>(&TgTypeParser::parseJsonAndGetForumTopicCreated, data, "forum_topic_created");
    result->forumTopicEdited = tryParseJson<ForumTopicEdited>(&TgTypeParser::parseJsonAndGetForumTopicEdited, data, "forum_topic_edited");
    result->forumTopicClosed = tryParseJson<ForumTopicClosed>(&TgTypeParser::parseJsonAndGetForumTopicClosed, data, "forum_topic_closed");
    result->forumTopicReopened = tryParseJson<ForumTopicReopened>(&TgTypeParser::parseJsonAndGetForumTopicReopened, data, "forum_topic_reopened");
    result->generalForumTopicHidden = tryParseJson<GeneralForumTopicHidden>(&TgTypeParser::parseJsonAndGetGeneralForumTopicHidden, data, "general_forum_topic_hidden");
    result->generalForumTopicUnhidden = tryParseJson<GeneralForumTopicUnhidden>(&TgTypeParser::parseJsonAndGetGeneralForumTopicUnhidden, data, "general_forum_topic_unhidden");
    result->videoChatScheduled = tryParseJson<VideoChatScheduled>(&TgTypeParser::parseJsonAndGetVideoChatScheduled, data, "video_chat_scheduled");
    result->videoChatStarted = tryParseJson<VideoChatStarted>(&TgTypeParser::parseJsonAndGetVideoChatStarted, data, "video_chat_started");
    result->videoChatEnded = tryParseJson<VideoChatEnded>(&TgTypeParser::parseJsonAndGetVideoChatEnded, data, "video_chat_ended");
    result->videoChatParticipantsInvited = tryParseJson<VideoChatParticipantsInvited>(&TgTypeParser::parseJsonAndGetVideoChatParticipantsInvited, data, "video_chat_participants_invited");
    result->webAppData = tryParseJson<WebAppData>(&TgTypeParser::parseJsonAndGetWebAppData, data, "web_app_data");
    result->replyMarkup = tryParseJson<InlineKeyboardMarkup>(&TgTypeParser::parseJsonAndGetInlineKeyboardMarkup, data, "reply_markup");
    return result;
}

std::string TgTypeParser::parseMessage(const Message::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "message_thread_id", object->messageThreadId);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "sender_chat", parseChat(object->senderChat));
    appendToJson(result, "date", object->date);
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "forward_from", parseUser(object->forwardFrom));
    appendToJson(result, "forward_from_chat", parseChat(object->forwardFromChat));
    appendToJson(result, "forward_from_message_id", object->forwardFromMessageId);
    appendToJson(result, "forward_signature", object->forwardSignature);
    appendToJson(result, "forward_sender_name", object->forwardSenderName);
    appendToJson(result, "forward_date", object->forwardDate);
    appendToJson(result, "is_topic_message", object->isTopicMessage);
    appendToJson(result, "is_automatic_forward", object->isAutomaticForward);
    appendToJson(result, "reply_to_message", parseMessage(object->replyToMessage));
    appendToJson(result, "via_bot", parseUser(object->viaBot));
    appendToJson(result, "edit_date", object->editDate);
    appendToJson(result, "has_protected_content", object->hasProtectedContent);
    appendToJson(result, "media_group_id", object->mediaGroupId);
    appendToJson(result, "author_signature", object->authorSignature);
    appendToJson(result, "text", object->text);
    appendToJson(result, "entities", parseArray(&TgTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "animation", parseAnimation(object->animation));
    appendToJson(result, "audio", parseAudio(object->audio));
    appendToJson(result, "document", parseDocument(object->document));
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "sticker", parseSticker(object->sticker));
    appendToJson(result, "video", parseVideo(object->video));
    appendToJson(result, "video_note", parseVideoNote(object->videoNote));
    appendToJson(result, "voice", parseVoice(object->voice));
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "has_media_spoiler", object->hasMediaSpoiler);
    appendToJson(result, "contact", parseContact(object->contact));
    appendToJson(result, "dice", parseDice(object->dice));
    appendToJson(result, "game", parseGame(object->game));
    appendToJson(result, "poll", parsePoll(object->poll));
    appendToJson(result, "venue", parseVenue(object->venue));
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "new_chat_members", parseArray(&TgTypeParser::parseUser, object->newChatMembers));
    appendToJson(result, "left_chat_member", parseUser(object->leftChatMember));
    appendToJson(result, "new_chat_title", object->newChatTitle);
    appendToJson(result, "new_chat_photo", parseArray(&TgTypeParser::parsePhotoSize, object->newChatPhoto));
    appendToJson(result, "delete_chat_photo", object->deleteChatPhoto);
    appendToJson(result, "group_chat_created", object->groupChatCreated);
    appendToJson(result, "supergroup_chat_created", object->supergroupChatCreated);
    appendToJson(result, "channel_chat_created", object->channelChatCreated);
    appendToJson(result, "message_auto_delete_timer_changed", parseMessageAutoDeleteTimerChanged(object->messageAutoDeleteTimerChanged));
    appendToJson(result, "migrate_to_chat_id", object->migrateToChatId);
    appendToJson(result, "migrate_from_chat_id", object->migrateFromChatId);
    appendToJson(result, "pinned_message", parseMessage(object->pinnedMessage));
    appendToJson(result, "invoice", parseInvoice(object->invoice));
    appendToJson(result, "successful_payment", parseSuccessfulPayment(object->successfulPayment));
    appendToJson(result, "user_shared", parseUserShared(object->userShared));
    appendToJson(result, "chat_shared", parseChatShared(object->chatShared));
    appendToJson(result, "connected_website", object->connectedWebsite);
    appendToJson(result, "write_access_allowed", parseWriteAccessAllowed(object->writeAccessAllowed));
    appendToJson(result, "passport_data", parsePassportData(object->passportData));
    appendToJson(result, "proximity_alert_triggered", parseProximityAlertTriggered(object->proximityAlertTriggered));
    appendToJson(result, "forum_topic_created", parseForumTopicCreated(object->forumTopicCreated));
    appendToJson(result, "forum_topic_edited", parseForumTopicEdited(object->forumTopicEdited));
    appendToJson(result, "forum_topic_closed", parseForumTopicClosed(object->forumTopicClosed));
    appendToJson(result, "forum_topic_reopened", parseForumTopicReopened(object->forumTopicReopened));
    appendToJson(result, "general_forum_topic_hidden", parseGeneralForumTopicHidden(object->generalForumTopicHidden));
    appendToJson(result, "general_forum_topic_unhidden", parseGeneralForumTopicUnhidden(object->generalForumTopicUnhidden));
    appendToJson(result, "video_chat_scheduled", parseVideoChatScheduled(object->videoChatScheduled));
    appendToJson(result, "video_chat_started", parseVideoChatStarted(object->videoChatStarted));
    appendToJson(result, "video_chat_ended", parseVideoChatEnded(object->videoChatEnded));
    appendToJson(result, "video_chat_participants_invited", parseVideoChatParticipantsInvited(object->videoChatParticipantsInvited));
    appendToJson(result, "web_app_data", parseWebAppData(object->webAppData));
    appendToJson(result, "reply_markup", parseInlineKeyboardMarkup(object->replyMarkup));
    removeLastComma(result);
    result += '}';
    return result;
}

MessageId::Ptr TgTypeParser::parseJsonAndGetMessageId(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MessageId>());
    result->messageId = data.get<std::int32_t>("message_id", 0);
    return result;
}

std::string TgTypeParser::parseMessageId(const MessageId::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "message_id", object->messageId);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageEntity::Ptr TgTypeParser::parseJsonAndGetMessageEntity(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MessageEntity>());
    std::string type = data.get<std::string>("type", "");
    if (type == "mention") {
        result->type = MessageEntity::Type::Mention;
    } else if (type == "hashtag") {
        result->type = MessageEntity::Type::Hashtag;
    } else if (type == "cashtag") {
        result->type = MessageEntity::Type::Cashtag;
    } else if (type == "bot_command") {
        result->type = MessageEntity::Type::BotCommand;
    } else if (type == "url") {
        result->type = MessageEntity::Type::Url;
    } else if (type == "email") {
        result->type = MessageEntity::Type::Email;
    } else if (type == "phone_number") {
        result->type = MessageEntity::Type::PhoneNumber;
    } else if (type == "bold") {
        result->type = MessageEntity::Type::Bold;
    } else if (type == "italic") {
        result->type = MessageEntity::Type::Italic;
    } else if (type == "underline") {
        result->type = MessageEntity::Type::Underline;
    } else if (type == "strikethrough") {
        result->type = MessageEntity::Type::Strikethrough;
    } else if (type == "spoiler") {
        result->type = MessageEntity::Type::Spoiler;
    } else if (type == "code") {
        result->type = MessageEntity::Type::Code;
    } else if (type == "pre") {
        result->type = MessageEntity::Type::Pre;
    } else if (type == "text_link") {
        result->type = MessageEntity::Type::TextLink;
    } else if (type == "text_mention") {
        result->type = MessageEntity::Type::TextMention;
    } else if (type == "custom_emoji") {
        result->type = MessageEntity::Type::CustomEmoji;
    }
    result->offset = data.get<std::int32_t>("offset", 0);
    result->length = data.get<std::int32_t>("length", 0);
    result->url = data.get<std::string>("url", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->language = data.get<std::string>("language", "");
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    return result;
}

std::string TgTypeParser::parseMessageEntity(const MessageEntity::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    if (object->type == MessageEntity::Type::Mention) {
        appendToJson(result, "type", "mention");
    } else if (object->type == MessageEntity::Type::Hashtag) {
        appendToJson(result, "type", "hashtag");
    } else if (object->type == MessageEntity::Type::Cashtag) {
        appendToJson(result, "type", "cashtag");
    } else if (object->type == MessageEntity::Type::BotCommand) {
        appendToJson(result, "type", "bot_command");
    } else if (object->type == MessageEntity::Type::Url) {
        appendToJson(result, "type", "url");
    } else if (object->type == MessageEntity::Type::Email) {
        appendToJson(result, "type", "email");
    } else if (object->type == MessageEntity::Type::PhoneNumber) {
        appendToJson(result, "type", "phone_number");
    } else if (object->type == MessageEntity::Type::Bold) {
        appendToJson(result, "type", "bold");
    } else if (object->type == MessageEntity::Type::Italic) {
        appendToJson(result, "type", "italic");
    } else if (object->type == MessageEntity::Type::Underline) {
        appendToJson(result, "type", "underline");
    } else if (object->type == MessageEntity::Type::Strikethrough) {
        appendToJson(result, "type", "strikethrough");
    } else if (object->type == MessageEntity::Type::Spoiler) {
        appendToJson(result, "type", "spoiler");
    } else if (object->type == MessageEntity::Type::Code) {
        appendToJson(result, "type", "code");
    } else if (object->type == MessageEntity::Type::Pre) {
        appendToJson(result, "type", "pre");
    } else if (object->type == MessageEntity::Type::TextLink) {
        appendToJson(result, "type", "text_link");
    } else if (object->type == MessageEntity::Type::TextMention) {
        appendToJson(result, "type", "text_mention");
    } else if (object->type == MessageEntity::Type::CustomEmoji) {
        appendToJson(result, "type", "custom_emoji");
    }
    appendToJson(result, "offset", object->offset);
    appendToJson(result, "length", object->length);
    appendToJson(result, "url", object->url);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "language", object->language);
    appendToJson(result, "custom_emoji_id", object->customEmojiId);
    removeLastComma(result);
    result += '}';
    return result;
}

PhotoSize::Ptr TgTypeParser::parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PhotoSize>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parsePhotoSize(const PhotoSize::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Animation::Ptr TgTypeParser::parseJsonAndGetAnimation(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Animation>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parseAnimation(const Animation::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Audio::Ptr TgTypeParser::parseJsonAndGetAudio(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Audio>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->performer = data.get<std::string>("performer", "");
    result->title = data.get<std::string>("title", "");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    return result;
}

std::string TgTypeParser::parseAudio(const Audio::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "title", object->title);
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    removeLastComma(result);
    result += '}';
    return result;
}

Document::Ptr TgTypeParser::parseJsonAndGetDocument(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Document>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parseDocument(const Document::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Video::Ptr TgTypeParser::parseJsonAndGetVideo(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Video>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parseVideo(const Video::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

VideoNote::Ptr TgTypeParser::parseJsonAndGetVideoNote(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<VideoNote>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->length = data.get<std::int32_t>("length", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileSize = data.get("file_size", 0);
    return result;
}

std::string TgTypeParser::parseVideoNote(const VideoNote::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "length", object->length);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Voice::Ptr TgTypeParser::parseJsonAndGetVoice(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Voice>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parseVoice(const Voice::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Contact::Ptr TgTypeParser::parseJsonAndGetContact(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Contact>());
    result->phoneNumber = data.get<std::string>("phone_number");
    result->firstName = data.get<std::string>("first_name");
    result->lastName = data.get("last_name", "");
    result->userId = data.get("user_id", 0);
    result->vcard = data.get("vcard", "");
    return result;
}

std::string TgTypeParser::parseContact(const Contact::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "user_id", object->userId);
    appendToJson(result, "vcard", object->vcard);
    removeLastComma(result);
    result += '}';
    return result;
}

Dice::Ptr TgTypeParser::parseJsonAndGetDice(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Dice>());
    result->emoji = data.get<std::string>("emoji", "");
    result->value = data.get<std::int32_t>("value", 0);
    return result;
}

std::string TgTypeParser::parseDice(const Dice::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "emoji", object->emoji);
    appendToJson(result, "value", object->value);
    removeLastComma(result);
    result += '}';
    return result;
}

PollOption::Ptr TgTypeParser::parseJsonAndGetPollOption(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PollOption>());
    result->text = data.get("text", "");
    result->voterCount = data.get("voter_count", 0);
    return result;
}

std::string TgTypeParser::parsePollOption(const PollOption::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "voter_count", object->voterCount);
    removeLastComma(result);
    result += '}';
    return result;
}

PollAnswer::Ptr TgTypeParser::parseJsonAndGetPollAnswer(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PollAnswer>());
    result->pollId = data.get<std::string>("poll_id", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->optionIds = parseJsonAndGetArray<std::int32_t>(
        [] (const boost::property_tree::ptree& innerData)->std::int32_t {
        return innerData.get<std::int32_t>("");
    }, data, "option_ids");
    return result;
}

std::string TgTypeParser::parsePollAnswer(const PollAnswer::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "poll_id", object->pollId);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "option_ids", parseArray<std::int32_t>([] (std::int32_t i)->std::int32_t {
        return i;
    }, object->optionIds));
    removeLastComma(result);
    result += '}';
    return result;
}

Poll::Ptr TgTypeParser::parseJsonAndGetPoll(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Poll>());
    result->id = data.get<std::string>("id", "");
    result->question = data.get<std::string>("question", "");
    result->options = parseJsonAndGetArray<PollOption>(&TgTypeParser::parseJsonAndGetPollOption, data, "options");
    result->totalVoterCount = data.get<std::int32_t>("total_voter_count", 0);
    result->isClosed = data.get<bool>("is_closed", false);
    result->isAnonymous = data.get<bool>("is_anonymous", true);
    result->type = data.get<std::string>("type", "");
    result->allowsMultipleAnswers = data.get<bool>("allows_multiple_answers", false);
    result->correctOptionId = data.get<std::int32_t>("correct_option_id", 0);
    result->explanation = data.get<std::string>("explanation", "");
    result->explanationEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "explanation_entities");
    result->openPeriod = data.get<std::int32_t>("open_period", 0);
    result->closeDate = data.get<std::int64_t>("close_date", 0);
    return result;
}

std::string TgTypeParser::parsePoll(const Poll::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "question", object->question);
    appendToJson(result, "options", parseArray(&TgTypeParser::parsePollOption, object->options));
    appendToJson(result, "total_voter_count", object->totalVoterCount);
    appendToJson(result, "is_closed", object->isClosed);
    appendToJson(result, "is_anonymous", object->isAnonymous);
    appendToJson(result, "type", object->type);
    appendToJson(result, "allows_multiple_answers", object->allowsMultipleAnswers);
    appendToJson(result, "correct_option_id", object->correctOptionId);
    appendToJson(result, "explanation", object->correctOptionId);
    appendToJson(result, "explanation_entities", parseArray(&TgTypeParser::parseMessageEntity, object->explanationEntities));
    appendToJson(result, "open_period", object->openPeriod);
    appendToJson(result, "close_date", object->closeDate);
    removeLastComma(result);
    result += '}';
    return result;
}

Location::Ptr TgTypeParser::parseJsonAndGetLocation(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Location>());
    result->longitude = data.get<float>("longitude", 0);
    result->latitude = data.get<float>("latitude", 0);
    result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
    result->livePeriod = data.get<std::int32_t>("live_period", 0);
    result->heading = data.get<std::int32_t>("heading", 0);
    result->proximityAlertRadius = data.get<std::int32_t>("proximity_alert_radius", 0);
    return result;
}

std::string TgTypeParser::parseLocation(const Location::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "horizontal_accuracy", object->horizontalAccuracy);
    appendToJson(result, "live_period", object->livePeriod);
    appendToJson(result, "heading", object->heading);
    appendToJson(result, "proximity_alert_radius", object->proximityAlertRadius);
    removeLastComma(result);
    result += '}';
    return result;
}

Venue::Ptr TgTypeParser::parseJsonAndGetVenue(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Venue>());
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->title = data.get<std::string>("title", "");
    result->address = data.get<std::string>("address", "");
    result->foursquareId = data.get<std::string>("foursquare_id", "");
    result->foursquareType = data.get<std::string>("foursquare_type", "");
    result->googlePlaceId = data.get<std::string>("google_place_id", "");
    result->googlePlaceType = data.get<std::string>("google_place_type", "");
    return result;
}

std::string TgTypeParser::parseVenue(const Venue::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "title", object->title);
    appendToJson(result, "address", object->address);
    appendToJson(result, "foursquare_id", object->foursquareId);
    appendToJson(result, "foursquare_type", object->foursquareType);
    appendToJson(result, "google_place_id", object->googlePlaceId);
    appendToJson(result, "google_place_type", object->googlePlaceType);
    removeLastComma(result);
    result += '}';
    return result;
}

WebAppData::Ptr TgTypeParser::parseJsonAndGetWebAppData(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<WebAppData>());
    result->data = data.get<std::string>("data", "");
    result->buttonText = data.get<std::string>("button_text", "");
    return result;
}

std::string TgTypeParser::parseWebAppData(const WebAppData::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "data", object->data);
    appendToJson(result, "button_text", object->buttonText);
    removeLastComma(result);
    result += '}';
    return result;
}

ProximityAlertTriggered::Ptr TgTypeParser::parseJsonAndGetProximityAlertTriggered(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ProximityAlertTriggered>());
    result->traveler = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "traveler");
    result->watcher = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "watcher");
    result->distance = data.get<std::int32_t>("distance", 0);
    return result;
}

std::string TgTypeParser::parseProximityAlertTriggered(const ProximityAlertTriggered::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "traveler", parseUser(object->traveler));
    appendToJson(result, "watcher", parseUser(object->watcher));
    appendToJson(result, "distance", object->distance);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageAutoDeleteTimerChanged::Ptr TgTypeParser::parseJsonAndGetMessageAutoDeleteTimerChanged(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MessageAutoDeleteTimerChanged>());
    result->messageAutoDeleteTime = data.get<std::int32_t>("message_auto_delete_time", 0);
    return result;
}

std::string TgTypeParser::parseMessageAutoDeleteTimerChanged(const MessageAutoDeleteTimerChanged::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "message_auto_delete_time", object->messageAutoDeleteTime);
    removeLastComma(result);
    result += '}';
    return result;
}

ForumTopicCreated::Ptr TgTypeParser::parseJsonAndGetForumTopicCreated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForumTopicCreated>());
    result->name = data.get<std::string>("name", "");
    result->iconColor = data.get<std::int32_t>("icon_color", 0);
    result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
    return result;
}

std::string TgTypeParser::parseForumTopicCreated(const ForumTopicCreated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "name", object->name);
    appendToJson(result, "icon_color", object->iconColor);
    appendToJson(result, "icon_custom_emoji_id", object->iconCustomEmojiId);
    removeLastComma(result);
    result += '}';
    return result;
}

ForumTopicClosed::Ptr TgTypeParser::parseJsonAndGetForumTopicClosed(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForumTopicClosed>());
    return result;
}

std::string TgTypeParser::parseForumTopicClosed(const ForumTopicClosed::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

ForumTopicEdited::Ptr TgTypeParser::parseJsonAndGetForumTopicEdited(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForumTopicEdited>());
    result->name = data.get<std::string>("name", "");
    result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
    return result;
}

std::string TgTypeParser::parseForumTopicEdited(const ForumTopicEdited::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "name", object->name);
    appendToJson(result, "icon_custom_emoji_id", object->iconCustomEmojiId);
    removeLastComma(result);
    result += '}';
    return result;
}

ForumTopicReopened::Ptr TgTypeParser::parseJsonAndGetForumTopicReopened(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForumTopicReopened>());
    return result;
}

std::string TgTypeParser::parseForumTopicReopened(const ForumTopicReopened::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

GeneralForumTopicHidden::Ptr TgTypeParser::parseJsonAndGetGeneralForumTopicHidden(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GeneralForumTopicHidden>());
    return result;
}

std::string TgTypeParser::parseGeneralForumTopicHidden(const GeneralForumTopicHidden::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

GeneralForumTopicUnhidden::Ptr TgTypeParser::parseJsonAndGetGeneralForumTopicUnhidden(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GeneralForumTopicUnhidden>());
    return result;
}

std::string TgTypeParser::parseGeneralForumTopicUnhidden(const GeneralForumTopicUnhidden::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

UserShared::Ptr TgTypeParser::parseJsonAndGetUserShared(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<UserShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->userId = data.get<std::int64_t>("user_id", 0);
    return result;
}

std::string TgTypeParser::parseUserShared(const UserShared::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "user_id", object->userId);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatShared::Ptr TgTypeParser::parseJsonAndGetChatShared(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->userId = data.get<std::int64_t>("user_id", 0);
    return result;
}

std::string TgTypeParser::parseChatShared(const ChatShared::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "user_id", object->userId);
    removeLastComma(result);
    result += '}';
    return result;
}

WriteAccessAllowed::Ptr TgTypeParser::parseJsonAndGetWriteAccessAllowed(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<WriteAccessAllowed>());
    return result;
}

std::string TgTypeParser::parseWriteAccessAllowed(const WriteAccessAllowed::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

VideoChatScheduled::Ptr TgTypeParser::parseJsonAndGetVideoChatScheduled(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<VideoChatScheduled>());
    result->startDate = data.get<std::int32_t>("start_date", 0);
    return result;
}

std::string TgTypeParser::parseVideoChatScheduled(const VideoChatScheduled::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "start_date", object->startDate);
    removeLastComma(result);
    result += '}';
    return result;
}

VideoChatStarted::Ptr TgTypeParser::parseJsonAndGetVideoChatStarted(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<VideoChatStarted>());
    return result;
}

std::string TgTypeParser::parseVideoChatStarted(const VideoChatStarted::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    result += '}';
    return result;
}

VideoChatEnded::Ptr TgTypeParser::parseJsonAndGetVideoChatEnded(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<VideoChatEnded>());
    result->duration = data.get<std::int32_t>("duration", 0);
    return result;
}

std::string TgTypeParser::parseVideoChatEnded(const VideoChatEnded::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "duration", object->duration);
    removeLastComma(result);
    result += '}';
    return result;
}

VideoChatParticipantsInvited::Ptr TgTypeParser::parseJsonAndGetVideoChatParticipantsInvited(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<VideoChatParticipantsInvited>());
    result->users = parseJsonAndGetArray<User>(&TgTypeParser::parseJsonAndGetUser, data, "users");
    return result;
}

std::string TgTypeParser::parseVideoChatParticipantsInvited(const VideoChatParticipantsInvited::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "users", parseArray(&TgTypeParser::parseUser, object->users));
    removeLastComma(result);
    result += '}';
    return result;
}

UserProfilePhotos::Ptr TgTypeParser::parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<UserProfilePhotos>());
    result->totalCount = data.get<std::int32_t>("total_count");
    result->photos = parseJsonAndGet2DArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photos");
    return result;
}

std::string TgTypeParser::parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "total_count", object->totalCount);
    appendToJson(result, "photos", parse2DArray(&TgTypeParser::parsePhotoSize, object->photos));
    removeLastComma(result);
    result += '}';
    return result;
}

File::Ptr TgTypeParser::parseJsonAndGetFile(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<File>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    result->filePath = data.get<std::string>("file_path", "");
    return result;
}

std::string TgTypeParser::parseFile(const File::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "file_size", object->fileSize);
    appendToJson(result, "file_path", object->filePath);
    removeLastComma(result);
    result += '}';
    return result;
}

WebAppInfo::Ptr TgTypeParser::parseJsonAndGetWebAppInfo(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<WebAppInfo>());
    result->url = data.get<std::string>("url", "");
    return result;
}

std::string TgTypeParser::parseWebAppInfo(const WebAppInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "url", object->url);
    removeLastComma(result);
    result += '}';
    return result;
}

ReplyKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ReplyKeyboardMarkup>());
    for (const auto& item : data.find("keyboard")->second) {
        result->keyboard.push_back(parseJsonAndGetArray<KeyboardButton>(&TgTypeParser::parseJsonAndGetKeyboardButton, item.second));
    }
    result->isPersistent = data.get<bool>("is_persistent", false);
    result->resizeKeyboard = data.get<bool>("resize_keyboard", false);
    result->oneTimeKeyboard = data.get<bool>("one_time_keyboard", false);
    result->inputFieldPlaceholder = data.get<std::string>("input_field_placeholder", "");
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string TgTypeParser::parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    result += R"("keyboard":[)";
    for (const auto& item : object->keyboard) {
        result += '[';
        for (const auto& innerItem : item) {
            result += parseKeyboardButton(innerItem);
            result += ',';
        }
        removeLastComma(result);
        result += "],";
    }
    if (!object->keyboard.empty())
        removeLastComma(result);
    result += "],";
    appendToJson(result, "is_persistent", object->isPersistent);
    appendToJson(result, "resize_keyboard", object->resizeKeyboard);
    appendToJson(result, "one_time_keyboard", object->oneTimeKeyboard);
    appendToJson(result, "input_field_placeholder", object->inputFieldPlaceholder);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButton::Ptr TgTypeParser::parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<KeyboardButton>());
    result->text = data.get<std::string>("text", "");
    result->requestUser = tryParseJson<KeyboardButtonRequestUser>(&TgTypeParser::parseJsonAndGetKeyboardButtonRequestUser, data, "request_user");
    result->requestChat = tryParseJson<KeyboardButtonRequestChat>(&TgTypeParser::parseJsonAndGetKeyboardButtonRequestChat, data, "request_chat");
    result->requestContact = data.get<bool>("request_contact", false);
    result->requestLocation = data.get<bool>("request_location", false);
    result->requestPoll = tryParseJson<KeyboardButtonPollType>(&TgTypeParser::parseJsonAndGetKeyboardButtonPollType, data, "request_poll");
    result->webApp = tryParseJson<WebAppInfo>(&TgTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    return result;
}

std::string TgTypeParser::parseKeyboardButton(const KeyboardButton::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "request_user", parseKeyboardButtonRequestUser(object->requestUser));
    appendToJson(result, "request_chat", parseKeyboardButtonRequestChat(object->requestChat));
    appendToJson(result, "request_contact", object->requestContact);
    appendToJson(result, "request_location", object->requestLocation);
    appendToJson(result, "request_poll", parseKeyboardButtonPollType(object->requestPoll));
    appendToJson(result, "web_app", parseWebAppInfo(object->webApp));
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButtonRequestUser::Ptr TgTypeParser::parseJsonAndGetKeyboardButtonRequestUser(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<KeyboardButtonRequestUser>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->userIsBot = data.get<bool>("user_is_bot", false);
    result->userIsPremium = data.get<bool>("user_is_premium", false);
    return result;
}

std::string TgTypeParser::parseKeyboardButtonRequestUser(const KeyboardButtonRequestUser::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "user_is_bot", object->userIsBot);
    appendToJson(result, "user_is_premium", object->userIsPremium);
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButtonRequestChat::Ptr TgTypeParser::parseJsonAndGetKeyboardButtonRequestChat(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<KeyboardButtonRequestChat>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->chatIsChannel = data.get<bool>("chat_is_channel", false);
    result->chatIsForum = data.get<bool>("chat_is_forum", false);
    result->chatHasUsername = data.get<bool>("chat_has_username", false);
    result->chatIsCreated = data.get<bool>("chat_is_created", false);
    result->userAdministratorRights = tryParseJson<ChatAdministratorRights>(&TgTypeParser::parseJsonAndGetChatAdministratorRights, data, "user_administrator_rights");
    result->botAdministratorRights = tryParseJson<ChatAdministratorRights>(&TgTypeParser::parseJsonAndGetChatAdministratorRights, data, "bot_administrator_rights");
    result->botIsMember = data.get<bool>("bot_is_member", false);
    return result;
}

std::string TgTypeParser::parseKeyboardButtonRequestChat(const KeyboardButtonRequestChat::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "chat_is_channel", object->chatIsChannel);
    appendToJson(result, "chat_is_forum", object->chatIsForum);
    appendToJson(result, "chat_has_username", object->chatHasUsername);
    appendToJson(result, "chat_is_created", object->chatIsCreated);
    appendToJson(result, "user_administrator_rights", parseChatAdministratorRights(object->userAdministratorRights));
    appendToJson(result, "bot_administrator_rights", parseChatAdministratorRights(object->botAdministratorRights));
    appendToJson(result, "bot_is_member", object->botIsMember);
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButtonPollType::Ptr TgTypeParser::parseJsonAndGetKeyboardButtonPollType(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<KeyboardButtonPollType>());
    result->type = data.get<std::string>("type", "");
    return result;
}

std::string TgTypeParser::parseKeyboardButtonPollType(const KeyboardButtonPollType::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    removeLastComma(result);
    result += '}';
    return result;
}

ReplyKeyboardRemove::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ReplyKeyboardRemove>());
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string TgTypeParser::parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "remove_keyboard", object->removeKeyboard);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

InlineKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InlineKeyboardMarkup>());
    for (const auto& item : data.find("inline_keyboard")->second) {
        result->inlineKeyboard.push_back(parseJsonAndGetArray<InlineKeyboardButton>(&TgTypeParser::parseJsonAndGetInlineKeyboardButton, item.second));
    }
    return result;
}

std::string TgTypeParser::parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    result += R"("inline_keyboard":[)";
    for (const auto& item : object->inlineKeyboard) {
        result += '[';
        for (const auto& innerItem : item) {
            result += parseInlineKeyboardButton(innerItem);
            result += ',';
        }
        removeLastComma(result);
        result += "],";
    }
    if (!object->inlineKeyboard.empty())
        removeLastComma(result);
    result += "]}";
    return result;
}

InlineKeyboardButton::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InlineKeyboardButton>());
    result->text = data.get<std::string>("text", "");
    result->url = data.get<std::string>("url", "");
    result->callbackData = data.get<std::string>("callback_data", "");
    result->webApp = tryParseJson<WebAppInfo>(&TgTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    result->loginUrl = tryParseJson<LoginUrl>(&TgTypeParser::parseJsonAndGetLoginUrl, data, "login_url");
    result->switchInlineQuery = data.get<std::string>("switch_inline_query", "");
    result->switchInlineQueryCurrentChat = data.get<std::string>("switch_inline_query_current_chat", "");
    result->callbackGame = tryParseJson<CallbackGame>(&TgTypeParser::parseJsonAndGetCallbackGame, data, "callback_game");
    result->pay = data.get<bool>("pay", false);
    return result;
}
std::string TgTypeParser::parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "url", object->url);
    appendToJson(result, "callback_data", object->callbackData);
    appendToJson(result, "web_app", parseWebAppInfo(object->webApp));
    appendToJson(result, "login_url", parseLoginUrl(object->loginUrl));
    appendToJson(result, "switch_inline_query", object->switchInlineQuery);
    appendToJson(result, "switch_inline_query_current_chat", object->switchInlineQueryCurrentChat);
    appendToJson(result, "callback_game", parseCallbackGame(object->callbackGame));
    appendToJson(result, "pay", object->pay);
    removeLastComma(result);
    result += '}';
    return result;
}

LoginUrl::Ptr TgTypeParser::parseJsonAndGetLoginUrl(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<LoginUrl>());
    result->url = data.get<std::string>("url", "");
    result->forwardText = data.get<std::string>("forward_text", "");
    result->botUsername = data.get<std::string>("bot_username", "");
    result->requestWriteAccess = data.get<bool>("request_write_access", false);
    return result;
}

std::string TgTypeParser::parseLoginUrl(const LoginUrl::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "url", object->url);
    appendToJson(result, "forward_text", object->forwardText);
    appendToJson(result, "bot_username", object->botUsername);
    appendToJson(result, "request_write_access", object->requestWriteAccess);
    removeLastComma(result);
    result += '}';
    return result;
}

CallbackQuery::Ptr TgTypeParser::parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<CallbackQuery>());
    result->id = data.get<std::string>("id");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    result->chatInstance = data.get<std::string>("chat_instance");
    result->gameShortName = data.get<std::string>("game_short_name", "");
    result->data = data.get<std::string>("data", "");
    return result;
}

std::string TgTypeParser::parseCallbackQuery(const CallbackQuery::Ptr& object) const {
    if (!object) {
        return "";
    }

    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "message", parseMessage(object->message));
    appendToJson(result, "inline_message_id", object->inlineMessageId);
    appendToJson(result, "chat_instance", object->chatInstance);
    appendToJson(result, "game_short_name", object->gameShortName);
    appendToJson(result, "data", object->data);
    removeLastComma(result);
    result += '}';
    return result;
}

ForceReply::Ptr TgTypeParser::parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForceReply>());
    result->inputFieldPlaceholder = data.get<std::string>("input_field_placeholder", "");
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string TgTypeParser::parseForceReply(const ForceReply::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "force_reply", object->forceReply);
    appendToJson(result, "input_field_placeholder", object->inputFieldPlaceholder);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatPhoto::Ptr TgTypeParser::parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatPhoto>());
    result->smallFileId = data.get<std::string>("small_file_id", "");
    result->smallFileUniqueId = data.get<std::string>("small_file_unique_id", "");
    result->bigFileId = data.get<std::string>("big_file_id", "");
    result->bigFileUniqueId = data.get<std::string>("big_file_unique_id", "");
    return result;
}

std::string TgTypeParser::parseChatPhoto(const ChatPhoto::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "small_file_id", object->smallFileId);
    appendToJson(result, "small_file_unique_id", object->smallFileUniqueId);
    appendToJson(result, "big_file_id", object->bigFileId);
    appendToJson(result, "big_file_unique_id", object->bigFileUniqueId);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatInviteLink::Ptr TgTypeParser::parseJsonAndGetChatInviteLink(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatInviteLink>());
    result->inviteLink = data.get<std::string>("invite_link", "");
    result->creator = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "creator");
    result->createsJoinRequest = data.get<bool>("creates_join_request", false);
    result->isPrimary = data.get<bool>("is_primary", false);
    result->isRevoked = data.get<bool>("is_revoked", false);
    result->name = data.get<std::string>("name", "");
    result->expireDate = data.get<std::uint32_t>("expire_date", 0);
    result->memberLimit = data.get<std::uint32_t>("member_limit", 0);
    result->pendingJoinRequestCount = data.get<std::uint32_t>("pending_join_request_count", 0);
    return result;
}

std::string TgTypeParser::parseChatInviteLink(const ChatInviteLink::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "invite_link", object->inviteLink);
    appendToJson(result, "creator", parseUser(object->creator));
    appendToJson(result, "creates_join_request", object->createsJoinRequest);
    appendToJson(result, "is_primary", object->isPrimary);
    appendToJson(result, "is_revoked", object->isRevoked);
    appendToJson(result, "name", object->name);
    appendToJson(result, "expire_date", object->expireDate);
    appendToJson(result, "member_limit", object->memberLimit);
    appendToJson(result, "pending_join_request_count", object->pendingJoinRequestCount);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatAdministratorRights::Ptr TgTypeParser::parseJsonAndGetChatAdministratorRights(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatAdministratorRights>());
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    result->canManageChat = data.get<bool>("can_manage_chat", false);
    result->canDeleteMessages = data.get<bool>("can_delete_messages", false);
    result->canManageVideoChats = data.get<bool>("can_manage_video_chats", false);
    result->canRestrictMembers = data.get<bool>("can_restrict_members", false);
    result->canPromoteMembers = data.get<bool>("can_promote_members", false);
    result->canChangeInfo = data.get<bool>("can_change_info", false);
    result->canInviteUsers = data.get<bool>("can_invite_users", false);
    result->canPostMessages = data.get<bool>("can_post_messages", false);
    result->canEditMessages = data.get<bool>("can_edit_messages", false);
    result->canPinMessages = data.get<bool>("can_pin_messages", false);
    result->canManageTopics = data.get<bool>("can_manage_topics", false);
    return result;
}

std::string TgTypeParser::parseChatAdministratorRights(const ChatAdministratorRights::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "is_anonymous", object->isAnonymous);
    appendToJson(result, "can_manage_chat", object->canManageChat);
    appendToJson(result, "can_delete_messages", object->canDeleteMessages);
    appendToJson(result, "can_manage_video_chats", object->canManageVideoChats);
    appendToJson(result, "can_restrict_members", object->canRestrictMembers);
    appendToJson(result, "can_promote_members", object->canPromoteMembers);
    appendToJson(result, "can_change_info", object->canChangeInfo);
    appendToJson(result, "can_invite_users", object->canInviteUsers);
    appendToJson(result, "can_post_messages", object->canPostMessages);
    appendToJson(result, "can_edit_messages", object->canEditMessages);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatMember::Ptr TgTypeParser::parseJsonAndGetChatMember(const boost::property_tree::ptree& data) const {
    std::string status = data.get<std::string>("status", "");
    ChatMember::Ptr result;

    if (status == ChatMemberOwner::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberOwner(data));
    } else if (status == ChatMemberAdministrator::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberAdministrator(data));
    } else if (status == ChatMemberMember::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberMember(data));
    } else if (status == ChatMemberRestricted::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberRestricted(data));
    } else if (status == ChatMemberLeft::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberLeft(data));
    } else if (status == ChatMemberBanned::STATUS) {
        result = std::static_pointer_cast<ChatMember>(parseJsonAndGetChatMemberBanned(data));
    } else {
        result = std::make_shared<ChatMember>();
    }

    result->status = status;
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");

    return result;
}

std::string TgTypeParser::parseChatMember(const ChatMember::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "status", object->status);
    appendToJson(result, "user", parseUser(object->user));

    if (object->status == ChatMemberOwner::STATUS) {
        result += parseChatMemberOwner(std::static_pointer_cast<ChatMemberOwner>(object));
    } else if (object->status == ChatMemberAdministrator::STATUS) {
        result += parseChatMemberAdministrator(std::static_pointer_cast<ChatMemberAdministrator>(object));
    } else if (object->status == ChatMemberMember::STATUS) {
        result += parseChatMemberMember(std::static_pointer_cast<ChatMemberMember>(object));
    } else if (object->status == ChatMemberRestricted::STATUS) {
        result += parseChatMemberRestricted(std::static_pointer_cast<ChatMemberRestricted>(object));
    } else if (object->status == ChatMemberLeft::STATUS) {
        result += parseChatMemberLeft(std::static_pointer_cast<ChatMemberLeft>(object));
    } else if (object->status == ChatMemberBanned::STATUS) {
        result += parseChatMemberBanned(std::static_pointer_cast<ChatMemberBanned>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

ChatMemberOwner::Ptr TgTypeParser::parseJsonAndGetChatMemberOwner(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberOwner>());
    result->customTitle = data.get<std::string>("custom_title", "");
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    return result;
}

std::string TgTypeParser::parseChatMemberOwner(const ChatMemberOwner::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "custom_title", object->customTitle);
    appendToJson(result, "is_anonymous", object->isAnonymous);
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberAdministrator::Ptr TgTypeParser::parseJsonAndGetChatMemberAdministrator(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberAdministrator>());
    result->canBeEdited = data.get<bool>("can_be_edited", false);
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    result->canManageChat = data.get<bool>("can_manage_chat", false);
    result->canDeleteMessages = data.get<bool>("can_delete_messages", false);
    result->canManageVideoChats = data.get<bool>("can_manage_video_chats", false);
    result->canRestrictMembers = data.get<bool>("can_restrict_members", false);
    result->canPromoteMembers = data.get<bool>("can_promote_members", false);
    result->canChangeInfo = data.get<bool>("can_change_info", false);
    result->canInviteUsers = data.get<bool>("can_invite_users", false);
    result->canPostMessages = data.get<bool>("can_post_messages", false);
    result->canEditMessages = data.get<bool>("can_edit_messages", false);
    result->canPinMessages = data.get<bool>("can_pin_messages", false);
    result->canManageTopics = data.get<bool>("can_manage_topics", false);
    result->customTitle = data.get<std::string>("custom_title", "");
    return result;
}

std::string TgTypeParser::parseChatMemberAdministrator(const ChatMemberAdministrator::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "can_be_edited", object->canBeEdited);
    appendToJson(result, "is_anonymous", object->isAnonymous);
    appendToJson(result, "can_manage_chat", object->canManageChat);
    appendToJson(result, "can_delete_messages", object->canDeleteMessages);
    appendToJson(result, "can_manage_video_chats", object->canManageVideoChats);
    appendToJson(result, "can_restrict_members", object->canRestrictMembers);
    appendToJson(result, "can_promote_members", object->canPromoteMembers);
    appendToJson(result, "can_change_info", object->canChangeInfo);
    appendToJson(result, "can_invite_users", object->canInviteUsers);
    appendToJson(result, "can_post_messages", object->canPostMessages);
    appendToJson(result, "can_edit_messages", object->canEditMessages);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    appendToJson(result, "custom_title", object->customTitle);
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberMember::Ptr TgTypeParser::parseJsonAndGetChatMemberMember(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberMember>());
    return result;
}

std::string TgTypeParser::parseChatMemberMember(const ChatMemberMember::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberRestricted::Ptr TgTypeParser::parseJsonAndGetChatMemberRestricted(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberRestricted>());
    result->isMember = data.get<bool>("is_member", false);
    result->canSendMessages = data.get<bool>("can_send_messages", false);
    result->canSendAudios = data.get<bool>("can_send_audios", false);
    result->canSendDocuments = data.get<bool>("can_send_documents", false);
    result->canSendPhotos = data.get<bool>("can_send_photos", false);
    result->canSendVideos = data.get<bool>("can_send_videos", false);
    result->canSendVideoNotes = data.get<bool>("can_send_video_notes", false);
    result->canSendVoiceNotes = data.get<bool>("can_send_voice_notes", false);
    result->canSendPolls = data.get<bool>("can_send_polls", false);
    result->canSendOtherMessages = data.get<bool>("can_send_other_messages", false);
    result->canAddWebPagePreviews = data.get<bool>("can_add_web_page_previews", false);
    result->canChangeInfo = data.get<bool>("can_change_info", false);
    result->canInviteUsers = data.get<bool>("can_invite_users", false);
    result->canPinMessages = data.get<bool>("can_pin_messages", false);
    result->canManageTopics = data.get<bool>("can_manage_topics", false);
    result->untilDate = data.get<std::uint32_t>("until_date", 0);
    return result;
}

std::string TgTypeParser::parseChatMemberRestricted(const ChatMemberRestricted::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "is_member", object->isMember);
    appendToJson(result, "can_send_messages", object->canSendMessages);
    appendToJson(result, "can_send_audios", object->canSendAudios);
    appendToJson(result, "can_send_documents", object->canSendDocuments);
    appendToJson(result, "can_send_photos", object->canSendPhotos);
    appendToJson(result, "can_send_videos", object->canSendVideos);
    appendToJson(result, "can_send_video_notes", object->canSendVideoNotes);
    appendToJson(result, "can_send_voice_notes", object->canSendVoiceNotes);
    appendToJson(result, "can_send_polls", object->canSendPolls);
    appendToJson(result, "can_send_other_messages", object->canSendOtherMessages);
    appendToJson(result, "can_add_web_page_previews", object->canAddWebPagePreviews);
    appendToJson(result, "can_change_info", object->canChangeInfo);
    appendToJson(result, "can_invite_users", object->canInviteUsers);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    appendToJson(result, "until_date", object->untilDate);
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberLeft::Ptr TgTypeParser::parseJsonAndGetChatMemberLeft(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberLeft>());
    return result;
}

std::string TgTypeParser::parseChatMemberLeft(const ChatMemberLeft::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberBanned::Ptr TgTypeParser::parseJsonAndGetChatMemberBanned(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberBanned>());
    result->untilDate = data.get<uint32_t>("until_date", 0);
    return result;
}

std::string TgTypeParser::parseChatMemberBanned(const ChatMemberBanned::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "until_date", object->untilDate);
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberUpdated::Ptr TgTypeParser::parseJsonAndGetChatMemberUpdated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatMemberUpdated>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->date = data.get<uint32_t>("date", 0);
    result->oldChatMember = tryParseJson<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, data, "old_chat_member");
    result->newChatMember = tryParseJson<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, data, "new_chat_member");
    result->inviteLink = tryParseJson<ChatInviteLink>(&TgTypeParser::parseJsonAndGetChatInviteLink, data, "invite_link");
    return result;
}

std::string TgTypeParser::parseChatMemberUpdated(const ChatMemberUpdated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "date", object->date);
    appendToJson(result, "old_chat_member", parseChatMember(object->oldChatMember));
    appendToJson(result, "new_chat_member", parseChatMember(object->newChatMember));
    appendToJson(result, "invite_link", parseChatInviteLink(object->inviteLink));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatJoinRequest::Ptr TgTypeParser::parseJsonAndGetChatJoinRequest(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatJoinRequest>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->userChatId = data.get<std::int64_t>("user_chat_id", 0);
    result->date = data.get<std::int32_t>("date", 0);
    result->bio = data.get<std::string>("bio", "");
    result->inviteLink = tryParseJson<ChatInviteLink>(&TgTypeParser::parseJsonAndGetChatInviteLink, data, "invite_link");
    return result;
}

std::string TgTypeParser::parseChatJoinRequest(const ChatJoinRequest::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "user_chat_id", object->userChatId);
    appendToJson(result, "date", object->date);
    appendToJson(result, "bio", object->bio);
    appendToJson(result, "invite_link", parseChatInviteLink(object->inviteLink));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatPermissions::Ptr TgTypeParser::parseJsonAndGetChatPermissions(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatPermissions>());
    result->canSendMessages = data.get<bool>("can_send_messages", false);
    result->canSendAudios = data.get<bool>("can_send_audios", false);
    result->canSendDocuments = data.get<bool>("can_send_documents", false);
    result->canSendPhotos = data.get<bool>("can_send_photos", false);
    result->canSendVideos = data.get<bool>("can_send_videos", false);
    result->canSendVideoNotes = data.get<bool>("can_send_video_notes", false);
    result->canSendVoiceNotes = data.get<bool>("can_send_voice_notes", false);
    result->canSendPolls = data.get<bool>("can_send_polls", false);
    result->canSendOtherMessages = data.get<bool>("can_send_other_messages", false);
    result->canAddWebPagePreviews = data.get<bool>("can_add_web_page_previews", false);
    result->canChangeInfo = data.get<bool>("can_change_info", false);
    result->canInviteUsers = data.get<bool>("can_invite_users", false);
    result->canPinMessages = data.get<bool>("can_pin_messages", false);
    result->canManageTopics = data.get<bool>("can_manage_topics", false);
    return result;
}

std::string TgTypeParser::parseChatPermissions(const ChatPermissions::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "can_send_messages", object->canSendMessages);
    appendToJson(result, "can_send_audios", object->canSendAudios);
    appendToJson(result, "can_send_documents", object->canSendDocuments);
    appendToJson(result, "can_send_photos", object->canSendPhotos);
    appendToJson(result, "can_send_videos", object->canSendVideos);
    appendToJson(result, "can_send_video_notes", object->canSendVideoNotes);
    appendToJson(result, "can_send_voice_notes", object->canSendVoiceNotes);
    appendToJson(result, "can_send_polls", object->canSendPolls);
    appendToJson(result, "can_send_other_messages", object->canSendOtherMessages);
    appendToJson(result, "can_add_web_page_previews", object->canAddWebPagePreviews);
    appendToJson(result, "can_change_info", object->canChangeInfo);
    appendToJson(result, "can_invite_users", object->canInviteUsers);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatLocation::Ptr TgTypeParser::parseJsonAndGetChatLocation(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatLocation>());
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->address = data.get<std::string>("address", "");
    return result;
}

std::string TgTypeParser::parseChatLocation(const ChatLocation::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "address", object->address);
    removeLastComma(result);
    result += '}';
    return result;
}

ForumTopic::Ptr TgTypeParser::parseJsonAndGetForumTopic(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForumTopic>());
    result->messageThreadId = data.get<std::int32_t>("message_thread_id", 0);
    result->name = data.get<std::string>("name", "");
    result->iconColor = data.get<std::int32_t>("icon_color", 0);
    result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
    return result;
}

std::string TgTypeParser::parseForumTopic(const ForumTopic::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "message_thread_id", object->messageThreadId);
    appendToJson(result, "name", object->name);
    appendToJson(result, "icon_color", object->iconColor);
    appendToJson(result, "icon_custom_emoji_id", object->iconCustomEmojiId);
    removeLastComma(result);
    result += '}';
    return result;
}

BotCommand::Ptr TgTypeParser::parseJsonAndGetBotCommand(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BotCommand>());
    result->command = data.get("command", "");
    result->description = data.get("description", "");
    return result;
}

std::string TgTypeParser::parseBotCommand(const BotCommand::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "command", object->command);
    appendToJson(result, "description", object->description);
    removeLastComma(result);
    result += '}';
    return result;
}

BotCommandScope::Ptr TgTypeParser::parseJsonAndGetBotCommandScope(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    BotCommandScope::Ptr result;

    if (type == BotCommandScopeDefault::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeDefault(data));
    } else if (type == BotCommandScopeAllPrivateChats::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeAllPrivateChats(data));
    } else if (type == BotCommandScopeAllGroupChats::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeAllGroupChats(data));
    } else if (type == BotCommandScopeAllChatAdministrators::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeAllChatAdministrators(data));
    } else if (type == BotCommandScopeChat::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeChat(data));
    } else if (type == BotCommandScopeChatAdministrators::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeChatAdministrators(data));
    } else if (type == BotCommandScopeChatMember::TYPE) {
        result = std::static_pointer_cast<BotCommandScope>(parseJsonAndGetBotCommandScopeChatMember(data));
    } else {
        result = std::make_shared<BotCommandScope>();
    }

    result->type = type;

    return result;
}

std::string TgTypeParser::parseBotCommandScope(const BotCommandScope::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);

    if (object->type == BotCommandScopeDefault::TYPE) {
        result += parseBotCommandScopeDefault(std::static_pointer_cast<BotCommandScopeDefault>(object));
    } else if (object->type == BotCommandScopeAllPrivateChats::TYPE) {
        result += parseBotCommandScopeAllPrivateChats(std::static_pointer_cast<BotCommandScopeAllPrivateChats>(object));
    } else if (object->type == BotCommandScopeAllGroupChats::TYPE) {
        result += parseBotCommandScopeAllGroupChats(std::static_pointer_cast<BotCommandScopeAllGroupChats>(object));
    } else if (object->type == BotCommandScopeAllChatAdministrators::TYPE) {
        result += parseBotCommandScopeAllChatAdministrators(std::static_pointer_cast<BotCommandScopeAllChatAdministrators>(object));
    } else if (object->type == BotCommandScopeChat::TYPE) {
        result += parseBotCommandScopeChat(std::static_pointer_cast<BotCommandScopeChat>(object));
    } else if (object->type == BotCommandScopeChatAdministrators::TYPE) {
        result += parseBotCommandScopeChatAdministrators(std::static_pointer_cast<BotCommandScopeChatAdministrators>(object));
    } else if (object->type == BotCommandScopeChatMember::TYPE) {
        result += parseBotCommandScopeChatMember(std::static_pointer_cast<BotCommandScopeChatMember>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

BotCommandScopeDefault::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeDefault(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeDefault>());
    return result;
}

std::string TgTypeParser::parseBotCommandScopeDefault(const BotCommandScopeDefault::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllPrivateChats::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllPrivateChats(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllPrivateChats>());
    return result;
}

std::string TgTypeParser::parseBotCommandScopeAllPrivateChats(const BotCommandScopeAllPrivateChats::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllGroupChats::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllGroupChats(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllGroupChats>());
    return result;
}

std::string TgTypeParser::parseBotCommandScopeAllGroupChats(const BotCommandScopeAllGroupChats::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllChatAdministrators::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllChatAdministrators(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllChatAdministrators>());
    return result;
}

std::string TgTypeParser::parseBotCommandScopeAllChatAdministrators(const BotCommandScopeAllChatAdministrators::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeChat::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeChat(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChat>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    return result;
}

std::string TgTypeParser::parseBotCommandScopeChat(const BotCommandScopeChat::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "chat_id", object->chatId);
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeChatAdministrators::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeChatAdministrators(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChatAdministrators>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    return result;
}

std::string TgTypeParser::parseBotCommandScopeChatAdministrators(const BotCommandScopeChatAdministrators::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "chat_id", object->chatId);
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeChatMember::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeChatMember(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChatMember>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->userId = data.get<std::int64_t>("user_id", 0);
    return result;
}

std::string TgTypeParser::parseBotCommandScopeChatMember(const BotCommandScopeChatMember::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "chat_id", object->chatId);
    appendToJson(result, "user_id", object->userId);
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

MenuButton::Ptr TgTypeParser::parseJsonAndGetMenuButton(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    MenuButton::Ptr result;

    if (type == MenuButtonCommands::TYPE) {
        result = std::static_pointer_cast<MenuButton>(parseJsonAndGetMenuButtonCommands(data));
    } else if (type == MenuButtonWebApp::TYPE) {
        result = std::static_pointer_cast<MenuButton>(parseJsonAndGetMenuButtonWebApp(data));
    } else if (type == MenuButtonDefault::TYPE) {
        result = std::static_pointer_cast<MenuButton>(parseJsonAndGetMenuButtonDefault(data));
    } else {
        result = std::make_shared<MenuButton>();
    }

    result->type = type;

    return result;
}

std::string TgTypeParser::parseMenuButton(const MenuButton::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);

    if (object->type == MenuButtonCommands::TYPE) {
        result += parseMenuButtonCommands(std::static_pointer_cast<MenuButtonCommands>(object));
    } else if (object->type == MenuButtonWebApp::TYPE) {
        result += parseMenuButtonWebApp(std::static_pointer_cast<MenuButtonWebApp>(object));
    } else if (object->type == MenuButtonDefault::TYPE) {
        result += parseMenuButtonDefault(std::static_pointer_cast<MenuButtonDefault>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

MenuButtonCommands::Ptr TgTypeParser::parseJsonAndGetMenuButtonCommands(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonCommands>());
    return result;
}

std::string TgTypeParser::parseMenuButtonCommands(const MenuButtonCommands::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMenuButton(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseMenuButton().
    return result;
}

MenuButtonWebApp::Ptr TgTypeParser::parseJsonAndGetMenuButtonWebApp(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonWebApp>());
    result->text = data.get<std::string>("text", "");
    result->webApp = tryParseJson<WebAppInfo>(&TgTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    return result;
}

std::string TgTypeParser::parseMenuButtonWebApp(const MenuButtonWebApp::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMenuButton(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "text", object->text);
    appendToJson(result, "web_app", parseWebAppInfo(object->webApp));
    // The last comma will be erased by parseMenuButton().
    return result;
}

MenuButtonDefault::Ptr TgTypeParser::parseJsonAndGetMenuButtonDefault(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonDefault>());
    return result;
}

std::string TgTypeParser::parseMenuButtonDefault(const MenuButtonDefault::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMenuButton(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseMenuButton().
    return result;
}

ResponseParameters::Ptr TgTypeParser::parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ResponseParameters>());
    result->migrateToChatId = data.get<std::int64_t>("migrate_to_chat_id", 0);
    result->retryAfter = data.get<std::int32_t>("retry_after", 0);
    return result;
}

std::string TgTypeParser::parseResponseParameters(const ResponseParameters::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "migrate_to_chat_id", object->migrateToChatId);
    appendToJson(result, "retry_after", object->retryAfter);
    removeLastComma(result);
    result += '}';
    return result;
}

InputMedia::Ptr TgTypeParser::parseJsonAndGetInputMedia(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    InputMedia::Ptr result;

    if (type == InputMediaPhoto::TYPE) {
        result = std::static_pointer_cast<InputMedia>(parseJsonAndGetInputMediaPhoto(data));
    } else if (type == InputMediaVideo::TYPE) {
        result = std::static_pointer_cast<InputMedia>(parseJsonAndGetInputMediaVideo(data));
    } else if (type == InputMediaAnimation::TYPE) {
        result = std::static_pointer_cast<InputMedia>(parseJsonAndGetInputMediaAnimation(data));
    } else if (type == InputMediaAudio::TYPE) {
        result = std::static_pointer_cast<InputMedia>(parseJsonAndGetInputMediaAudio(data));
    } else if (type == InputMediaDocument::TYPE) {
        result = std::static_pointer_cast<InputMedia>(parseJsonAndGetInputMediaDocument(data));
    } else {
        result = std::make_shared<InputMedia>();
    }

    result->type = data.get<std::string>("type", "");
    result->media = data.get<std::string>("media", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");

    return result;
}

std::string TgTypeParser::parseInputMedia(const InputMedia::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "media", object->media);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));

    if (object->type == InputMediaPhoto::TYPE) {
        result += parseInputMediaPhoto(std::static_pointer_cast<InputMediaPhoto>(object));
    } else if (object->type == InputMediaVideo::TYPE) {
        result += parseInputMediaVideo(std::static_pointer_cast<InputMediaVideo>(object));
    } else if (object->type == InputMediaAnimation::TYPE) {
        result += parseInputMediaAnimation(std::static_pointer_cast<InputMediaAnimation>(object));
    } else if (object->type == InputMediaAudio::TYPE) {
        result += parseInputMediaAudio(std::static_pointer_cast<InputMediaAudio>(object));
    } else if (object->type == InputMediaDocument::TYPE) {
        result += parseInputMediaDocument(std::static_pointer_cast<InputMediaDocument>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InputMediaPhoto::Ptr TgTypeParser::parseJsonAndGetInputMediaPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaPhoto>());
    result->hasSpoiler = data.get<bool>("has_spoiler", false);
    return result;
}

std::string TgTypeParser::parseInputMediaPhoto(const InputMediaPhoto::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMedia(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "has_spoiler", object->hasSpoiler);
    // The last comma will be erased by parseInputMedia().
    return result;
}

InputMediaVideo::Ptr TgTypeParser::parseJsonAndGetInputMediaVideo(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaVideo>());
    result->thumb = data.get<std::string>("thumb", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->supportsStreaming = data.get<bool>("supports_streaming", false);
    result->hasSpoiler = data.get<bool>("has_spoiler", false);
    return result;
}

std::string TgTypeParser::parseInputMediaVideo(const InputMediaVideo::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMedia(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "thumb", object->thumb);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "supports_streaming", object->supportsStreaming);
    appendToJson(result, "has_spoiler", object->hasSpoiler);
    // The last comma will be erased by parseInputMedia().
    return result;
}

InputMediaAnimation::Ptr TgTypeParser::parseJsonAndGetInputMediaAnimation(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaAnimation>());
    result->thumb = data.get<std::string>("thumb", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->hasSpoiler = data.get<bool>("has_spoiler", false);
    return result;
}

std::string TgTypeParser::parseInputMediaAnimation(const InputMediaAnimation::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMedia(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "thumb", object->thumb);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "has_spoiler", object->hasSpoiler);
    // The last comma will be erased by parseInputMedia().
    return result;
}

InputMediaAudio::Ptr TgTypeParser::parseJsonAndGetInputMediaAudio(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaAudio>());
    result->thumb = data.get<std::string>("thumb", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->performer = data.get<std::string>("performer", "");
    result->title = data.get<std::string>("title", "");
    return result;
}

std::string TgTypeParser::parseInputMediaAudio(const InputMediaAudio::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMedia(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "thumb", object->thumb);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "title", object->title);
    // The last comma will be erased by parseInputMedia().
    return result;
}

InputMediaDocument::Ptr TgTypeParser::parseJsonAndGetInputMediaDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaDocument>());
    result->thumb = data.get<std::string>("thumb", "");
    result->disableContentTypeDetection = data.get<bool>("disable_content_type_detection", false);
    return result;
}

std::string TgTypeParser::parseInputMediaDocument(const InputMediaDocument::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMedia(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "thumb", object->thumb);
    appendToJson(result, "disable_content_type_detection", object->disableContentTypeDetection);
    // The last comma will be erased by parseInputMedia().
    return result;
}

Sticker::Ptr TgTypeParser::parseJsonAndGetSticker(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Sticker>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    std::string type = data.get<std::string>("type", "");
    if (type == "regular") {
        result->type = Sticker::Type::Regular;
    } else if (type == "mask") {
        result->type = Sticker::Type::Mask;
    } else if (type == "custom_emoji") {
        result->type = Sticker::Type::CustomEmoji;
    }
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->isAnimated = data.get<bool>("is_animated", false);
    result->isVideo = data.get<bool>("is_video", false);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->emoji = data.get<std::string>("emoji", "");
    result->setName = data.get<std::string>("set_name", "");
    result->premiumAnimation = tryParseJson<File>(&TgTypeParser::parseJsonAndGetFile, data, "premium_animation");
    result->maskPosition = tryParseJson<MaskPosition>(&TgTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    return result;
}

std::string TgTypeParser::parseSticker(const Sticker::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    if (object->type == Sticker::Type::Regular) {
        appendToJson(result, "type", "regular");
    } else if (object->type == Sticker::Type::Mask) {
        appendToJson(result, "type", "mask");
    } else if (object->type == Sticker::Type::CustomEmoji) {
        appendToJson(result, "type", "custom_emoji");
    }
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "is_animated", object->isAnimated);
    appendToJson(result, "is_video", object->isVideo);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "emoji", object->emoji);
    appendToJson(result, "set_name", object->setName);
    appendToJson(result, "premium_animation", parseFile(object->premiumAnimation));
    appendToJson(result, "mask_position", parseMaskPosition(object->maskPosition));
    appendToJson(result, "custom_emoji_id", object->customEmojiId);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

StickerSet::Ptr TgTypeParser::parseJsonAndGetStickerSet(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<StickerSet>());
    result->name = data.get<std::string>("name", "");
    result->title = data.get<std::string>("title", "");
    std::string type = data.get<std::string>("type", "");
    if (type == "regular") {
        result->type = StickerSet::Type::Regular;
    } else if (type == "mask") {
        result->type = StickerSet::Type::Mask;
    } else if (type == "custom_emoji") {
        result->type = StickerSet::Type::CustomEmoji;
    }
    result->isAnimated = data.get<bool>("is_animated", false);
    result->isVideo = data.get<bool>("is_video", false);
    result->stickers = parseJsonAndGetArray<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "stickers");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    return result;
}

std::string TgTypeParser::parseStickerSet(const StickerSet::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "name", object->name);
    appendToJson(result, "title", object->title);
    if (object->type == StickerSet::Type::Regular) {
        appendToJson(result, "type", "regular");
    } else if (object->type == StickerSet::Type::Mask) {
        appendToJson(result, "type", "mask");
    } else if (object->type == StickerSet::Type::CustomEmoji) {
        appendToJson(result, "type", "custom_emoji");
    }
    appendToJson(result, "is_animated", object->isAnimated);
    appendToJson(result, "is_video", object->isVideo);
    appendToJson(result, "stickers", parseArray(&TgTypeParser::parseSticker, object->stickers));
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    removeLastComma(result);
    result += '}';
    return result;
}

MaskPosition::Ptr TgTypeParser::parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MaskPosition>());
    result->point = data.get("point", "");
    result->xShift = data.get<float>("x_shift", 0);
    result->yShift = data.get<float>("y_shift", 0);
    result->scale = data.get<float>("scale", 0);
    return result;
}

std::string TgTypeParser::parseMaskPosition(const MaskPosition::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "point", object->point);
    appendToJson(result, "x_shift", object->xShift);
    appendToJson(result, "y_shift", object->yShift);
    appendToJson(result, "scale", object->scale);
    removeLastComma(result);
    result += '}';
    return result;
}

InlineQuery::Ptr TgTypeParser::parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InlineQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->query = data.get<std::string>("query", "");
    result->offset = data.get<std::string>("offset", "");
    result->chatType = data.get<std::string>("chat_type", "");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    return result;
}

std::string TgTypeParser::parseInlineQuery(const InlineQuery::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "query", object->query);
    appendToJson(result, "offset", object->offset);
    appendToJson(result, "chat_type", object->chatType);
    appendToJson(result, "location", parseLocation(object->location));
    removeLastComma(result);
    result += '}';
    return result;
}

InlineQueryResult::Ptr TgTypeParser::parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    InlineQueryResult::Ptr result;

    if (type == InlineQueryResultCachedAudio::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedAudio(data));
    } else if (type == InlineQueryResultCachedDocument::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedDocument(data));
    } else if (type == InlineQueryResultCachedGif::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedGif(data));
    } else if (type == InlineQueryResultCachedMpeg4Gif::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedMpeg4Gif(data));
    } else if (type == InlineQueryResultCachedPhoto::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedPhoto(data));
    } else if (type == InlineQueryResultCachedSticker::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedSticker(data));
    } else if (type == InlineQueryResultCachedVideo::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedVideo(data));
    } else if (type == InlineQueryResultCachedVoice::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedVoice(data));
    } else if (type == InlineQueryResultArticle::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultArticle(data));
    } else if (type == InlineQueryResultAudio::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultAudio(data));
    } else if (type == InlineQueryResultContact::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultContact(data));
    } else if (type == InlineQueryResultGame::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultGame(data));
    } else if (type == InlineQueryResultDocument::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultDocument(data));
    } else if (type == InlineQueryResultLocation::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultLocation(data));
    } else if (type == InlineQueryResultVenue::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVenue(data));
    } else if (type == InlineQueryResultVoice::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVoice(data));
    } else if (type == InlineQueryResultPhoto::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultPhoto(data));
    } else if (type == InlineQueryResultGif::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultGif(data));
    } else if (type == InlineQueryResultMpeg4Gif::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultMpeg4Gif(data));
    } else if (type == InlineQueryResultVideo::TYPE) {
        result = std::static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVideo(data));
    } else {
        result = std::make_shared<InlineQueryResult>();
    }

    result->type = type;
    result->id = data.get<std::string>("id", "");
    result->replyMarkup = tryParseJson<InlineKeyboardMarkup>(&TgTypeParser::parseJsonAndGetInlineKeyboardMarkup, data, "reply_markup");

    return result;
}

std::string TgTypeParser::parseInlineQueryResult(const InlineQueryResult::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "id", object->id);
    appendToJson(result, "reply_markup", parseInlineKeyboardMarkup(object->replyMarkup));

    if (object->type == InlineQueryResultCachedAudio::TYPE) {
        result += parseInlineQueryResultCachedAudio(std::static_pointer_cast<InlineQueryResultCachedAudio>(object));
    } else if (object->type == InlineQueryResultCachedDocument::TYPE) {
        result += parseInlineQueryResultCachedDocument(std::static_pointer_cast<InlineQueryResultCachedDocument>(object));
    } else if (object->type == InlineQueryResultCachedGif::TYPE) {
        result += parseInlineQueryResultCachedGif(std::static_pointer_cast<InlineQueryResultCachedGif>(object));
    } else if (object->type == InlineQueryResultCachedMpeg4Gif::TYPE) {
        result += parseInlineQueryResultCachedMpeg4Gif(std::static_pointer_cast<InlineQueryResultCachedMpeg4Gif>(object));
    } else if (object->type == InlineQueryResultCachedPhoto::TYPE) {
        result += parseInlineQueryResultCachedPhoto(std::static_pointer_cast<InlineQueryResultCachedPhoto>(object));
    } else if (object->type == InlineQueryResultCachedSticker::TYPE) {
        result += parseInlineQueryResultCachedSticker(std::static_pointer_cast<InlineQueryResultCachedSticker>(object));
    } else if (object->type == InlineQueryResultCachedVideo::TYPE) {
        result += parseInlineQueryResultCachedVideo(std::static_pointer_cast<InlineQueryResultCachedVideo>(object));
    } else if (object->type == InlineQueryResultCachedVoice::TYPE) {
        result += parseInlineQueryResultCachedVoice(std::static_pointer_cast<InlineQueryResultCachedVoice>(object));
    } else if (object->type == InlineQueryResultArticle::TYPE) {
        result += parseInlineQueryResultArticle(std::static_pointer_cast<InlineQueryResultArticle>(object));
    } else if (object->type == InlineQueryResultAudio::TYPE) {
        result += parseInlineQueryResultAudio(std::static_pointer_cast<InlineQueryResultAudio>(object));
    } else if (object->type == InlineQueryResultContact::TYPE) {
        result += parseInlineQueryResultContact(std::static_pointer_cast<InlineQueryResultContact>(object));
    } else if (object->type == InlineQueryResultGame::TYPE) {
        result += parseInlineQueryResultGame(std::static_pointer_cast<InlineQueryResultGame>(object));
    } else if (object->type == InlineQueryResultDocument::TYPE) {
        result += parseInlineQueryResultDocument(std::static_pointer_cast<InlineQueryResultDocument>(object));
    } else if (object->type == InlineQueryResultLocation::TYPE) {
        result += parseInlineQueryResultLocation(std::static_pointer_cast<InlineQueryResultLocation>(object));
    } else if (object->type == InlineQueryResultVenue::TYPE) {
        result += parseInlineQueryResultVenue(std::static_pointer_cast<InlineQueryResultVenue>(object));
    } else if (object->type == InlineQueryResultVoice::TYPE) {
        result += parseInlineQueryResultVoice(std::static_pointer_cast<InlineQueryResultVoice>(object));
    } else if (object->type == InlineQueryResultPhoto::TYPE) {
        result += parseInlineQueryResultPhoto(std::static_pointer_cast<InlineQueryResultPhoto>(object));
    } else if (object->type == InlineQueryResultGif::TYPE) {
        result += parseInlineQueryResultGif(std::static_pointer_cast<InlineQueryResultGif>(object));
    } else if (object->type == InlineQueryResultMpeg4Gif::TYPE) {
        result += parseInlineQueryResultMpeg4Gif(std::static_pointer_cast<InlineQueryResultMpeg4Gif>(object));
    } else if (object->type == InlineQueryResultVideo::TYPE) {
        result += parseInlineQueryResultVideo(std::static_pointer_cast<InlineQueryResultVideo>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InlineQueryResultArticle::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultArticle>());
    result->title = data.get<std::string>("title", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->url = data.get<std::string>("url", "");
    result->hideUrl = data.get<bool>("hide_url", false);
    result->description = data.get<std::string>("description", "");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbWidth = data.get<std::int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<std::int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "title", object->title);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    appendToJson(result, "url", object->url);
    appendToJson(result, "hide_url", object->hideUrl);
    appendToJson(result, "description", object->description);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultPhoto>());
    result->photoUrl = data.get<std::string>("photo_url", "");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->photoWidth = data.get<std::int32_t>("photo_width", 0);
    result->photoHeight = data.get<std::int32_t>("photo_height", 0);
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "photo_url", object->photoUrl);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "photo_width", object->photoWidth);
    appendToJson(result, "photo_height", object->photoHeight);
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultGif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultGif>());
    result->gifUrl = data.get<std::string>("gif_url", "");
    result->gifWidth = data.get<std::int32_t>("gif_width", 0);
    result->gifHeight = data.get<std::int32_t>("gif_height", 0);
    result->gifDuration = data.get<std::int32_t>("gif_duration", 0);
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbMimeType = data.get<std::string>("thumb_mime_type", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "gif_url", object->gifUrl);
    appendToJson(result, "gif_width", object->gifWidth);
    appendToJson(result, "gif_height", object->gifHeight);
    appendToJson(result, "gif_duration", object->gifDuration);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_mime_type", object->thumbMimeType);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultMpeg4Gif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultMpeg4Gif>());
    result->mpeg4Url = data.get<std::string>("mpeg4_url", "");
    result->mpeg4Width = data.get<std::int32_t>("mpeg4_width", 0);
    result->mpeg4Height = data.get<std::int32_t>("mpeg4_height", 0);
    result->mpeg4Duration = data.get<std::int32_t>("mpeg4_duration", 0);
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbMimeType = data.get<std::string>("thumb_mime_type", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "mpeg4_url", object->mpeg4Url);
    appendToJson(result, "mpeg4_width", object->mpeg4Width);
    appendToJson(result, "mpeg4_height", object->mpeg4Height);
    appendToJson(result, "mpeg4_duration", object->mpeg4Duration);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_mime_type", object->thumbMimeType);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVideo::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultVideo>());
    result->videoUrl = data.get<std::string>("video_url", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->videoWidth = data.get<std::int32_t>("video_width", 0);
    result->videoHeight = data.get<std::int32_t>("video_height", 0);
    result->videoDuration = data.get<std::int32_t>("video_duration", 0);
    result->description = data.get<std::string>("description", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "video_url", object->videoUrl);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "video_width", object->videoWidth);
    appendToJson(result, "video_height", object->videoHeight);
    appendToJson(result, "video_duration", object->videoDuration);
    appendToJson(result, "description", object->description);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultAudio::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultAudio>());
    result->audioUrl = data.get<std::string>("audio_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->performer = data.get<std::string>("performer", "");
    result->audioDuration = data.get<std::int32_t>("audio_duration", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "audio_url", object->audioUrl);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "audio_duration", object->audioDuration);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVoice::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultVoice>());
    result->voiceUrl = data.get<std::string>("voice_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->voiceDuration = data.get<std::int32_t>("voice_duration", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "voice_url", object->voiceUrl);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "voice_duration", object->voiceDuration);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultDocument::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultDocument>());
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->documentUrl = data.get<std::string>("document_url", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->description = data.get<std::string>("description", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbWidth = data.get<std::int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<std::int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "document_url", object->documentUrl);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "description", object->description);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultLocation::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultLocation>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->title = data.get<std::string>("title", "");
    result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
    result->livePeriod = data.get<std::int32_t>("live_period", 0);
    result->heading = data.get<std::int32_t>("heading", 0);
    result->proximityAlertRadius = data.get<std::int32_t>("proximity_alert_radius", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbWidth = data.get<std::int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<std::int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "title", object->title);
    appendToJson(result, "horizontal_accuracy", object->horizontalAccuracy);
    appendToJson(result, "live_period", object->livePeriod);
    appendToJson(result, "heading", object->heading);
    appendToJson(result, "proximity_alert_radius", object->proximityAlertRadius);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVenue::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultVenue>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->title = data.get<std::string>("title", "");
    result->address = data.get<std::string>("address", "");
    result->foursquareId = data.get<std::string>("foursquare_id", "");
    result->foursquareType = data.get<std::string>("foursquare_type", "");
    result->googlePlaceId = data.get<std::string>("google_place_id", "");
    result->googlePlaceType = data.get<std::string>("google_place_type", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbWidth = data.get<std::int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<std::int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "title", object->title);
    appendToJson(result, "address", object->address);
    appendToJson(result, "foursquare_id", object->foursquareId);
    appendToJson(result, "foursquare_type", object->foursquareType);
    appendToJson(result, "google_place_id", object->googlePlaceId);
    appendToJson(result, "google_place_type", object->googlePlaceType);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultContact::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultContact>());
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->vcard = data.get<std::string>("vcard", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbUrl = data.get<std::string>("thumb_url", "");
    result->thumbWidth = data.get<std::int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<std::int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "vcard", object->vcard);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultGame::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultGame>());
    result->gameShortName = data.get<std::string>("game_short_name", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "game_short_name", object->gameShortName);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedPhoto>());
    result->photoFileId = data.get<std::string>("photo_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "photo_file_id", object->photoFileId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedGif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedGif>());
    result->gifFileId = data.get<std::string>("gif_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "gif_file_id", object->gifFileId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedMpeg4Gif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedMpeg4Gif>());
    result->mpeg4FileId = data.get<std::string>("mpeg4_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "mpeg4_file_id", object->mpeg4FileId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedSticker::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedSticker>());
    result->stickerFileId = data.get<std::string>("sticker_file_id", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "sticker_file_id", object->stickerFileId);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedDocument::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedDocument>());
    result->title = data.get<std::string>("title", "");
    result->documentFileId = data.get<std::string>("document_file_id", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "title", object->title);
    appendToJson(result, "document_file_id", object->documentFileId);
    appendToJson(result, "description", object->description);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedVideo::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedVideo>());
    result->videoFileId = data.get<std::string>("video_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "video_file_id", object->videoFileId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedVoice::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedVoice>());
    result->voiceFileId = data.get<std::string>("voice_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "voice_file_id", object->voiceFileId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedAudio::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedAudio>());
    result->audioFileId = data.get<std::string>("audio_file_id", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "audio_file_id", object->audioFileId);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&TgTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InputMessageContent::Ptr TgTypeParser::parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data) const {
    InputMessageContent::Ptr result;

    std::string messageText = data.get<std::string>("message_text", "");
    float latitude = data.get<float>("latitude", 1000); // latitude belong (-90,90)
    std::string address = data.get<std::string>("address", "");
    std::string phoneNumber = data.get<std::string>("phone_number", "");
    std::string description = data.get<std::string>("description", "");

    if (!messageText.empty()) {
        result = std::static_pointer_cast<InputMessageContent>(parseJsonAndGetInputTextMessageContent(data));
    } else if (!address.empty()) {
        result = std::static_pointer_cast<InputMessageContent>(parseJsonAndGetInputVenueMessageContent(data));
    } else if (latitude != 1000) {
        result = std::static_pointer_cast<InputMessageContent>(parseJsonAndGetInputLocationMessageContent(data));
    } else if (!phoneNumber.empty()) {
        result = std::static_pointer_cast<InputMessageContent>(parseJsonAndGetInputContactMessageContent(data));
    } else if (!description.empty()) {
        result = std::static_pointer_cast<InputMessageContent>(parseJsonAndGetInputInvoiceMessageContent(data));
    } else {
        result = std::make_shared<InputMessageContent>();
    }

    return result;
}

std::string TgTypeParser::parseInputMessageContent(const InputMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';

    if (object->type == InputTextMessageContent::TYPE) {
        result += parseInputTextMessageContent(std::static_pointer_cast<InputTextMessageContent>(object));
    } else if (object->type == InputLocationMessageContent::TYPE) {
        result += parseInputLocationMessageContent(std::static_pointer_cast<InputLocationMessageContent>(object));
    } else if (object->type == InputVenueMessageContent::TYPE) {
        result += parseInputVenueMessageContent(std::static_pointer_cast<InputVenueMessageContent>(object));
    } else if (object->type == InputContactMessageContent::TYPE) {
        result += parseInputContactMessageContent(std::static_pointer_cast<InputContactMessageContent>(object));
    } else if (object->type == InputInvoiceMessageContent::TYPE) {
        result += parseInputInvoiceMessageContent(std::static_pointer_cast<InputInvoiceMessageContent>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InputTextMessageContent::Ptr TgTypeParser::parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputTextMessageContent>());
    result->messageText = data.get<std::string>("message_text", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->disableWebPagePreview = data.get<bool>("disable_web_page_preview", false);
    return result;
}

std::string TgTypeParser::parseInputTextMessageContent(const InputTextMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "message_text", object->messageText);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "entities", parseArray(&TgTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "disable_web_page_preview", object->disableWebPagePreview);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputLocationMessageContent::Ptr TgTypeParser::parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputLocationMessageContent>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
    result->livePeriod = data.get<std::int32_t>("live_period", 0);
    result->heading = data.get<std::int32_t>("heading", 0);
    result->proximityAlertRadius = data.get<std::int32_t>("proximity_alert_radius", 0);
    return result;
}

std::string TgTypeParser::parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "horizontal_accuracy", object->horizontalAccuracy);
    appendToJson(result, "live_period", object->livePeriod);
    appendToJson(result, "heading", object->heading);
    appendToJson(result, "proximity_alert_radius", object->proximityAlertRadius);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputVenueMessageContent::Ptr TgTypeParser::parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputVenueMessageContent>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->title = data.get<std::string>("title", "");
    result->address = data.get<std::string>("address", "");
    result->foursquareId = data.get<std::string>("foursquare_id", "");
    result->foursquareType = data.get<std::string>("foursquare_type", "");
    result->googlePlaceId = data.get<std::string>("google_place_id", "");
    result->googlePlaceType = data.get<std::string>("google_place_type", "");
    return result;
}

std::string TgTypeParser::parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "title", object->title);
    appendToJson(result, "address", object->address);
    appendToJson(result, "foursquare_id", object->foursquareId);
    appendToJson(result, "foursquare_type", object->foursquareType);
    appendToJson(result, "google_place_id", object->googlePlaceId);
    appendToJson(result, "google_place_type", object->googlePlaceType);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputContactMessageContent::Ptr TgTypeParser::parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputContactMessageContent>());
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->vcard = data.get<std::string>("vcard", "");
    return result;
}

std::string TgTypeParser::parseInputContactMessageContent(const InputContactMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "vcard", object->vcard);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputInvoiceMessageContent::Ptr TgTypeParser::parseJsonAndGetInputInvoiceMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputInvoiceMessageContent>());
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->payload = data.get<std::string>("payload", "");
    result->providerToken = data.get<std::string>("provider_token", "");
    result->currency = data.get<std::string>("currency", "");
    result->prices = parseJsonAndGetArray<LabeledPrice>(&TgTypeParser::parseJsonAndGetLabeledPrice, data, "prices");
    result->maxTipAmount = data.get<std::int32_t>("max_tip_amount", 0);
    result->suggestedTipAmounts = parseJsonAndGetArray<std::int32_t>(
        [] (const boost::property_tree::ptree& innerData)->std::int32_t {
        return innerData.get<std::int32_t>("");
    }, data, "suggested_tip_amounts");
    result->providerData = data.get<std::string>("provider_data", "");
    result->photoUrl = data.get<std::string>("photo_url", "");
    result->photoSize = data.get<std::int32_t>("photo_size", 0);
    result->photoWidth = data.get<std::int32_t>("photo_width", 0);
    result->photoHeight = data.get<std::int32_t>("photo_height", 0);
    result->needName = data.get<bool>("need_name", false);
    result->needPhoneNumber = data.get<bool>("need_phone_number", false);
    result->needEmail = data.get<bool>("need_email", false);
    result->needShippingAddress = data.get<bool>("need_shipping_address", false);
    result->sendPhoneNumberToProvider = data.get<bool>("send_phone_number_to_provider", false);
    result->sendEmailToProvider = data.get<bool>("send_email_to_provider", false);
    result->isFlexible = data.get<bool>("is_flexible", false);
    return result;
}

std::string TgTypeParser::parseInputInvoiceMessageContent(const InputInvoiceMessageContent::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "payload", object->payload);
    appendToJson(result, "provider_token", object->providerToken);
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "prices", parseArray(&TgTypeParser::parseLabeledPrice, object->prices));
    appendToJson(result, "max_tip_amount", object->maxTipAmount);
    appendToJson(result, "suggested_tip_amounts", parseArray<std::int32_t>([] (std::int32_t i)->std::int32_t {
        return i;
    }, object->suggestedTipAmounts));
    appendToJson(result, "provider_data", object->providerData);
    appendToJson(result, "photo_url", object->photoUrl);
    appendToJson(result, "photo_size", object->photoSize);
    appendToJson(result, "photo_width", object->photoWidth);
    appendToJson(result, "photo_height", object->photoHeight);
    appendToJson(result, "need_name", object->needName);
    appendToJson(result, "need_phone_number", object->needPhoneNumber);
    appendToJson(result, "need_email", object->needEmail);
    appendToJson(result, "need_shipping_address", object->needShippingAddress);
    appendToJson(result, "send_phone_number_to_provider", object->sendPhoneNumberToProvider);
    appendToJson(result, "send_email_to_provider", object->sendEmailToProvider);
    appendToJson(result, "is_flexible", object->isFlexible);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

ChosenInlineResult::Ptr TgTypeParser::parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChosenInlineResult>());
    result->resultId = data.get<std::string>("result_id", "");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    result->query = data.get<std::string>("query", "");
    return result;
}

std::string TgTypeParser::parseChosenInlineResult(const ChosenInlineResult::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "result_id", object->resultId);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "query", object->query);
    removeLastComma(result);
    result += '}';
    return result;
}

SentWebAppMessage::Ptr TgTypeParser::parseJsonAndGetSentWebAppMessage(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<SentWebAppMessage>());
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    return result;
}

std::string TgTypeParser::parseSentWebAppMessage(const SentWebAppMessage::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "inline_message_id", object->inlineMessageId);
    removeLastComma(result);
    result += '}';
    return result;
}

LabeledPrice::Ptr TgTypeParser::parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<LabeledPrice>());
    result->label = data.get<std::string>("label");
    result->amount = data.get<std::int32_t>("amount");
    return result;
}

std::string TgTypeParser::parseLabeledPrice(const LabeledPrice::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "label", object->label);
    appendToJson(result, "amount", object->amount);
    removeLastComma(result);
    result += '}';
    return result;
}

Invoice::Ptr TgTypeParser::parseJsonAndGetInvoice(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Invoice>());
    result->title = data.get<std::string>("title");
    result->description = data.get<std::string>("description");
    result->startParameter = data.get<std::string>("start_parameter");
    result->currency = data.get<std::string>("currency");
    result->totalAmount = data.get<std::int32_t>("total_amount");
    return result;
}

std::string TgTypeParser::parseInvoice(const Invoice::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "start_parameter", object->startParameter);
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingAddress::Ptr TgTypeParser::parseJsonAndGetShippingAddress(const boost::property_tree::ptree& data) const {
    ShippingAddress::Ptr result;
    result->countryCode = data.get<std::string>("country_code");
    result->state = data.get<std::string>("state", "");
    result->city = data.get<std::string>("city");
    result->streetLine1 = data.get<std::string>("street_line1");
    result->streetLine2 = data.get<std::string>("street_line2");
    result->postCode = data.get<std::string>("post_code");
    return result;
}

std::string TgTypeParser::parseShippingAddress(const ShippingAddress::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "country_code", object->countryCode);
    if (!object->state.empty()) {
        appendToJson(result, "state", object->state);
    }
    appendToJson(result, "city", object->city);
    appendToJson(result, "street_line1", object->streetLine1);
    appendToJson(result, "street_line2", object->streetLine2);
    appendToJson(result, "post_code", object->postCode);
    removeLastComma(result);
    result += '}';
    return result;
}

OrderInfo::Ptr TgTypeParser::parseJsonAndGetOrderInfo(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<OrderInfo>());
    result->name = data.get<std::string>("name", "");
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->email = data.get<std::string>("email", "");
    result->shippingAddress = tryParseJson(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

std::string TgTypeParser::parseOrderInfo(const OrderInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    if (!object->name.empty()) {
        appendToJson(result, "name", object->name);
    }
    if (!object->phoneNumber.empty()) {
        appendToJson(result, "phone_number", object->phoneNumber);
    }
    if (!object->email.empty()) {
        appendToJson(result, "email", object->email);
    }
    if (!object->shippingAddress) {
        result += R"("shipping_address":)";
        result += parseShippingAddress(object->shippingAddress);
        result += ",";
    }
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingOption::Ptr TgTypeParser::parseJsonAndGetShippingOption(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ShippingOption>());
    result->id = data.get<std::string>("id");
    result->title = data.get<std::string>("title");
    result->prices = parseJsonAndGetArray<LabeledPrice>(&TgTypeParser::parseJsonAndGetLabeledPrice, data, "prices");
    return result;
}

std::string TgTypeParser::parseShippingOption(const ShippingOption::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "title", object->title);
    removeLastComma(result);
    result += R"("prices":)";
    result += parseArray(&TgTypeParser::parseLabeledPrice, object->prices);
    result += '}';
    return result;
}

SuccessfulPayment::Ptr TgTypeParser::parseJsonAndGetSuccessfulPayment(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<SuccessfulPayment>());
    result->currency = data.get<std::string>("currency");
    result->totalAmount = data.get<std::int32_t>("total_amount");
    result->invoicePayload = data.get<std::string>("invoice_payload");
    result->shippingOptionId = data.get<std::string>("shipping_option_id");
    result->orderInfo = tryParseJson(&TgTypeParser::parseJsonAndGetOrderInfo, data, "order_info");
    return result;
}

std::string TgTypeParser::parseSuccessfulPayment(const SuccessfulPayment::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    appendToJson(result, "invoice_payload", object->invoicePayload);
    appendToJson(result, "shipping_option_id", object->shippingOptionId);
    result += R"("order_info":)";
    result += parseOrderInfo(object->orderInfo);
    result += ",";
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingQuery::Ptr TgTypeParser::parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ShippingQuery>());
    result->id = data.get<std::string>("id");
    result->from = tryParseJson(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->invoicePayload = data.get<std::string>("invoice_payload");
    result->shippingAddress = tryParseJson(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

std::string TgTypeParser::parseShippingQuery(const ShippingQuery::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    result += R"("from":)";
    result += parseUser(object->from);
    result += ",";
    appendToJson(result, "invoice_payload", object->invoicePayload);
    result += R"("shipping_address":)";
    result += parseShippingAddress(object->shippingAddress);
    result += ",";
    removeLastComma(result);
    result += '}';
    return result;
}

PreCheckoutQuery::Ptr TgTypeParser::parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PreCheckoutQuery>());
    result->id = data.get<std::string>("id");
    result->from = tryParseJson(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->currency = data.get<std::string>("currency");
    result->totalAmount = data.get<std::int32_t>("total_amount");
    return result;
}

std::string TgTypeParser::parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    result += R"("user":)";
    result += parseUser(object->from);
    result += ",";
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    removeLastComma(result);
    result += '}';
    return result;
}

PassportData::Ptr TgTypeParser::parseJsonAndGetPassportData(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PassportData>());
    result->data = parseJsonAndGetArray<EncryptedPassportElement>(&TgTypeParser::parseJsonAndGetEncryptedPassportElement, data, "data");
    result->credentials = tryParseJson(&TgTypeParser::parseJsonAndGetEncryptedCredentials, data, "credentials");
    return result;
}

std::string TgTypeParser::parsePassportData(const PassportData::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "data", parseArray(&TgTypeParser::parseEncryptedPassportElement, object->data));
    appendToJson(result, "credentials", parseEncryptedCredentials(object->credentials));
    removeLastComma(result);
    result += '}';
    return result;
}

PassportFile::Ptr TgTypeParser::parseJsonAndGetPassportFile(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PassportFile>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    result->fileDate = data.get<std::int32_t>("file_date", 0);
    return result;
}

std::string TgTypeParser::parsePassportFile(const PassportFile::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_unique_id", object->fileUniqueId);
    appendToJson(result, "file_size", object->fileSize);
    appendToJson(result, "file_date", object->fileDate);
    removeLastComma(result);
    result += '}';
    return result;
}

EncryptedPassportElement::Ptr TgTypeParser::parseJsonAndGetEncryptedPassportElement(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<EncryptedPassportElement>());
    result->type = data.get<std::string>("type", "");
    result->data = data.get<std::string>("data", "");
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->email = data.get<std::string>("email", "");
    result->files = parseJsonAndGetArray<PassportFile>(&TgTypeParser::parseJsonAndGetPassportFile, data, "files");
    result->frontSide = tryParseJson(&TgTypeParser::parseJsonAndGetPassportFile, data, "front_side");
    result->reverseSide = tryParseJson(&TgTypeParser::parseJsonAndGetPassportFile, data, "reverse_side");
    result->selfie = tryParseJson(&TgTypeParser::parseJsonAndGetPassportFile, data, "selfie");
    result->translation = parseJsonAndGetArray<PassportFile>(&TgTypeParser::parseJsonAndGetPassportFile, data, "translation");
    result->hash = data.get<std::string>("hash", "");
    return result;
}

std::string TgTypeParser::parseEncryptedPassportElement(const EncryptedPassportElement::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "data", object->data);
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "email", object->email);
    appendToJson(result, "files", parseArray(&TgTypeParser::parsePassportFile, object->files));
    appendToJson(result, "front_side", parsePassportFile(object->frontSide));
    appendToJson(result, "reverse_side", parsePassportFile(object->reverseSide));
    appendToJson(result, "selfie", parsePassportFile(object->selfie));
    appendToJson(result, "translation", parseArray(&TgTypeParser::parsePassportFile, object->translation));
    appendToJson(result, "hash", object->hash);
    removeLastComma(result);
    result += '}';
    return result;
}

EncryptedCredentials::Ptr TgTypeParser::parseJsonAndGetEncryptedCredentials(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<EncryptedCredentials>());
    result->data = data.get<std::string>("data", "");
    result->hash = data.get<std::string>("hash", "");
    result->secret = data.get<std::string>("secret", "");
    return result;
}

std::string TgTypeParser::parseEncryptedCredentials(const EncryptedCredentials::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "data", object->data);
    appendToJson(result, "hash", object->hash);
    appendToJson(result, "secret", object->secret);
    removeLastComma(result);
    result += '}';
    return result;
}

PassportElementError::Ptr TgTypeParser::parseJsonAndGetPassportElementError(const boost::property_tree::ptree& data) const {
    std::string source = data.get<std::string>("source", "");
    PassportElementError::Ptr result;

    if (source == PassportElementErrorDataField::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorDataField(data));
    } else if (source == PassportElementErrorFrontSide::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorFrontSide(data));
    } else if (source == PassportElementErrorReverseSide::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorReverseSide(data));
    } else if (source == PassportElementErrorSelfie::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorSelfie(data));
    } else if (source == PassportElementErrorFile::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorFile(data));
    } else if (source == PassportElementErrorFiles::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorFiles(data));
    } else if (source == PassportElementErrorTranslationFile::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorTranslationFile(data));
    } else if (source == PassportElementErrorTranslationFiles::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorTranslationFiles(data));
    } else if (source == PassportElementErrorUnspecified::SOURCE) {
        result = std::static_pointer_cast<PassportElementError>(parseJsonAndGetPassportElementErrorUnspecified(data));
    } else {
        result = std::make_shared<PassportElementError>();
    }

    result->source = data.get<std::string>("source", "");
    result->type = data.get<std::string>("type", "");
    result->message = data.get<std::string>("message", "");

    return result;
}

std::string TgTypeParser::parsePassportElementError(const PassportElementError::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "source", object->source);
    appendToJson(result, "type", object->type);
    appendToJson(result, "message", object->message);

    if (object->source == PassportElementErrorDataField::SOURCE) {
        result += parsePassportElementErrorDataField(std::static_pointer_cast<PassportElementErrorDataField>(object));
    } else if (object->source == PassportElementErrorFrontSide::SOURCE) {
        result += parsePassportElementErrorFrontSide(std::static_pointer_cast<PassportElementErrorFrontSide>(object));
    } else if (object->source == PassportElementErrorReverseSide::SOURCE) {
        result += parsePassportElementErrorReverseSide(std::static_pointer_cast<PassportElementErrorReverseSide>(object));
    } else if (object->source == PassportElementErrorSelfie::SOURCE) {
        result += parsePassportElementErrorSelfie(std::static_pointer_cast<PassportElementErrorSelfie>(object));
    } else if (object->source == PassportElementErrorFile::SOURCE) {
        result += parsePassportElementErrorFile(std::static_pointer_cast<PassportElementErrorFile>(object));
    } else if (object->source == PassportElementErrorFiles::SOURCE) {
        result += parsePassportElementErrorFiles(std::static_pointer_cast<PassportElementErrorFiles>(object));
    } else if (object->source == PassportElementErrorTranslationFile::SOURCE) {
        result += parsePassportElementErrorTranslationFile(std::static_pointer_cast<PassportElementErrorTranslationFile>(object));
    } else if (object->source == PassportElementErrorTranslationFiles::SOURCE) {
        result += parsePassportElementErrorTranslationFiles(std::static_pointer_cast<PassportElementErrorTranslationFiles>(object));
    } else if (object->source == PassportElementErrorUnspecified::SOURCE) {
        result += parsePassportElementErrorUnspecified(std::static_pointer_cast<PassportElementErrorUnspecified>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

PassportElementErrorDataField::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorDataField(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorDataField>());
    result->fieldName = data.get<std::string>("field_name", "");
    result->dataHash = data.get<std::string>("data_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorDataField(const PassportElementErrorDataField::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "field_name", object->fieldName);
    appendToJson(result, "data_hash", object->dataHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorFrontSide::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorFrontSide(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorFrontSide>());
    result->fileHash = data.get<std::string>("file_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorFrontSide(const PassportElementErrorFrontSide::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hash", object->fileHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorReverseSide::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorReverseSide(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorReverseSide>());
    result->fileHash = data.get<std::string>("file_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorReverseSide(const PassportElementErrorReverseSide::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hash", object->fileHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorSelfie::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorSelfie(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorSelfie>());
    result->fileHash = data.get<std::string>("file_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorSelfie(const PassportElementErrorSelfie::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hash", object->fileHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorFile::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorFile(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorFile>());
    result->fileHash = data.get<std::string>("file_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorFile(const PassportElementErrorFile::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hash", object->fileHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorFiles::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorFiles(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorFiles>());
    result->fileHashes = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "file_hashes");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorFiles(const PassportElementErrorFiles::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hashes",
                 parseArray<std::string>([] (const std::string& s)->std::string {
        return s;
    }, object->fileHashes));
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorTranslationFile::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorTranslationFile(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorTranslationFile>());
    result->fileHash = data.get<std::string>("file_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorTranslationFile(const PassportElementErrorTranslationFile::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hash", object->fileHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorTranslationFiles::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorTranslationFiles(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorTranslationFiles>());
    result->fileHashes = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "file_hashes");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorTranslationFiles(const PassportElementErrorTranslationFiles::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "file_hashes",
                 parseArray<std::string>([] (const std::string& s)->std::string {
        return s;
    }, object->fileHashes));
    // The last comma will be erased by parsePassportElementError().
    return result;
}

PassportElementErrorUnspecified::Ptr TgTypeParser::parseJsonAndGetPassportElementErrorUnspecified(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetPassportElementError().
    auto result(std::make_shared<PassportElementErrorUnspecified>());
    result->elementHash = data.get<std::string>("element_hash", "");
    return result;
}

std::string TgTypeParser::parsePassportElementErrorUnspecified(const PassportElementErrorUnspecified::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parsePassportElementError(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "element_hash", object->elementHash);
    // The last comma will be erased by parsePassportElementError().
    return result;
}

Game::Ptr TgTypeParser::parseJsonAndGetGame(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Game>());
    result->title = data.get("title", "");
    result->description = data.get("description", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->text = data.get("text", "");
    result->textEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "text_entities");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    return result;
}

std::string TgTypeParser::parseGame(const Game::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "text", object->text);
    appendToJson(result, "text_entities", parseArray(&TgTypeParser::parseMessageEntity, object->textEntities));
    appendToJson(result, "animation", parseAnimation(object->animation));
    removeLastComma(result);
    result += '}';
    return result;
}

CallbackGame::Ptr TgTypeParser::parseJsonAndGetCallbackGame(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<CallbackGame>());
    return result;
}

std::string TgTypeParser::parseCallbackGame(const CallbackGame::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    result += '}';
    return result;
}

GameHighScore::Ptr TgTypeParser::parseJsonAndGetGameHighScore(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GameHighScore>());
    result->position = data.get("position", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->score = data.get<std::int32_t>("score", 0);
    return result;
}

std::string TgTypeParser::parseGameHighScore(const GameHighScore::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "position", object->position);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "score", object->score);
    removeLastComma(result);
    result += '}';
    return result;
}

GenericReply::Ptr TgTypeParser::parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const {
    if (data.find("force_reply") != data.not_found()) {
        return std::static_pointer_cast<GenericReply>(parseJsonAndGetForceReply(data));
    } else if (data.find("remove_keyboard") != data.not_found()) {
        return std::static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardRemove(data));
    } else if (data.find("keyboard") != data.not_found()) {
        return std::static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardMarkup(data));
    } else if (data.find("inline_keyboard") != data.not_found()) {
        return std::static_pointer_cast<GenericReply>(parseJsonAndGetInlineKeyboardMarkup(data));
    }
    return std::make_shared<GenericReply>();
}

std::string TgTypeParser::parseGenericReply(const GenericReply::Ptr& object) const {
    if (!object) {
        return "";
    }
    if (std::dynamic_pointer_cast<ForceReply>(object) != nullptr) {
        return parseForceReply(std::static_pointer_cast<ForceReply>(object));
    } else if (std::dynamic_pointer_cast<ReplyKeyboardRemove>(object) != nullptr) {
        return parseReplyKeyboardRemove(std::static_pointer_cast<ReplyKeyboardRemove>(object));
    } else if (std::dynamic_pointer_cast<ReplyKeyboardMarkup>(object) != nullptr) {
        return parseReplyKeyboardMarkup(std::static_pointer_cast<ReplyKeyboardMarkup>(object));
    } else if (std::dynamic_pointer_cast<InlineKeyboardMarkup>(object) != nullptr) {
        return parseInlineKeyboardMarkup(std::static_pointer_cast<InlineKeyboardMarkup>(object));
    }
    return "";
}

void TgTypeParser::appendToJson(std::string& json, const std::string& varName, const std::string& value) const {
    if (value.empty()) {
        return;
    }
    json += '"';
    json += varName;
    json += R"(":)";
    if (value.front() != '{') {
        json += '"';
    }
    json += value;
    if (value.back() != '}') {
        json += '"';
    }
    json += ',';
}
}
