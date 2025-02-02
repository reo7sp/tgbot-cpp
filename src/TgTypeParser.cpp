#include "tgbot/TgTypeParser.h"

namespace TgBot {

Update::Ptr TgTypeParser::parseJsonAndGetUpdate(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Update>());
    result->updateId = data.get<std::int32_t>("update_id", 0);
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->editedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_message");
    result->channelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "channel_post");
    result->editedChannelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_channel_post");
    result->businessConnection = tryParseJson<BusinessConnection>(&TgTypeParser::parseJsonAndGetBusinessConnection, data, "business_connection");
    result->businessMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "business_message");
    result->editedBusinessMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_business_message");
    result->deletedBusinessMessages = tryParseJson<BusinessMessagesDeleted>(&TgTypeParser::parseJsonAndGetBusinessMessagesDeleted, data, "deleted_business_messages");
    result->messageReaction = tryParseJson<MessageReactionUpdated>(&TgTypeParser::parseJsonAndGetMessageReactionUpdated, data, "message_reaction");
    result->messageReactionCount = tryParseJson<MessageReactionCountUpdated>(&TgTypeParser::parseJsonAndGetMessageReactionCountUpdated, data, "message_reaction_count");
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
    result->chatBoost = tryParseJson<ChatBoostUpdated>(&TgTypeParser::parseJsonAndGetChatBoostUpdated, data, "chat_boost");
    result->removedChatBoost = tryParseJson<ChatBoostRemoved>(&TgTypeParser::parseJsonAndGetChatBoostRemoved, data, "removed_chat_boost");
    result->successfulPayment = tryParseJson<SuccessfulPayment>(&TgTypeParser::parseJsonAndGetSuccessfulPayment, data, "successful_payment");
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
    appendToJson(result, "business_connection", parseBusinessConnection(object->businessConnection));
    appendToJson(result, "business_message", parseMessage(object->businessMessage));
    appendToJson(result, "edited_business_message", parseMessage(object->editedBusinessMessage));
    appendToJson(result, "deleted_business_messages", parseBusinessMessagesDeleted(object->deletedBusinessMessages));
    appendToJson(result, "message_reaction", parseMessageReactionUpdated(object->messageReaction));
    appendToJson(result, "message_reaction_count", parseMessageReactionCountUpdated(object->messageReactionCount));
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
    appendToJson(result, "chat_boost", parseChatBoostUpdated(object->chatBoost));
    appendToJson(result, "removed_chat_boost", parseChatBoostRemoved(object->removedChatBoost));
    appendToJson(result, "successful_payment", parseSuccessfulPayment(object->successfulPayment));
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
    }, data, "allowed_updates");
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
    appendToJson(result, "allowed_updates", parseArray<std::string>(
        [] (const std::string& s)->std::string {
        return s;
    }, object->allowedUpdates));
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
    result->canConnectToBusiness = data.get<bool>("can_connect_to_business", false);
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
    appendToJson(result, "can_connect_to_business", object->canConnectToBusiness);
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
    result->birthdate = tryParseJson<Birthdate>(&TgTypeParser::parseJsonAndGetBirthdate, data, "birthdate");
    result->businessIntro = tryParseJson<BusinessIntro>(&TgTypeParser::parseJsonAndGetBusinessIntro, data, "business_intro");
    result->businessLocation = tryParseJson<BusinessLocation>(&TgTypeParser::parseJsonAndGetBusinessLocation, data, "business_location");
    result->businessOpeningHours = tryParseJson<BusinessOpeningHours>(&TgTypeParser::parseJsonAndGetBusinessOpeningHours, data, "business_opening_hours");
    result->personalChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "personal_chat");
    result->availableReactions = parseJsonAndGetArray<ReactionType>(&TgTypeParser::parseJsonAndGetReactionType, data, "available_reactions");
    result->accentColorId = data.get<std::int32_t>("accent_color_id", 0);
    result->backgroundCustomEmojiId = data.get<std::string>("background_custom_emoji_id", "");
    result->profileAccentColorId = data.get<std::int32_t>("profile_accent_color_id", 0);
    result->profileBackgroundCustomEmojiId = data.get<std::string>("profile_background_custom_emoji_id", "");
    result->emojiStatusCustomEmojiId = data.get<std::string>("emoji_status_custom_emoji_id", "");
    result->emojiStatusExpirationDate = data.get<std::uint32_t>("emoji_status_expiration_date", 0);
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
    result->unrestrictBoostCount = data.get<std::int32_t>("unrestrict_boost_count", 0);
    result->messageAutoDeleteTime = data.get<std::int32_t>("message_auto_delete_time", 0);
    result->hasAggressiveAntiSpamEnabled = data.get<bool>("has_aggressive_anti_spam_enabled", false);
    result->hasHiddenMembers = data.get<bool>("has_hidden_members", false);
    result->hasProtectedContent = data.get<bool>("has_protected_content", false);
    result->hasVisibleHistory = data.get<bool>("has_visible_history", false);
    result->stickerSetName = data.get<std::string>("sticker_set_name", "");
    result->canSetStickerSet = data.get<bool>("can_set_sticker_set", false);
    result->customEmojiStickerSetName = data.get<std::string>("custom_emoji_sticker_set_name", "");
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
    appendToJson(result, "active_usernames", parseArray<std::string>(
        [] (const std::string& s)->std::string {
        return s;
    }, object->activeUsernames));
    appendToJson(result, "birthdate", parseBirthdate(object->birthdate));
    appendToJson(result, "business_intro", parseBusinessIntro(object->businessIntro));
    appendToJson(result, "business_location", parseBusinessLocation(object->businessLocation));
    appendToJson(result, "business_opening_hours", parseBusinessOpeningHours(object->businessOpeningHours));
    appendToJson(result, "personal_chat", parseChat(object->personalChat));
    appendToJson(result, "available_reactions", parseArray(&TgTypeParser::parseReactionType, object->availableReactions));
    appendToJson(result, "accent_color_id", object->accentColorId);
    appendToJson(result, "background_custom_emoji_id", object->backgroundCustomEmojiId);
    appendToJson(result, "profile_accent_color_id", object->profileAccentColorId);
    appendToJson(result, "profile_background_custom_emoji_id", object->profileBackgroundCustomEmojiId);
    appendToJson(result, "emoji_status_custom_emoji_id", object->emojiStatusCustomEmojiId);
    appendToJson(result, "emoji_status_expiration_date", object->emojiStatusExpirationDate);
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
    appendToJson(result, "unrestrict_boost_count", object->unrestrictBoostCount);
    appendToJson(result, "message_auto_delete_time", object->messageAutoDeleteTime);
    appendToJson(result, "has_aggressive_anti_spam_enabled", object->hasAggressiveAntiSpamEnabled);
    appendToJson(result, "has_hidden_members", object->hasHiddenMembers);
    appendToJson(result, "has_protected_content", object->hasProtectedContent);
    appendToJson(result, "has_visible_history", object->hasVisibleHistory);
    appendToJson(result, "sticker_set_name", object->stickerSetName);
    appendToJson(result, "can_set_sticker_set", object->canSetStickerSet);
    appendToJson(result, "custom_emoji_sticker_set_name", object->customEmojiStickerSetName);
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
    result->senderBoostCount = data.get<std::int32_t>("sender_boost_count", 0);
    result->senderBusinessBot = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "sender_business_bot");
    result->date = data.get<std::uint32_t>("date", 0);
    result->businessConnectionId = data.get<std::string>("business_connection_id", "");
    result->chat = parseJsonAndGetChat(data.find("chat")->second);
    result->forwardOrigin = tryParseJson<MessageOrigin>(&TgTypeParser::parseJsonAndGetMessageOrigin, data, "forward_origin");
    result->isTopicMessage = data.get<bool>("is_topic_message", false);
    result->isAutomaticForward = data.get<bool>("is_automatic_forward", false);
    result->replyToMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "reply_to_message");
    result->externalReply = tryParseJson<ExternalReplyInfo>(&TgTypeParser::parseJsonAndGetExternalReplyInfo, data, "external_reply");
    result->quote = tryParseJson<TextQuote>(&TgTypeParser::parseJsonAndGetTextQuote, data, "quote");
    result->replyToStory = tryParseJson<Story>(&TgTypeParser::parseJsonAndGetStory, data, "reply_to_story");
    result->viaBot = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "via_bot");
    result->editDate = data.get<std::uint32_t>("edit_date", 0);
    result->hasProtectedContent = data.get<bool>("has_protected_content", false);
    result->isFromOffline = data.get<bool>("is_from_offline", false);
    result->mediaGroupId = data.get<std::string>("media_group_id", "");
    result->authorSignature = data.get<std::string>("author_signature", "");
    result->text = data.get<std::string>("text", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->linkPreviewOptions = tryParseJson<LinkPreviewOptions>(&TgTypeParser::parseJsonAndGetLinkPreviewOptions, data, "link_preview_options");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
    result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
    result->story = tryParseJson<Story>(&TgTypeParser::parseJsonAndGetStory, data, "story");
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
    result->usersShared = tryParseJson<UsersShared>(&TgTypeParser::parseJsonAndGetUsersShared, data, "users_shared");
    result->chatShared = tryParseJson<ChatShared>(&TgTypeParser::parseJsonAndGetChatShared, data, "chat_shared");
    result->connectedWebsite = data.get<std::string>("connected_website", "");
    result->writeAccessAllowed = tryParseJson<WriteAccessAllowed>(&TgTypeParser::parseJsonAndGetWriteAccessAllowed, data, "write_access_allowed");
    result->passportData = tryParseJson<PassportData>(&TgTypeParser::parseJsonAndGetPassportData, data, "passport_data");
    result->proximityAlertTriggered = tryParseJson<ProximityAlertTriggered>(&TgTypeParser::parseJsonAndGetProximityAlertTriggered, data, "proximity_alert_triggered");
    result->boostAdded = tryParseJson<ChatBoostAdded>(&TgTypeParser::parseJsonAndGetChatBoostAdded, data, "boost_added");
    result->forumTopicCreated = tryParseJson<ForumTopicCreated>(&TgTypeParser::parseJsonAndGetForumTopicCreated, data, "forum_topic_created");
    result->forumTopicEdited = tryParseJson<ForumTopicEdited>(&TgTypeParser::parseJsonAndGetForumTopicEdited, data, "forum_topic_edited");
    result->forumTopicClosed = tryParseJson<ForumTopicClosed>(&TgTypeParser::parseJsonAndGetForumTopicClosed, data, "forum_topic_closed");
    result->forumTopicReopened = tryParseJson<ForumTopicReopened>(&TgTypeParser::parseJsonAndGetForumTopicReopened, data, "forum_topic_reopened");
    result->generalForumTopicHidden = tryParseJson<GeneralForumTopicHidden>(&TgTypeParser::parseJsonAndGetGeneralForumTopicHidden, data, "general_forum_topic_hidden");
    result->generalForumTopicUnhidden = tryParseJson<GeneralForumTopicUnhidden>(&TgTypeParser::parseJsonAndGetGeneralForumTopicUnhidden, data, "general_forum_topic_unhidden");
    result->giveawayCreated = tryParseJson<GiveawayCreated>(&TgTypeParser::parseJsonAndGetGiveawayCreated, data, "giveaway_created");
    result->giveaway = tryParseJson<Giveaway>(&TgTypeParser::parseJsonAndGetGiveaway, data, "giveaway");
    result->giveawayWinners = tryParseJson<GiveawayWinners>(&TgTypeParser::parseJsonAndGetGiveawayWinners, data, "giveaway_winners");
    result->giveawayCompleted = tryParseJson<GiveawayCompleted>(&TgTypeParser::parseJsonAndGetGiveawayCompleted, data, "giveaway_completed");
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
    appendToJson(result, "sender_boost_count", object->senderBoostCount);
    appendToJson(result, "sender_business_bot", parseUser(object->senderBusinessBot));
    appendToJson(result, "date", object->date);
    appendToJson(result, "business_connection_id", object->businessConnectionId);
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "forward_origin", parseMessageOrigin(object->forwardOrigin));
    appendToJson(result, "is_topic_message", object->isTopicMessage);
    appendToJson(result, "is_automatic_forward", object->isAutomaticForward);
    appendToJson(result, "reply_to_message", parseMessage(object->replyToMessage));
    appendToJson(result, "external_reply", parseExternalReplyInfo(object->externalReply));
    appendToJson(result, "quote", parseTextQuote(object->quote));
    appendToJson(result, "reply_to_story", parseStory(object->replyToStory));
    appendToJson(result, "via_bot", parseUser(object->viaBot));
    appendToJson(result, "edit_date", object->editDate);
    appendToJson(result, "has_protected_content", object->hasProtectedContent);
    appendToJson(result, "is_from_offline", object->isFromOffline);
    appendToJson(result, "media_group_id", object->mediaGroupId);
    appendToJson(result, "author_signature", object->authorSignature);
    appendToJson(result, "text", object->text);
    appendToJson(result, "entities", parseArray(&TgTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "link_preview_options", parseLinkPreviewOptions(object->linkPreviewOptions));
    appendToJson(result, "animation", parseAnimation(object->animation));
    appendToJson(result, "audio", parseAudio(object->audio));
    appendToJson(result, "document", parseDocument(object->document));
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "sticker", parseSticker(object->sticker));
    appendToJson(result, "story", parseStory(object->story));
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
    appendToJson(result, "users_shared", parseUsersShared(object->usersShared));
    appendToJson(result, "chat_shared", parseChatShared(object->chatShared));
    appendToJson(result, "connected_website", object->connectedWebsite);
    appendToJson(result, "write_access_allowed", parseWriteAccessAllowed(object->writeAccessAllowed));
    appendToJson(result, "passport_data", parsePassportData(object->passportData));
    appendToJson(result, "proximity_alert_triggered", parseProximityAlertTriggered(object->proximityAlertTriggered));
    appendToJson(result, "boost_added", parseChatBoostAdded(object->boostAdded));
    appendToJson(result, "forum_topic_created", parseForumTopicCreated(object->forumTopicCreated));
    appendToJson(result, "forum_topic_edited", parseForumTopicEdited(object->forumTopicEdited));
    appendToJson(result, "forum_topic_closed", parseForumTopicClosed(object->forumTopicClosed));
    appendToJson(result, "forum_topic_reopened", parseForumTopicReopened(object->forumTopicReopened));
    appendToJson(result, "general_forum_topic_hidden", parseGeneralForumTopicHidden(object->generalForumTopicHidden));
    appendToJson(result, "general_forum_topic_unhidden", parseGeneralForumTopicUnhidden(object->generalForumTopicUnhidden));
    appendToJson(result, "giveaway_created", parseGiveawayCreated(object->giveawayCreated));
    appendToJson(result, "giveaway", parseGiveaway(object->giveaway));
    appendToJson(result, "giveaway_winners", parseGiveawayWinners(object->giveawayWinners));
    appendToJson(result, "giveaway_completed", parseGiveawayCompleted(object->giveawayCompleted));
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

InaccessibleMessage::Ptr TgTypeParser::parseJsonAndGetInaccessibleMessage(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InaccessibleMessage>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->date = data.get<std::uint8_t>("date", 0);
    return result;
}

std::string TgTypeParser::parseInaccessibleMessage(const InaccessibleMessage::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "date", object->date);
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
    } else if (type == "blockquote") {
        result->type = MessageEntity::Type::Blockquote;
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
    } else if (object->type == MessageEntity::Type::Blockquote) {
        appendToJson(result, "type", "blockquote");
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

TextQuote::Ptr TgTypeParser::parseJsonAndGetTextQuote(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<TextQuote>());
    result->text = data.get<std::string>("text", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->position = data.get<std::int32_t>("position", 0);
    result->isManual = data.get<bool>("is_manual", false);
    return result;
}

std::string TgTypeParser::parseTextQuote(const TextQuote::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "entities", parseArray(&TgTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "position", object->position);
    appendToJson(result, "is_manual", object->isManual);
    removeLastComma(result);
    result += '}';
    return result;
}

ExternalReplyInfo::Ptr TgTypeParser::parseJsonAndGetExternalReplyInfo(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ExternalReplyInfo>());
    result->origin = tryParseJson<MessageOrigin>(&TgTypeParser::parseJsonAndGetMessageOrigin, data, "origin");
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->linkPreviewOptions = tryParseJson<LinkPreviewOptions>(&TgTypeParser::parseJsonAndGetLinkPreviewOptions, data, "link_preview_options");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
    result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
    result->story = tryParseJson<Story>(&TgTypeParser::parseJsonAndGetStory, data, "story");
    result->video = tryParseJson<Video>(&TgTypeParser::parseJsonAndGetVideo, data, "video");
    result->videoNote = tryParseJson<VideoNote>(&TgTypeParser::parseJsonAndGetVideoNote, data, "video_note");
    result->voice = tryParseJson<Voice>(&TgTypeParser::parseJsonAndGetVoice, data, "voice");
    result->hasMediaSpoiler = data.get<bool>("has_media_spoiler", false);
    result->contact = tryParseJson<Contact>(&TgTypeParser::parseJsonAndGetContact, data, "contact");
    result->dice = tryParseJson<Dice>(&TgTypeParser::parseJsonAndGetDice, data, "dice");
    result->game = tryParseJson<Game>(&TgTypeParser::parseJsonAndGetGame, data, "game");
    result->giveaway = tryParseJson<Giveaway>(&TgTypeParser::parseJsonAndGetGiveaway, data, "giveaway");
    result->giveawayWinners = tryParseJson<GiveawayWinners>(&TgTypeParser::parseJsonAndGetGiveawayWinners, data, "giveaway_winners");
    result->invoice = tryParseJson<Invoice>(&TgTypeParser::parseJsonAndGetInvoice, data, "invoice");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->poll = tryParseJson<Poll>(&TgTypeParser::parseJsonAndGetPoll, data, "poll");
    result->venue = tryParseJson<Venue>(&TgTypeParser::parseJsonAndGetVenue, data, "venue");
    return result;
}

std::string TgTypeParser::parseExternalReplyInfo(const ExternalReplyInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "origin", parseMessageOrigin(object->origin));
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "link_preview_options", parseLinkPreviewOptions(object->linkPreviewOptions));
    appendToJson(result, "animation", parseAnimation(object->animation));
    appendToJson(result, "audio", parseAudio(object->audio));
    appendToJson(result, "document", parseDocument(object->document));
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "sticker", parseSticker(object->sticker));
    appendToJson(result, "story", parseStory(object->story));
    appendToJson(result, "video", parseVideo(object->video));
    appendToJson(result, "video_note", parseVideoNote(object->videoNote));
    appendToJson(result, "voice", parseVoice(object->voice));
    appendToJson(result, "has_media_spoiler", object->hasMediaSpoiler);
    appendToJson(result, "contact", parseContact(object->contact));
    appendToJson(result, "dice", parseDice(object->dice));
    appendToJson(result, "game", parseGame(object->game));
    appendToJson(result, "giveaway", parseGiveaway(object->giveaway));
    appendToJson(result, "giveaway_winners", parseGiveawayWinners(object->giveawayWinners));
    appendToJson(result, "invoice", parseInvoice(object->invoice));
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "poll", parsePoll(object->poll));
    appendToJson(result, "venue", parseVenue(object->venue));
    removeLastComma(result);
    result += '}';
    return result;
}

ReplyParameters::Ptr TgTypeParser::parseJsonAndGetReplyParameters(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ReplyParameters>());
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->allowSendingWithoutReply = data.get<bool>("allow_sending_without_reply", false);
    result->quote = data.get<std::string>("quote", "");
    result->quoteParseMode = data.get<std::string>("quote_parse_mode", "");
    result->quoteEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "quote_entities");
    result->quotePosition = data.get<std::int32_t>("quote_position", 0);
    return result;
}

std::string TgTypeParser::parseReplyParameters(const ReplyParameters::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "chat_id", object->chatId);
    appendToJson(result, "allow_sending_without_reply", object->allowSendingWithoutReply);
    appendToJson(result, "quote", object->quote);
    appendToJson(result, "quote_parse_mode", object->quoteParseMode);
    appendToJson(result, "quote_entities", parseArray(&TgTypeParser::parseMessageEntity, object->quoteEntities));
    appendToJson(result, "quote_position", object->quotePosition);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageOrigin::Ptr TgTypeParser::parseJsonAndGetMessageOrigin(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    MessageOrigin::Ptr result;

    if (type == MessageOriginUser::TYPE) {
        result = std::static_pointer_cast<MessageOrigin>(parseJsonAndGetMessageOriginUser(data));
    } else if (type == MessageOriginHiddenUser::TYPE) {
        result = std::static_pointer_cast<MessageOrigin>(parseJsonAndGetMessageOriginHiddenUser(data));
    } else if (type == MessageOriginChat::TYPE) {
        result = std::static_pointer_cast<MessageOrigin>(parseJsonAndGetMessageOriginChat(data));
    } else if (type == MessageOriginChannel::TYPE) {
        result = std::static_pointer_cast<MessageOrigin>(parseJsonAndGetMessageOriginChannel(data));
    } else {
        result = std::make_shared<MessageOrigin>();
    }

    result->type = type;
    result->date = data.get<std::int32_t>("date", 0);

    return result;
}

std::string TgTypeParser::parseMessageOrigin(const MessageOrigin::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "date", object->date);

    if (object->type == MessageOriginUser::TYPE) {
        result += parseMessageOriginUser(std::static_pointer_cast<MessageOriginUser>(object));
    } else if (object->type == MessageOriginHiddenUser::TYPE) {
        result += parseMessageOriginHiddenUser(std::static_pointer_cast<MessageOriginHiddenUser>(object));
    } else if (object->type == MessageOriginChat::TYPE) {
        result += parseMessageOriginChat(std::static_pointer_cast<MessageOriginChat>(object));
    } else if (object->type == MessageOriginChannel::TYPE) {
        result += parseMessageOriginChannel(std::static_pointer_cast<MessageOriginChannel>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

MessageOriginUser::Ptr TgTypeParser::parseJsonAndGetMessageOriginUser(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginUser>());
    result->senderUser = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "sender_user");
    return result;
}

std::string TgTypeParser::parseMessageOriginUser(const MessageOriginUser::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMessageOrigin(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "sender_user", parseUser(object->senderUser));
    // The last comma will be erased by parseMessageOrigin().
    return result;
}

MessageOriginHiddenUser::Ptr TgTypeParser::parseJsonAndGetMessageOriginHiddenUser(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginHiddenUser>());
    result->senderUserName = data.get<std::string>("sender_user_name", "");
    return result;
}

std::string TgTypeParser::parseMessageOriginHiddenUser(const MessageOriginHiddenUser::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMessageOrigin(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "sender_user_name", object->senderUserName);
    // The last comma will be erased by parseMessageOrigin().
    return result;
}

MessageOriginChat::Ptr TgTypeParser::parseJsonAndGetMessageOriginChat(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginChat>());
    result->senderChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "sender_chat");
    result->authorSignature = data.get<std::string>("author_signature", "");
    return result;
}

std::string TgTypeParser::parseMessageOriginChat(const MessageOriginChat::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMessageOrigin(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "sender_chat", parseChat(object->senderChat));
    appendToJson(result, "author_signature", object->authorSignature);
    // The last comma will be erased by parseMessageOrigin().
    return result;
}

MessageOriginChannel::Ptr TgTypeParser::parseJsonAndGetMessageOriginChannel(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginChannel>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->authorSignature = data.get<std::string>("author_signature", "");
    return result;
}

std::string TgTypeParser::parseMessageOriginChannel(const MessageOriginChannel::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseMessageOrigin(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "author_signature", object->authorSignature);
    // The last comma will be erased by parseMessageOrigin().
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
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
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
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
    removeLastComma(result);
    result += '}';
    return result;
}

Document::Ptr TgTypeParser::parseJsonAndGetDocument(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Document>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Story::Ptr TgTypeParser::parseJsonAndGetStory(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Story>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->id = data.get<std::int32_t>("id", 0);
    return result;
}

std::string TgTypeParser::parseStory(const Story::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "id", object->id);
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
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
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
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->fileSize = data.get<std::int32_t>("file_size", 0);
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
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
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->userId = data.get<std::int64_t>("user_id", 0);
    result->vcard = data.get<std::string>("vcard", "");
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
    result->text = data.get<std::string>("text", "");
    result->voterCount = data.get<std::int32_t>("voter_count", 0);
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
    result->voterChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "voter_chat");
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
    appendToJson(result, "voter_chat", parseChat(object->voterChat));
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "option_ids", parseArray<std::int32_t>(
        [] (std::int32_t i)->std::int32_t {
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
    result->isAnonymous = data.get<bool>("is_anonymous", false);
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
    appendToJson(result, "explanation", object->explanation);
    appendToJson(result, "explanation_entities", parseArray(&TgTypeParser::parseMessageEntity, object->explanationEntities));
    appendToJson(result, "open_period", object->openPeriod);
    appendToJson(result, "close_date", object->closeDate);
    removeLastComma(result);
    result += '}';
    return result;
}

Location::Ptr TgTypeParser::parseJsonAndGetLocation(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Location>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
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
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
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

ChatBoostAdded::Ptr TgTypeParser::parseJsonAndGetChatBoostAdded(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatBoostAdded>());
    result->boostCount = data.get<std::int32_t>("boost_count", 0);
    return result;
}

std::string TgTypeParser::parseChatBoostAdded(const ChatBoostAdded::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "boost_count", object->boostCount);
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

ForumTopicClosed::Ptr TgTypeParser::parseJsonAndGetForumTopicClosed(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<ForumTopicClosed>());
    return result;
}

std::string TgTypeParser::parseForumTopicClosed(const ForumTopicClosed::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
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

ForumTopicReopened::Ptr TgTypeParser::parseJsonAndGetForumTopicReopened(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<ForumTopicReopened>());
    return result;
}

std::string TgTypeParser::parseForumTopicReopened(const ForumTopicReopened::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

GeneralForumTopicHidden::Ptr TgTypeParser::parseJsonAndGetGeneralForumTopicHidden(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<GeneralForumTopicHidden>());
    return result;
}

std::string TgTypeParser::parseGeneralForumTopicHidden(const GeneralForumTopicHidden::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

GeneralForumTopicUnhidden::Ptr TgTypeParser::parseJsonAndGetGeneralForumTopicUnhidden(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<GeneralForumTopicUnhidden>());
    return result;
}

std::string TgTypeParser::parseGeneralForumTopicUnhidden(const GeneralForumTopicUnhidden::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

SharedUser::Ptr TgTypeParser::parseJsonAndGetSharedUser(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<SharedUser>());
    result->userId = data.get<std::int64_t>("user_id", 0);
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->username = data.get<std::string>("username", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    return result;
}

std::string TgTypeParser::parseSharedUser(const SharedUser::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "user_id", object->userId);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "username", object->username);
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    removeLastComma(result);
    result += '}';
    return result;
}

UsersShared::Ptr TgTypeParser::parseJsonAndGetUsersShared(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<UsersShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->users = parseJsonAndGetArray<SharedUser>(&TgTypeParser::parseJsonAndGetSharedUser, data, "users");
    return result;
}

std::string TgTypeParser::parseUsersShared(const UsersShared::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "users", parseArray(&TgTypeParser::parseSharedUser, object->users));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatShared::Ptr TgTypeParser::parseJsonAndGetChatShared(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->title = data.get<std::string>("title", "");
    result->username = data.get<std::string>("username", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    return result;
}

std::string TgTypeParser::parseChatShared(const ChatShared::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "chat_id", object->chatId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "username", object->username);
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    removeLastComma(result);
    result += '}';
    return result;
}

WriteAccessAllowed::Ptr TgTypeParser::parseJsonAndGetWriteAccessAllowed(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<WriteAccessAllowed>());
    result->fromRequest = data.get<bool>("from_request", false);
    result->webAppName = data.get<std::string>("web_app_name", "");
    result->fromAttachmentMenu = data.get<bool>("from_attachment_menu", false);
    return result;
}

std::string TgTypeParser::parseWriteAccessAllowed(const WriteAccessAllowed::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "from_request", object->fromRequest);
    appendToJson(result, "web_app_name", object->webAppName);
    appendToJson(result, "from_attachment_menu", object->fromAttachmentMenu);
    removeLastComma(result);
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

VideoChatStarted::Ptr TgTypeParser::parseJsonAndGetVideoChatStarted(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<VideoChatStarted>());
    return result;
}

std::string TgTypeParser::parseVideoChatStarted(const VideoChatStarted::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
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

GiveawayCreated::Ptr TgTypeParser::parseJsonAndGetGiveawayCreated(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<GiveawayCreated>());
    return result;
}

std::string TgTypeParser::parseGiveawayCreated(const GiveawayCreated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

Giveaway::Ptr TgTypeParser::parseJsonAndGetGiveaway(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Giveaway>());
    result->chats = parseJsonAndGetArray<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chats");
    result->winnersSelectionDate = data.get<std::uint32_t>("winners_selection_date", 0);
    result->winnerCount = data.get<std::int32_t>("winner_count", 0);
    result->onlyNewMembers = data.get<bool>("only_new_members", false);
    result->hasPublicWinners = data.get<bool>("has_public_winners", false);
    result->prizeDescription = data.get<std::string>("prize_description", "");
    result->countryCodes = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "country_codes");
    result->premiumSubscriptionMonthCount = data.get<std::int32_t>("premium_subscription_month_count", 0);
    return result;
}

std::string TgTypeParser::parseGiveaway(const Giveaway::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chats", parseArray(&TgTypeParser::parseChat, object->chats));
    appendToJson(result, "winners_selection_date", object->winnersSelectionDate);
    appendToJson(result, "winner_count", object->winnerCount);
    appendToJson(result, "only_new_members", object->onlyNewMembers);
    appendToJson(result, "has_public_winners", object->hasPublicWinners);
    appendToJson(result, "prize_description", object->prizeDescription);
    appendToJson(result, "country_codes", parseArray<std::string>(
        [] (const std::string& s)->std::string {
        return s;
    }, object->countryCodes));
    appendToJson(result, "premium_subscription_month_count", object->premiumSubscriptionMonthCount);
    removeLastComma(result);
    result += '}';
    return result;
}

GiveawayWinners::Ptr TgTypeParser::parseJsonAndGetGiveawayWinners(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GiveawayWinners>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
    result->winnersSelectionDate = data.get<std::uint32_t>("winners_selection_date", 0);
    result->winnerCount = data.get<std::int32_t>("winner_count", 0);
    result->winners = parseJsonAndGetArray<User>(&TgTypeParser::parseJsonAndGetUser, data, "winners");
    result->additionalChatCount = data.get<std::int32_t>("additional_chat_count", 0);
    result->premiumSubscriptionMonthCount = data.get<std::int32_t>("premium_subscription_month_count", 0);
    result->unclaimedPrizeCount = data.get<std::int32_t>("unclaimed_prize_count", 0);
    result->onlyNewMembers = data.get<bool>("only_new_members", false);
    result->wasRefunded = data.get<bool>("was_refunded", false);
    result->prizeDescription = data.get<std::string>("prize_description", "");
    return result;
}

std::string TgTypeParser::parseGiveawayWinners(const GiveawayWinners::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "giveaway_message_id", object->giveawayMessageId);
    appendToJson(result, "winners_selection_date", object->winnersSelectionDate);
    appendToJson(result, "winner_count", object->winnerCount);
    appendToJson(result, "winners", parseArray(&TgTypeParser::parseUser, object->winners));
    appendToJson(result, "additional_chat_count", object->additionalChatCount);
    appendToJson(result, "premium_subscription_month_count", object->premiumSubscriptionMonthCount);
    appendToJson(result, "unclaimed_prize_count", object->unclaimedPrizeCount);
    appendToJson(result, "only_new_members", object->onlyNewMembers);
    appendToJson(result, "was_refunded", object->wasRefunded);
    appendToJson(result, "prize_description", object->prizeDescription);
    removeLastComma(result);
    result += '}';
    return result;
}

GiveawayCompleted::Ptr TgTypeParser::parseJsonAndGetGiveawayCompleted(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GiveawayCompleted>());
    result->winnerCount = data.get<std::int32_t>("winner_count", 0);
    result->unclaimedPrizeCount = data.get<std::int32_t>("unclaimed_prize_count", 0);
    result->giveawayMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "giveaway_message");
    return result;
}

std::string TgTypeParser::parseGiveawayCompleted(const GiveawayCompleted::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "winner_count", object->winnerCount);
    appendToJson(result, "unclaimed_prize_count", object->unclaimedPrizeCount);
    appendToJson(result, "giveaway_message", parseMessage(object->giveawayMessage));
    removeLastComma(result);
    result += '}';
    return result;
}

LinkPreviewOptions::Ptr TgTypeParser::parseJsonAndGetLinkPreviewOptions(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<LinkPreviewOptions>());
    result->isDisabled = data.get<bool>("is_disabled", false);
    result->url = data.get<std::string>("url", "");
    result->preferSmallMedia = data.get<bool>("prefer_small_media", false);
    result->preferLargeMedia = data.get<bool>("prefer_large_media", false);
    result->showAboveText = data.get<bool>("show_above_text", false);
    return result;
}

std::string TgTypeParser::parseLinkPreviewOptions(const LinkPreviewOptions::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "is_disabled", object->isDisabled);
    appendToJson(result, "url", object->url);
    appendToJson(result, "prefer_small_media", object->preferSmallMedia);
    appendToJson(result, "prefer_large_media", object->preferLargeMedia);
    appendToJson(result, "show_above_text", object->showAboveText);
    removeLastComma(result);
    result += '}';
    return result;
}

UserProfilePhotos::Ptr TgTypeParser::parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<UserProfilePhotos>());
    result->totalCount = data.get<std::int32_t>("total_count", 0);
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
    result->requestUsers = tryParseJson<KeyboardButtonRequestUsers>(&TgTypeParser::parseJsonAndGetKeyboardButtonRequestUsers, data, "request_users");
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
    appendToJson(result, "request_users", parseKeyboardButtonRequestUsers(object->requestUsers));
    appendToJson(result, "request_chat", parseKeyboardButtonRequestChat(object->requestChat));
    appendToJson(result, "request_contact", object->requestContact);
    appendToJson(result, "request_location", object->requestLocation);
    appendToJson(result, "request_poll", parseKeyboardButtonPollType(object->requestPoll));
    appendToJson(result, "web_app", parseWebAppInfo(object->webApp));
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButtonRequestUsers::Ptr TgTypeParser::parseJsonAndGetKeyboardButtonRequestUsers(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<KeyboardButtonRequestUsers>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->userIsBot = data.get<bool>("user_is_bot", false);
    result->userIsPremium = data.get<bool>("user_is_premium", false);
    result->maxQuantity = data.get<std::uint8_t>("max_quantity", 1);
    result->requestName = data.get<bool>("request_name", false);
    result->requestUsername = data.get<bool>("request_username", false);
    result->requestPhoto = data.get<bool>("request_photo", false);
    return result;
}

std::string TgTypeParser::parseKeyboardButtonRequestUsers(const KeyboardButtonRequestUsers::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "user_is_bot", object->userIsBot);
    appendToJson(result, "user_is_premium", object->userIsPremium);
    appendToJson(result, "max_quantity", object->maxQuantity);
    appendToJson(result, "request_name", object->requestName);
    appendToJson(result, "request_username", object->requestUsername);
    appendToJson(result, "request_photo", object->requestPhoto);
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
    result->requestTitle = data.get<bool>("request_title", false);
    result->requestUsername = data.get<bool>("request_username", false);
    result->requestPhoto = data.get<bool>("request_photo", false);
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
    appendToJson(result, "request_title", object->requestTitle);
    appendToJson(result, "request_username", object->requestUsername);
    appendToJson(result, "request_photo", object->requestPhoto);
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
    result->removeKeyboard = data.get<bool>("remove_keyboard", false);
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
    result->switchInlineQueryChosenChat = tryParseJson<SwitchInlineQueryChosenChat>(&TgTypeParser::parseJsonAndGetSwitchInlineQueryChosenChat, data, "switch_inline_query_chosen_chat");
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
    appendToJson(result, "switch_inline_query_chosen_chat", parseSwitchInlineQueryChosenChat(object->switchInlineQueryChosenChat));
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

SwitchInlineQueryChosenChat::Ptr TgTypeParser::parseJsonAndGetSwitchInlineQueryChosenChat(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<SwitchInlineQueryChosenChat>());
    result->query = data.get<std::string>("query", "");
    result->allowUserChats = data.get<bool>("allow_user_chats", false);
    result->allowBotChats = data.get<bool>("allow_bot_chats", false);
    result->allowGroupChats = data.get<bool>("allow_group_chats", false);
    result->allowChannelChats = data.get<bool>("allow_channel_chats", false);
    return result;
}

std::string TgTypeParser::parseSwitchInlineQueryChosenChat(const SwitchInlineQueryChosenChat::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "query", object->query);
    appendToJson(result, "allow_user_chats", object->allowUserChats);
    appendToJson(result, "allow_bot_chats", object->allowBotChats);
    appendToJson(result, "allow_group_chats", object->allowGroupChats);
    appendToJson(result, "allow_channel_chats", object->allowChannelChats);
    removeLastComma(result);
    result += '}';
    return result;
}

CallbackQuery::Ptr TgTypeParser::parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<CallbackQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    result->chatInstance = data.get<std::string>("chat_instance", "");
    result->data = data.get<std::string>("data", "");
    result->gameShortName = data.get<std::string>("game_short_name", "");
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
    appendToJson(result, "data", object->data);
    appendToJson(result, "game_short_name", object->gameShortName);
    removeLastComma(result);
    result += '}';
    return result;
}

ForceReply::Ptr TgTypeParser::parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ForceReply>());
    result->forceReply = data.get<bool>("force_reply", false);
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
    result->canPostStories = data.get<bool>("can_post_stories", false);
    result->canEditStories = data.get<bool>("can_edit_stories", false);
    result->canDeleteStories = data.get<bool>("can_delete_stories", false);
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
    appendToJson(result, "can_post_stories", object->canPostStories);
    appendToJson(result, "can_edit_stories", object->canEditStories);
    appendToJson(result, "can_delete_stories", object->canDeleteStories);
    appendToJson(result, "can_post_messages", object->canPostMessages);
    appendToJson(result, "can_edit_messages", object->canEditMessages);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatMemberUpdated::Ptr TgTypeParser::parseJsonAndGetChatMemberUpdated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatMemberUpdated>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->date = data.get<std::uint32_t>("date", 0);
    result->oldChatMember = tryParseJson<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, data, "old_chat_member");
    result->newChatMember = tryParseJson<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, data, "new_chat_member");
    result->inviteLink = tryParseJson<ChatInviteLink>(&TgTypeParser::parseJsonAndGetChatInviteLink, data, "invite_link");
    result->viaChatFolderInviteLink = data.get<bool>("via_chat_folder_invite_link", false);
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
    appendToJson(result, "via_chat_folder_invite_link", object->viaChatFolderInviteLink);
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
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    result->customTitle = data.get<std::string>("custom_title", "");
    return result;
}

std::string TgTypeParser::parseChatMemberOwner(const ChatMemberOwner::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "is_anonymous", object->isAnonymous);
    appendToJson(result, "custom_title", object->customTitle);
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
    result->canPostStories = data.get<bool>("can_post_stories", false);
    result->canEditStories = data.get<bool>("can_edit_stories", false);
    result->canDeleteStories = data.get<bool>("can_delete_stories", false);
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
    appendToJson(result, "can_post_stories", object->canPostStories);
    appendToJson(result, "can_edit_stories", object->canEditStories);
    appendToJson(result, "can_delete_stories", object->canDeleteStories);
    appendToJson(result, "can_post_messages", object->canPostMessages);
    appendToJson(result, "can_edit_messages", object->canEditMessages);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    appendToJson(result, "can_manage_topics", object->canManageTopics);
    appendToJson(result, "custom_title", object->customTitle);
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberMember::Ptr TgTypeParser::parseJsonAndGetChatMemberMember(const boost::property_tree::ptree& /*data*/) const {
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

ChatMemberLeft::Ptr TgTypeParser::parseJsonAndGetChatMemberLeft(const boost::property_tree::ptree& /*data*/) const {
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
    result->untilDate = data.get<std::uint32_t>("until_date", 0);
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

Birthdate::Ptr TgTypeParser::parseJsonAndGetBirthdate(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<Birthdate>());
    result->day = data.get<std::uint8_t>("day", 0);
    result->month = data.get<std::uint8_t>("month", 0);
    result->year = data.get<std::uint16_t>("year", 0);
    return result;
}

std::string TgTypeParser::parseBirthdate(const Birthdate::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "day", object->day);
    appendToJson(result, "month", object->month);
    appendToJson(result, "year", object->year);
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessIntro::Ptr TgTypeParser::parseJsonAndGetBusinessIntro(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessIntro>());
    result->title = data.get<std::string>("title", "");
    result->message = data.get<std::string>("message", "");
    result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
    return result;
}

std::string TgTypeParser::parseBusinessIntro(const BusinessIntro::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "title", object->title);
    appendToJson(result, "message", object->message);
    appendToJson(result, "sticker", parseSticker(object->sticker));
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessLocation::Ptr TgTypeParser::parseJsonAndGetBusinessLocation(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessLocation>());
    result->address = data.get<std::string>("address", "");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    return result;
}

std::string TgTypeParser::parseBusinessLocation(const BusinessLocation::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "address", object->address);
    appendToJson(result, "location", parseLocation(object->location));
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessOpeningHoursInterval::Ptr TgTypeParser::parseJsonAndGetBusinessOpeningHoursInterval(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessOpeningHoursInterval>());
    result->openingMinute = data.get<std::int32_t>("opening_minute", 0);
    result->closingMinute = data.get<std::int32_t>("closing_minute", 0);
    return result;
}

std::string TgTypeParser::parseBusinessOpeningHoursInterval(const BusinessOpeningHoursInterval::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "opening_minute", object->openingMinute);
    appendToJson(result, "closing_minute", object->closingMinute);
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessOpeningHours::Ptr TgTypeParser::parseJsonAndGetBusinessOpeningHours(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessOpeningHours>());
    result->timeZoneName = data.get<std::string>("time_zone_name", "");
    result->openingHours = parseJsonAndGetArray<BusinessOpeningHoursInterval>(&TgTypeParser::parseJsonAndGetBusinessOpeningHoursInterval, data, "opening_hours");
    return result;
}

std::string TgTypeParser::parseBusinessOpeningHours(const BusinessOpeningHours::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "time_zone_name", object->timeZoneName);
    appendToJson(result, "opening_hours", parseArray(&TgTypeParser::parseBusinessOpeningHoursInterval, object->openingHours));
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

ReactionType::Ptr TgTypeParser::parseJsonAndGetReactionType(const boost::property_tree::ptree& data) const {
    std::string type = data.get<std::string>("type", "");
    ReactionType::Ptr result;

    if (type == ReactionTypeEmoji::TYPE) {
        result = std::static_pointer_cast<ReactionType>(parseJsonAndGetReactionTypeEmoji(data));
    } else if (type == ReactionTypeCustomEmoji::TYPE) {
        result = std::static_pointer_cast<ReactionType>(parseJsonAndGetReactionTypeCustomEmoji(data));
    } else {
        result = std::make_shared<ReactionType>();
    }

    result->type = type;

    return result;
}

std::string TgTypeParser::parseReactionType(const ReactionType::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);

    if (object->type == ReactionTypeEmoji::TYPE) {
        result += parseReactionTypeEmoji(std::static_pointer_cast<ReactionTypeEmoji>(object));
    } else if (object->type == ReactionTypeCustomEmoji::TYPE) {
        result += parseReactionTypeCustomEmoji(std::static_pointer_cast<ReactionTypeCustomEmoji>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

ReactionTypeEmoji::Ptr TgTypeParser::parseJsonAndGetReactionTypeEmoji(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetReactionType().
    auto result(std::make_shared<ReactionTypeEmoji>());
    result->emoji = data.get<std::string>("emoji", "");
    return result;
}

std::string TgTypeParser::parseReactionTypeEmoji(const ReactionTypeEmoji::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    // This function will be called by parseReactionType(), so I don't add
    // curly brackets to the result std::string.
    appendToJson(result, "emoji", object->emoji);
    // The last comma will be erased by parseReactionType().
    return result;
}

ReactionTypeCustomEmoji::Ptr TgTypeParser::parseJsonAndGetReactionTypeCustomEmoji(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetReactionType().
    auto result(std::make_shared<ReactionTypeCustomEmoji>());
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    return result;
}

std::string TgTypeParser::parseReactionTypeCustomEmoji(const ReactionTypeCustomEmoji::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    // This function will be called by parseReactionType(), so I don't add
    // curly brackets to the result std::string.
    appendToJson(result, "custom_emoji_id", object->customEmojiId);
    // The last comma will be erased by parseReactionType().
    return result;
}

ReactionCount::Ptr TgTypeParser::parseJsonAndGetReactionCount(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ReactionCount>());
    result->type = tryParseJson<ReactionType>(&TgTypeParser::parseJsonAndGetReactionType, data, "type");
    result->totalCount = data.get<std::int32_t>("total_count", 0);
    return result;
}

std::string TgTypeParser::parseReactionCount(const ReactionCount::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", parseReactionType(object->type));
    appendToJson(result, "total_count", object->totalCount);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageReactionUpdated::Ptr TgTypeParser::parseJsonAndGetMessageReactionUpdated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MessageReactionUpdated>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->actorChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "actor_chat");
    result->date = data.get<std::uint32_t>("date", 0);
    result->oldReaction = parseJsonAndGetArray<ReactionType>(&TgTypeParser::parseJsonAndGetReactionType, data, "old_reaction");
    result->newReaction = parseJsonAndGetArray<ReactionType>(&TgTypeParser::parseJsonAndGetReactionType, data, "new_reaction");
    return result;
}

std::string TgTypeParser::parseMessageReactionUpdated(const MessageReactionUpdated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "actor_chat", parseChat(object->actorChat));
    appendToJson(result, "date", object->date);
    appendToJson(result, "old_reaction", parseArray(&TgTypeParser::parseReactionType, object->oldReaction));
    appendToJson(result, "new_reaction", parseArray(&TgTypeParser::parseReactionType, object->newReaction));
    removeLastComma(result);
    result += '}';
    return result;
}

MessageReactionCountUpdated::Ptr TgTypeParser::parseJsonAndGetMessageReactionCountUpdated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MessageReactionCountUpdated>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->date = data.get<std::uint32_t>("date", 0);
    result->reactions = parseJsonAndGetArray<ReactionCount>(&TgTypeParser::parseJsonAndGetReactionCount, data, "reactions");
    return result;
}

std::string TgTypeParser::parseMessageReactionCountUpdated(const MessageReactionCountUpdated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "date", object->date);
    appendToJson(result, "reactions", parseArray(&TgTypeParser::parseReactionCount, object->reactions));
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
    result->command = data.get<std::string>("command", "");
    result->description = data.get<std::string>("description", "");
    return result;
}

std::string TgTypeParser::parseBotCommand(const BotCommand::Ptr& object) const {
    if (!object) {
        return "";
    }
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

BotCommandScopeDefault::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeDefault(const boost::property_tree::ptree& /*data*/) const {
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

BotCommandScopeAllPrivateChats::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllPrivateChats(const boost::property_tree::ptree& /*data*/) const {
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

BotCommandScopeAllGroupChats::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllGroupChats(const boost::property_tree::ptree& /*data*/) const {
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

BotCommandScopeAllChatAdministrators::Ptr TgTypeParser::parseJsonAndGetBotCommandScopeAllChatAdministrators(const boost::property_tree::ptree& /*data*/) const {
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

BotName::Ptr TgTypeParser::parseJsonAndGetBotName(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BotName>());
    result->name = data.get<std::string>("name", "");
    return result;
}

std::string TgTypeParser::parseBotName(const BotName::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "name", object->name);
    removeLastComma(result);
    result += '}';
    return result;
}

BotDescription::Ptr TgTypeParser::parseJsonAndGetBotDescription(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BotDescription>());
    result->description = data.get<std::string>("description", "");
    return result;
}

std::string TgTypeParser::parseBotDescription(const BotDescription::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "description", object->description);
    removeLastComma(result);
    result += '}';
    return result;
}

BotShortDescription::Ptr TgTypeParser::parseJsonAndGetBotShortDescription(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BotShortDescription>());
    result->shortDescription = data.get<std::string>("short_description", "");
    return result;
}

std::string TgTypeParser::parseBotShortDescription(const BotShortDescription::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "short_description", object->shortDescription);
    removeLastComma(result);
    result += '}';
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

MenuButtonCommands::Ptr TgTypeParser::parseJsonAndGetMenuButtonCommands(const boost::property_tree::ptree& /*data*/) const {
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

MenuButtonDefault::Ptr TgTypeParser::parseJsonAndGetMenuButtonDefault(const boost::property_tree::ptree& /*data*/) const {
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

ChatBoostSource::Ptr TgTypeParser::parseJsonAndGetChatBoostSource(const boost::property_tree::ptree& data) const {
    std::string source = data.get<std::string>("source", "");
    ChatBoostSource::Ptr result;

    if (source == ChatBoostSourcePremium::SOURCE) {
        result = std::static_pointer_cast<ChatBoostSource>(parseJsonAndGetChatBoostSourcePremium(data));
    } else if (source == ChatBoostSourceGiftCode::SOURCE) {
        result = std::static_pointer_cast<ChatBoostSource>(parseJsonAndGetChatBoostSourceGiftCode(data));
    } else if (source == ChatBoostSourceGiveaway::SOURCE) {
        result = std::static_pointer_cast<ChatBoostSource>(parseJsonAndGetChatBoostSourceGiveaway(data));
    } else {
        result = std::make_shared<ChatBoostSource>();
    }

    result->source = source;
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");

    return result;
}

std::string TgTypeParser::parseChatBoostSource(const ChatBoostSource::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "source", object->source);
    appendToJson(result, "user", parseUser(object->user));

    if (object->source == ChatBoostSourcePremium::SOURCE) {
        result += parseChatBoostSourcePremium(std::static_pointer_cast<ChatBoostSourcePremium>(object));
    } else if (object->source == ChatBoostSourceGiftCode::SOURCE) {
        result += parseChatBoostSourceGiftCode(std::static_pointer_cast<ChatBoostSourceGiftCode>(object));
    } else if (object->source == ChatBoostSourceGiveaway::SOURCE) {
        result += parseChatBoostSourceGiveaway(std::static_pointer_cast<ChatBoostSourceGiveaway>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

ChatBoostSourcePremium::Ptr TgTypeParser::parseJsonAndGetChatBoostSourcePremium(const boost::property_tree::ptree& /*data*/) const {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourcePremium>());
    return result;
}

std::string TgTypeParser::parseChatBoostSourcePremium(const ChatBoostSourcePremium::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatBoostSource(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatBoostSource().
    return result;
}

ChatBoostSourceGiftCode::Ptr TgTypeParser::parseJsonAndGetChatBoostSourceGiftCode(const boost::property_tree::ptree& /*data*/) const {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourceGiftCode>());
    return result;
}

std::string TgTypeParser::parseChatBoostSourceGiftCode(const ChatBoostSourceGiftCode::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatBoostSource(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatBoostSource().
    return result;
}

ChatBoostSourceGiveaway::Ptr TgTypeParser::parseJsonAndGetChatBoostSourceGiveaway(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourceGiveaway>());
    result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
    result->isUnclaimed = data.get<bool>("is_unclaimed", false);
    return result;
}

std::string TgTypeParser::parseChatBoostSourceGiveaway(const ChatBoostSourceGiveaway::Ptr& object) const {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatBoostSource(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "giveaway_message_id", object->giveawayMessageId);
    appendToJson(result, "is_unclaimed", object->isUnclaimed);
    // The last comma will be erased by parseChatBoostSource().
    return result;
}

ChatBoost::Ptr TgTypeParser::parseJsonAndGetChatBoost(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatBoost>());
    result->boostId = data.get<std::string>("boost_id", "");
    result->addDate = data.get<std::uint32_t>("add_date", 0);
    result->expirationDate = data.get<std::uint32_t>("expiration_date", 0);
    result->source = tryParseJson<ChatBoostSource>(&TgTypeParser::parseJsonAndGetChatBoostSource, data, "source");
    return result;
}

std::string TgTypeParser::parseChatBoost(const ChatBoost::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "boost_id", object->boostId);
    appendToJson(result, "add_date", object->addDate);
    appendToJson(result, "expiration_date", object->expirationDate);
    appendToJson(result, "source", parseChatBoostSource(object->source));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatBoostUpdated::Ptr TgTypeParser::parseJsonAndGetChatBoostUpdated(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatBoostUpdated>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->boost = tryParseJson<ChatBoost>(&TgTypeParser::parseJsonAndGetChatBoost, data, "boost");
    return result;
}

std::string TgTypeParser::parseChatBoostUpdated(const ChatBoostUpdated::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "boost", parseChatBoost(object->boost));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatBoostRemoved::Ptr TgTypeParser::parseJsonAndGetChatBoostRemoved(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ChatBoostRemoved>());
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->boostId = data.get<std::string>("boost_id", "");
    result->removeDate = data.get<std::uint32_t>("remove_date", 0);
    result->source = tryParseJson<ChatBoostSource>(&TgTypeParser::parseJsonAndGetChatBoostSource, data, "source");
    return result;
}

std::string TgTypeParser::parseChatBoostRemoved(const ChatBoostRemoved::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "boost_id", object->boostId);
    appendToJson(result, "remove_date", object->removeDate);
    appendToJson(result, "source", parseChatBoostSource(object->source));
    removeLastComma(result);
    result += '}';
    return result;
}

UserChatBoosts::Ptr TgTypeParser::parseJsonAndGetUserChatBoosts(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<UserChatBoosts>());
    result->boosts = parseJsonAndGetArray<ChatBoost>(&TgTypeParser::parseJsonAndGetChatBoost, data, "boosts");
    return result;
}

std::string TgTypeParser::parseUserChatBoosts(const UserChatBoosts::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "boosts", parseArray(&TgTypeParser::parseChatBoost, object->boosts));
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessConnection::Ptr TgTypeParser::parseJsonAndGetBusinessConnection(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessConnection>());
    result->id = data.get<std::string>("id", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->userChatId = data.get<std::int64_t>("user_chat_id", 0);
    result->date = data.get<std::uint32_t>("date", 0);
    result->canReply = data.get<bool>("can_reply", false);
    result->isEnabled = data.get<bool>("is_enabled", false);
    return result;
}

std::string TgTypeParser::parseBusinessConnection(const BusinessConnection::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "user_chat_id", object->userChatId);
    appendToJson(result, "date", object->date);
    appendToJson(result, "can_reply", object->canReply);
    appendToJson(result, "is_enabled", object->isEnabled);
    removeLastComma(result);
    result += '}';
    return result;
}

BusinessMessagesDeleted::Ptr TgTypeParser::parseJsonAndGetBusinessMessagesDeleted(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<BusinessMessagesDeleted>());
    result->businessConnectionId = data.get<std::string>("business_connection_id", "");
    result->chat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageIds = parseJsonAndGetArray<std::int32_t>(
        [] (const boost::property_tree::ptree& innerData)->std::int32_t {
        return innerData.get<std::int32_t>("");
    }, data, "message_ids");
    return result;
}

std::string TgTypeParser::parseBusinessMessagesDeleted(const BusinessMessagesDeleted::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "business_connection_id", object->businessConnectionId);
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "message_ids", parseArray<std::int32_t>(
        [] (std::int32_t i)->std::int32_t {
        return i;
    }, object->messageIds));
    removeLastComma(result);
    result += '}';
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
    result->thumbnail = data.get<std::string>("thumbnail", "");
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
    appendToJson(result, "thumbnail", object->thumbnail);
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
    result->thumbnail = data.get<std::string>("thumbnail", "");
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
    appendToJson(result, "thumbnail", object->thumbnail);
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
    result->thumbnail = data.get<std::string>("thumbnail", "");
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
    appendToJson(result, "thumbnail", object->thumbnail);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "title", object->title);
    // The last comma will be erased by parseInputMedia().
    return result;
}

InputMediaDocument::Ptr TgTypeParser::parseJsonAndGetInputMediaDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaDocument>());
    result->thumbnail = data.get<std::string>("thumbnail", "");
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
    appendToJson(result, "thumbnail", object->thumbnail);
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
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->emoji = data.get<std::string>("emoji", "");
    result->setName = data.get<std::string>("set_name", "");
    result->premiumAnimation = tryParseJson<File>(&TgTypeParser::parseJsonAndGetFile, data, "premium_animation");
    result->maskPosition = tryParseJson<MaskPosition>(&TgTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    result->needsRepainting = data.get<bool>("needs_repainting", true);
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
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
    appendToJson(result, "emoji", object->emoji);
    appendToJson(result, "set_name", object->setName);
    appendToJson(result, "premium_animation", parseFile(object->premiumAnimation));
    appendToJson(result, "mask_position", parseMaskPosition(object->maskPosition));
    appendToJson(result, "custom_emoji_id", object->customEmojiId);
    appendToJson(result, "needs_repainting", object->needsRepainting);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

StickerSet::Ptr TgTypeParser::parseJsonAndGetStickerSet(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<StickerSet>());
    result->name = data.get<std::string>("name", "");
    result->title = data.get<std::string>("title", "");
    std::string stickerType = data.get<std::string>("sticker_type", "");
    if (stickerType == "regular") {
        result->stickerType = StickerSet::Type::Regular;
    } else if (stickerType == "mask") {
        result->stickerType = StickerSet::Type::Mask;
    } else if (stickerType == "custom_emoji") {
        result->stickerType = StickerSet::Type::CustomEmoji;
    }
    result->stickers = parseJsonAndGetArray<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "stickers");
    result->thumbnail = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
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
    if (object->stickerType == StickerSet::Type::Regular) {
        appendToJson(result, "sticker_type", "regular");
    } else if (object->stickerType == StickerSet::Type::Mask) {
        appendToJson(result, "sticker_type", "mask");
    } else if (object->stickerType == StickerSet::Type::CustomEmoji) {
        appendToJson(result, "sticker_type", "custom_emoji");
    }
    appendToJson(result, "stickers", parseArray(&TgTypeParser::parseSticker, object->stickers));
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
    removeLastComma(result);
    result += '}';
    return result;
}

MaskPosition::Ptr TgTypeParser::parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<MaskPosition>());
    result->point = data.get<std::string>("point", "");
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

InputSticker::Ptr TgTypeParser::parseJsonAndGetInputSticker(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InputSticker>());
    result->sticker = data.get<std::string>("sticker", "");
    result->format = data.get<std::string>("format", "");
    result->emojiList = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "emoji_list");
    result->maskPosition = tryParseJson<MaskPosition>(&TgTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->keywords = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "keywords");
    return result;
}

std::string TgTypeParser::parseInputSticker(const InputSticker::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "sticker", object->sticker);
    appendToJson(result, "format", object->format);
    appendToJson(result, "emoji_list", parseArray<std::string>(
        [] (const std::string& s)->std::string {
        return s;
    }, object->emojiList));
    appendToJson(result, "mask_position", parseMaskPosition(object->maskPosition));
    appendToJson(result, "keywords", parseArray<std::string>(
        [] (const std::string& s)->std::string {
        return s;
    }, object->keywords));
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

InlineQueryResultsButton::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultsButton(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<InlineQueryResultsButton>());
    result->text = data.get<std::string>("text", "");
    result->webApp = tryParseJson<WebAppInfo>(&TgTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    result->startParameter = data.get<std::string>("start_parameter", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultsButton(const InlineQueryResultsButton::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "web_app", parseWebAppInfo(object->webApp));
    appendToJson(result, "start_parameter", object->startParameter);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_width", object->thumbnailWidth);
    appendToJson(result, "thumbnail_height", object->thumbnailHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultPhoto>());
    result->photoUrl = data.get<std::string>("photo_url", "");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailMimeType = data.get<std::string>("thumbnail_mime_type", "");
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_mime_type", object->thumbnailMimeType);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailMimeType = data.get<std::string>("thumbnail_mime_type", "");
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_mime_type", object->thumbnailMimeType);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_width", object->thumbnailWidth);
    appendToJson(result, "thumbnail_height", object->thumbnailHeight);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_width", object->thumbnailWidth);
    appendToJson(result, "thumbnail_height", object->thumbnailHeight);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_width", object->thumbnailWidth);
    appendToJson(result, "thumbnail_height", object->thumbnailHeight);
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
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
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
    appendToJson(result, "thumbnail_url", object->thumbnailUrl);
    appendToJson(result, "thumbnail_width", object->thumbnailWidth);
    appendToJson(result, "thumbnail_height", object->thumbnailHeight);
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
    result->linkPreviewOptions = tryParseJson<LinkPreviewOptions>(&TgTypeParser::parseJsonAndGetLinkPreviewOptions, data, "link_preview_options");
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
    appendToJson(result, "link_preview_options", parseLinkPreviewOptions(object->linkPreviewOptions));
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
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "inline_message_id", object->inlineMessageId);
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
    result->label = data.get<std::string>("label", "");
    result->amount = data.get<std::int32_t>("amount", 0);
    return result;
}

std::string TgTypeParser::parseLabeledPrice(const LabeledPrice::Ptr& object) const {
    if (!object) {
        return "";
    }
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
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->startParameter = data.get<std::string>("start_parameter", "");
    result->currency = data.get<std::string>("currency", "");
    result->totalAmount = data.get<std::int32_t>("total_amount", 0);
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
    auto result(std::make_shared<ShippingAddress>());
    result->countryCode = data.get<std::string>("country_code", "");
    result->state = data.get<std::string>("state", "");
    result->city = data.get<std::string>("city", "");
    result->streetLine1 = data.get<std::string>("street_line1", "");
    result->streetLine2 = data.get<std::string>("street_line2", "");
    result->postCode = data.get<std::string>("post_code", "");
    return result;
}

std::string TgTypeParser::parseShippingAddress(const ShippingAddress::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "country_code", object->countryCode);
    appendToJson(result, "state", object->state);
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
    result->shippingAddress = tryParseJson<ShippingAddress>(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

std::string TgTypeParser::parseOrderInfo(const OrderInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "name", object->name);
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "email", object->email);
    appendToJson(result, "shipping_address", parseShippingAddress(object->shippingAddress));
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingOption::Ptr TgTypeParser::parseJsonAndGetShippingOption(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ShippingOption>());
    result->id = data.get<std::string>("id", "");
    result->title = data.get<std::string>("title", "");
    result->prices = parseJsonAndGetArray<LabeledPrice>(&TgTypeParser::parseJsonAndGetLabeledPrice, data, "prices");
    return result;
}

std::string TgTypeParser::parseShippingOption(const ShippingOption::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "title", object->title);
    appendToJson(result, "prices", parseArray(&TgTypeParser::parseLabeledPrice, object->prices));
    removeLastComma(result);
    result += '}';
    return result;
}

SuccessfulPayment::Ptr TgTypeParser::parseJsonAndGetSuccessfulPayment(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<SuccessfulPayment>());
    result->currency = data.get<std::string>("currency", "");
    result->totalAmount = data.get<std::int32_t>("total_amount", 0);
    result->invoicePayload = data.get<std::string>("invoice_payload", "");
    result->shippingOptionId = data.get<std::string>("shipping_option_id", "");
    result->orderInfo = tryParseJson<OrderInfo>(&TgTypeParser::parseJsonAndGetOrderInfo, data, "order_info");
    result->telegramPaymentChargeId = data.get<std::string>("telegram_payment_charge_id", "");
    result->providerPaymentChargeId = data.get<std::string>("provider_payment_charge_id", "");
    return result;
}

std::string TgTypeParser::parseSuccessfulPayment(const SuccessfulPayment::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    appendToJson(result, "invoice_payload", object->invoicePayload);
    appendToJson(result, "shipping_option_id", object->shippingOptionId);
    appendToJson(result, "order_info", parseOrderInfo(object->orderInfo));
    appendToJson(result, "telegram_payment_charge_id", object->telegramPaymentChargeId);
    appendToJson(result, "provider_payment_charge_id", object->providerPaymentChargeId);
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingQuery::Ptr TgTypeParser::parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<ShippingQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->invoicePayload = data.get<std::string>("invoice_payload", "");
    result->shippingAddress = tryParseJson<ShippingAddress>(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

std::string TgTypeParser::parseShippingQuery(const ShippingQuery::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "invoice_payload", object->invoicePayload);
    appendToJson(result, "shipping_address", parseShippingAddress(object->shippingAddress));
    removeLastComma(result);
    result += '}';
    return result;
}

PreCheckoutQuery::Ptr TgTypeParser::parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PreCheckoutQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->currency = data.get<std::string>("currency", "");
    result->totalAmount = data.get<std::int32_t>("total_amount", 0);
    result->invoicePayload = data.get<std::string>("invoice_payload", "");
    result->shippingOptionId = data.get<std::string>("shipping_option_id", "");
    result->orderInfo = tryParseJson<OrderInfo>(&TgTypeParser::parseJsonAndGetOrderInfo, data, "order_info");
    return result;
}

std::string TgTypeParser::parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    appendToJson(result, "invoice_payload", object->invoicePayload);
    appendToJson(result, "shipping_option_id", object->shippingOptionId);
    appendToJson(result, "order_info", parseOrderInfo(object->orderInfo));
    removeLastComma(result);
    result += '}';
    return result;
}

PassportData::Ptr TgTypeParser::parseJsonAndGetPassportData(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<PassportData>());
    result->data = parseJsonAndGetArray<EncryptedPassportElement>(&TgTypeParser::parseJsonAndGetEncryptedPassportElement, data, "data");
    result->credentials = tryParseJson<EncryptedCredentials>(&TgTypeParser::parseJsonAndGetEncryptedCredentials, data, "credentials");
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
    result->frontSide = tryParseJson<PassportFile>(&TgTypeParser::parseJsonAndGetPassportFile, data, "front_side");
    result->reverseSide = tryParseJson<PassportFile>(&TgTypeParser::parseJsonAndGetPassportFile, data, "reverse_side");
    result->selfie = tryParseJson<PassportFile>(&TgTypeParser::parseJsonAndGetPassportFile, data, "selfie");
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
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->text = data.get<std::string>("text", "");
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

CallbackGame::Ptr TgTypeParser::parseJsonAndGetCallbackGame(const boost::property_tree::ptree& /*data*/) const {
    auto result(std::make_shared<CallbackGame>());
    return result;
}

std::string TgTypeParser::parseCallbackGame(const CallbackGame::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    //removeLastComma(result);
    result += '}';
    return result;
}

GameHighScore::Ptr TgTypeParser::parseJsonAndGetGameHighScore(const boost::property_tree::ptree& data) const {
    auto result(std::make_shared<GameHighScore>());
    result->position = data.get<std::int32_t>("position", 0);
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
