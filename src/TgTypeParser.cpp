#include "tgbot/TgTypeParser.h"
#include "tgbot/types/PhotoSize.h"
#include <boost/property_tree/ptree_fwd.hpp>

namespace TgBot {

// T should be instance of std::shared_ptr.
template <typename T>
std::shared_ptr<T> parse(const boost::property_tree::ptree &data,
                         const std::string &key) {
  if (data.empty() || data.find(key) == data.not_found()) {
    return nullptr;
  }
  auto treeItem = data.find(key);
  return parse<T>(treeItem->second);
}

// Pre-defined parsing functions for known types.
DECLARE_PARSER_FROM_PTREE(Message) {
  auto result = std::make_shared<Message>();
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->messageThreadId = data.get<std::int32_t>("message_thread_id", 0);
  result->from = parse<User>(data, "from");
  result->senderChat = parse<Chat>(data, "sender_chat");
  result->senderBoostCount = data.get<std::int32_t>("sender_boost_count", 0);
  result->senderBusinessBot = parse<User>(data, "sender_business_bot");
  result->date = data.get<std::uint32_t>("date", 0);
  result->businessConnectionId =
      data.get<std::string>("business_connection_id", "");
  result->chat = parse<Chat>(data, "chat");
  result->forwardOrigin = parse<MessageOrigin>(data, "forward_origin");
  result->isTopicMessage = data.get<bool>("is_topic_message", false);
  result->isAutomaticForward = data.get<bool>("is_automatic_forward", false);
  result->replyToMessage = parse<Message>(data, "reply_to_message");
  result->externalReply = parse<ExternalReplyInfo>(data, "external_reply");
  result->quote = parse<TextQuote>(data, "quote");
  result->replyToStory = parse<Story>(data, "reply_to_story");
  result->viaBot = parse<User>(data, "via_bot");
  result->editDate = data.get<std::uint32_t>("edit_date", 0);
  result->hasProtectedContent = data.get<bool>("has_protected_content", false);
  result->isFromOffline = data.get<bool>("is_from_offline", false);
  result->mediaGroupId = data.get<std::string>("media_group_id", "");
  result->authorSignature = data.get<std::string>("author_signature", "");
  result->text = data.get<std::string>("text", "");
  result->entities = parseArray<MessageEntity>(data, "entities");
  result->linkPreviewOptions =
      parse<LinkPreviewOptions>(data, "link_preview_options");
  result->animation = parse<Animation>(data, "animation");
  result->audio = parse<Audio>(data, "audio");
  result->document = parse<Document>(data, "document");
  result->photo = parseArray<PhotoSize>(data, "photo");
  result->sticker = parse<Sticker>(data, "sticker");
  result->story = parse<Story>(data, "story");
  result->video = parse<Video>(data, "video");
  result->videoNote = parse<VideoNote>(data, "video_note");
  result->voice = parse<Voice>(data, "voice");
  result->caption = data.get<std::string>("caption", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->hasMediaSpoiler = data.get<bool>("has_media_spoiler", false);
  result->contact = parse<Contact>(data, "contact");
  result->dice = parse<Dice>(data, "dice");
  result->game = parse<Game>(data, "game");
  result->poll = parse<Poll>(data, "poll");
  result->venue = parse<Venue>(data, "venue");
  result->location = parse<Location>(data, "location");
  result->newChatMembers = parseArray<User>(data, "new_chat_members");
  result->leftChatMember = parse<User>(data, "left_chat_member");
  result->newChatTitle = data.get<std::string>("new_chat_title", "");
  result->newChatPhoto = parseArray<PhotoSize>(data, "new_chat_photo");
  result->deleteChatPhoto = data.get<bool>("delete_chat_photo", false);
  result->groupChatCreated = data.get<bool>("group_chat_created", false);
  result->supergroupChatCreated =
      data.get<bool>("supergroup_chat_created", false);
  result->channelChatCreated = data.get<bool>("channel_chat_created", false);
  result->messageAutoDeleteTimerChanged = parse<MessageAutoDeleteTimerChanged>(
      data, "message_auto_delete_timer_changed");
  result->migrateToChatId = data.get<std::int64_t>("migrate_to_chat_id", 0);
  result->migrateFromChatId = data.get<std::int64_t>("migrate_from_chat_id", 0);
  result->pinnedMessage = parse<Message>(data, "pinned_message");
  result->invoice = parse<Invoice>(data, "invoice");
  result->successfulPayment =
      parse<SuccessfulPayment>(data, "successful_payment");
  result->usersShared = parse<UsersShared>(data, "users_shared");
  result->chatShared = parse<ChatShared>(data, "chat_shared");
  result->connectedWebsite = data.get<std::string>("connected_website", "");
  result->writeAccessAllowed =
      parse<WriteAccessAllowed>(data, "write_access_allowed");
  result->passportData = parse<PassportData>(data, "passport_data");
  result->proximityAlertTriggered =
      parse<ProximityAlertTriggered>(data, "proximity_alert_triggered");
  result->boostAdded = parse<ChatBoostAdded>(data, "boost_added");
  result->forumTopicCreated =
      parse<ForumTopicCreated>(data, "forum_topic_created");
  result->forumTopicEdited =
      parse<ForumTopicEdited>(data, "forum_topic_edited");
  result->forumTopicClosed =
      parse<ForumTopicClosed>(data, "forum_topic_closed");
  result->forumTopicReopened =
      parse<ForumTopicReopened>(data, "forum_topic_reopened");
  result->generalForumTopicHidden =
      parse<GeneralForumTopicHidden>(data, "general_forum_topic_hidden");
  result->generalForumTopicUnhidden =
      parse<GeneralForumTopicUnhidden>(data, "general_forum_topic_unhidden");
  result->giveawayCreated = parse<GiveawayCreated>(data, "giveaway_created");
  result->giveaway = parse<Giveaway>(data, "giveaway");
  result->giveawayWinners = parse<GiveawayWinners>(data, "giveaway_winners");
  result->giveawayCompleted =
      parse<GiveawayCompleted>(data, "giveaway_completed");
  result->videoChatScheduled =
      parse<VideoChatScheduled>(data, "video_chat_scheduled");
  result->videoChatStarted =
      parse<VideoChatStarted>(data, "video_chat_started");
  result->videoChatEnded = parse<VideoChatEnded>(data, "video_chat_ended");
  result->videoChatParticipantsInvited = parse<VideoChatParticipantsInvited>(
      data, "video_chat_participants_invited");
  result->webAppData = parse<WebAppData>(data, "web_app_data");
  result->replyMarkup = parse<InlineKeyboardMarkup>(data, "reply_markup");
  return result;
}

DECLARE_PARSER_TO_PTREE(Message) {
  boost::property_tree::ptree json;

  if (object) {
    // Simple fields
    json.put("message_id", object->messageId);
    json.put("message_thread_id", object->messageThreadId);
    json.add_child("from", put(object->from));
    json.add_child("sender_chat", put(object->senderChat));
    json.put("sender_boost_count", object->senderBoostCount);
    json.add_child("sender_business_bot", put(object->senderBusinessBot));
    json.put("date", object->date);
    json.put("business_connection_id", object->businessConnectionId);
    json.add_child("chat", put(object->chat));
    json.add_child("forward_origin", put(object->forwardOrigin));
    json.put("is_topic_message", object->isTopicMessage);
    json.put("is_automatic_forward", object->isAutomaticForward);
    json.add_child("reply_to_message", put(object->replyToMessage));
    json.add_child("external_reply", put(object->externalReply));
    json.add_child("quote", put(object->quote));
    json.add_child("reply_to_story", put(object->replyToStory));
    json.add_child("via_bot", put(object->viaBot));
    json.put("edit_date", object->editDate);
    json.put("has_protected_content", object->hasProtectedContent);
    json.put("is_from_offline", object->isFromOffline);
    json.put("media_group_id", object->mediaGroupId);
    json.put("author_signature", object->authorSignature);
    json.put("text", object->text);
    json.add_child("entities", put(object->entities));
    json.add_child("link_preview_options", put(object->linkPreviewOptions));
    json.add_child("animation", put(object->animation));
    json.add_child("audio", put(object->audio));
    json.add_child("document", put(object->document));
    json.add_child("photo", put(object->photo));
    json.add_child("sticker", put(object->sticker));
    json.add_child("story", put(object->story));
    json.add_child("video", put(object->video));
    json.add_child("video_note", put(object->videoNote));
    json.add_child("voice", put(object->voice));
    json.put("caption", object->caption);
    json.add_child("caption_entities", put(object->captionEntities));
    json.put("has_media_spoiler", object->hasMediaSpoiler);
    json.add_child("contact", put(object->contact));
    json.add_child("dice", put(object->dice));
    json.add_child("game", put(object->game));
    json.add_child("poll", put(object->poll));
    json.add_child("venue", put(object->venue));
    json.add_child("location", put(object->location));
    json.add_child("new_chat_members", put(object->newChatMembers));
    json.add_child("left_chat_member", put(object->leftChatMember));
    json.put("new_chat_title", object->newChatTitle);
    json.add_child("new_chat_photo", put(object->newChatPhoto));
    json.put("delete_chat_photo", object->deleteChatPhoto);
    json.put("group_chat_created", object->groupChatCreated);
    json.put("supergroup_chat_created", object->supergroupChatCreated);
    json.put("channel_chat_created", object->channelChatCreated);
    json.add_child("message_auto_delete_timer_changed",
                   put(object->messageAutoDeleteTimerChanged));
    json.put("migrate_to_chat_id", object->migrateToChatId);
    json.put("migrate_from_chat_id", object->migrateFromChatId);
    json.add_child("pinned_message", put(object->pinnedMessage));
    json.add_child("invoice", put(object->invoice));
    json.add_child("successful_payment", put(object->successfulPayment));
    json.add_child("users_shared", put(object->usersShared));
    json.add_child("chat_shared", put(object->chatShared));
    json.put("connected_website", object->connectedWebsite);
    json.add_child("write_access_allowed", put(object->writeAccessAllowed));
    json.add_child("passport_data", put(object->passportData));
    json.add_child("proximity_alert_triggered",
                   put(object->proximityAlertTriggered));
    json.add_child("boost_added", put(object->boostAdded));
    json.add_child("forum_topic_created", put(object->forumTopicCreated));
    json.add_child("forum_topic_edited", put(object->forumTopicEdited));
    json.add_child("forum_topic_closed", put(object->forumTopicClosed));
    json.add_child("forum_topic_reopened", put(object->forumTopicReopened));
    json.add_child("general_forum_topic_hidden",
                   put(object->generalForumTopicHidden));
    json.add_child("general_forum_topic_unhidden",
                   put(object->generalForumTopicUnhidden));
    json.add_child("giveaway_created", put(object->giveawayCreated));
    json.add_child("giveaway", put(object->giveaway));
    json.add_child("giveaway_winners", put(object->giveawayWinners));
    json.add_child("giveaway_completed", put(object->giveawayCompleted));
    json.add_child("video_chat_scheduled", put(object->videoChatScheduled));
    json.add_child("video_chat_started", put(object->videoChatStarted));
    json.add_child("video_chat_ended", put(object->videoChatEnded));
    json.add_child("video_chat_participants_invited",
                   put(object->videoChatParticipantsInvited));
    json.add_child("web_app_data", put(object->webAppData));
    json.add_child("reply_markup", put(object->replyMarkup));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(Update) {
  auto result(std::make_shared<Update>());
  result->updateId = data.get<std::int32_t>("update_id", 0);
  result->message = parse<Message>(data, "message");
  result->editedMessage = parse<Message>(data, "edited_message");
  result->channelPost = parse<Message>(data, "channel_post");
  result->editedChannelPost = parse<Message>(data, "edited_channel_post");
  result->businessConnection =
      parse<BusinessConnection>(data, "business_connection");
  result->businessMessage = parse<Message>(data, "business_message");
  result->editedBusinessMessage =
      parse<Message>(data, "edited_business_message");
  result->deletedBusinessMessages =
      parse<BusinessMessagesDeleted>(data, "deleted_business_messages");
  result->messageReaction =
      parse<MessageReactionUpdated>(data, "message_reaction");
  result->messageReactionCount =
      parse<MessageReactionCountUpdated>(data, "message_reaction_count");
  result->inlineQuery = parse<InlineQuery>(data, "inline_query");
  result->chosenInlineResult =
      parse<ChosenInlineResult>(data, "chosen_inline_result");
  result->callbackQuery = parse<CallbackQuery>(data, "callback_query");
  result->shippingQuery = parse<ShippingQuery>(data, "shipping_query");
  result->preCheckoutQuery =
      parse<PreCheckoutQuery>(data, "pre_checkout_query");
  result->poll = parse<Poll>(data, "poll");
  result->pollAnswer = parse<PollAnswer>(data, "poll_answer");
  result->myChatMember = parse<ChatMemberUpdated>(data, "my_chat_member");
  result->chatMember = parse<ChatMemberUpdated>(data, "chat_member");
  result->chatJoinRequest = parse<ChatJoinRequest>(data, "chat_join_request");
  result->chatBoost = parse<ChatBoostUpdated>(data, "chat_boost");
  result->removedChatBoost =
      parse<ChatBoostRemoved>(data, "removed_chat_boost");
  return result;
}

DECLARE_PARSER_TO_PTREE(Update) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("update_id", object->updateId);
    json.add_child("message", put(object->message));
    json.add_child("edited_message", put(object->editedMessage));
    json.add_child("channel_post", put(object->channelPost));
    json.add_child("edited_channel_post", put(object->editedChannelPost));
    json.add_child("business_connection", put(object->businessConnection));
    json.add_child("business_message", put(object->businessMessage));
    json.add_child("edited_business_message",
                   put(object->editedBusinessMessage));
    json.add_child("deleted_business_messages",
                   put(object->deletedBusinessMessages));
    json.add_child("message_reaction", put(object->messageReaction));
    json.add_child("message_reaction_count", put(object->messageReactionCount));
    json.add_child("inline_query", put(object->inlineQuery));
    json.add_child("chosen_inline_result", put(object->chosenInlineResult));
    json.add_child("callback_query", put(object->callbackQuery));
    json.add_child("shipping_query", put(object->shippingQuery));
    json.add_child("pre_checkout_query", put(object->preCheckoutQuery));
    json.add_child("poll", put(object->poll));
    json.add_child("poll_answer", put(object->pollAnswer));
    json.add_child("my_chat_member", put(object->myChatMember));
    json.add_child("chat_member", put(object->chatMember));
    json.add_child("chat_join_request", put(object->chatJoinRequest));
    json.add_child("chat_boost", put(object->chatBoost));
    json.add_child("removed_chat_boost", put(object->removedChatBoost));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(WebhookInfo) {
  auto result(std::make_shared<WebhookInfo>());
  result->url = data.get<std::string>("url", "");
  result->hasCustomCertificate =
      data.get<bool>("has_custom_certificate", false);
  result->pendingUpdateCount =
      data.get<std::int32_t>("pending_update_count", 0);
  result->ipAddress = data.get<std::string>("ip_address", "");
  result->lastErrorDate = data.get<std::int32_t>("last_error_date", 0);
  result->lastErrorMessage = data.get<std::string>("last_error_message", "");
  result->lastSynchronizationErrorDate =
      data.get<std::int32_t>("last_synchronization_error_date", 0);
  result->maxConnections = data.get<std::int32_t>("max_connections", 0);
  result->allowedUpdates =
      parsePrimitiveArray<std::string>(data, "allowed_updates");
  return result;
}

DECLARE_PARSER_TO_PTREE(WebhookInfo) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("url", object->url);
    json.put("has_custom_certificate", object->hasCustomCertificate);
    json.put("pending_update_count", object->pendingUpdateCount);
    json.put("ip_address", object->ipAddress);
    json.put("last_error_date", object->lastErrorDate);
    json.put("last_error_message", object->lastErrorMessage);
    json.put("last_synchronization_error_date",
             object->lastSynchronizationErrorDate);
    json.put("max_connections", object->maxConnections);

    json.add_child("allowed_updates", put(object->allowedUpdates));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(User) {
  auto result(std::make_shared<User>());
  result->id = data.get<std::int64_t>("id", 0);
  result->isBot = data.get<bool>("is_bot", false);
  result->firstName = data.get<std::string>("first_name", "");
  result->lastName = data.get<std::string>("last_name", "");
  result->username = data.get<std::string>("username", "");
  result->languageCode = data.get<std::string>("language_code", "");
  result->isPremium = data.get<bool>("is_premium", false);
  result->addedToAttachmentMenu =
      data.get<bool>("added_to_attachment_menu", false);
  result->canJoinGroups = data.get<bool>("can_join_groups", false);
  result->canReadAllGroupMessages =
      data.get<bool>("can_read_all_group_messages", false);
  result->supportsInlineQueries =
      data.get<bool>("supports_inline_queries", false);
  result->canConnectToBusiness =
      data.get<bool>("can_connect_to_business", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(User) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("id", object->id);
    json.put("is_bot", object->isBot);
    json.put("first_name", object->firstName);
    json.put("last_name", object->lastName);
    json.put("username", object->username);
    json.put("language_code", object->languageCode);
    json.put("is_premium", object->isPremium);
    json.put("added_to_attachment_menu", object->addedToAttachmentMenu);
    json.put("can_join_groups", object->canJoinGroups);
    json.put("can_read_all_group_messages", object->canReadAllGroupMessages);
    json.put("supports_inline_queries", object->supportsInlineQueries);
    json.put("can_connect_to_business", object->canConnectToBusiness);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(Chat) {
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
  result->photo = parse<ChatPhoto>(data, "photo");
  result->activeUsernames =
      parsePrimitiveArray<std::string>(data, "active_usernames");
  result->birthdate = parse<Birthdate>(data, "birthdate");
  result->businessIntro = parse<BusinessIntro>(data, "business_intro");
  result->businessLocation = parse<BusinessLocation>(data, "business_location");
  result->businessOpeningHours =
      parse<BusinessOpeningHours>(data, "business_opening_hours");
  result->personalChat = parse<Chat>(data, "personal_chat");
  result->availableReactions =
      parseArray<ReactionType>(data, "available_reactions");
  result->accentColorId = data.get<std::int32_t>("accent_color_id", 0);
  result->backgroundCustomEmojiId =
      data.get<std::string>("background_custom_emoji_id", "");
  result->profileAccentColorId =
      data.get<std::int32_t>("profile_accent_color_id", 0);
  result->profileBackgroundCustomEmojiId =
      data.get<std::string>("profile_background_custom_emoji_id", "");
  result->emojiStatusCustomEmojiId =
      data.get<std::string>("emoji_status_custom_emoji_id", "");
  result->emojiStatusExpirationDate =
      data.get<std::uint32_t>("emoji_status_expiration_date", 0);
  result->bio = data.get<std::string>("bio", "");
  result->hasPrivateForwards = data.get<bool>("has_private_forwards", false);
  result->hasRestrictedVoiceAndVideoMessages =
      data.get<bool>("has_restricted_voice_and_video_messages", false);
  result->joinToSendMessages = data.get<bool>("join_to_send_messages", false);
  result->joinByRequest = data.get<bool>("join_by_request", false);
  result->description = data.get<std::string>("description", "");
  result->inviteLink = data.get<std::string>("invite_link", "");
  result->pinnedMessage = parse<Message>(data, "pinned_message");
  result->permissions = parse<ChatPermissions>(data, "permissions");
  result->slowModeDelay = data.get<std::int32_t>("slow_mode_delay", 0);
  result->unrestrictBoostCount =
      data.get<std::int32_t>("unrestrict_boost_count", 0);
  result->messageAutoDeleteTime =
      data.get<std::int32_t>("message_auto_delete_time", 0);
  result->hasAggressiveAntiSpamEnabled =
      data.get<bool>("has_aggressive_anti_spam_enabled", false);
  result->hasHiddenMembers = data.get<bool>("has_hidden_members", false);
  result->hasProtectedContent = data.get<bool>("has_protected_content", false);
  result->hasVisibleHistory = data.get<bool>("has_visible_history", false);
  result->stickerSetName = data.get<std::string>("sticker_set_name", "");
  result->canSetStickerSet = data.get<bool>("can_set_sticker_set", false);
  result->customEmojiStickerSetName =
      data.get<std::string>("custom_emoji_sticker_set_name", "");
  result->linkedChatId = data.get<std::int64_t>("linked_chat_id", 0);
  result->location = parse<ChatLocation>(data, "location");
  return result;
}

DECLARE_PARSER_TO_PTREE(Chat) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("id", object->id);

    switch (object->type) {
    case Chat::Type::Private:
      json.put("type", "private");
      break;
    case Chat::Type::Group:
      json.put("type", "group");
      break;
    case Chat::Type::Supergroup:
      json.put("type", "supergroup");
      break;
    case Chat::Type::Channel:
      json.put("type", "channel");
      break;
    }

    json.put("title", object->title);
    json.put("username", object->username);
    json.put("first_name", object->firstName);
    json.put("last_name", object->lastName);
    json.put("is_forum", object->isForum);
    json.add_child("photo", put(object->photo));
    json.add_child("active_usernames", put(object->activeUsernames));
    json.add_child("birthdate", put(object->birthdate));
    json.add_child("business_intro", put(object->businessIntro));
    json.add_child("business_location", put(object->businessLocation));
    json.add_child("business_opening_hours", put(object->businessOpeningHours));
    json.add_child("personal_chat", put(object->personalChat));

    json.add_child("available_reactions", put(object->availableReactions));

    json.put("accent_color_id", object->accentColorId);
    json.put("background_custom_emoji_id", object->backgroundCustomEmojiId);
    json.put("profile_accent_color_id", object->profileAccentColorId);
    json.put("profile_background_custom_emoji_id",
             object->profileBackgroundCustomEmojiId);
    json.put("emoji_status_custom_emoji_id", object->emojiStatusCustomEmojiId);
    json.put("emoji_status_expiration_date", object->emojiStatusExpirationDate);
    json.put("bio", object->bio);
    json.put("has_private_forwards", object->hasPrivateForwards);
    json.put("has_restricted_voice_and_video_messages",
             object->hasRestrictedVoiceAndVideoMessages);
    json.put("join_to_send_messages", object->joinToSendMessages);
    json.put("join_by_request", object->joinByRequest);
    json.put("description", object->description);
    json.put("invite_link", object->inviteLink);
    json.add_child("pinned_message", put(object->pinnedMessage));
    json.add_child("permissions", put(object->permissions));
    json.put("slow_mode_delay", object->slowModeDelay);
    json.put("unrestrict_boost_count", object->unrestrictBoostCount);
    json.put("message_auto_delete_time", object->messageAutoDeleteTime);
    json.put("has_aggressive_anti_spam_enabled",
             object->hasAggressiveAntiSpamEnabled);
    json.put("has_hidden_members", object->hasHiddenMembers);
    json.put("has_protected_content", object->hasProtectedContent);
    json.put("has_visible_history", object->hasVisibleHistory);
    json.put("sticker_set_name", object->stickerSetName);
    json.put("can_set_sticker_set", object->canSetStickerSet);
    json.put("custom_emoji_sticker_set_name",
             object->customEmojiStickerSetName);
    json.put("linked_chat_id", object->linkedChatId);
    json.add_child("location", put(object->location));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageId) {
  auto result(std::make_shared<MessageId>());
  result->messageId = data.get<std::int32_t>("message_id", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageId) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("message_id", object->messageId);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(InaccessibleMessage) {
  auto result(std::make_shared<InaccessibleMessage>());
  result->chat = parse<Chat>(data, "chat");
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->date = data.get<std::uint8_t>("date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InaccessibleMessage) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("message_id", object->messageId);
    json.put("date", object->date);
    json.add_child("chat", put(object->chat));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageEntity) {
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
  result->user = parse<User>(data, "user");
  result->language = data.get<std::string>("language", "");
  result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageEntity) {
  boost::property_tree::ptree json;

  if (object) {
    switch (object->type) {
    case MessageEntity::Type::Mention:
      json.put("type", "mention");
      break;
    case MessageEntity::Type::Hashtag:
      json.put("type", "hashtag");
      break;
    case MessageEntity::Type::Cashtag:
      json.put("type", "cashtag");
      break;
    case MessageEntity::Type::BotCommand:
      json.put("type", "bot_command");
      break;
    case MessageEntity::Type::Url:
      json.put("type", "url");
      break;
    case MessageEntity::Type::Email:
      json.put("type", "email");
      break;
    case MessageEntity::Type::PhoneNumber:
      json.put("type", "phone_number");
      break;
    case MessageEntity::Type::Bold:
      json.put("type", "bold");
      break;
    case MessageEntity::Type::Italic:
      json.put("type", "italic");
      break;
    case MessageEntity::Type::Underline:
      json.put("type", "underline");
      break;
    case MessageEntity::Type::Strikethrough:
      json.put("type", "strikethrough");
      break;
    case MessageEntity::Type::Spoiler:
      json.put("type", "spoiler");
      break;
    case MessageEntity::Type::Blockquote:
      json.put("type", "blockquote");
      break;
    case MessageEntity::Type::Code:
      json.put("type", "code");
      break;
    case MessageEntity::Type::Pre:
      json.put("type", "pre");
      break;
    case MessageEntity::Type::TextLink:
      json.put("type", "text_link");
      break;
    case MessageEntity::Type::TextMention:
      json.put("type", "text_mention");
      break;
    case MessageEntity::Type::CustomEmoji:
      json.put("type", "custom_emoji");
      break;
    }

    json.put("offset", object->offset);
    json.put("length", object->length);
    json.put("url", object->url);
    json.add_child("user", put(object->user));
    json.put("language", object->language);
    json.put("custom_emoji_id", object->customEmojiId);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(TextQuote) {
  auto result(std::make_shared<TextQuote>());
  result->text = data.get<std::string>("text", "");
  result->entities = parseArray<MessageEntity>(data, "entities");
  result->position = data.get<std::int32_t>("position", 0);
  result->isManual = data.get<bool>("is_manual", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(TextQuote) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("text", object->text);
    json.add_child("entities", put(object->entities));
    json.put("position", object->position);
    json.put("is_manual", object->isManual);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(ExternalReplyInfo) {
  auto result(std::make_shared<ExternalReplyInfo>());
  result->origin = parse<MessageOrigin>(data, "origin");
  result->chat = parse<Chat>(data, "chat");
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->linkPreviewOptions =
      parse<LinkPreviewOptions>(data, "link_preview_options");
  result->animation = parse<Animation>(data, "animation");
  result->audio = parse<Audio>(data, "audio");
  result->document = parse<Document>(data, "document");
  result->photo = parseArray<PhotoSize>(data, "photo");
  result->sticker = parse<Sticker>(data, "sticker");
  result->story = parse<Story>(data, "story");
  result->video = parse<Video>(data, "video");
  result->videoNote = parse<VideoNote>(data, "video_note");
  result->voice = parse<Voice>(data, "voice");
  result->hasMediaSpoiler = data.get<bool>("has_media_spoiler", false);
  result->contact = parse<Contact>(data, "contact");
  result->dice = parse<Dice>(data, "dice");
  result->game = parse<Game>(data, "game");
  result->giveaway = parse<Giveaway>(data, "giveaway");
  result->giveawayWinners = parse<GiveawayWinners>(data, "giveaway_winners");
  result->invoice = parse<Invoice>(data, "invoice");
  result->location = parse<Location>(data, "location");
  result->poll = parse<Poll>(data, "poll");
  result->venue = parse<Venue>(data, "venue");
  return result;
}

DECLARE_PARSER_TO_PTREE(ExternalReplyInfo) {
  boost::property_tree::ptree json;

  if (object) {
    json.add_child("origin", put(object->origin));
    json.add_child("chat", put(object->chat));
    json.put("message_id", object->messageId);
    json.add_child("link_preview_options", put(object->linkPreviewOptions));
    json.add_child("animation", put(object->animation));
    json.add_child("audio", put(object->audio));
    json.add_child("document", put(object->document));
    json.add_child("photo", put(object->photo));
    json.add_child("sticker", put(object->sticker));
    json.add_child("story", put(object->story));
    json.add_child("video", put(object->video));
    json.add_child("video_note", put(object->videoNote));
    json.add_child("voice", put(object->voice));
    json.put("has_media_spoiler", object->hasMediaSpoiler);
    json.add_child("contact", put(object->contact));
    json.add_child("dice", put(object->dice));
    json.add_child("game", put(object->game));
    json.add_child("giveaway", put(object->giveaway));
    json.add_child("giveaway_winners", put(object->giveawayWinners));
    json.add_child("invoice", put(object->invoice));
    json.add_child("location", put(object->location));
    json.add_child("poll", put(object->poll));
    json.add_child("venue", put(object->venue));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(ReplyParameters) {
  auto result(std::make_shared<ReplyParameters>());
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->chatId = data.get<std::int64_t>("chat_id", 0);
  result->allowSendingWithoutReply =
      data.get<bool>("allow_sending_without_reply", false);
  result->quote = data.get<std::string>("quote", "");
  result->quoteParseMode = data.get<std::string>("quote_parse_mode", "");
  result->quoteEntities = parseArray<MessageEntity>(data, "quote_entities");
  result->quotePosition = data.get<std::int32_t>("quote_position", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ReplyParameters) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("message_id", object->messageId);
    json.put("chat_id", object->chatId);
    json.put("allow_sending_without_reply", object->allowSendingWithoutReply);
    json.put("quote", object->quote);
    json.put("quote_parse_mode", object->quoteParseMode);
    json.add_child("quote_entities", put(object->quoteEntities));
    json.put("quote_position", object->quotePosition);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageOrigin) {
  std::string type = data.get<std::string>("type", "");
  MessageOrigin::Ptr result;

  if (type == MessageOriginUser::TYPE) {
    result =
        std::static_pointer_cast<MessageOrigin>(parse<MessageOriginUser>(data));
  } else if (type == MessageOriginHiddenUser::TYPE) {
    result = std::static_pointer_cast<MessageOrigin>(
        parse<MessageOriginHiddenUser>(data));
  } else if (type == MessageOriginChat::TYPE) {
    result =
        std::static_pointer_cast<MessageOrigin>(parse<MessageOriginChat>(data));
  } else if (type == MessageOriginChannel::TYPE) {
    result = std::static_pointer_cast<MessageOrigin>(
        parse<MessageOriginChannel>(data));
  } else {
    result = std::make_shared<MessageOrigin>();
  }

  result->type = type;
  result->date = data.get<std::int32_t>("date", 0);

  return result;
}

DECLARE_PARSER_TO_PTREE(MessageOrigin) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("type", object->type);
    json.put("date", object->date);

    if (object->type == MessageOriginUser::TYPE) {
      json.add_child("origin", put<MessageOriginUser>(object));
    } else if (object->type == MessageOriginHiddenUser::TYPE) {
      json.add_child("origin", put<MessageOriginHiddenUser>(object));
    } else if (object->type == MessageOriginChat::TYPE) {
      json.add_child("origin", put<MessageOriginChat>(object));
    } else if (object->type == MessageOriginChannel::TYPE) {
      json.add_child("origin", put<MessageOriginChannel>(object));
    }
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageOriginUser) {
  auto result(std::make_shared<MessageOriginUser>());
  result->senderUser = parse<User>(data, "sender_user");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageOriginUser) {
  boost::property_tree::ptree json;

  if (object) {
    json.add_child("sender_user", put(object->senderUser));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageOriginHiddenUser) {
  auto result(std::make_shared<MessageOriginHiddenUser>());
  result->senderUserName = data.get<std::string>("sender_user_name", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageOriginHiddenUser) {
  boost::property_tree::ptree result;

  if (object) {
    result.put("sender_user_name", object->senderUserName);
  }
  return result;
}

DECLARE_PARSER_FROM_PTREE(MessageOriginChat) {
  // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
  auto result(std::make_shared<MessageOriginChat>());
  result->senderChat = parse<Chat>(data, "sender_chat");
  result->authorSignature = data.get<std::string>("author_signature", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageOriginChat) {
  boost::property_tree::ptree result;

  if (object) {
    result.add_child("sender_chat", put(object->senderChat));
    result.put("author_signature", object->authorSignature);
  }

  return result;
}

DECLARE_PARSER_FROM_PTREE(MessageOriginChannel) {
  // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
  auto result(std::make_shared<MessageOriginChannel>());
  result->chat = parse<Chat>(data, "chat");
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->authorSignature = data.get<std::string>("author_signature", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageOriginChannel) {
  boost::property_tree::ptree result;

  if (object) {
    result.add_child("chat", put(object->chat));
    result.put("message_id", object->messageId);
    result.put("author_signature", object->authorSignature);
  }

  return result;
}

DECLARE_PARSER_FROM_PTREE(PhotoSize) {
  auto result(std::make_shared<PhotoSize>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->width = data.get<std::int32_t>("width", 0);
  result->height = data.get<std::int32_t>("height", 0);
  result->fileSize = data.get<std::int32_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(PhotoSize) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("width", object->width);
    json.put("height", object->height);
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Animation) {
  auto result(std::make_shared<Animation>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->width = data.get<std::int32_t>("width", 0);
  result->height = data.get<std::int32_t>("height", 0);
  result->duration = data.get<std::int32_t>("duration", 0);
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  result->fileName = data.get<std::string>("file_name", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Animation) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("width", object->width);
    json.put("height", object->height);
    json.put("duration", object->duration);
    json.add_child("thumbnail", put(object->thumbnail));
    json.put("file_name", object->fileName);
    json.put("mime_type", object->mimeType);
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Audio) {
  auto result(std::make_shared<Audio>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->duration = data.get<std::int32_t>("duration", 0);
  result->performer = data.get<std::string>("performer", "");
  result->title = data.get<std::string>("title", "");
  result->fileName = data.get<std::string>("file_name", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  return result;
}

DECLARE_PARSER_TO_PTREE(Audio) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("duration", object->duration);
    json.put("performer", object->performer);
    json.put("title", object->title);
    json.put("file_name", object->fileName);
    json.put("mime_type", object->mimeType);
    json.put("file_size", object->fileSize);
    json.add_child("thumbnail", put(object->thumbnail));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Document) {
  auto result(std::make_shared<Document>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  result->fileName = data.get<std::string>("file_name", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Document) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.add_child("thumbnail", put(object->thumbnail));
    json.put("file_name", object->fileName);
    json.put("mime_type", object->mimeType);
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Story) {
  auto result(std::make_shared<Story>());
  result->chat = parse<Chat>(data, "chat");
  result->id = data.get<std::int32_t>("id", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Story) {
  boost::property_tree::ptree json;

  if (object) {
    json.add_child("chat", put(object->chat));
    json.put("id", object->id);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(Video) {
  auto result(std::make_shared<Video>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->width = data.get<std::int32_t>("width", 0);
  result->height = data.get<std::int32_t>("height", 0);
  result->duration = data.get<std::int32_t>("duration", 0);
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  result->fileName = data.get<std::string>("file_name", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Video) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("width", object->width);
    json.put("height", object->height);
    json.put("duration", object->duration);
    json.add_child("thumbnail", put(object->thumbnail));
    json.put("file_name", object->fileName);
    json.put("mime_type", object->mimeType);
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(VideoNote) {
  auto result(std::make_shared<VideoNote>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->length = data.get<std::int32_t>("length", 0);
  result->duration = data.get<std::int32_t>("duration", 0);
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  result->fileSize = data.get<std::int32_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(VideoNote) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("length", object->length);
    json.put("duration", object->duration);
    json.add_child("thumbnail", put(object->thumbnail));
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Voice) {
  auto result(std::make_shared<Voice>());
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->duration = data.get<std::int32_t>("duration", 0);
  result->mimeType = data.get<std::string>("mime_type", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Voice) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("duration", object->duration);
    json.put("mime_type", object->mimeType);
    json.put("file_size", object->fileSize);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Contact) {
  auto result(std::make_shared<Contact>());
  result->phoneNumber = data.get<std::string>("phone_number", "");
  result->firstName = data.get<std::string>("first_name", "");
  result->lastName = data.get<std::string>("last_name", "");
  result->userId = data.get<std::int64_t>("user_id", 0);
  result->vcard = data.get<std::string>("vcard", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(Contact) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("phone_number", object->phoneNumber);
    json.put("first_name", object->firstName);
    json.put("last_name", object->lastName);
    json.put("user_id", object->userId);
    json.put("vcard", object->vcard);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(Dice) {
  auto result(std::make_shared<Dice>());
  result->emoji = data.get<std::string>("emoji", "");
  result->value = data.get<std::int32_t>("value", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Dice) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("emoji", object->emoji);
    json.put("value", object->value);
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(PollOption) {
  auto result(std::make_shared<PollOption>());
  result->text = data.get<std::string>("text", "");
  result->voterCount = data.get<std::int32_t>("voter_count", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(PollOption) {
  boost::property_tree::ptree json;

  if (object) {
    json.put("text", object->text);
    json.put("voter_count", object->voterCount);
  }

  return json;
}
DECLARE_PARSER_FROM_PTREE(PollAnswer) {
  auto result(std::make_shared<PollAnswer>());
  result->pollId = data.get<std::string>("poll_id", "");
  result->voterChat = parse<Chat>(data, "voter_chat");
  result->user = parse<User>(data, "user");
  result->optionIds = parsePrimitiveArray<std::int32_t>(data, "option_ids");
  return result;
}

DECLARE_PARSER_TO_PTREE(PollAnswer) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("poll_id", object->pollId);
    json.add_child("voter_chat", put(object->voterChat));
    json.add_child("user", put(object->user));
    json.add_child("option_ids", put(object->optionIds));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(Poll) {
  auto result(std::make_shared<Poll>());
  result->id = data.get<std::string>("id", "");
  result->question = data.get<std::string>("question", "");
  result->options = parseArray<PollOption>(data, "options");
  result->totalVoterCount = data.get<std::int32_t>("total_voter_count", 0);
  result->isClosed = data.get<bool>("is_closed", false);
  result->isAnonymous = data.get<bool>("is_anonymous", false);
  result->type = data.get<std::string>("type", "");
  result->allowsMultipleAnswers =
      data.get<bool>("allows_multiple_answers", false);
  result->correctOptionId = data.get<std::int32_t>("correct_option_id", 0);
  result->explanation = data.get<std::string>("explanation", "");
  result->explanationEntities =
      parseArray<MessageEntity>(data, "explanation_entities");
  result->openPeriod = data.get<std::int32_t>("open_period", 0);
  result->closeDate = data.get<std::int64_t>("close_date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Poll) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("id", object->id);
    json.put("question", object->question);
    json.add_child("options", put(object->options));
    json.put("total_voter_count", object->totalVoterCount);
    json.put("is_closed", object->isClosed);
    json.put("is_anonymous", object->isAnonymous);
    json.put("type", object->type);
    json.put("allows_multiple_answers", object->allowsMultipleAnswers);
    json.put("correct_option_id", object->correctOptionId);
    json.put("explanation", object->explanation);
    json.add_child("explanation_entities", put(object->explanationEntities));
    json.put("open_period", object->openPeriod);
    json.put("close_date", object->closeDate);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(Location) {
  auto result(std::make_shared<Location>());
  result->latitude = data.get<float>("latitude", 0);
  result->longitude = data.get<float>("longitude", 0);
  result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
  result->livePeriod = data.get<std::int32_t>("live_period", 0);
  result->heading = data.get<std::int32_t>("heading", 0);
  result->proximityAlertRadius =
      data.get<std::int32_t>("proximity_alert_radius", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Location) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("latitude", object->latitude);
    json.put("longitude", object->longitude);
    json.put("horizontal_accuracy", object->horizontalAccuracy);
    json.put("live_period", object->livePeriod);
    json.put("heading", object->heading);
    json.put("proximity_alert_radius", object->proximityAlertRadius);
  }
  return json;
}
DECLARE_PARSER_FROM_PTREE(Venue) {
  auto result = std::make_shared<Venue>();
  result->location = parse<Location>(data, "location");
  result->title = data.get<std::string>("title", "");
  result->address = data.get<std::string>("address", "");
  result->foursquareId = data.get<std::string>("foursquare_id", "");
  result->foursquareType = data.get<std::string>("foursquare_type", "");
  result->googlePlaceId = data.get<std::string>("google_place_id", "");
  result->googlePlaceType = data.get<std::string>("google_place_type", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(Venue) {
  boost::property_tree::ptree json;
  if (object) {
    json.add_child("location", put(object->location));
    json.put("title", object->title);
    json.put("address", object->address);
    json.put("foursquare_id", object->foursquareId);
    json.put("foursquare_type", object->foursquareType);
    json.put("google_place_id", object->googlePlaceId);
    json.put("google_place_type", object->googlePlaceType);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(WebAppData) {
  auto result = std::make_shared<WebAppData>();
  result->data = data.get<std::string>("data", "");
  result->buttonText = data.get<std::string>("button_text", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(WebAppData) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("data", object->data);
    json.put("button_text", object->buttonText);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ProximityAlertTriggered) {
  auto result = std::make_shared<ProximityAlertTriggered>();
  result->traveler = parse<User>(data, "traveler");
  result->watcher = parse<User>(data, "watcher");
  result->distance = data.get<std::int32_t>("distance", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ProximityAlertTriggered) {
  boost::property_tree::ptree json;
  if (object) {
    json.add_child("traveler", put(object->traveler));
    json.add_child("watcher", put(object->watcher));
    json.put("distance", object->distance);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageAutoDeleteTimerChanged) {
  auto result = std::make_shared<MessageAutoDeleteTimerChanged>();
  result->messageAutoDeleteTime =
      data.get<std::int32_t>("message_auto_delete_time", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageAutoDeleteTimerChanged) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("message_auto_delete_time", object->messageAutoDeleteTime);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatBoostAdded) {
  auto result = std::make_shared<ChatBoostAdded>();
  result->boostCount = data.get<std::int32_t>("boost_count", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatBoostAdded) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("boost_count", object->boostCount);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ForumTopicCreated) {
  auto result = std::make_shared<ForumTopicCreated>();
  result->name = data.get<std::string>("name", "");
  result->iconColor = data.get<std::int32_t>("icon_color", 0);
  result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ForumTopicCreated) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("name", object->name);
    json.put("icon_color", object->iconColor);
    json.put("icon_custom_emoji_id", object->iconCustomEmojiId);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ForumTopicClosed) {
  return std::make_shared<ForumTopicClosed>();
}

DECLARE_PARSER_TO_PTREE(ForumTopicClosed) {
  return boost::property_tree::ptree(); // Empty JSON for closed topic
}

DECLARE_PARSER_FROM_PTREE(ForumTopicEdited) {
  auto result = std::make_shared<ForumTopicEdited>();
  result->name = data.get<std::string>("name", "");
  result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ForumTopicEdited) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("name", object->name);
    json.put("icon_custom_emoji_id", object->iconCustomEmojiId);
  }
  return json;
}
DECLARE_PARSER_FROM_PTREE(ForumTopicReopened) {
  return std::make_shared<ForumTopicReopened>();
}

DECLARE_PARSER_TO_PTREE(ForumTopicReopened) {
  return boost::property_tree::ptree(); // Empty JSON for reopened topic
}

DECLARE_PARSER_FROM_PTREE(GeneralForumTopicHidden) {
  return std::make_shared<GeneralForumTopicHidden>();
}

DECLARE_PARSER_TO_PTREE(GeneralForumTopicHidden) {
  return boost::property_tree::ptree(); // Empty JSON for hidden topic
}

DECLARE_PARSER_FROM_PTREE(GeneralForumTopicUnhidden) {
  return std::make_shared<GeneralForumTopicUnhidden>();
}

DECLARE_PARSER_TO_PTREE(GeneralForumTopicUnhidden) {
  return boost::property_tree::ptree(); // Empty JSON for unhidden topic
}

DECLARE_PARSER_FROM_PTREE(SharedUser) {
  auto result = std::make_shared<SharedUser>();
  result->userId = data.get<std::int64_t>("user_id", 0);
  result->firstName = data.get<std::string>("first_name", "");
  result->lastName = data.get<std::string>("last_name", "");
  result->username = data.get<std::string>("username", "");
  result->photo = parseArray<PhotoSize>(data, "photo");
  return result;
}

DECLARE_PARSER_TO_PTREE(SharedUser) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("user_id", object->userId);
    json.put("first_name", object->firstName);
    json.put("last_name", object->lastName);
    json.put("username", object->username);
    json.add_child("photo", put(object->photo));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(UsersShared) {
  auto result = std::make_shared<UsersShared>();
  result->requestId = data.get<std::int32_t>("request_id", 0);
  result->users = parseArray<SharedUser>(data, "users");
  return result;
}

DECLARE_PARSER_TO_PTREE(UsersShared) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("request_id", object->requestId);
    json.add_child("users", put(object->users));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatShared) {
  auto result = std::make_shared<ChatShared>();
  result->requestId = data.get<std::int32_t>("request_id", 0);
  result->chatId = data.get<std::int64_t>("chat_id", 0);
  result->title = data.get<std::string>("title", "");
  result->username = data.get<std::string>("username", "");
  result->photo = parseArray<PhotoSize>(data, "photo");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatShared) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("request_id", object->requestId);
    json.put("chat_id", object->chatId);
    json.put("title", object->title);
    json.put("username", object->username);
    json.add_child("photo", put(object->photo));
  }
  return json;
}
DECLARE_PARSER_FROM_PTREE(WriteAccessAllowed) {
  auto result = std::make_shared<WriteAccessAllowed>();
  result->fromRequest = data.get<bool>("from_request", false);
  result->webAppName = data.get<std::string>("web_app_name", "");
  result->fromAttachmentMenu = data.get<bool>("from_attachment_menu", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(WriteAccessAllowed) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("from_request", object->fromRequest);
    json.put("web_app_name", object->webAppName);
    json.put("from_attachment_menu", object->fromAttachmentMenu);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(VideoChatScheduled) {
  auto result = std::make_shared<VideoChatScheduled>();
  result->startDate = data.get<std::int32_t>("start_date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(VideoChatScheduled) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("start_date", object->startDate);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(VideoChatStarted) {
  return std::make_shared<VideoChatStarted>(); // No fields to parse
}

DECLARE_PARSER_TO_PTREE(VideoChatStarted) {
  return boost::property_tree::ptree(); // Empty JSON for started chat
}

DECLARE_PARSER_FROM_PTREE(VideoChatEnded) {
  auto result = std::make_shared<VideoChatEnded>();
  result->duration = data.get<std::int32_t>("duration", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(VideoChatEnded) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("duration", object->duration);
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(VideoChatParticipantsInvited) {
  auto result = std::make_shared<VideoChatParticipantsInvited>();
  result->users = parseArray<User>(data, "users");
  return result;
}

DECLARE_PARSER_TO_PTREE(VideoChatParticipantsInvited) {
  boost::property_tree::ptree json;
  if (object) {
    json.add_child("users", put(object->users));
  }
  return json;
}

// GiveawayCreated Parser
DECLARE_PARSER_FROM_PTREE(GiveawayCreated) {
  return std::make_shared<GiveawayCreated>(); // No fields to parse
}

DECLARE_PARSER_TO_PTREE(GiveawayCreated) {
  return boost::property_tree::ptree(); // Empty JSON
}

// Giveaway Parser
DECLARE_PARSER_FROM_PTREE(Giveaway) {
  auto result = std::make_shared<Giveaway>();
  result->chats = parseArray<Chat>(data, "chats");
  result->winnersSelectionDate =
      data.get<std::uint32_t>("winners_selection_date", 0);
  result->winnerCount = data.get<std::int32_t>("winner_count", 0);
  result->onlyNewMembers = data.get<bool>("only_new_members", false);
  result->hasPublicWinners = data.get<bool>("has_public_winners", false);
  result->prizeDescription = data.get<std::string>("prize_description", "");
  result->countryCodes =
      parsePrimitiveArray<std::string>(data, "country_codes");
  result->premiumSubscriptionMonthCount =
      data.get<std::int32_t>("premium_subscription_month_count", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Giveaway) {
  boost::property_tree::ptree json;
  if (object) {
    json.add_child("chats", put(object->chats));
    json.put("winners_selection_date", object->winnersSelectionDate);
    json.put("winner_count", object->winnerCount);
    json.put("only_new_members", object->onlyNewMembers);
    json.put("has_public_winners", object->hasPublicWinners);
    json.put("prize_description", object->prizeDescription);
    json.add_child("country_codes", put(object->countryCodes));
    json.put("premium_subscription_month_count",
             object->premiumSubscriptionMonthCount);
  }
  return json;
}

// GiveawayWinners Parser
DECLARE_PARSER_FROM_PTREE(GiveawayWinners) {
  auto result = std::make_shared<GiveawayWinners>();
  result->chat = parse<Chat>(data, "chat");
  result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
  result->winnersSelectionDate =
      data.get<std::uint32_t>("winners_selection_date", 0);
  result->winnerCount = data.get<std::int32_t>("winner_count", 0);
  result->winners = parseArray<User>(data, "winners");
  result->additionalChatCount =
      data.get<std::int32_t>("additional_chat_count", 0);
  result->premiumSubscriptionMonthCount =
      data.get<std::int32_t>("premium_subscription_month_count", 0);
  result->unclaimedPrizeCount =
      data.get<std::int32_t>("unclaimed_prize_count", 0);
  result->onlyNewMembers = data.get<bool>("only_new_members", false);
  result->wasRefunded = data.get<bool>("was_refunded", false);
  result->prizeDescription = data.get<std::string>("prize_description", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(GiveawayWinners) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("giveaway_message_id", object->giveawayMessageId);
    json.put("winners_selection_date", object->winnersSelectionDate);
    json.put("winner_count", object->winnerCount);
    json.add_child("winners", put(object->winners));
    json.put("additional_chat_count", object->additionalChatCount);
    json.put("premium_subscription_month_count",
             object->premiumSubscriptionMonthCount);
    json.put("unclaimed_prize_count", object->unclaimedPrizeCount);
    json.put("only_new_members", object->onlyNewMembers);
    json.put("was_refunded", object->wasRefunded);
    json.put("prize_description", object->prizeDescription);
  }
  return json;
}
// GiveawayCompleted Parser
DECLARE_PARSER_FROM_PTREE(GiveawayCompleted) {
  auto result = std::make_shared<GiveawayCompleted>();
  result->winnerCount = data.get<std::int32_t>("winner_count", 0);
  result->unclaimedPrizeCount =
      data.get<std::int32_t>("unclaimed_prize_count", 0);
  result->giveawayMessage = parse<Message>(data, "giveaway_message");
  return result;
}

DECLARE_PARSER_TO_PTREE(GiveawayCompleted) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("winner_count", object->winnerCount);
    json.put("unclaimed_prize_count", object->unclaimedPrizeCount);
    json.add_child("giveaway_message", put(object->giveawayMessage));
  }
  return json;
}

// LinkPreviewOptions Parser
DECLARE_PARSER_FROM_PTREE(LinkPreviewOptions) {
  auto result = std::make_shared<LinkPreviewOptions>();
  result->isDisabled = data.get<bool>("is_disabled", false);
  result->url = data.get<std::string>("url", "");
  result->preferSmallMedia = data.get<bool>("prefer_small_media", false);
  result->preferLargeMedia = data.get<bool>("prefer_large_media", false);
  result->showAboveText = data.get<bool>("show_above_text", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(LinkPreviewOptions) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("is_disabled", object->isDisabled);
    json.put("url", object->url);
    json.put("prefer_small_media", object->preferSmallMedia);
    json.put("prefer_large_media", object->preferLargeMedia);
    json.put("show_above_text", object->showAboveText);
  }
  return json;
}

// UserProfilePhotos Parser
DECLARE_PARSER_FROM_PTREE(UserProfilePhotos) {
  auto result = std::make_shared<UserProfilePhotos>();
  result->totalCount = data.get<std::int32_t>("total_count", 0);
  result->photos = parseMatrix<PhotoSize>(data, "photos");
  return result;
}

DECLARE_PARSER_TO_PTREE(UserProfilePhotos) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("total_count", object->totalCount);
    json.add_child("photos", put(object->photos));
  }
  return json;
}

// File Parser
DECLARE_PARSER_FROM_PTREE(File) {
  auto result = std::make_shared<File>();
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->fileSize = data.get<std::int64_t>("file_size", 0);
  result->filePath = data.get<std::string>("file_path", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(File) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("file_id", object->fileId);
    json.put("file_unique_id", object->fileUniqueId);
    json.put("file_size", object->fileSize);
    json.put("file_path", object->filePath);
  }
  return json;
}

// WebAppInfo Parser
DECLARE_PARSER_FROM_PTREE(WebAppInfo) {
  auto result = std::make_shared<WebAppInfo>();
  result->url = data.get<std::string>("url", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(WebAppInfo) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("url", object->url);
  }
  return json;
}

// ReplyKeyboardMarkup Parser
DECLARE_PARSER_FROM_PTREE(ReplyKeyboardMarkup) {
  auto result = std::make_shared<ReplyKeyboardMarkup>();
  for (const auto &item : data.find("keyboard")->second) {
    result->keyboard.push_back(parseArray<KeyboardButton>(item.second));
  }
  result->isPersistent = data.get<bool>("is_persistent", false);
  result->resizeKeyboard = data.get<bool>("resize_keyboard", false);
  result->oneTimeKeyboard = data.get<bool>("one_time_keyboard", false);
  result->inputFieldPlaceholder =
      data.get<std::string>("input_field_placeholder", "");
  result->selective = data.get<bool>("selective", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(ReplyKeyboardMarkup) {
  boost::property_tree::ptree json;
  if (object) {
    json.add_child("keyboard", put(object->keyboard));
    json.put("is_persistent", object->isPersistent);
    json.put("resize_keyboard", object->resizeKeyboard);
    json.put("one_time_keyboard", object->oneTimeKeyboard);
    json.put("input_field_placeholder", object->inputFieldPlaceholder);
    json.put("selective", object->selective);
  }
  return json;
}

// KeyboardButton Parser
DECLARE_PARSER_FROM_PTREE(KeyboardButton) {
  auto result = std::make_shared<KeyboardButton>();
  result->text = data.get<std::string>("text", "");
  result->requestUsers =
      parse<KeyboardButtonRequestUsers>(data, "request_users");
  result->requestChat = parse<KeyboardButtonRequestChat>(data, "request_chat");
  result->requestContact = data.get<bool>("request_contact", false);
  result->requestLocation = data.get<bool>("request_location", false);
  result->requestPoll = parse<KeyboardButtonPollType>(data, "request_poll");
  result->webApp = parse<WebAppInfo>(data, "web_app");
  return result;
}

DECLARE_PARSER_TO_PTREE(KeyboardButton) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("text", object->text);
    json.add_child("request_users", put(object->requestUsers));
    json.add_child("request_chat", put(object->requestChat));
    json.put("request_contact", object->requestContact);
    json.put("request_location", object->requestLocation);
    json.add_child("request_poll", put(object->requestPoll));
    json.add_child("web_app", put(object->webApp));
  }
  return json;
}

// KeyboardButtonRequestUsers Parser
DECLARE_PARSER_FROM_PTREE(KeyboardButtonRequestUsers) {
  auto result = std::make_shared<KeyboardButtonRequestUsers>();
  result->requestId = data.get<std::int32_t>("request_id", 0);
  result->userIsBot = data.get<bool>("user_is_bot", false);
  result->userIsPremium = data.get<bool>("user_is_premium", false);
  result->maxQuantity = data.get<std::uint8_t>("max_quantity", 1);
  result->requestName = data.get<bool>("request_name", false);
  result->requestUsername = data.get<bool>("request_username", false);
  result->requestPhoto = data.get<bool>("request_photo", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(KeyboardButtonRequestUsers) {
  boost::property_tree::ptree json;
  if (object) {
    json.put("request_id", object->requestId);
    json.put("user_is_bot", object->userIsBot);
    json.put("user_is_premium", object->userIsPremium);
    json.put("max_quantity", object->maxQuantity);
    json.put("request_name", object->requestName);
    json.put("request_username", object->requestUsername);
    json.put("request_photo", object->requestPhoto);
  }
  return json;
}

// Function for parsing KeyboardButtonRequestChat from JSON
DECLARE_PARSER_FROM_PTREE(KeyboardButtonRequestChat) {
  auto result = std::make_shared<KeyboardButtonRequestChat>();
  result->requestId = data.get<std::int32_t>("request_id", 0);
  result->chatIsChannel = data.get<bool>("chat_is_channel", false);
  result->chatIsForum = data.get<bool>("chat_is_forum", false);
  result->chatHasUsername = data.get<bool>("chat_has_username", false);
  result->chatIsCreated = data.get<bool>("chat_is_created", false);
  result->userAdministratorRights =
      parse<ChatAdministratorRights>(data, "user_administrator_rights");
  result->botAdministratorRights =
      parse<ChatAdministratorRights>(data, "bot_administrator_rights");
  result->botIsMember = data.get<bool>("bot_is_member", false);
  result->requestTitle = data.get<bool>("request_title", false);
  result->requestUsername = data.get<bool>("request_username", false);
  result->requestPhoto = data.get<bool>("request_photo", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(KeyboardButtonRequestChat) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("request_id", object->requestId);
  json.put("chat_is_channel", object->chatIsChannel);
  json.put("chat_is_forum", object->chatIsForum);
  json.put("chat_has_username", object->chatHasUsername);
  json.put("chat_is_created", object->chatIsCreated);
  json.add_child("user_administrator_rights",
                 put(object->userAdministratorRights));
  json.add_child("bot_administrator_rights",
                 put(object->botAdministratorRights));
  json.put("bot_is_member", object->botIsMember);
  json.put("request_title", object->requestTitle);
  json.put("request_username", object->requestUsername);
  json.put("request_photo", object->requestPhoto);
  return json;
}

// Function for parsing KeyboardButtonPollType from JSON
DECLARE_PARSER_FROM_PTREE(KeyboardButtonPollType) {
  auto result = std::make_shared<KeyboardButtonPollType>();
  result->type = data.get<std::string>("type", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(KeyboardButtonPollType) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("type", object->type);
  return json;
}

// Function for parsing ReplyKeyboardRemove from JSON
DECLARE_PARSER_FROM_PTREE(ReplyKeyboardRemove) {
  auto result = std::make_shared<ReplyKeyboardRemove>();
  result->removeKeyboard = data.get<bool>("remove_keyboard", false);
  result->selective = data.get<bool>("selective", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(ReplyKeyboardRemove) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("remove_keyboard", object->removeKeyboard);
  json.put("selective", object->selective);
  return json;
}

// Function for parsing InlineKeyboardMarkup from JSON
DECLARE_PARSER_FROM_PTREE(InlineKeyboardMarkup) {
  auto result = std::make_shared<InlineKeyboardMarkup>();
  for (const auto &item : data.find("inline_keyboard")->second) {
    result->inlineKeyboard.push_back(
        parseArray<InlineKeyboardButton>(item.second));
  }
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineKeyboardMarkup) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("inline_keyboard", put(object->inlineKeyboard));
  return json;
}
DECLARE_PARSER_FROM_PTREE(ForceReply) {
  auto result = std::make_shared<ForceReply>();
  result->forceReply = data.get<bool>("force_reply", false);
  result->inputFieldPlaceholder =
      data.get<std::string>("input_field_placeholder", "");
  result->selective = data.get<bool>("selective", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(ForceReply) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("force_reply", object->forceReply);
  json.put("input_field_placeholder", object->inputFieldPlaceholder);
  json.put("selective", object->selective);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatPhoto) {
  auto result = std::make_shared<ChatPhoto>();
  result->smallFileId = data.get<std::string>("small_file_id", "");
  result->smallFileUniqueId = data.get<std::string>("small_file_unique_id", "");
  result->bigFileId = data.get<std::string>("big_file_id", "");
  result->bigFileUniqueId = data.get<std::string>("big_file_unique_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatPhoto) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("small_file_id", object->smallFileId);
  json.put("small_file_unique_id", object->smallFileUniqueId);
  json.put("big_file_id", object->bigFileId);
  json.put("big_file_unique_id", object->bigFileUniqueId);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatInviteLink) {
  auto result = std::make_shared<ChatInviteLink>();
  result->inviteLink = data.get<std::string>("invite_link", "");
  result->creator = parse<User>(data, "creator");
  result->createsJoinRequest = data.get<bool>("creates_join_request", false);
  result->isPrimary = data.get<bool>("is_primary", false);
  result->isRevoked = data.get<bool>("is_revoked", false);
  result->name = data.get<std::string>("name", "");
  result->expireDate = data.get<std::uint32_t>("expire_date", 0);
  result->memberLimit = data.get<std::uint32_t>("member_limit", 0);
  result->pendingJoinRequestCount =
      data.get<std::uint32_t>("pending_join_request_count", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatInviteLink) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("invite_link", object->inviteLink);
  json.add_child("creator", put(object->creator));
  json.put("creates_join_request", object->createsJoinRequest);
  json.put("is_primary", object->isPrimary);
  json.put("is_revoked", object->isRevoked);
  json.put("name", object->name);
  json.put("expire_date", object->expireDate);
  json.put("member_limit", object->memberLimit);
  json.put("pending_join_request_count", object->pendingJoinRequestCount);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatAdministratorRights) {
  auto result = std::make_shared<ChatAdministratorRights>();
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

DECLARE_PARSER_TO_PTREE(ChatAdministratorRights) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("is_anonymous", object->isAnonymous);
  json.put("can_manage_chat", object->canManageChat);
  json.put("can_delete_messages", object->canDeleteMessages);
  json.put("can_manage_video_chats", object->canManageVideoChats);
  json.put("can_restrict_members", object->canRestrictMembers);
  json.put("can_promote_members", object->canPromoteMembers);
  json.put("can_change_info", object->canChangeInfo);
  json.put("can_invite_users", object->canInviteUsers);
  json.put("can_post_stories", object->canPostStories);
  json.put("can_edit_stories", object->canEditStories);
  json.put("can_delete_stories", object->canDeleteStories);
  json.put("can_post_messages", object->canPostMessages);
  json.put("can_edit_messages", object->canEditMessages);
  json.put("can_pin_messages", object->canPinMessages);
  json.put("can_manage_topics", object->canManageTopics);
  return json;
}
DECLARE_PARSER_FROM_PTREE(ChatMemberUpdated) {
  auto result = std::make_shared<ChatMemberUpdated>();
  result->chat = parse<Chat>(data, "chat");
  result->from = parse<User>(data, "from");
  result->date = data.get<std::uint32_t>("date", 0);
  result->oldChatMember = parse<ChatMember>(data, "old_chat_member");
  result->newChatMember = parse<ChatMember>(data, "new_chat_member");
  result->inviteLink = parse<ChatInviteLink>(data, "invite_link");
  result->viaChatFolderInviteLink =
      data.get<bool>("via_chat_folder_invite_link", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatMemberUpdated) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("chat", put(object->chat));
  json.add_child("from", put(object->from));
  json.put("date", object->date);
  json.add_child("old_chat_member", put(object->oldChatMember));
  json.add_child("new_chat_member", put(object->newChatMember));
  json.add_child("invite_link", put(object->inviteLink));
  json.put("via_chat_folder_invite_link", object->viaChatFolderInviteLink);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatMember) {
  auto result = std::make_shared<ChatMember>();
  std::string status = data.get<std::string>("status", "");
  if (status == ChatMemberOwner::STATUS) {
    result = parse<ChatMemberOwner>(data);
  } else if (status == ChatMemberAdministrator::STATUS) {
    result = parse<ChatMemberAdministrator>(data);
  } else if (status == ChatMemberMember::STATUS) {
    result = parse<ChatMemberMember>(data);
  } else if (status == ChatMemberRestricted::STATUS) {
    result = parse<ChatMemberRestricted>(data);
  } else if (status == ChatMemberLeft::STATUS) {
    result = parse<ChatMemberLeft>(data);
  } else if (status == ChatMemberBanned::STATUS) {
    result = parse<ChatMemberBanned>(data);
  }
  result->status = status;
  result->user = parse<User>(data, "user");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatMember) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("status", object->status);
  json.add_child("user", put(object->user));

  if (object->status == ChatMemberOwner::STATUS) {
    json.add_child("extra", put<ChatMemberOwner>(object));
  } else if (object->status == ChatMemberAdministrator::STATUS) {
    json.add_child("extra", put<ChatMemberAdministrator>(object));
  } else if (object->status == ChatMemberMember::STATUS) {
    json.add_child("extra", put<ChatMemberMember>(object));
  } else if (object->status == ChatMemberRestricted::STATUS) {
    json.add_child("extra", put<ChatMemberRestricted>(object));
  } else if (object->status == ChatMemberLeft::STATUS) {
    json.add_child("extra", put<ChatMemberLeft>(object));
  } else if (object->status == ChatMemberBanned::STATUS) {
    json.add_child("extra", put<ChatMemberBanned>(object));
  }
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatMemberOwner) {
  auto result = std::make_shared<ChatMemberOwner>();
  result->isAnonymous = data.get<bool>("is_anonymous", false);
  result->customTitle = data.get<std::string>("custom_title", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatMemberOwner) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("is_anonymous", object->isAnonymous);
  json.put("custom_title", object->customTitle);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatMemberAdministrator) {
  auto result = std::make_shared<ChatMemberAdministrator>();
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

DECLARE_PARSER_TO_PTREE(ChatMemberAdministrator) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("can_be_edited", object->canBeEdited);
  json.put("is_anonymous", object->isAnonymous);
  json.put("can_manage_chat", object->canManageChat);
  json.put("can_delete_messages", object->canDeleteMessages);
  json.put("can_manage_video_chats", object->canManageVideoChats);
  json.put("can_restrict_members", object->canRestrictMembers);
  json.put("can_promote_members", object->canPromoteMembers);
  json.put("can_change_info", object->canChangeInfo);
  json.put("can_invite_users", object->canInviteUsers);
  json.put("can_post_stories", object->canPostStories);
  json.put("can_edit_stories", object->canEditStories);
  json.put("can_delete_stories", object->canDeleteStories);
  json.put("can_post_messages", object->canPostMessages);
  json.put("can_edit_messages", object->canEditMessages);
  json.put("can_pin_messages", object->canPinMessages);
  json.put("can_manage_topics", object->canManageTopics);
  json.put("custom_title", object->customTitle);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatMemberMember) {
  return std::make_shared<ChatMemberMember>();
}

DECLARE_PARSER_TO_PTREE(ChatMemberMember) {
  if (!object)
    return {};
  return {};
}

DECLARE_PARSER_FROM_PTREE(ChatMemberRestricted) {
  auto result = std::make_shared<ChatMemberRestricted>();
  result->isMember = data.get<bool>("is_member", false);
  result->canSendMessages = data.get<bool>("can_send_messages", false);
  result->canSendAudios = data.get<bool>("can_send_audios", false);
  result->canSendDocuments = data.get<bool>("can_send_documents", false);
  result->canSendPhotos = data.get<bool>("can_send_photos", false);
  result->canSendVideos = data.get<bool>("can_send_videos", false);
  result->canSendVideoNotes = data.get<bool>("can_send_video_notes", false);
  result->canSendVoiceNotes = data.get<bool>("can_send_voice_notes", false);
  result->canSendPolls = data.get<bool>("can_send_polls", false);
  result->canSendOtherMessages =
      data.get<bool>("can_send_other_messages", false);
  result->canAddWebPagePreviews =
      data.get<bool>("can_add_web_page_previews", false);
  result->canChangeInfo = data.get<bool>("can_change_info", false);
  result->canInviteUsers = data.get<bool>("can_invite_users", false);
  result->canPinMessages = data.get<bool>("can_pin_messages", false);
  result->canManageTopics = data.get<bool>("can_manage_topics", false);
  result->untilDate = data.get<std::uint32_t>("until_date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatMemberRestricted) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("is_member", object->isMember);
  json.put("can_send_messages", object->canSendMessages);
  json.put("can_send_audios", object->canSendAudios);
  json.put("can_send_documents", object->canSendDocuments);
  json.put("can_send_photos", object->canSendPhotos);
  json.put("can_send_videos", object->canSendVideos);
  json.put("can_send_video_notes", object->canSendVideoNotes);
  json.put("can_send_voice_notes", object->canSendVoiceNotes);
  json.put("can_send_polls", object->canSendPolls);
  json.put("can_send_other_messages", object->canSendOtherMessages);
  json.put("can_add_web_page_previews", object->canAddWebPagePreviews);
  json.put("can_change_info", object->canChangeInfo);
  json.put("can_invite_users", object->canInviteUsers);
  json.put("can_pin_messages", object->canPinMessages);
  json.put("can_manage_topics", object->canManageTopics);
  json.put("until_date", object->untilDate);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatMemberLeft) {
  return std::make_shared<ChatMemberLeft>();
}

DECLARE_PARSER_TO_PTREE(ChatMemberLeft) {
  if (!object)
    return {};
  return {};
}

DECLARE_PARSER_FROM_PTREE(ChatMemberBanned) {
  auto result = std::make_shared<ChatMemberBanned>();
  result->untilDate = data.get<std::uint32_t>("until_date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatMemberBanned) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("until_date", object->untilDate);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatJoinRequest) {
  auto result = std::make_shared<ChatJoinRequest>();
  result->chat = parse<Chat>(data, "chat");
  result->from = parse<User>(data, "from");
  result->userChatId = data.get<std::int64_t>("user_chat_id", 0);
  result->date = data.get<std::int32_t>("date", 0);
  result->bio = data.get<std::string>("bio", "");
  result->inviteLink = parse<ChatInviteLink>(data, "invite_link");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatJoinRequest) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("chat", put(object->chat));
  json.add_child("from", put(object->from));
  json.put("user_chat_id", object->userChatId);
  json.put("date", object->date);
  json.put("bio", object->bio);
  json.add_child("invite_link", put(object->inviteLink));
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatPermissions) {
  auto result = std::make_shared<ChatPermissions>();
  result->canSendMessages = data.get<bool>("can_send_messages", false);
  result->canSendAudios = data.get<bool>("can_send_audios", false);
  result->canSendDocuments = data.get<bool>("can_send_documents", false);
  result->canSendPhotos = data.get<bool>("can_send_photos", false);
  result->canSendVideos = data.get<bool>("can_send_videos", false);
  result->canSendVideoNotes = data.get<bool>("can_send_video_notes", false);
  result->canSendVoiceNotes = data.get<bool>("can_send_voice_notes", false);
  result->canSendPolls = data.get<bool>("can_send_polls", false);
  result->canSendOtherMessages =
      data.get<bool>("can_send_other_messages", false);
  result->canAddWebPagePreviews =
      data.get<bool>("can_add_web_page_previews", false);
  result->canChangeInfo = data.get<bool>("can_change_info", false);
  result->canInviteUsers = data.get<bool>("can_invite_users", false);
  result->canPinMessages = data.get<bool>("can_pin_messages", false);
  result->canManageTopics = data.get<bool>("can_manage_topics", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatPermissions) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("can_send_messages", object->canSendMessages);
  json.put("can_send_audios", object->canSendAudios);
  json.put("can_send_documents", object->canSendDocuments);
  json.put("can_send_photos", object->canSendPhotos);
  json.put("can_send_videos", object->canSendVideos);
  json.put("can_send_video_notes", object->canSendVideoNotes);
  json.put("can_send_voice_notes", object->canSendVoiceNotes);
  json.put("can_send_polls", object->canSendPolls);
  json.put("can_send_other_messages", object->canSendOtherMessages);
  json.put("can_add_web_page_previews", object->canAddWebPagePreviews);
  json.put("can_change_info", object->canChangeInfo);
  json.put("can_invite_users", object->canInviteUsers);
  json.put("can_pin_messages", object->canPinMessages);
  json.put("can_manage_topics", object->canManageTopics);
  return json;
}
DECLARE_PARSER_FROM_PTREE(Birthdate) {
  auto result = std::make_shared<Birthdate>();
  result->day = data.get<std::uint8_t>("day", 0);
  result->month = data.get<std::uint8_t>("month", 0);
  result->year = data.get<std::uint16_t>("year", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Birthdate) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("day", object->day);
  json.put("month", object->month);
  json.put("year", object->year);
  return json;
}

DECLARE_PARSER_FROM_PTREE(BusinessIntro) {
  auto result = std::make_shared<BusinessIntro>();
  result->title = data.get<std::string>("title", "");
  result->message = data.get<std::string>("message", "");
  result->sticker = parse<Sticker>(data, "sticker");
  return result;
}

DECLARE_PARSER_TO_PTREE(BusinessIntro) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("title", object->title);
  json.put("message", object->message);
  json.add_child("sticker", put(object->sticker));
  return json;
}

DECLARE_PARSER_FROM_PTREE(BusinessLocation) {
  auto result = std::make_shared<BusinessLocation>();
  result->address = data.get<std::string>("address", "");
  result->location = parse<Location>(data, "location");
  return result;
}

DECLARE_PARSER_TO_PTREE(BusinessLocation) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("address", object->address);
  json.add_child("location", put(object->location));
  return json;
}

DECLARE_PARSER_FROM_PTREE(BusinessOpeningHoursInterval) {
  auto result = std::make_shared<BusinessOpeningHoursInterval>();
  result->openingMinute = data.get<std::int32_t>("opening_minute", 0);
  result->closingMinute = data.get<std::int32_t>("closing_minute", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(BusinessOpeningHoursInterval) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("opening_minute", object->openingMinute);
  json.put("closing_minute", object->closingMinute);
  return json;
}

DECLARE_PARSER_FROM_PTREE(BusinessOpeningHours) {
  auto result = std::make_shared<BusinessOpeningHours>();
  result->timeZoneName = data.get<std::string>("time_zone_name", "");
  result->openingHours =
      parseArray<BusinessOpeningHoursInterval>(data, "opening_hours");
  return result;
}

DECLARE_PARSER_TO_PTREE(BusinessOpeningHours) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("time_zone_name", object->timeZoneName);
  json.add_child("opening_hours", put(object->openingHours));
  return json;
}

DECLARE_PARSER_FROM_PTREE(ChatLocation) {
  auto result = std::make_shared<ChatLocation>();
  result->location = parse<Location>(data, "location");
  result->address = data.get<std::string>("address", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChatLocation) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("location", put(object->location));
  json.put("address", object->address);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ReactionType) {
  std::string type = data.get<std::string>("type", "");
  ReactionType::Ptr result;

  if (type == ReactionTypeEmoji::TYPE) {
    result =
        std::static_pointer_cast<ReactionType>(parse<ReactionTypeEmoji>(data));
  } else if (type == ReactionTypeCustomEmoji::TYPE) {
    result = std::static_pointer_cast<ReactionType>(
        parse<ReactionTypeCustomEmoji>(data));
  } else {
    result = std::make_shared<ReactionType>();
  }

  result->type = type;
  return result;
}

DECLARE_PARSER_TO_PTREE(ReactionType) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("type", object->type);

  if (object->type == ReactionTypeEmoji::TYPE) {
    json.add_child("emoji", put(object));
  } else if (object->type == ReactionTypeCustomEmoji::TYPE) {
    json.add_child("custom_emoji", put(object));
  }

  return json;
}

DECLARE_PARSER_FROM_PTREE(ReactionTypeEmoji) {
  auto result = std::make_shared<ReactionTypeEmoji>();
  result->emoji = data.get<std::string>("emoji", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ReactionTypeEmoji) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("emoji", object->emoji);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ReactionTypeCustomEmoji) {
  auto result = std::make_shared<ReactionTypeCustomEmoji>();
  result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ReactionTypeCustomEmoji) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.put("custom_emoji_id", object->customEmojiId);
  return json;
}

DECLARE_PARSER_FROM_PTREE(ReactionCount) {
  auto result = std::make_shared<ReactionCount>();
  result->type = parse<ReactionType>(data, "type");
  result->totalCount = data.get<std::int32_t>("total_count", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(ReactionCount) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("type", put(object->type));
  json.put("total_count", object->totalCount);
  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageReactionUpdated) {
  auto result = std::make_shared<MessageReactionUpdated>();
  result->chat = parse<Chat>(data, "chat");
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->user = parse<User>(data, "user");
  result->actorChat = parse<Chat>(data, "actor_chat");
  result->date = data.get<std::uint32_t>("date", 0);
  result->oldReaction = parseArray<ReactionType>(data, "old_reaction");
  result->newReaction = parseArray<ReactionType>(data, "new_reaction");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageReactionUpdated) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("chat", put(object->chat));
  json.put("message_id", object->messageId);
  json.add_child("user", put(object->user));
  json.add_child("actor_chat", put(object->actorChat));
  json.put("date", object->date);
  json.add_child("old_reaction", put(object->oldReaction));
  json.add_child("new_reaction", put(object->newReaction));
  return json;
}

DECLARE_PARSER_FROM_PTREE(MessageReactionCountUpdated) {
  auto result = std::make_shared<MessageReactionCountUpdated>();
  result->chat = parse<Chat>(data, "chat");
  result->messageId = data.get<std::int32_t>("message_id", 0);
  result->date = data.get<std::uint32_t>("date", 0);
  result->reactions = parseArray<ReactionCount>(data, "reactions");
  return result;
}

DECLARE_PARSER_TO_PTREE(MessageReactionCountUpdated) {
  if (!object)
    return {};
  boost::property_tree::ptree json;
  json.add_child("chat", put(object->chat));
  json.put("message_id", object->messageId);
  json.put("date", object->date);
  json.add_child("reactions", put(object->reactions));
  return json;
}

DECLARE_PARSER_FROM_PTREE(ForumTopic) {
  auto result = std::make_shared<ForumTopic>();
  result->messageThreadId = data.get<std::int32_t>("message_thread_id", 0);
  result->name = data.get<std::string>("name", "");
  result->iconColor = data.get<std::int32_t>("icon_color", 0);
  result->iconCustomEmojiId = data.get<std::string>("icon_custom_emoji_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ForumTopic) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("message_thread_id", object->messageThreadId);
  ptree.add("name", object->name);
  ptree.add("icon_color", object->iconColor);
  ptree.add("icon_custom_emoji_id", object->iconCustomEmojiId);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotCommand) {
  auto result = std::make_shared<BotCommand>();
  result->command = data.get<std::string>("command", "");
  result->description = data.get<std::string>("description", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(BotCommand) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("command", object->command);
  ptree.add("description", object->description);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotCommandScope) {
  std::string type = data.get<std::string>("type", "");
  BotCommandScope::Ptr result;

  if (type == BotCommandScopeDefault::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeDefault>(data));
  } else if (type == BotCommandScopeAllPrivateChats::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeAllPrivateChats>(data));
  } else if (type == BotCommandScopeAllGroupChats::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeAllGroupChats>(data));
  } else if (type == BotCommandScopeAllChatAdministrators::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeAllChatAdministrators>(data));
  } else if (type == BotCommandScopeChat::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeChat>(data));
  } else if (type == BotCommandScopeChatAdministrators::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeChatAdministrators>(data));
  } else if (type == BotCommandScopeChatMember::TYPE) {
    result = std::static_pointer_cast<BotCommandScope>(
        parse<BotCommandScopeChatMember>(data));
  } else {
    result = std::make_shared<BotCommandScope>();
  }

  result->type = type;
  return result;
}

DECLARE_PARSER_TO_PTREE(BotCommandScope) {
  boost::property_tree::ptree ptree;
  if (!object)
    return {}; // Return an empty ptree if object is null
  ptree.add("type", object->type);

  if (object->type == BotCommandScopeDefault::TYPE) {
    ptree.add_child("", put<BotCommandScopeDefault>(object));
  } else if (object->type == BotCommandScopeAllPrivateChats::TYPE) {
    ptree.add_child("", put<BotCommandScopeAllPrivateChats>(object));
  } else if (object->type == BotCommandScopeAllGroupChats::TYPE) {
    ptree.add_child("", put<BotCommandScopeAllGroupChats>(object));
  } else if (object->type == BotCommandScopeAllChatAdministrators::TYPE) {
    ptree.add_child("", put<BotCommandScopeAllChatAdministrators>(object));
  } else if (object->type == BotCommandScopeChat::TYPE) {
    ptree.add_child("", put<BotCommandScopeChat>(object));
  } else if (object->type == BotCommandScopeChatAdministrators::TYPE) {
    ptree.add_child("", put<BotCommandScopeChatAdministrators>(object));
  } else if (object->type == BotCommandScopeChatMember::TYPE) {
    ptree.add_child("", put<BotCommandScopeChatMember>(object));
  }
  return ptree;
}

// Parsing from JSON to BotCommandScopeChatAdministrators
DECLARE_PARSER_FROM_PTREE(BotCommandScopeChatAdministrators) {
  auto result = std::make_shared<BotCommandScopeChatAdministrators>();
  result->chatId = data.get<std::int64_t>("chat_id", 0);
  return result;
}

// Serializing BotCommandScopeChatAdministrators to JSON
DECLARE_PARSER_TO_PTREE(BotCommandScopeChatAdministrators) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("chat_id", object->chatId);

  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotCommandScopeChat) {
  auto result = std::make_shared<BotCommandScopeChat>();
  result->chatId = data.get<std::int64_t>("chat_id", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeChat) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("chat_id", object->chatId);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotCommandScopeChatMember) {
  auto result = std::make_shared<BotCommandScopeChatMember>();
  result->chatId = data.get<std::int64_t>("chat_id", 0);
  result->userId = data.get<std::int64_t>("user_id", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeChatMember) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("chat_id", object->chatId);
  ptree.add("user_id", object->userId);
  return ptree;
}
// BotName Parsing
DECLARE_PARSER_TO_PTREE(BotName) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("name", object->name);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotName) {
  auto result = std::make_shared<BotName>();
  result->name = data.get<std::string>("name", "");
  return result;
}

// BotDescription Parsing
DECLARE_PARSER_TO_PTREE(BotDescription) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("description", object->description);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotDescription) {
  auto result = std::make_shared<BotDescription>();
  result->description = data.get<std::string>("description", "");
  return result;
}

// BotShortDescription Parsing
DECLARE_PARSER_TO_PTREE(BotShortDescription) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("short_description", object->shortDescription);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BotShortDescription) {
  auto result = std::make_shared<BotShortDescription>();
  result->shortDescription = data.get<std::string>("short_description", "");
  return result;
}

// ChatBoostSource Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostSource) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("source", object->source);
  ptree.add_child("user", put(object->user));

  if (object->source == ChatBoostSourcePremium::SOURCE) {
    ptree.add_child("", put<ChatBoostSourcePremium>(object));
  } else if (object->source == ChatBoostSourceGiftCode::SOURCE) {
    ptree.add_child("", put<ChatBoostSourceGiftCode>(object));
  } else if (object->source == ChatBoostSourceGiveaway::SOURCE) {
    ptree.add_child("", put<ChatBoostSourceGiveaway>(object));
  }
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChatBoostSource) {
  std::string source = data.get<std::string>("source", "");
  ChatBoostSource::Ptr result;

  if (source == ChatBoostSourcePremium::SOURCE) {
    result = parse<ChatBoostSourcePremium>(data);
  } else if (source == ChatBoostSourceGiftCode::SOURCE) {
    result = parse<ChatBoostSourceGiftCode>(data);
  } else if (source == ChatBoostSourceGiveaway::SOURCE) {
    result = parse<ChatBoostSourceGiveaway>(data);
  } else {
    result = std::make_shared<ChatBoostSource>();
  }

  result->source = source;
  result->user = parse<User>(data, "user");
  return result;
}

// MenuButton Parsing
DECLARE_PARSER_TO_PTREE(MenuButton) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("type", object->type);

  if (object->type == MenuButtonCommands::TYPE) {
    ptree.add_child("", put<MenuButtonCommands>(object));
  } else if (object->type == MenuButtonWebApp::TYPE) {
    ptree.add_child("", put<MenuButtonWebApp>(object));
  } else if (object->type == MenuButtonDefault::TYPE) {
    ptree.add_child("", put<MenuButtonDefault>(object));
  }
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(MenuButton) {
  std::string type = data.get<std::string>("type", "");
  MenuButton::Ptr result;

  if (type == MenuButtonCommands::TYPE) {
    result = parse<MenuButtonCommands>(data);
  } else if (type == MenuButtonWebApp::TYPE) {
    result = parse<MenuButtonWebApp>(data);
  } else if (type == MenuButtonDefault::TYPE) {
    result = parse<MenuButtonDefault>(data);
  } else {
    result = std::make_shared<MenuButton>();
  }

  result->type = type;
  return result;
}

// ChatBoost Parsing
DECLARE_PARSER_TO_PTREE(ChatBoost) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("boost_id", object->boostId);
  ptree.add("add_date", object->addDate);
  ptree.add("expiration_date", object->expirationDate);
  ptree.add_child("source", put(object->source));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChatBoost) {
  auto result = std::make_shared<ChatBoost>();
  result->boostId = data.get<std::string>("boost_id", "");
  result->addDate = data.get<std::uint32_t>("add_date", 0);
  result->expirationDate = data.get<std::uint32_t>("expiration_date", 0);
  result->source = parse<ChatBoostSource>(data, "source");
  return result;
}

// ChatBoostUpdated Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostUpdated) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add_child("chat", put(object->chat));
  ptree.add_child("boost", put(object->boost));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChatBoostUpdated) {
  auto result = std::make_shared<ChatBoostUpdated>();
  result->chat = parse<Chat>(data, "chat");
  result->boost = parse<ChatBoost>(data, "boost");
  return result;
}

// ChatBoostRemoved Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostRemoved) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add_child("chat", put(object->chat));
  ptree.add("boost_id", object->boostId);
  ptree.add("remove_date", object->removeDate);
  ptree.add_child("source", put(object->source));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChatBoostRemoved) {
  auto result = std::make_shared<ChatBoostRemoved>();
  result->chat = parse<Chat>(data, "chat");
  result->boostId = data.get<std::string>("boost_id", "");
  result->removeDate = data.get<std::uint32_t>("remove_date", 0);
  result->source = parse<ChatBoostSource>(data, "source");
  return result;
}

// UserChatBoosts Parsing
DECLARE_PARSER_TO_PTREE(UserChatBoosts) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add_child("boosts", put(object->boosts));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(UserChatBoosts) {
  auto result = std::make_shared<UserChatBoosts>();
  result->boosts = parseArray<ChatBoost>(data, "boosts");
  return result;
}

// MenuButton Commands Parsing
DECLARE_PARSER_TO_PTREE(MenuButtonCommands) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  return ptree; // Add any MenuButtonCommands specific fields if needed
}

DECLARE_PARSER_FROM_PTREE(MenuButtonCommands) {
  auto result = std::make_shared<MenuButtonCommands>();
  return result;
}

// MenuButton WebApp Parsing
DECLARE_PARSER_TO_PTREE(MenuButtonWebApp) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("text", object->text);
  ptree.add_child("web_app", put(object->webApp));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(MenuButtonWebApp) {
  auto result = std::make_shared<MenuButtonWebApp>();
  result->text = data.get<std::string>("text", "");
  result->webApp = parse<WebAppInfo>(data, "web_app");
  return result;
}

// MenuButton Default Parsing
DECLARE_PARSER_TO_PTREE(MenuButtonDefault) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  return ptree; // Add any MenuButtonDefault specific fields if needed
}

DECLARE_PARSER_FROM_PTREE(MenuButtonDefault) {
  auto result = std::make_shared<MenuButtonDefault>();
  return result;
}

// ChatBoostSourcePremium Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostSourcePremium) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  return ptree; // Add specific fields for ChatBoostSourcePremium if any
}

DECLARE_PARSER_FROM_PTREE(ChatBoostSourcePremium) {
  auto result = std::make_shared<ChatBoostSourcePremium>();
  return result;
}

// ChatBoostSourceGiftCode Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostSourceGiftCode) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  return ptree; // Add specific fields for ChatBoostSourceGiftCode if any
}

DECLARE_PARSER_FROM_PTREE(ChatBoostSourceGiftCode) {
  auto result = std::make_shared<ChatBoostSourceGiftCode>();
  return result;
}

// ChatBoostSourceGiveaway Parsing
DECLARE_PARSER_TO_PTREE(ChatBoostSourceGiveaway) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("giveaway_message_id", object->giveawayMessageId);
  ptree.add("is_unclaimed", object->isUnclaimed);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChatBoostSourceGiveaway) {
  auto result = std::make_shared<ChatBoostSourceGiveaway>();
  result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
  result->isUnclaimed = data.get<bool>("is_unclaimed", false);
  return result;
}

// BusinessConnection Parsing
DECLARE_PARSER_TO_PTREE(BusinessConnection) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("id", object->id);
  ptree.add_child("user", put(object->user));
  ptree.add("user_chat_id", object->userChatId);
  ptree.add("date", object->date);
  ptree.add("can_reply", object->canReply);
  ptree.add("is_enabled", object->isEnabled);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BusinessConnection) {
  auto result = std::make_shared<BusinessConnection>();
  result->id = data.get<std::string>("id", "");
  result->user = parse<User>(data, "user");
  result->userChatId = data.get<std::int64_t>("user_chat_id", 0);
  result->date = data.get<std::uint32_t>("date", 0);
  result->canReply = data.get<bool>("can_reply", false);
  result->isEnabled = data.get<bool>("is_enabled", false);
  return result;
}

// BusinessMessagesDeleted Parsing
DECLARE_PARSER_TO_PTREE(BusinessMessagesDeleted) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("business_connection_id", object->businessConnectionId);
  ptree.add_child("chat", put(object->chat));
  ptree.add_child("message_ids", put(object->messageIds));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(BusinessMessagesDeleted) {
  auto result = std::make_shared<BusinessMessagesDeleted>();
  result->businessConnectionId =
      data.get<std::string>("business_connection_id", "");
  result->chat = parse<Chat>(data, "chat");
  result->messageIds = parsePrimitiveArray<std::int32_t>(data, "message_ids");
  return result;
}

// ResponseParameters Parsing
DECLARE_PARSER_TO_PTREE(ResponseParameters) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("migrate_to_chat_id", object->migrateToChatId);
  ptree.add("retry_after", object->retryAfter);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ResponseParameters) {
  auto result = std::make_shared<ResponseParameters>();
  result->migrateToChatId = data.get<std::int64_t>("migrate_to_chat_id", 0);
  result->retryAfter = data.get<std::int32_t>("retry_after", 0);
  return result;
}

// InputMedia Parsing
DECLARE_PARSER_TO_PTREE(InputMedia) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("type", object->type);
  ptree.add("media", object->media);
  ptree.add("caption", object->caption);
  ptree.add("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));

  if (object->type == InputMediaPhoto::TYPE) {
    ptree.add_child("", put<InputMediaPhoto>(object));
  } else if (object->type == InputMediaVideo::TYPE) {
    ptree.add_child("", put<InputMediaVideo>(object));
  } else if (object->type == InputMediaAnimation::TYPE) {
    ptree.add_child("", put<InputMediaAnimation>(object));
  } else if (object->type == InputMediaAudio::TYPE) {
    ptree.add_child("", put<InputMediaAudio>(object));
  } else if (object->type == InputMediaDocument::TYPE) {
    ptree.add_child("", put<InputMediaDocument>(object));
  }

  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMedia) {
  std::string type = data.get<std::string>("type", "");
  InputMedia::Ptr result;

  if (type == InputMediaPhoto::TYPE) {
    result = parse<InputMediaPhoto>(data);
  } else if (type == InputMediaVideo::TYPE) {
    result = parse<InputMediaVideo>(data);
  } else if (type == InputMediaAnimation::TYPE) {
    result = parse<InputMediaAnimation>(data);
  } else if (type == InputMediaAudio::TYPE) {
    result = parse<InputMediaAudio>(data);
  } else if (type == InputMediaDocument::TYPE) {
    result = parse<InputMediaDocument>(data);
  } else {
    result = std::make_shared<InputMedia>();
  }

  result->type = data.get<std::string>("type", "");
  result->media = data.get<std::string>("media", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");

  return result;
}

// InputMediaPhoto Parsing
DECLARE_PARSER_TO_PTREE(InputMediaPhoto) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("has_spoiler", object->hasSpoiler);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMediaPhoto) {
  auto result = std::make_shared<InputMediaPhoto>();
  result->hasSpoiler = data.get<bool>("has_spoiler", false);
  return result;
}

// InputMediaVideo Parsing
DECLARE_PARSER_TO_PTREE(InputMediaVideo) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("thumbnail", object->thumbnail);
  ptree.add("width", object->width);
  ptree.add("height", object->height);
  ptree.add("duration", object->duration);
  ptree.add("supports_streaming", object->supportsStreaming);
  ptree.add("has_spoiler", object->hasSpoiler);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMediaVideo) {
  auto result = std::make_shared<InputMediaVideo>();
  result->thumbnail = data.get<std::string>("thumbnail", "");
  result->width = data.get<std::int32_t>("width", 0);
  result->height = data.get<std::int32_t>("height", 0);
  result->duration = data.get<std::int32_t>("duration", 0);
  result->supportsStreaming = data.get<bool>("supports_streaming", false);
  result->hasSpoiler = data.get<bool>("has_spoiler", false);
  return result;
}

// InputMediaAnimation Parsing
DECLARE_PARSER_TO_PTREE(InputMediaAnimation) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("thumbnail", object->thumbnail);
  ptree.add("width", object->width);
  ptree.add("height", object->height);
  ptree.add("duration", object->duration);
  ptree.add("has_spoiler", object->hasSpoiler);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMediaAnimation) {
  auto result = std::make_shared<InputMediaAnimation>();
  result->thumbnail = data.get<std::string>("thumbnail", "");
  result->width = data.get<std::int32_t>("width", 0);
  result->height = data.get<std::int32_t>("height", 0);
  result->duration = data.get<std::int32_t>("duration", 0);
  result->hasSpoiler = data.get<bool>("has_spoiler", false);
  return result;
}

// InputMediaAudio Parsing
DECLARE_PARSER_TO_PTREE(InputMediaAudio) {
  boost::property_tree::ptree ptree;
  if (!object)
    return ptree;
  ptree.add("thumbnail", object->thumbnail);
  ptree.add("duration", object->duration);
  ptree.add("performer", object->performer);
  ptree.add("title", object->title);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMediaAudio) {
  auto result = std::make_shared<InputMediaAudio>();
  result->thumbnail = data.get<std::string>("thumbnail", "");
  result->duration = data.get<std::int32_t>("duration", 0);
  result->performer = data.get<std::string>("performer", "");
  result->title = data.get<std::string>("title", "");
  return result;
}

// InputMediaDocument
DECLARE_PARSER_FROM_PTREE(InputMediaDocument) {
  auto result = std::make_shared<InputMediaDocument>();
  result->thumbnail = data.get<std::string>("thumbnail", "");
  result->disableContentTypeDetection =
      data.get<bool>("disable_content_type_detection", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(InputMediaDocument) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("thumbnail", object->thumbnail);
  ptree.put("disable_content_type_detection",
            object->disableContentTypeDetection);
  return ptree;
}

// Sticker
DECLARE_PARSER_FROM_PTREE(Sticker) {
  auto result = std::make_shared<Sticker>();
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
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  result->emoji = data.get<std::string>("emoji", "");
  result->setName = data.get<std::string>("set_name", "");
  result->premiumAnimation = parse<File>(data, "premium_animation");
  result->maskPosition = parse<MaskPosition>(data, "mask_position");
  result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
  result->needsRepainting = data.get<bool>("needs_repainting", true);
  result->fileSize = data.get<std::int32_t>("file_size", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Sticker) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_id", object->fileId);
  ptree.put("file_unique_id", object->fileUniqueId);
  if (object->type == Sticker::Type::Regular) {
    ptree.put("type", "regular");
  } else if (object->type == Sticker::Type::Mask) {
    ptree.put("type", "mask");
  } else if (object->type == Sticker::Type::CustomEmoji) {
    ptree.put("type", "custom_emoji");
  }
  ptree.put("width", object->width);
  ptree.put("height", object->height);
  ptree.put("is_animated", object->isAnimated);
  ptree.put("is_video", object->isVideo);
  ptree.add_child("thumbnail", put(object->thumbnail));
  ptree.put("emoji", object->emoji);
  ptree.put("set_name", object->setName);
  ptree.add_child("premium_animation", put(object->premiumAnimation));
  ptree.add_child("mask_position", put(object->maskPosition));
  ptree.put("custom_emoji_id", object->customEmojiId);
  ptree.put("needs_repainting", object->needsRepainting);
  ptree.put("file_size", object->fileSize);
  return ptree;
}

// StickerSet
DECLARE_PARSER_FROM_PTREE(StickerSet) {
  auto result = std::make_shared<StickerSet>();
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
  result->stickers = parseArray<Sticker>(data, "stickers");
  result->thumbnail = parse<PhotoSize>(data, "thumbnail");
  return result;
}

// BotCommandScopeDefault
DECLARE_PARSER_FROM_PTREE(BotCommandScopeDefault) {
  return std::make_shared<BotCommandScopeDefault>();
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeDefault) {
  if (!object)
    return {};
  return {};
}

// BotCommandScopeAllPrivateChats
DECLARE_PARSER_FROM_PTREE(BotCommandScopeAllPrivateChats) {
  return std::make_shared<BotCommandScopeAllPrivateChats>();
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeAllPrivateChats) {
  if (!object)
    return {};
  return {};
}

// BotCommandScopeAllGroupChats
DECLARE_PARSER_FROM_PTREE(BotCommandScopeAllGroupChats) {
  return std::make_shared<BotCommandScopeAllGroupChats>();
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeAllGroupChats) {
  if (!object)
    return {};
  return {};
}

// BotCommandScopeAllChatAdministrators
DECLARE_PARSER_FROM_PTREE(BotCommandScopeAllChatAdministrators) {
  return std::make_shared<BotCommandScopeAllChatAdministrators>();
}

DECLARE_PARSER_TO_PTREE(BotCommandScopeAllChatAdministrators) {
  if (!object)
    return {};
  return {};
}

DECLARE_PARSER_TO_PTREE(StickerSet) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("name", object->name);
  ptree.put("title", object->title);
  if (object->stickerType == StickerSet::Type::Regular) {
    ptree.put("sticker_type", "regular");
  } else if (object->stickerType == StickerSet::Type::Mask) {
    ptree.put("sticker_type", "mask");
  } else if (object->stickerType == StickerSet::Type::CustomEmoji) {
    ptree.put("sticker_type", "custom_emoji");
  }
  ptree.add_child("stickers", put(object->stickers));
  ptree.add_child("thumbnail", put(object->thumbnail));
  return ptree;
}

// CallbackQuery
DECLARE_PARSER_FROM_PTREE(CallbackQuery) {
  auto result = std::make_shared<CallbackQuery>();
  result->id = data.get<std::string>("id", "");
  result->from = parse<User>(data, "from");
  result->message = parse<Message>(data, "message");
  result->inlineMessageId = data.get<std::string>("inline_message_id", "");
  result->chatInstance = data.get<std::string>("chat_instance", "");
  result->data = data.get<std::string>("data", "");
  result->gameShortName = data.get<std::string>("game_short_name", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(CallbackQuery) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("id", object->id);
  ptree.add_child("from", put(object->from));
  ptree.add_child("message", put(object->message));
  ptree.put("inline_message_id", object->inlineMessageId);
  ptree.put("chat_instance", object->chatInstance);
  ptree.put("data", object->data);
  ptree.put("game_short_name", object->gameShortName);
  return ptree;
}

// MaskPosition
DECLARE_PARSER_FROM_PTREE(MaskPosition) {
  auto result = std::make_shared<MaskPosition>();
  result->point = data.get<std::string>("point", "");
  result->xShift = data.get<float>("x_shift", 0);
  result->yShift = data.get<float>("y_shift", 0);
  result->scale = data.get<float>("scale", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(MaskPosition) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("point", object->point);
  ptree.put("x_shift", object->xShift);
  ptree.put("y_shift", object->yShift);
  ptree.put("scale", object->scale);
  return ptree;
}
// Parsing from JSON to InlineQuery
DECLARE_PARSER_FROM_PTREE(InlineQuery) {
  auto result = std::make_shared<InlineQuery>();
  result->id = data.get<std::string>("id", "");
  result->from = parse<User>(data, "from");
  result->query = data.get<std::string>("query", "");
  result->offset = data.get<std::string>("offset", "");
  result->chatType = data.get<std::string>("chat_type", "");
  result->location = parse<Location>(data, "location");
  return result;
}

// Serializing InlineQuery to JSON
DECLARE_PARSER_TO_PTREE(InlineQuery) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("id", object->id);
  ptree.add_child("from", put(object->from));
  ptree.put("query", object->query);
  ptree.put("offset", object->offset);
  ptree.put("chat_type", object->chatType);
  ptree.add_child("location", put(object->location));

  return ptree;
}

// Parsing from JSON to InlineKeyboardButton
DECLARE_PARSER_FROM_PTREE(InlineKeyboardButton) {
  auto result = std::make_shared<InlineKeyboardButton>();
  result->text = data.get<std::string>("text", "");
  result->url = data.get<std::string>("url", "");
  result->callbackData = data.get<std::string>("callback_data", "");
  result->webApp = parse<WebAppInfo>(data, "web_app");
  result->loginUrl = parse<LoginUrl>(data, "login_url");
  result->switchInlineQuery = data.get<std::string>("switch_inline_query", "");
  result->switchInlineQueryCurrentChat =
      data.get<std::string>("switch_inline_query_current_chat", "");
  result->switchInlineQueryChosenChat = parse<SwitchInlineQueryChosenChat>(
      data, "switch_inline_query_chosen_chat");
  result->callbackGame = parse<CallbackGame>(data, "callback_game");
  result->pay = data.get<bool>("pay", false);
  return result;
}

// Serializing InlineKeyboardButton to JSON
DECLARE_PARSER_TO_PTREE(InlineKeyboardButton) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("text", object->text);
  ptree.put("url", object->url);
  ptree.put("callback_data", object->callbackData);
  ptree.add_child("web_app", put(object->webApp));
  ptree.add_child("login_url", put(object->loginUrl));
  ptree.put("switch_inline_query", object->switchInlineQuery);
  ptree.put("switch_inline_query_current_chat",
            object->switchInlineQueryCurrentChat);
  ptree.add_child("switch_inline_query_chosen_chat",
                  put(object->switchInlineQueryChosenChat));
  ptree.add_child("callback_game", put(object->callbackGame));
  ptree.put("pay", object->pay);

  return ptree;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResult) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.add("type", object->type);
  ptree.add("id", object->id);
  ptree.add_child("reply_markup", put(object->replyMarkup));

  if (object->type == InlineQueryResultCachedAudio::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedAudio>(object));
  } else if (object->type == InlineQueryResultCachedDocument::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedDocument>(object));
  } else if (object->type == InlineQueryResultCachedGif::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedGif>(object));
  } else if (object->type == InlineQueryResultCachedMpeg4Gif::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedMpeg4Gif>(object));
  } else if (object->type == InlineQueryResultCachedPhoto::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedPhoto>(object));
  } else if (object->type == InlineQueryResultCachedSticker::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedSticker>(object));
  } else if (object->type == InlineQueryResultCachedVideo::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedVideo>(object));
  } else if (object->type == InlineQueryResultCachedVoice::TYPE) {
    ptree.add_child("data", put<InlineQueryResultCachedVoice>(object));
  } else if (object->type == InlineQueryResultArticle::TYPE) {
    ptree.add_child("data", put<InlineQueryResultArticle>(object));
  } else if (object->type == InlineQueryResultAudio::TYPE) {
    ptree.add_child("data", put<InlineQueryResultAudio>(object));
  } else if (object->type == InlineQueryResultContact::TYPE) {
    ptree.add_child("data", put<InlineQueryResultContact>(object));
  } else if (object->type == InlineQueryResultGame::TYPE) {
    ptree.add_child("data", put<InlineQueryResultGame>(object));
  } else if (object->type == InlineQueryResultDocument::TYPE) {
    ptree.add_child("data", put<InlineQueryResultDocument>(object));
  } else if (object->type == InlineQueryResultLocation::TYPE) {
    ptree.add_child("data", put<InlineQueryResultLocation>(object));
  } else if (object->type == InlineQueryResultVenue::TYPE) {
    ptree.add_child("data", put<InlineQueryResultVenue>(object));
  } else if (object->type == InlineQueryResultVoice::TYPE) {
    ptree.add_child("data", put<InlineQueryResultVoice>(object));
  } else if (object->type == InlineQueryResultPhoto::TYPE) {
    ptree.add_child("data", put<InlineQueryResultPhoto>(object));
  } else if (object->type == InlineQueryResultGif::TYPE) {
    ptree.add_child("data", put<InlineQueryResultGif>(object));
  } else if (object->type == InlineQueryResultMpeg4Gif::TYPE) {
    ptree.add_child("data", put<InlineQueryResultMpeg4Gif>(object));
  } else if (object->type == InlineQueryResultVideo::TYPE) {
    ptree.add_child("data", put<InlineQueryResultVideo>(object));
  }
  return ptree;
}
// Parsing from JSON to InputSticker
DECLARE_PARSER_FROM_PTREE(InputSticker) {
  auto result = std::make_shared<InputSticker>();
  result->sticker = data.get<std::string>("sticker", "");
  result->format = data.get<std::string>("format", "");
  result->emojiList = parsePrimitiveArray<std::string>(data, "emoji_list");
  result->maskPosition = parse<MaskPosition>(data, "mask_position");
  result->keywords = parsePrimitiveArray<std::string>(data, "keywords");
  return result;
}

// Serializing InputSticker to JSON
DECLARE_PARSER_TO_PTREE(InputSticker) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("sticker", object->sticker);
  ptree.put("format", object->format);
  ptree.add_child("emoji_list", put(object->emojiList));
  ptree.add_child("mask_position", put(object->maskPosition));
  ptree.add_child("keywords", put(object->keywords));

  return ptree;
}
// Parsing from JSON to SwitchInlineQueryChosenChat
DECLARE_PARSER_FROM_PTREE(SwitchInlineQueryChosenChat) {
    auto result = std::make_shared<SwitchInlineQueryChosenChat>();
    result->query = data.get<std::string>("query", "");
    result->allowUserChats = data.get<bool>("allow_user_chats", false);
    result->allowBotChats = data.get<bool>("allow_bot_chats", false);
    result->allowGroupChats = data.get<bool>("allow_group_chats", false);
    result->allowChannelChats = data.get<bool>("allow_channel_chats", false);
    return result;
}

// Serializing SwitchInlineQueryChosenChat to JSON
DECLARE_PARSER_TO_PTREE(SwitchInlineQueryChosenChat) {
    if (!object) return {};
    
    boost::property_tree::ptree ptree;
    ptree.put("query", object->query);
    ptree.put("allow_user_chats", object->allowUserChats);
    ptree.put("allow_bot_chats", object->allowBotChats);
    ptree.put("allow_group_chats", object->allowGroupChats);
    ptree.put("allow_channel_chats", object->allowChannelChats);
    
    return ptree;
}

// Parsing from JSON to LoginUrl
DECLARE_PARSER_FROM_PTREE(LoginUrl) {
    auto result = std::make_shared<LoginUrl>();
    result->url = data.get<std::string>("url", "");
    result->forwardText = data.get<std::string>("forward_text", "");
    result->botUsername = data.get<std::string>("bot_username", "");
    result->requestWriteAccess = data.get<bool>("request_write_access", false);
    return result;
}

// Serializing LoginUrl to JSON
DECLARE_PARSER_TO_PTREE(LoginUrl) {
    if (!object) return {};
    
    boost::property_tree::ptree ptree;
    ptree.put("url", object->url);
    ptree.put("forward_text", object->forwardText);
    ptree.put("bot_username", object->botUsername);
    ptree.put("request_write_access", object->requestWriteAccess);
    
    return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultsButton) {
  auto result = std::make_shared<InlineQueryResultsButton>();
  result->text = data.get<std::string>("text", "");
  result->webApp = parse<WebAppInfo>(data, "web_app");
  result->startParameter = data.get<std::string>("start_parameter", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultsButton) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("text", object->text);
  ptree.add_child("web_app", put(object->webApp));
  ptree.put("start_parameter", object->startParameter);

  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultArticle) {
  auto result = std::make_shared<InlineQueryResultArticle>();
  result->title = data.get<std::string>("title", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  result->url = data.get<std::string>("url", "");
  result->hideUrl = data.get<bool>("hide_url", false);
  result->description = data.get<std::string>("description", "");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
  result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultArticle) {
  if (!object)
    return {};

  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  ptree.put("url", object->url);
  ptree.put("hide_url", object->hideUrl);
  ptree.put("description", object->description);
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_width", object->thumbnailWidth);
  ptree.put("thumbnail_height", object->thumbnailHeight);

  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultPhoto) {
  auto result = std::make_shared<InlineQueryResultPhoto>();
  result->photoUrl = data.get<std::string>("photo_url", "");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->photoWidth = data.get<std::int32_t>("photo_width", 0);
  result->photoHeight = data.get<std::int32_t>("photo_height", 0);
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultPhoto) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.add("photo_url", object->photoUrl);
  ptree.add("thumbnail_url", object->thumbnailUrl);
  ptree.add("photo_width", object->photoWidth);
  ptree.add("photo_height", object->photoHeight);
  ptree.add("title", object->title);
  ptree.add("description", object->description);
  ptree.add("caption", object->caption);
  ptree.add("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultGif) {
  auto result = std::make_shared<InlineQueryResultGif>();
  result->gifUrl = data.get<std::string>("gif_url", "");
  result->gifWidth = data.get<std::int32_t>("gif_width", 0);
  result->gifHeight = data.get<std::int32_t>("gif_height", 0);
  result->gifDuration = data.get<std::int32_t>("gif_duration", 0);
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailMimeType = data.get<std::string>("thumbnail_mime_type", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultGif) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("gif_url", object->gifUrl);
  ptree.put("gif_width", object->gifWidth);
  ptree.put("gif_height", object->gifHeight);
  ptree.put("gif_duration", object->gifDuration);
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_mime_type", object->thumbnailMimeType);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultMpeg4Gif) {
  auto result = std::make_shared<InlineQueryResultMpeg4Gif>();
  result->mpeg4Url = data.get<std::string>("mpeg4_url", "");
  result->mpeg4Width = data.get<std::int32_t>("mpeg4_width", 0);
  result->mpeg4Height = data.get<std::int32_t>("mpeg4_height", 0);
  result->mpeg4Duration = data.get<std::int32_t>("mpeg4_duration", 0);
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailMimeType = data.get<std::string>("thumbnail_mime_type", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultMpeg4Gif) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("mpeg4_url", object->mpeg4Url);
  ptree.put("mpeg4_width", object->mpeg4Width);
  ptree.put("mpeg4_height", object->mpeg4Height);
  ptree.put("mpeg4_duration", object->mpeg4Duration);
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_mime_type", object->thumbnailMimeType);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultVideo) {
  auto result = std::make_shared<InlineQueryResultVideo>();
  result->videoUrl = data.get<std::string>("video_url", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->videoWidth = data.get<std::int32_t>("video_width", 0);
  result->videoHeight = data.get<std::int32_t>("video_height", 0);
  result->videoDuration = data.get<std::int32_t>("video_duration", 0);
  result->description = data.get<std::string>("description", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultVideo) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("video_url", object->videoUrl);
  ptree.put("mime_type", object->mimeType);
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.put("video_width", object->videoWidth);
  ptree.put("video_height", object->videoHeight);
  ptree.put("video_duration", object->videoDuration);
  ptree.put("description", object->description);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultAudio) {
  auto result = std::make_shared<InlineQueryResultAudio>();
  result->audioUrl = data.get<std::string>("audio_url", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->performer = data.get<std::string>("performer", "");
  result->audioDuration = data.get<std::int32_t>("audio_duration", 0);
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultAudio) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("audio_url", object->audioUrl);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.put("performer", object->performer);
  ptree.put("audio_duration", object->audioDuration);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultVoice) {
  auto result = std::make_shared<InlineQueryResultVoice>();
  result->voiceUrl = data.get<std::string>("voice_url", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->voiceDuration = data.get<std::int32_t>("voice_duration", 0);
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultVoice) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("voice_url", object->voiceUrl);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.put("voice_duration", object->voiceDuration);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultDocument) {
  auto result = std::make_shared<InlineQueryResultDocument>();
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->documentUrl = data.get<std::string>("document_url", "");
  result->mimeType = data.get<std::string>("mime_type", "");
  result->description = data.get<std::string>("description", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
  result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultDocument) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.put("document_url", object->documentUrl);
  ptree.put("mime_type", object->mimeType);
  ptree.put("description", object->description);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_width", object->thumbnailWidth);
  ptree.put("thumbnail_height", object->thumbnailHeight);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultLocation) {
  auto result = std::make_shared<InlineQueryResultLocation>();
  result->latitude = data.get<float>("latitude", 0);
  result->longitude = data.get<float>("longitude", 0);
  result->title = data.get<std::string>("title", "");
  result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
  result->livePeriod = data.get<std::int32_t>("live_period", 0);
  result->heading = data.get<std::int32_t>("heading", 0);
  result->proximityAlertRadius =
      data.get<std::int32_t>("proximity_alert_radius", 0);
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
  result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultLocation) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("latitude", object->latitude);
  ptree.put("longitude", object->longitude);
  ptree.put("title", object->title);
  ptree.put("horizontal_accuracy", object->horizontalAccuracy);
  ptree.put("live_period", object->livePeriod);
  ptree.put("heading", object->heading);
  ptree.put("proximity_alert_radius", object->proximityAlertRadius);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_width", object->thumbnailWidth);
  ptree.put("thumbnail_height", object->thumbnailHeight);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultVenue) {
  auto result = std::make_shared<InlineQueryResultVenue>();
  result->latitude = data.get<float>("latitude", 0);
  result->longitude = data.get<float>("longitude", 0);
  result->title = data.get<std::string>("title", "");
  result->address = data.get<std::string>("address", "");
  result->foursquareId = data.get<std::string>("foursquare_id", "");
  result->foursquareType = data.get<std::string>("foursquare_type", "");
  result->googlePlaceId = data.get<std::string>("google_place_id", "");
  result->googlePlaceType = data.get<std::string>("google_place_type", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
  result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultVenue) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("latitude", object->latitude);
  ptree.put("longitude", object->longitude);
  ptree.put("title", object->title);
  ptree.put("address", object->address);
  ptree.put("foursquare_id", object->foursquareId);
  ptree.put("foursquare_type", object->foursquareType);
  ptree.put("google_place_id", object->googlePlaceId);
  ptree.put("google_place_type", object->googlePlaceType);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_width", object->thumbnailWidth);
  ptree.put("thumbnail_height", object->thumbnailHeight);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultContact) {
  auto result = std::make_shared<InlineQueryResultContact>();
  result->phoneNumber = data.get<std::string>("phone_number", "");
  result->firstName = data.get<std::string>("first_name", "");
  result->lastName = data.get<std::string>("last_name", "");
  result->vcard = data.get<std::string>("vcard", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
  result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
  result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultContact) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("phone_number", object->phoneNumber);
  ptree.put("first_name", object->firstName);
  ptree.put("last_name", object->lastName);
  ptree.put("vcard", object->vcard);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  ptree.put("thumbnail_url", object->thumbnailUrl);
  ptree.put("thumbnail_width", object->thumbnailWidth);
  ptree.put("thumbnail_height", object->thumbnailHeight);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultGame) {
  auto result = std::make_shared<InlineQueryResultGame>();
  result->gameShortName = data.get<std::string>("game_short_name", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultGame) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("game_short_name", object->gameShortName);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedPhoto) {
  auto result = std::make_shared<InlineQueryResultCachedPhoto>();
  result->photoFileId = data.get<std::string>("photo_file_id", "");
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedPhoto) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("photo_file_id", object->photoFileId);
  ptree.put("title", object->title);
  ptree.put("description", object->description);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedGif) {
  auto result = std::make_shared<InlineQueryResultCachedGif>();
  result->gifFileId = data.get<std::string>("gif_file_id", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedGif) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("gif_file_id", object->gifFileId);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedMpeg4Gif) {
  auto result = std::make_shared<InlineQueryResultCachedMpeg4Gif>();
  result->mpeg4FileId = data.get<std::string>("mpeg4_file_id", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedMpeg4Gif) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("mpeg4_file_id", object->mpeg4FileId);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}
DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedSticker) {
  auto result = std::make_shared<InlineQueryResultCachedSticker>();
  result->stickerFileId = data.get<std::string>("sticker_file_id", "");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedSticker) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("sticker_file_id", object->stickerFileId);
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedDocument) {
  auto result = std::make_shared<InlineQueryResultCachedDocument>();
  result->title = data.get<std::string>("title", "");
  result->documentFileId = data.get<std::string>("document_file_id", "");
  result->description = data.get<std::string>("description", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedDocument) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.put("document_file_id", object->documentFileId);
  ptree.put("description", object->description);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedVideo) {
  auto result = std::make_shared<InlineQueryResultCachedVideo>();
  result->videoFileId = data.get<std::string>("video_file_id", "");
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedVideo) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("video_file_id", object->videoFileId);
  ptree.put("title", object->title);
  ptree.put("description", object->description);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedVoice) {
  auto result = std::make_shared<InlineQueryResultCachedVoice>();
  result->voiceFileId = data.get<std::string>("voice_file_id", "");
  result->title = data.get<std::string>("title", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedVoice) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("voice_file_id", object->voiceFileId);
  ptree.put("title", object->title);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InlineQueryResultCachedAudio) {
  auto result = std::make_shared<InlineQueryResultCachedAudio>();
  result->audioFileId = data.get<std::string>("audio_file_id", "");
  result->caption = data.get<std::string>("caption", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->captionEntities = parseArray<MessageEntity>(data, "caption_entities");
  result->inputMessageContent =
      parse<InputMessageContent>(data, "input_message_content");
  return result;
}

DECLARE_PARSER_TO_PTREE(InlineQueryResultCachedAudio) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("audio_file_id", object->audioFileId);
  ptree.put("caption", object->caption);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("caption_entities", put(object->captionEntities));
  ptree.add_child("input_message_content", put(object->inputMessageContent));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputMessageContent) {
  InputMessageContent::Ptr result;

  std::string messageText = data.get<std::string>("message_text", "");
  float latitude = data.get<float>("latitude", 1000);
  std::string address = data.get<std::string>("address", "");
  std::string phoneNumber = data.get<std::string>("phone_number", "");
  std::string description = data.get<std::string>("description", "");

  if (!messageText.empty()) {
    result = parse<InputTextMessageContent>(data);
  } else if (!address.empty()) {
    result = parse<InputVenueMessageContent>(data);
  } else if (latitude != 1000) {
    result = parse<InputLocationMessageContent>(data);
  } else if (!phoneNumber.empty()) {
    result = parse<InputContactMessageContent>(data);
  } else if (!description.empty()) {
    result = parse<InputInvoiceMessageContent>(data);
  } else {
    result = std::make_shared<InputMessageContent>();
  }

  return result;
}

DECLARE_PARSER_TO_PTREE(InputMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;

  if (object->type == InputTextMessageContent::TYPE) {
    ptree = put<InputTextMessageContent>(object);
  } else if (object->type == InputLocationMessageContent::TYPE) {
    ptree = put<InputLocationMessageContent>(object);
  } else if (object->type == InputVenueMessageContent::TYPE) {
    ptree = put<InputVenueMessageContent>(object);
  } else if (object->type == InputContactMessageContent::TYPE) {
    ptree = put<InputContactMessageContent>(object);
  } else if (object->type == InputInvoiceMessageContent::TYPE) {
    ptree = put<InputInvoiceMessageContent>(object);
  }

  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputTextMessageContent) {
  auto result = std::make_shared<InputTextMessageContent>();
  result->messageText = data.get<std::string>("message_text", "");
  result->parseMode = data.get<std::string>("parse_mode", "");
  result->entities = parseArray<MessageEntity>(data, "entities");
  result->linkPreviewOptions =
      parse<LinkPreviewOptions>(data, "link_preview_options");
  return result;
}

DECLARE_PARSER_TO_PTREE(InputTextMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("message_text", object->messageText);
  ptree.put("parse_mode", object->parseMode);
  ptree.add_child("entities", put(object->entities));
  ptree.add_child("link_preview_options", put(object->linkPreviewOptions));
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputLocationMessageContent) {
  auto result = std::make_shared<InputLocationMessageContent>();
  result->latitude = data.get<float>("latitude", 0);
  result->longitude = data.get<float>("longitude", 0);
  result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
  result->livePeriod = data.get<std::int32_t>("live_period", 0);
  result->heading = data.get<std::int32_t>("heading", 0);
  result->proximityAlertRadius =
      data.get<std::int32_t>("proximity_alert_radius", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(InputLocationMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("latitude", object->latitude);
  ptree.put("longitude", object->longitude);
  ptree.put("horizontal_accuracy", object->horizontalAccuracy);
  ptree.put("live_period", object->livePeriod);
  ptree.put("heading", object->heading);
  ptree.put("proximity_alert_radius", object->proximityAlertRadius);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputVenueMessageContent) {
  auto result = std::make_shared<InputVenueMessageContent>();
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

DECLARE_PARSER_TO_PTREE(InputVenueMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("latitude", object->latitude);
  ptree.put("longitude", object->longitude);
  ptree.put("title", object->title);
  ptree.put("address", object->address);
  ptree.put("foursquare_id", object->foursquareId);
  ptree.put("foursquare_type", object->foursquareType);
  ptree.put("google_place_id", object->googlePlaceId);
  ptree.put("google_place_type", object->googlePlaceType);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputContactMessageContent) {
  auto result = std::make_shared<InputContactMessageContent>();
  result->phoneNumber = data.get<std::string>("phone_number", "");
  result->firstName = data.get<std::string>("first_name", "");
  result->lastName = data.get<std::string>("last_name", "");
  result->vcard = data.get<std::string>("vcard", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(InputContactMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("phone_number", object->phoneNumber);
  ptree.put("first_name", object->firstName);
  ptree.put("last_name", object->lastName);
  ptree.put("vcard", object->vcard);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(InputInvoiceMessageContent) {
  auto result = std::make_shared<InputInvoiceMessageContent>();
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->payload = data.get<std::string>("payload", "");
  result->providerToken = data.get<std::string>("provider_token", "");
  result->currency = data.get<std::string>("currency", "");
  result->prices = parseArray<LabeledPrice>(data, "prices");
  result->maxTipAmount = data.get<std::int32_t>("max_tip_amount", 0);
  result->suggestedTipAmounts =
      parsePrimitiveArray<std::int32_t>(data, "suggested_tip_amounts");
  result->providerData = data.get<std::string>("provider_data", "");
  result->photoUrl = data.get<std::string>("photo_url", "");
  result->photoSize = data.get<std::int32_t>("photo_size", 0);
  result->photoWidth = data.get<std::int32_t>("photo_width", 0);
  result->photoHeight = data.get<std::int32_t>("photo_height", 0);
  result->needName = data.get<bool>("need_name", false);
  result->needPhoneNumber = data.get<bool>("need_phone_number", false);
  result->needEmail = data.get<bool>("need_email", false);
  result->needShippingAddress = data.get<bool>("need_shipping_address", false);
  result->sendPhoneNumberToProvider =
      data.get<bool>("send_phone_number_to_provider", false);
  result->sendEmailToProvider = data.get<bool>("send_email_to_provider", false);
  result->isFlexible = data.get<bool>("is_flexible", false);
  return result;
}

DECLARE_PARSER_TO_PTREE(InputInvoiceMessageContent) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.put("description", object->description);
  ptree.put("payload", object->payload);
  ptree.put("provider_token", object->providerToken);
  ptree.put("currency", object->currency);
  ptree.add_child("prices", put(object->prices));
  ptree.put("max_tip_amount", object->maxTipAmount);
  ptree.add_child("suggested_tip_amounts", put(object->suggestedTipAmounts));
  ptree.put("provider_data", object->providerData);
  ptree.put("photo_url", object->photoUrl);
  ptree.put("photo_size", object->photoSize);
  ptree.put("photo_width", object->photoWidth);
  ptree.put("photo_height", object->photoHeight);
  ptree.put("need_name", object->needName);
  ptree.put("need_phone_number", object->needPhoneNumber);
  ptree.put("need_email", object->needEmail);
  ptree.put("need_shipping_address", object->needShippingAddress);
  ptree.put("send_phone_number_to_provider", object->sendPhoneNumberToProvider);
  ptree.put("send_email_to_provider", object->sendEmailToProvider);
  ptree.put("is_flexible", object->isFlexible);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ChosenInlineResult) {
  auto result = std::make_shared<ChosenInlineResult>();
  result->resultId = data.get<std::string>("result_id", "");
  result->from = parse<User>(data, "from");
  result->location = parse<Location>(data, "location");
  result->inlineMessageId = data.get<std::string>("inline_message_id", "");
  result->query = data.get<std::string>("query", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ChosenInlineResult) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("result_id", object->resultId);
  ptree.add_child("from", put(object->from));
  ptree.add_child("location", put(object->location));
  ptree.put("inline_message_id", object->inlineMessageId);
  ptree.put("query", object->query);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(SentWebAppMessage) {
  auto result = std::make_shared<SentWebAppMessage>();
  result->inlineMessageId = data.get<std::string>("inline_message_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(SentWebAppMessage) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("inline_message_id", object->inlineMessageId);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(LabeledPrice) {
  auto result = std::make_shared<LabeledPrice>();
  result->label = data.get<std::string>("label", "");
  result->amount = data.get<std::int32_t>("amount", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(LabeledPrice) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("label", object->label);
  ptree.put("amount", object->amount);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(Invoice) {
  auto result = std::make_shared<Invoice>();
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->startParameter = data.get<std::string>("start_parameter", "");
  result->currency = data.get<std::string>("currency", "");
  result->totalAmount = data.get<std::int32_t>("total_amount", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(Invoice) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.put("description", object->description);
  ptree.put("start_parameter", object->startParameter);
  ptree.put("currency", object->currency);
  ptree.put("total_amount", object->totalAmount);
  return ptree;
}

DECLARE_PARSER_FROM_PTREE(ShippingAddress) {
  auto result = std::make_shared<ShippingAddress>();
  result->countryCode = data.get<std::string>("country_code", "");
  result->state = data.get<std::string>("state", "");
  result->city = data.get<std::string>("city", "");
  result->streetLine1 = data.get<std::string>("street_line1", "");
  result->streetLine2 = data.get<std::string>("street_line2", "");
  result->postCode = data.get<std::string>("post_code", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(ShippingAddress) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("country_code", object->countryCode);
  ptree.put("state", object->state);
  ptree.put("city", object->city);
  ptree.put("street_line1", object->streetLine1);
  ptree.put("street_line2", object->streetLine2);
  ptree.put("post_code", object->postCode);
  return ptree;
}
// OrderInfo
DECLARE_PARSER_FROM_PTREE(OrderInfo) {
  auto result = std::make_shared<OrderInfo>();
  result->name = data.get<std::string>("name", "");
  result->phoneNumber = data.get<std::string>("phone_number", "");
  result->email = data.get<std::string>("email", "");
  result->shippingAddress = parse<ShippingAddress>(data, "shipping_address");
  return result;
}

DECLARE_PARSER_TO_PTREE(OrderInfo) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("name", object->name);
  ptree.put("phone_number", object->phoneNumber);
  ptree.put("email", object->email);
  ptree.add_child("shipping_address", put(object->shippingAddress));
  return ptree;
}

// ShippingOption
DECLARE_PARSER_FROM_PTREE(ShippingOption) {
  auto result = std::make_shared<ShippingOption>();
  result->id = data.get<std::string>("id", "");
  result->title = data.get<std::string>("title", "");
  result->prices = parseArray<LabeledPrice>(data, "prices");
  return result;
}

DECLARE_PARSER_TO_PTREE(ShippingOption) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("id", object->id);
  ptree.put("title", object->title);
  ptree.add_child("prices", put(object->prices));
  return ptree;
}

// SuccessfulPayment
DECLARE_PARSER_FROM_PTREE(SuccessfulPayment) {
  auto result = std::make_shared<SuccessfulPayment>();
  result->currency = data.get<std::string>("currency", "");
  result->totalAmount = data.get<std::int32_t>("total_amount", 0);
  result->invoicePayload = data.get<std::string>("invoice_payload", "");
  result->shippingOptionId = data.get<std::string>("shipping_option_id", "");
  result->orderInfo = parse<OrderInfo>(data, "order_info");
  result->telegramPaymentChargeId =
      data.get<std::string>("telegram_payment_charge_id", "");
  result->providerPaymentChargeId =
      data.get<std::string>("provider_payment_charge_id", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(SuccessfulPayment) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("currency", object->currency);
  ptree.put("total_amount", object->totalAmount);
  ptree.put("invoice_payload", object->invoicePayload);
  ptree.put("shipping_option_id", object->shippingOptionId);
  ptree.add_child("order_info", put(object->orderInfo));
  ptree.put("telegram_payment_charge_id", object->telegramPaymentChargeId);
  ptree.put("provider_payment_charge_id", object->providerPaymentChargeId);
  return ptree;
}

// ShippingQuery
DECLARE_PARSER_FROM_PTREE(ShippingQuery) {
  auto result = std::make_shared<ShippingQuery>();
  result->id = data.get<std::string>("id", "");
  result->from = parse<User>(data, "from");
  result->invoicePayload = data.get<std::string>("invoice_payload", "");
  result->shippingAddress = parse<ShippingAddress>(data, "shipping_address");
  return result;
}

DECLARE_PARSER_TO_PTREE(ShippingQuery) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("id", object->id);
  ptree.add_child("from", put(object->from));
  ptree.put("invoice_payload", object->invoicePayload);
  ptree.add_child("shipping_address", put(object->shippingAddress));
  return ptree;
}

// PreCheckoutQuery
DECLARE_PARSER_FROM_PTREE(PreCheckoutQuery) {
  auto result = std::make_shared<PreCheckoutQuery>();
  result->id = data.get<std::string>("id", "");
  result->from = parse<User>(data, "from");
  result->currency = data.get<std::string>("currency", "");
  result->totalAmount = data.get<std::int32_t>("total_amount", 0);
  result->invoicePayload = data.get<std::string>("invoice_payload", "");
  result->shippingOptionId = data.get<std::string>("shipping_option_id", "");
  result->orderInfo = parse<OrderInfo>(data, "order_info");
  return result;
}

DECLARE_PARSER_TO_PTREE(PreCheckoutQuery) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("id", object->id);
  ptree.add_child("from", put(object->from));
  ptree.put("currency", object->currency);
  ptree.put("total_amount", object->totalAmount);
  ptree.put("invoice_payload", object->invoicePayload);
  ptree.put("shipping_option_id", object->shippingOptionId);
  ptree.add_child("order_info", put(object->orderInfo));
  return ptree;
}

// PassportData
DECLARE_PARSER_FROM_PTREE(PassportData) {
  auto result = std::make_shared<PassportData>();
  result->data = parseArray<EncryptedPassportElement>(data, "data");
  result->credentials = parse<EncryptedCredentials>(data, "credentials");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportData) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.add_child("data", put(object->data));
  ptree.add_child("credentials", put(object->credentials));
  return ptree;
}

// PassportFile
DECLARE_PARSER_FROM_PTREE(PassportFile) {
  auto result = std::make_shared<PassportFile>();
  result->fileId = data.get<std::string>("file_id", "");
  result->fileUniqueId = data.get<std::string>("file_unique_id", "");
  result->fileSize = data.get<std::int32_t>("file_size", 0);
  result->fileDate = data.get<std::int32_t>("file_date", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportFile) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_id", object->fileId);
  ptree.put("file_unique_id", object->fileUniqueId);
  ptree.put("file_size", object->fileSize);
  ptree.put("file_date", object->fileDate);
  return ptree;
}

// EncryptedPassportElement
DECLARE_PARSER_FROM_PTREE(EncryptedPassportElement) {
  auto result = std::make_shared<EncryptedPassportElement>();
  result->type = data.get<std::string>("type", "");
  result->data = data.get<std::string>("data", "");
  result->phoneNumber = data.get<std::string>("phone_number", "");
  result->email = data.get<std::string>("email", "");
  result->files = parseArray<PassportFile>(data, "files");
  result->frontSide = parse<PassportFile>(data, "front_side");
  result->reverseSide = parse<PassportFile>(data, "reverse_side");
  result->selfie = parse<PassportFile>(data, "selfie");
  result->translation = parseArray<PassportFile>(data, "translation");
  result->hash = data.get<std::string>("hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(EncryptedPassportElement) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("type", object->type);
  ptree.put("data", object->data);
  ptree.put("phone_number", object->phoneNumber);
  ptree.put("email", object->email);
  ptree.add_child("files", put(object->files));
  ptree.add_child("front_side", put(object->frontSide));
  ptree.add_child("reverse_side", put(object->reverseSide));
  ptree.add_child("selfie", put(object->selfie));
  ptree.add_child("translation", put(object->translation));
  ptree.put("hash", object->hash);
  return ptree;
}

// EncryptedCredentials
DECLARE_PARSER_FROM_PTREE(EncryptedCredentials) {
  auto result = std::make_shared<EncryptedCredentials>();
  result->data = data.get<std::string>("data", "");
  result->hash = data.get<std::string>("hash", "");
  result->secret = data.get<std::string>("secret", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(EncryptedCredentials) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("data", object->data);
  ptree.put("hash", object->hash);
  ptree.put("secret", object->secret);
  return ptree;
}

// PassportElementError
DECLARE_PARSER_FROM_PTREE(PassportElementError) {
  std::string source = data.get<std::string>("source", "");
  PassportElementError::Ptr result;
  if (source == PassportElementErrorDataField::SOURCE) {
    result = std::static_pointer_cast<PassportElementError>(
        parse<PassportElementErrorDataField>(data));
  } else if (source == PassportElementErrorFrontSide::SOURCE) {
    result = std::static_pointer_cast<PassportElementError>(
        parse<PassportElementErrorFrontSide>(data));
  } else if (source == PassportElementErrorReverseSide::SOURCE) {
    result = std::static_pointer_cast<PassportElementError>(
        parse<PassportElementErrorReverseSide>(data));
  } else if (source == PassportElementErrorSelfie::SOURCE) {
    result = std::static_pointer_cast<PassportElementError>(
        parse<PassportElementErrorSelfie>(data));
  } else {
    result = std::make_shared<PassportElementError>();
  }
  result->source = data.get<std::string>("source", "");
  result->type = data.get<std::string>("type", "");
  result->message = data.get<std::string>("message", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementError) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("source", object->source);
  ptree.put("type", object->type);
  ptree.put("message", object->message);
  return ptree;
}

// PassportElementErrorDataField
DECLARE_PARSER_FROM_PTREE(PassportElementErrorDataField) {
  auto result = std::make_shared<PassportElementErrorDataField>();
  result->fieldName = data.get<std::string>("field_name", "");
  result->dataHash = data.get<std::string>("data_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorDataField) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("field_name", object->fieldName);
  ptree.put("data_hash", object->dataHash);
  return ptree;
}

// PassportElementErrorFrontSide
DECLARE_PARSER_FROM_PTREE(PassportElementErrorFrontSide) {
  auto result = std::make_shared<PassportElementErrorFrontSide>();
  result->fileHash = data.get<std::string>("file_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorFrontSide) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_hash", object->fileHash);
  return ptree;
}

// PassportElementErrorReverseSide
DECLARE_PARSER_FROM_PTREE(PassportElementErrorReverseSide) {
  auto result = std::make_shared<PassportElementErrorReverseSide>();
  result->fileHash = data.get<std::string>("file_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorReverseSide) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_hash", object->fileHash);
  return ptree;
}

// PassportElementErrorSelfie
DECLARE_PARSER_FROM_PTREE(PassportElementErrorSelfie) {
  auto result = std::make_shared<PassportElementErrorSelfie>();
  result->fileHash = data.get<std::string>("file_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorSelfie) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_hash", object->fileHash);
  return ptree;
}

// PassportElementErrorFile
DECLARE_PARSER_FROM_PTREE(PassportElementErrorFile) {
  auto result = std::make_shared<PassportElementErrorFile>();
  result->fileHash = data.get<std::string>("file_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorFile) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_hash", object->fileHash);
  return ptree;
}

// PassportElementErrorFiles
DECLARE_PARSER_FROM_PTREE(PassportElementErrorFiles) {
  auto result = std::make_shared<PassportElementErrorFiles>();
  result->fileHashes = parsePrimitiveArray<std::string>(data, "file_hashes");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorFiles) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.add_child("file_hashes", put(object->fileHashes));
  return ptree;
}

// PassportElementErrorTranslationFile
DECLARE_PARSER_FROM_PTREE(PassportElementErrorTranslationFile) {
  auto result = std::make_shared<PassportElementErrorTranslationFile>();
  result->fileHash = data.get<std::string>("file_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorTranslationFile) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("file_hash", object->fileHash);
  return ptree;
}

// PassportElementErrorTranslationFiles
DECLARE_PARSER_FROM_PTREE(PassportElementErrorTranslationFiles) {
  auto result = std::make_shared<PassportElementErrorTranslationFiles>();
  result->fileHashes = parsePrimitiveArray<std::string>(data, "file_hashes");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorTranslationFiles) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.add_child("file_hashes", put(object->fileHashes));
  return ptree;
}

// PassportElementErrorUnspecified
DECLARE_PARSER_FROM_PTREE(PassportElementErrorUnspecified) {
  auto result = std::make_shared<PassportElementErrorUnspecified>();
  result->elementHash = data.get<std::string>("element_hash", "");
  return result;
}

DECLARE_PARSER_TO_PTREE(PassportElementErrorUnspecified) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("element_hash", object->elementHash);
  return ptree;
}

// Game
DECLARE_PARSER_FROM_PTREE(Game) {
  auto result = std::make_shared<Game>();
  result->title = data.get<std::string>("title", "");
  result->description = data.get<std::string>("description", "");
  result->photo = parseArray<PhotoSize>(data, "photo");
  result->text = data.get<std::string>("text", "");
  result->textEntities = parseArray<MessageEntity>(data, "text_entities");
  result->animation = parse<Animation>(data, "animation");
  return result;
}

DECLARE_PARSER_TO_PTREE(Game) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("title", object->title);
  ptree.put("description", object->description);
  ptree.add_child("photo", put(object->photo));
  ptree.put("text", object->text);
  ptree.add_child("text_entities", put(object->textEntities));
  ptree.add_child("animation", put(object->animation));
  return ptree;
}

// CallbackGame
DECLARE_PARSER_FROM_PTREE(CallbackGame) {
  auto result = std::make_shared<CallbackGame>();
  return result;
}

DECLARE_PARSER_TO_PTREE(CallbackGame) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  return ptree;
}

// GameHighScore
DECLARE_PARSER_FROM_PTREE(GameHighScore) {
  auto result = std::make_shared<GameHighScore>();
  result->position = data.get<std::int32_t>("position", 0);
  result->user = parse<User>(data, "user");
  result->score = data.get<std::int32_t>("score", 0);
  return result;
}

DECLARE_PARSER_TO_PTREE(GameHighScore) {
  if (!object)
    return {};
  boost::property_tree::ptree ptree;
  ptree.put("position", object->position);
  ptree.add_child("user", put(object->user));
  ptree.put("score", object->score);
  return ptree;
}

// GenericReply
DECLARE_PARSER_FROM_PTREE(GenericReply) {
  if (data.find("force_reply") != data.not_found()) {
    return parse<ForceReply>(data);
  } else if (data.find("remove_keyboard") != data.not_found()) {
    return parse<ReplyKeyboardRemove>(data);
  } else if (data.find("keyboard") != data.not_found()) {
    return parse<ReplyKeyboardMarkup>(data);
  } else if (data.find("inline_keyboard") != data.not_found()) {
    return parse<InlineKeyboardMarkup>(data);
  }
  return std::make_shared<GenericReply>();
}

DECLARE_PARSER_TO_PTREE(GenericReply) {
  if (!object)
    return {};
  if (std::dynamic_pointer_cast<ForceReply>(object) != nullptr) {
    return put<ForceReply>(object);
  } else if (std::dynamic_pointer_cast<ReplyKeyboardRemove>(object) !=
             nullptr) {
    return put<ReplyKeyboardRemove>(object);
  } else if (std::dynamic_pointer_cast<ReplyKeyboardMarkup>(object) !=
             nullptr) {
    return put<ReplyKeyboardMarkup>(object);
  } else if (std::dynamic_pointer_cast<InlineKeyboardMarkup>(object) !=
             nullptr) {
    return put<InlineKeyboardMarkup>(object);
  }
  return {};
}

} // namespace TgBot