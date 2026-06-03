#include "maxbot/BotTypeParser.h"
#include <type_traits>
#include <variant>

namespace MaxBot {

WebhookInfo::Ptr BotTypeParser::parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseWebhookInfo(const WebhookInfo::Ptr& object) {
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

Chat::Ptr BotTypeParser::parseJsonAndGetChat(const boost::property_tree::ptree& data) {
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
    result->photo = tryParseJson<ChatPhoto>(&BotTypeParser::parseJsonAndGetChatPhoto, data, "photo");
    result->activeUsernames = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "active_usernames");
    result->birthdate = tryParseJson<Birthdate>(&BotTypeParser::parseJsonAndGetBirthdate, data, "birthdate");
    result->personalChat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "personal_chat");
    result->availableReactions = parseJsonAndGetArray<ReactionType>(&BotTypeParser::parseJsonAndGetReactionType, data, "available_reactions");
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
    result->pinnedMessage = tryParseJson<Message>(&BotTypeParser::parseJsonAndGetMessage, data, "pinned_message");
    result->permissions = tryParseJson<ChatPermissions>(&BotTypeParser::parseJsonAndGetChatPermissions, data, "permissions");
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
    result->location = tryParseJson<ChatLocation>(&BotTypeParser::parseJsonAndGetChatLocation, data, "location");
    return result;
}

std::string BotTypeParser::parseNewMessageBody(const NewMessageBody::Ptr& msg) {
    if (!msg)
        return {};

    std::string result;
    result += '{';
    appendToJson(result, "text", msg->text);
    appendToJson(result, "notify", msg->notify);
    if (!msg->attachments.empty())
        appendToJson(result, "attachments", parseArray<AttachmentRequest>(&BotTypeParser::parseAttachmentRequest, msg->attachments));
    if (msg->link)
        appendToJson(result, "link", parseNewMessageLink(msg->link));
    if (!msg->format.empty())
        appendToJson(result, "format", msg->format);
    removeLastComma(result);
    result += '}';
    return result;
}

/*static*/ std::string BotTypeParser::parseAttachmentRequest(const AttachmentRequest::Ptr& o)
{
    if (!o) return {};
    std::string result;
    result += '{';
	appendToJson(result, "type", o->type);
	std::visit([&](auto arg) {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (!std::is_same_v<T, std::monostate>)
			if (!arg)
				return;

		result += "\"payload\":{";
		if constexpr (std::is_same_v<T, InlineKeyboardAttachmentRequest::Ptr>)
		{
			result += "\"buttons\":[";
			for (auto&& mIt : arg->payload.buttons)
			{
				result += '[';
				for (auto&& it : mIt)
				{
					result += '{';
					appendToJson(result, "text", it->text);
					appendToJson(result, "type", it->type);
					std::visit([&](auto btn) {
						using B = std::decay_t<decltype(btn)>;
						if (!btn)
							return;
						if constexpr (std::is_same_v<B, CallbackButton::Ptr>)
							appendToJson(result, "payload", btn->payload);
					}, it->_data);
					removeLastComma(result);
					result += '}';
				}
				result += "],";
			}

			removeLastComma(result);
			result += "],";
		}
		result += "},";
	}, o->_data);
    removeLastComma(result);
    result += '}';
    return result;
}

/*static*/ std::string BotTypeParser::parseNewMessageLink(const NewMessageLink::Ptr& o)
{
    if (!o) return {};
    std::string result;
    result += '{';
    appendToJson(result, "type", o->type);
    appendToJson(result, "mid", o->mid);
    removeLastComma(result);
    result += '}';
    return result;
}

std::string BotTypeParser::parseCallbackAnswer(const CallbackAnswer::Ptr& obj)
{
    if (!obj)
        return {};

    std::string result;
    result += '{';
    if (obj->message)
        appendToJson(result, "message", parseNewMessageBody(obj->message));
    if (!obj->notification.empty())
        appendToJson(result, "notification", obj->notification);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageId::Ptr BotTypeParser::parseJsonAndGetMessageId(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<MessageId>());
    result->messageId = data.get<std::int32_t>("message_id", 0);
    return result;
}

std::string BotTypeParser::parseMessageId(const MessageId::Ptr& object) {
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

InaccessibleMessage::Ptr BotTypeParser::parseJsonAndGetInaccessibleMessage(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InaccessibleMessage>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->date = data.get<std::uint8_t>("date", 0);
    return result;
}

MessageEntity::Ptr BotTypeParser::parseJsonAndGetMessageEntity(const boost::property_tree::ptree& data) {
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
    result->user = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "user");
    result->language = data.get<std::string>("language", "");
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    return result;
}

std::string BotTypeParser::parseMessageEntity(const MessageEntity::Ptr& object) {
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

TextQuote::Ptr BotTypeParser::parseJsonAndGetTextQuote(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<TextQuote>());
    result->text = data.get<std::string>("text", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->position = data.get<std::int32_t>("position", 0);
    result->isManual = data.get<bool>("is_manual", false);
    return result;
}

std::string BotTypeParser::parseTextQuote(const TextQuote::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "entities", parseArray(&BotTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "position", object->position);
    appendToJson(result, "is_manual", object->isManual);
    removeLastComma(result);
    result += '}';
    return result;
}

ExternalReplyInfo::Ptr BotTypeParser::parseJsonAndGetExternalReplyInfo(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ExternalReplyInfo>());
    result->origin = tryParseJson<MessageOrigin>(&BotTypeParser::parseJsonAndGetMessageOrigin, data, "origin");
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->linkPreviewOptions = tryParseJson<LinkPreviewOptions>(&BotTypeParser::parseJsonAndGetLinkPreviewOptions, data, "link_preview_options");
    result->animation = tryParseJson<Animation>(&BotTypeParser::parseJsonAndGetAnimation, data, "animation");
    result->audio = tryParseJson<Audio>(&BotTypeParser::parseJsonAndGetAudio, data, "audio");
    result->document = tryParseJson<Document>(&BotTypeParser::parseJsonAndGetDocument, data, "document");
    result->photo = parseJsonAndGetArray<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->sticker = tryParseJson<Sticker>(&BotTypeParser::parseJsonAndGetSticker, data, "sticker");
    result->story = tryParseJson<Story>(&BotTypeParser::parseJsonAndGetStory, data, "story");
    result->video = tryParseJson<Video>(&BotTypeParser::parseJsonAndGetVideo, data, "video");
    result->videoNote = tryParseJson<VideoNote>(&BotTypeParser::parseJsonAndGetVideoNote, data, "video_note");
    result->voice = tryParseJson<Voice>(&BotTypeParser::parseJsonAndGetVoice, data, "voice");
    result->hasMediaSpoiler = data.get<bool>("has_media_spoiler", false);
    result->contact = tryParseJson<Contact>(&BotTypeParser::parseJsonAndGetContact, data, "contact");
    result->giveaway = tryParseJson<Giveaway>(&BotTypeParser::parseJsonAndGetGiveaway, data, "giveaway");
    result->giveawayWinners = tryParseJson<GiveawayWinners>(&BotTypeParser::parseJsonAndGetGiveawayWinners, data, "giveaway_winners");
    result->invoice = tryParseJson<Invoice>(&BotTypeParser::parseJsonAndGetInvoice, data, "invoice");
    result->location = tryParseJson<Location>(&BotTypeParser::parseJsonAndGetLocation, data, "location");
    result->poll = tryParseJson<Poll>(&BotTypeParser::parseJsonAndGetPoll, data, "poll");
    return result;
}

ReplyParameters::Ptr BotTypeParser::parseJsonAndGetReplyParameters(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ReplyParameters>());
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->allowSendingWithoutReply = data.get<bool>("allow_sending_without_reply", false);
    result->quote = data.get<std::string>("quote", "");
    result->quoteParseMode = data.get<std::string>("quote_parse_mode", "");
    result->quoteEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "quote_entities");
    result->quotePosition = data.get<std::int32_t>("quote_position", 0);
    return result;
}

std::string BotTypeParser::parseReplyParameters(const ReplyParameters::Ptr& object) {
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
    appendToJson(result, "quote_entities", parseArray(&BotTypeParser::parseMessageEntity, object->quoteEntities));
    appendToJson(result, "quote_position", object->quotePosition);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageOrigin::Ptr BotTypeParser::parseJsonAndGetMessageOrigin(const boost::property_tree::ptree& data) {
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

MessageOriginUser::Ptr BotTypeParser::parseJsonAndGetMessageOriginUser(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginUser>());
    result->senderUser = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "sender_user");
    return result;
}

std::string BotTypeParser::parseMessageOriginUser(const MessageOriginUser::Ptr& object) {
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

MessageOriginHiddenUser::Ptr BotTypeParser::parseJsonAndGetMessageOriginHiddenUser(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginHiddenUser>());
    result->senderUserName = data.get<std::string>("sender_user_name", "");
    return result;
}

std::string BotTypeParser::parseMessageOriginHiddenUser(const MessageOriginHiddenUser::Ptr& object) {
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

MessageOriginChat::Ptr BotTypeParser::parseJsonAndGetMessageOriginChat(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginChat>());
    result->senderChat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "sender_chat");
    result->authorSignature = data.get<std::string>("author_signature", "");
    return result;
}

MessageOriginChannel::Ptr BotTypeParser::parseJsonAndGetMessageOriginChannel(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetMessageOrigin().
    auto result(std::make_shared<MessageOriginChannel>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->authorSignature = data.get<std::string>("author_signature", "");
    return result;
}

PhotoSize::Ptr BotTypeParser::parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<PhotoSize>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parsePhotoSize(const PhotoSize::Ptr& object) {
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

Animation::Ptr BotTypeParser::parseJsonAndGetAnimation(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Animation>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseAnimation(const Animation::Ptr& object) {
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

Audio::Ptr BotTypeParser::parseJsonAndGetAudio(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Audio>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->performer = data.get<std::string>("performer", "");
    result->title = data.get<std::string>("title", "");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    return result;
}

std::string BotTypeParser::parseAudio(const Audio::Ptr& object) {
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

Document::Ptr BotTypeParser::parseJsonAndGetDocument(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Document>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseDocument(const Document::Ptr& object) {
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

Story::Ptr BotTypeParser::parseJsonAndGetStory(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Story>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->id = data.get<std::int32_t>("id", 0);
    return result;
}

Video::Ptr BotTypeParser::parseJsonAndGetVideo(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Video>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->fileName = data.get<std::string>("file_name", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseVideo(const Video::Ptr& object) {
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

VideoNote::Ptr BotTypeParser::parseJsonAndGetVideoNote(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<VideoNote>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->length = data.get<std::int32_t>("length", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseVideoNote(const VideoNote::Ptr& object) {
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

Voice::Ptr BotTypeParser::parseJsonAndGetVoice(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Voice>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->mimeType = data.get<std::string>("mime_type", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseVoice(const Voice::Ptr& object) {
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

Contact::Ptr BotTypeParser::parseJsonAndGetContact(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Contact>());
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->userId = data.get<std::int64_t>("user_id", 0);
    result->vcard = data.get<std::string>("vcard", "");
    return result;
}

std::string BotTypeParser::parseContact(const Contact::Ptr& object) {
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

PollOption::Ptr BotTypeParser::parseJsonAndGetPollOption(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<PollOption>());
    result->text = data.get<std::string>("text", "");
    result->voterCount = data.get<std::int32_t>("voter_count", 0);
    return result;
}

std::string BotTypeParser::parsePollOption(const PollOption::Ptr& object) {
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

PollAnswer::Ptr BotTypeParser::parseJsonAndGetPollAnswer(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<PollAnswer>());
    result->pollId = data.get<std::string>("poll_id", "");
    result->voterChat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "voter_chat");
    result->user = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "user");
    result->optionIds = parseJsonAndGetArray<std::int32_t>(
        [] (const boost::property_tree::ptree& innerData)->std::int32_t {
        return innerData.get<std::int32_t>("");
    }, data, "option_ids");
    return result;
}

Poll::Ptr BotTypeParser::parseJsonAndGetPoll(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Poll>());
    result->id = data.get<std::string>("id", "");
    result->question = data.get<std::string>("question", "");
    result->options = parseJsonAndGetArray<PollOption>(&BotTypeParser::parseJsonAndGetPollOption, data, "options");
    result->totalVoterCount = data.get<std::int32_t>("total_voter_count", 0);
    result->isClosed = data.get<bool>("is_closed", false);
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    result->type = data.get<std::string>("type", "");
    result->allowsMultipleAnswers = data.get<bool>("allows_multiple_answers", false);
    result->correctOptionId = data.get<std::int32_t>("correct_option_id", 0);
    result->explanation = data.get<std::string>("explanation", "");
    result->explanationEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "explanation_entities");
    result->openPeriod = data.get<std::int32_t>("open_period", 0);
    result->closeDate = data.get<std::int64_t>("close_date", 0);
    return result;
}

std::string BotTypeParser::parsePoll(const Poll::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "question", object->question);
    appendToJson(result, "options", parseArray(&BotTypeParser::parsePollOption, object->options));
    appendToJson(result, "total_voter_count", object->totalVoterCount);
    appendToJson(result, "is_closed", object->isClosed);
    appendToJson(result, "is_anonymous", object->isAnonymous);
    appendToJson(result, "type", object->type);
    appendToJson(result, "allows_multiple_answers", object->allowsMultipleAnswers);
    appendToJson(result, "correct_option_id", object->correctOptionId);
    appendToJson(result, "explanation", object->explanation);
    appendToJson(result, "explanation_entities", parseArray(&BotTypeParser::parseMessageEntity, object->explanationEntities));
    appendToJson(result, "open_period", object->openPeriod);
    appendToJson(result, "close_date", object->closeDate);
    removeLastComma(result);
    result += '}';
    return result;
}

Location::Ptr BotTypeParser::parseJsonAndGetLocation(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Location>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
    result->livePeriod = data.get<std::int32_t>("live_period", 0);
    result->heading = data.get<std::int32_t>("heading", 0);
    result->proximityAlertRadius = data.get<std::int32_t>("proximity_alert_radius", 0);
    return result;
}

std::string BotTypeParser::parseLocation(const Location::Ptr& object) {
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

WebAppData::Ptr BotTypeParser::parseJsonAndGetWebAppData(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<WebAppData>());
    result->data = data.get<std::string>("data", "");
    result->buttonText = data.get<std::string>("button_text", "");
    return result;
}

std::string BotTypeParser::parseWebAppData(const WebAppData::Ptr& object) {
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

ProximityAlertTriggered::Ptr BotTypeParser::parseJsonAndGetProximityAlertTriggered(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ProximityAlertTriggered>());
    result->traveler = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "traveler");
    result->watcher = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "watcher");
    result->distance = data.get<std::int32_t>("distance", 0);
    return result;
}

std::string BotTypeParser::parseProximityAlertTriggered(const ProximityAlertTriggered::Ptr& object) {
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

MessageAutoDeleteTimerChanged::Ptr BotTypeParser::parseJsonAndGetMessageAutoDeleteTimerChanged(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<MessageAutoDeleteTimerChanged>());
    result->messageAutoDeleteTime = data.get<std::int32_t>("message_auto_delete_time", 0);
    return result;
}

std::string BotTypeParser::parseMessageAutoDeleteTimerChanged(const MessageAutoDeleteTimerChanged::Ptr& object) {
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

ChatBoostAdded::Ptr BotTypeParser::parseJsonAndGetChatBoostAdded(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatBoostAdded>());
    result->boostCount = data.get<std::int32_t>("boost_count", 0);
    return result;
}

std::string BotTypeParser::parseChatBoostAdded(const ChatBoostAdded::Ptr& object) {
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

SharedUser::Ptr BotTypeParser::parseJsonAndGetSharedUser(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<SharedUser>());
    result->userId = data.get<std::int64_t>("user_id", 0);
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->username = data.get<std::string>("username", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    return result;
}

std::string BotTypeParser::parseSharedUser(const SharedUser::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "user_id", object->userId);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "username", object->username);
    appendToJson(result, "photo", parseArray(&BotTypeParser::parsePhotoSize, object->photo));
    removeLastComma(result);
    result += '}';
    return result;
}

UsersShared::Ptr BotTypeParser::parseJsonAndGetUsersShared(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<UsersShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->users = parseJsonAndGetArray<SharedUser>(&BotTypeParser::parseJsonAndGetSharedUser, data, "users");
    return result;
}

std::string BotTypeParser::parseUsersShared(const UsersShared::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "users", parseArray(&BotTypeParser::parseSharedUser, object->users));
    removeLastComma(result);
    result += '}';
    return result;
}

ChatShared::Ptr BotTypeParser::parseJsonAndGetChatShared(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatShared>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->title = data.get<std::string>("title", "");
    result->username = data.get<std::string>("username", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    return result;
}

std::string BotTypeParser::parseChatShared(const ChatShared::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "request_id", object->requestId);
    appendToJson(result, "chat_id", object->chatId);
    appendToJson(result, "title", object->title);
    appendToJson(result, "username", object->username);
    appendToJson(result, "photo", parseArray(&BotTypeParser::parsePhotoSize, object->photo));
    removeLastComma(result);
    result += '}';
    return result;
}

WriteAccessAllowed::Ptr BotTypeParser::parseJsonAndGetWriteAccessAllowed(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<WriteAccessAllowed>());
    result->fromRequest = data.get<bool>("from_request", false);
    result->webAppName = data.get<std::string>("web_app_name", "");
    result->fromAttachmentMenu = data.get<bool>("from_attachment_menu", false);
    return result;
}

std::string BotTypeParser::parseWriteAccessAllowed(const WriteAccessAllowed::Ptr& object) {
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

VideoChatScheduled::Ptr BotTypeParser::parseJsonAndGetVideoChatScheduled(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<VideoChatScheduled>());
    result->startDate = data.get<std::int32_t>("start_date", 0);
    return result;
}

std::string BotTypeParser::parseVideoChatScheduled(const VideoChatScheduled::Ptr& object) {
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

VideoChatStarted::Ptr BotTypeParser::parseJsonAndGetVideoChatStarted(const boost::property_tree::ptree& /*data*/) {
    auto result(std::make_shared<VideoChatStarted>());
    return result;
}

std::string BotTypeParser::parseVideoChatStarted(const VideoChatStarted::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

VideoChatEnded::Ptr BotTypeParser::parseJsonAndGetVideoChatEnded(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<VideoChatEnded>());
    result->duration = data.get<std::int32_t>("duration", 0);
    return result;
}

std::string BotTypeParser::parseVideoChatEnded(const VideoChatEnded::Ptr& object) {
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

VideoChatParticipantsInvited::Ptr BotTypeParser::parseJsonAndGetVideoChatParticipantsInvited(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<VideoChatParticipantsInvited>());
    result->users = parseJsonAndGetArray<User>(&BotTypeParser::parseJsonAndGetUser, data, "users");
    return result;
}

std::string BotTypeParser::parseVideoChatParticipantsInvited(const VideoChatParticipantsInvited::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "users", parseArray(&BotTypeParser::parseUser, object->users));
    removeLastComma(result);
    result += '}';
    return result;
}

GiveawayCreated::Ptr BotTypeParser::parseJsonAndGetGiveawayCreated(const boost::property_tree::ptree& /*data*/) {
    auto result(std::make_shared<GiveawayCreated>());
    return result;
}

std::string BotTypeParser::parseGiveawayCreated(const GiveawayCreated::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    // removeLastComma(result);
    result += '}';
    return result;
}

Giveaway::Ptr BotTypeParser::parseJsonAndGetGiveaway(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Giveaway>());
    result->chats = parseJsonAndGetArray<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chats");
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

GiveawayWinners::Ptr BotTypeParser::parseJsonAndGetGiveawayWinners(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<GiveawayWinners>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
    result->winnersSelectionDate = data.get<std::uint32_t>("winners_selection_date", 0);
    result->winnerCount = data.get<std::int32_t>("winner_count", 0);
    result->winners = parseJsonAndGetArray<User>(&BotTypeParser::parseJsonAndGetUser, data, "winners");
    result->additionalChatCount = data.get<std::int32_t>("additional_chat_count", 0);
    result->premiumSubscriptionMonthCount = data.get<std::int32_t>("premium_subscription_month_count", 0);
    result->unclaimedPrizeCount = data.get<std::int32_t>("unclaimed_prize_count", 0);
    result->onlyNewMembers = data.get<bool>("only_new_members", false);
    result->wasRefunded = data.get<bool>("was_refunded", false);
    result->prizeDescription = data.get<std::string>("prize_description", "");
    return result;
}

GiveawayCompleted::Ptr BotTypeParser::parseJsonAndGetGiveawayCompleted(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<GiveawayCompleted>());
    result->winnerCount = data.get<std::int32_t>("winner_count", 0);
    result->unclaimedPrizeCount = data.get<std::int32_t>("unclaimed_prize_count", 0);
    result->giveawayMessage = tryParseJson<Message>(&BotTypeParser::parseJsonAndGetMessage, data, "giveaway_message");
    return result;
}

LinkPreviewOptions::Ptr BotTypeParser::parseJsonAndGetLinkPreviewOptions(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<LinkPreviewOptions>());
    result->isDisabled = data.get<bool>("is_disabled", false);
    result->url = data.get<std::string>("url", "");
    result->preferSmallMedia = data.get<bool>("prefer_small_media", false);
    result->preferLargeMedia = data.get<bool>("prefer_large_media", false);
    result->showAboveText = data.get<bool>("show_above_text", false);
    return result;
}

std::string BotTypeParser::parseLinkPreviewOptions(const LinkPreviewOptions::Ptr& object) {
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

UserProfilePhotos::Ptr BotTypeParser::parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<UserProfilePhotos>());
    result->totalCount = data.get<std::int32_t>("total_count", 0);
    result->photos = parseJsonAndGet2DArray<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "photos");
    return result;
}

std::string BotTypeParser::parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "total_count", object->totalCount);
    appendToJson(result, "photos", parse2DArray(&BotTypeParser::parsePhotoSize, object->photos));
    removeLastComma(result);
    result += '}';
    return result;
}

File::Ptr BotTypeParser::parseJsonAndGetFile(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<File>());
    result->fileId = data.get<std::string>("file_id", "");
    result->fileUniqueId = data.get<std::string>("file_unique_id", "");
    result->fileSize = data.get<std::int64_t>("file_size", 0);
    result->filePath = data.get<std::string>("file_path", "");
    return result;
}

std::string BotTypeParser::parseFile(const File::Ptr& object) {
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

WebAppInfo::Ptr BotTypeParser::parseJsonAndGetWebAppInfo(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<WebAppInfo>());
    result->url = data.get<std::string>("url", "");
    return result;
}

std::string BotTypeParser::parseWebAppInfo(const WebAppInfo::Ptr& object) {
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

ReplyKeyboardMarkup::Ptr BotTypeParser::parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ReplyKeyboardMarkup>());
    for (const auto& item : data.find("keyboard")->second) {
        result->keyboard.push_back(parseJsonAndGetArray<KeyboardButton>(&BotTypeParser::parseJsonAndGetKeyboardButton, item.second));
    }
    result->isPersistent = data.get<bool>("is_persistent", false);
    result->resizeKeyboard = data.get<bool>("resize_keyboard", false);
    result->oneTimeKeyboard = data.get<bool>("one_time_keyboard", false);
    result->inputFieldPlaceholder = data.get<std::string>("input_field_placeholder", "");
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string BotTypeParser::parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) {
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

KeyboardButton::Ptr BotTypeParser::parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<KeyboardButton>());
    result->text = data.get<std::string>("text", "");
    result->requestUsers = tryParseJson<KeyboardButtonRequestUsers>(&BotTypeParser::parseJsonAndGetKeyboardButtonRequestUsers, data, "request_users");
    result->requestChat = tryParseJson<KeyboardButtonRequestChat>(&BotTypeParser::parseJsonAndGetKeyboardButtonRequestChat, data, "request_chat");
    result->requestContact = data.get<bool>("request_contact", false);
    result->requestLocation = data.get<bool>("request_location", false);
    result->requestPoll = tryParseJson<KeyboardButtonPollType>(&BotTypeParser::parseJsonAndGetKeyboardButtonPollType, data, "request_poll");
    result->webApp = tryParseJson<WebAppInfo>(&BotTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    return result;
}

std::string BotTypeParser::parseKeyboardButton(const KeyboardButton::Ptr& object) {
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

KeyboardButtonRequestUsers::Ptr BotTypeParser::parseJsonAndGetKeyboardButtonRequestUsers(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseKeyboardButtonRequestUsers(const KeyboardButtonRequestUsers::Ptr& object) {
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

KeyboardButtonRequestChat::Ptr BotTypeParser::parseJsonAndGetKeyboardButtonRequestChat(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<KeyboardButtonRequestChat>());
    result->requestId = data.get<std::int32_t>("request_id", 0);
    result->chatIsChannel = data.get<bool>("chat_is_channel", false);
    result->chatIsForum = data.get<bool>("chat_is_forum", false);
    result->chatHasUsername = data.get<bool>("chat_has_username", false);
    result->chatIsCreated = data.get<bool>("chat_is_created", false);
    result->userAdministratorRights = tryParseJson<ChatAdministratorRights>(&BotTypeParser::parseJsonAndGetChatAdministratorRights, data, "user_administrator_rights");
    result->botAdministratorRights = tryParseJson<ChatAdministratorRights>(&BotTypeParser::parseJsonAndGetChatAdministratorRights, data, "bot_administrator_rights");
    result->botIsMember = data.get<bool>("bot_is_member", false);
    result->requestTitle = data.get<bool>("request_title", false);
    result->requestUsername = data.get<bool>("request_username", false);
    result->requestPhoto = data.get<bool>("request_photo", false);
    return result;
}

std::string BotTypeParser::parseKeyboardButtonRequestChat(const KeyboardButtonRequestChat::Ptr& object) {
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

KeyboardButtonPollType::Ptr BotTypeParser::parseJsonAndGetKeyboardButtonPollType(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<KeyboardButtonPollType>());
    result->type = data.get<std::string>("type", "");
    return result;
}

std::string BotTypeParser::parseKeyboardButtonPollType(const KeyboardButtonPollType::Ptr& object) {
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

ReplyKeyboardRemove::Ptr BotTypeParser::parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ReplyKeyboardRemove>());
    result->removeKeyboard = data.get<bool>("remove_keyboard", false);
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string BotTypeParser::parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object) {
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

InlineKeyboardMarkup::Ptr BotTypeParser::parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InlineKeyboardMarkup>());
    for (const auto& item : data.find("inline_keyboard")->second) {
        result->inlineKeyboard.push_back(parseJsonAndGetArray<InlineKeyboardButton>(&BotTypeParser::parseJsonAndGetInlineKeyboardButton, item.second));
    }
    return result;
}

std::string BotTypeParser::parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object) {
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

InlineKeyboardButton::Ptr BotTypeParser::parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InlineKeyboardButton>());
    result->text = data.get<std::string>("text", "");
    result->url = data.get<std::string>("url", "");
    result->callbackData = data.get<std::string>("callback_data", "");
    result->webApp = tryParseJson<WebAppInfo>(&BotTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    result->loginUrl = tryParseJson<LoginUrl>(&BotTypeParser::parseJsonAndGetLoginUrl, data, "login_url");
    result->switchInlineQuery = data.get<std::string>("switch_inline_query", "");
    result->switchInlineQueryCurrentChat = data.get<std::string>("switch_inline_query_current_chat", "");
    result->switchInlineQueryChosenChat = tryParseJson<SwitchInlineQueryChosenChat>(&BotTypeParser::parseJsonAndGetSwitchInlineQueryChosenChat, data, "switch_inline_query_chosen_chat");
    result->pay = data.get<bool>("pay", false);
    return result;
}

std::string BotTypeParser::parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) {
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
    if (object->pay)
        appendToJson(result, "pay", object->pay);
    removeLastComma(result);
    result += '}';
    return result;
}

LoginUrl::Ptr BotTypeParser::parseJsonAndGetLoginUrl(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<LoginUrl>());
    result->url = data.get<std::string>("url", "");
    result->forwardText = data.get<std::string>("forward_text", "");
    result->botUsername = data.get<std::string>("bot_username", "");
    result->requestWriteAccess = data.get<bool>("request_write_access", false);
    return result;
}

std::string BotTypeParser::parseLoginUrl(const LoginUrl::Ptr& object) {
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

SwitchInlineQueryChosenChat::Ptr BotTypeParser::parseJsonAndGetSwitchInlineQueryChosenChat(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<SwitchInlineQueryChosenChat>());
    result->query = data.get<std::string>("query", "");
    result->allowUserChats = data.get<bool>("allow_user_chats", false);
    result->allowBotChats = data.get<bool>("allow_bot_chats", false);
    result->allowGroupChats = data.get<bool>("allow_group_chats", false);
    result->allowChannelChats = data.get<bool>("allow_channel_chats", false);
    return result;
}

std::string BotTypeParser::parseSwitchInlineQueryChosenChat(const SwitchInlineQueryChosenChat::Ptr& object) {
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

CallbackQuery::Ptr BotTypeParser::parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<CallbackQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "from");
    result->message = tryParseJson<Message>(&BotTypeParser::parseJsonAndGetMessage, data, "message");
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    result->chatInstance = data.get<std::string>("chat_instance", "");
    result->data = data.get<std::string>("data", "");
    result->gameShortName = data.get<std::string>("game_short_name", "");
    return result;
}

ForceReply::Ptr BotTypeParser::parseJsonAndGetForceReply(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ForceReply>());
    result->forceReply = data.get<bool>("force_reply", false);
    result->inputFieldPlaceholder = data.get<std::string>("input_field_placeholder", "");
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string BotTypeParser::parseForceReply(const ForceReply::Ptr& object) {
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

ChatPhoto::Ptr BotTypeParser::parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatPhoto>());
    result->smallFileId = data.get<std::string>("small_file_id", "");
    result->smallFileUniqueId = data.get<std::string>("small_file_unique_id", "");
    result->bigFileId = data.get<std::string>("big_file_id", "");
    result->bigFileUniqueId = data.get<std::string>("big_file_unique_id", "");
    return result;
}

std::string BotTypeParser::parseChatPhoto(const ChatPhoto::Ptr& object) {
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

ChatInviteLink::Ptr BotTypeParser::parseJsonAndGetChatInviteLink(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatInviteLink>());
    result->inviteLink = data.get<std::string>("invite_link", "");
    result->creator = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "creator");
    result->createsJoinRequest = data.get<bool>("creates_join_request", false);
    result->isPrimary = data.get<bool>("is_primary", false);
    result->isRevoked = data.get<bool>("is_revoked", false);
    result->name = data.get<std::string>("name", "");
    result->expireDate = data.get<std::uint32_t>("expire_date", 0);
    result->memberLimit = data.get<std::uint32_t>("member_limit", 0);
    result->pendingJoinRequestCount = data.get<std::uint32_t>("pending_join_request_count", 0);
    return result;
}

std::string BotTypeParser::parseChatInviteLink(const ChatInviteLink::Ptr& object) {
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

ChatAdministratorRights::Ptr BotTypeParser::parseJsonAndGetChatAdministratorRights(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseChatAdministratorRights(const ChatAdministratorRights::Ptr& object) {
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

ChatMemberUpdated::Ptr BotTypeParser::parseJsonAndGetChatMemberUpdated(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatMemberUpdated>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->from = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "from");
    result->date = data.get<std::uint32_t>("date", 0);
    result->oldChatMember = tryParseJson<ChatMember>(&BotTypeParser::parseJsonAndGetChatMember, data, "old_chat_member");
    result->newChatMember = tryParseJson<ChatMember>(&BotTypeParser::parseJsonAndGetChatMember, data, "new_chat_member");
    result->inviteLink = tryParseJson<ChatInviteLink>(&BotTypeParser::parseJsonAndGetChatInviteLink, data, "invite_link");
    result->viaChatFolderInviteLink = data.get<bool>("via_chat_folder_invite_link", false);
    return result;
}

ChatMember::Ptr BotTypeParser::parseJsonAndGetChatMember(const boost::property_tree::ptree& data) {
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
    result->user = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "user");

    return result;
}

std::string BotTypeParser::parseChatMember(const ChatMember::Ptr& object) {
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

ChatMemberOwner::Ptr BotTypeParser::parseJsonAndGetChatMemberOwner(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberOwner>());
    result->isAnonymous = data.get<bool>("is_anonymous", false);
    result->customTitle = data.get<std::string>("custom_title", "");
    return result;
}

std::string BotTypeParser::parseChatMemberOwner(const ChatMemberOwner::Ptr& object) {
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

ChatMemberAdministrator::Ptr BotTypeParser::parseJsonAndGetChatMemberAdministrator(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseChatMemberAdministrator(const ChatMemberAdministrator::Ptr& object) {
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

ChatMemberMember::Ptr BotTypeParser::parseJsonAndGetChatMemberMember(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberMember>());
    return result;
}

std::string BotTypeParser::parseChatMemberMember(const ChatMemberMember::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberRestricted::Ptr BotTypeParser::parseJsonAndGetChatMemberRestricted(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseChatMemberRestricted(const ChatMemberRestricted::Ptr& object) {
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

ChatMemberLeft::Ptr BotTypeParser::parseJsonAndGetChatMemberLeft(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberLeft>());
    return result;
}

std::string BotTypeParser::parseChatMemberLeft(const ChatMemberLeft::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatMember(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatMember().
    return result;
}

ChatMemberBanned::Ptr BotTypeParser::parseJsonAndGetChatMemberBanned(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetChatMember().
    auto result(std::make_shared<ChatMemberBanned>());
    result->untilDate = data.get<std::uint32_t>("until_date", 0);
    return result;
}

std::string BotTypeParser::parseChatMemberBanned(const ChatMemberBanned::Ptr& object) {
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

ChatJoinRequest::Ptr BotTypeParser::parseJsonAndGetChatJoinRequest(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatJoinRequest>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->from = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "from");
    result->userChatId = data.get<std::int64_t>("user_chat_id", 0);
    result->date = data.get<std::int32_t>("date", 0);
    result->bio = data.get<std::string>("bio", "");
    result->inviteLink = tryParseJson<ChatInviteLink>(&BotTypeParser::parseJsonAndGetChatInviteLink, data, "invite_link");
    return result;
}

ChatPermissions::Ptr BotTypeParser::parseJsonAndGetChatPermissions(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseChatPermissions(const ChatPermissions::Ptr& object) {
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

Birthdate::Ptr BotTypeParser::parseJsonAndGetBirthdate(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Birthdate>());
    result->day = data.get<std::uint8_t>("day", 0);
    result->month = data.get<std::uint8_t>("month", 0);
    result->year = data.get<std::uint16_t>("year", 0);
    return result;
}

std::string BotTypeParser::parseBirthdate(const Birthdate::Ptr& object) {
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

ChatLocation::Ptr BotTypeParser::parseJsonAndGetChatLocation(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatLocation>());
    result->location = tryParseJson<Location>(&BotTypeParser::parseJsonAndGetLocation, data, "location");
    result->address = data.get<std::string>("address", "");
    return result;
}

std::string BotTypeParser::parseChatLocation(const ChatLocation::Ptr& object) {
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

ReactionType::Ptr BotTypeParser::parseJsonAndGetReactionType(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseReactionType(const ReactionType::Ptr& object) {
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

ReactionTypeEmoji::Ptr BotTypeParser::parseJsonAndGetReactionTypeEmoji(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetReactionType().
    auto result(std::make_shared<ReactionTypeEmoji>());
    result->emoji = data.get<std::string>("emoji", "");
    return result;
}

std::string BotTypeParser::parseReactionTypeEmoji(const ReactionTypeEmoji::Ptr& object) {
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

ReactionTypeCustomEmoji::Ptr BotTypeParser::parseJsonAndGetReactionTypeCustomEmoji(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetReactionType().
    auto result(std::make_shared<ReactionTypeCustomEmoji>());
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    return result;
}

std::string BotTypeParser::parseReactionTypeCustomEmoji(const ReactionTypeCustomEmoji::Ptr& object) {
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

ReactionCount::Ptr BotTypeParser::parseJsonAndGetReactionCount(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ReactionCount>());
    result->type = tryParseJson<ReactionType>(&BotTypeParser::parseJsonAndGetReactionType, data, "type");
    result->totalCount = data.get<std::int32_t>("total_count", 0);
    return result;
}

std::string BotTypeParser::parseReactionCount(const ReactionCount::Ptr& object) {
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

MessageReactionUpdated::Ptr BotTypeParser::parseJsonAndGetMessageReactionUpdated(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<MessageReactionUpdated>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->user = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "user");
    result->actorChat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "actor_chat");
    result->date = data.get<std::uint32_t>("date", 0);
    result->oldReaction = parseJsonAndGetArray<ReactionType>(&BotTypeParser::parseJsonAndGetReactionType, data, "old_reaction");
    result->newReaction = parseJsonAndGetArray<ReactionType>(&BotTypeParser::parseJsonAndGetReactionType, data, "new_reaction");
    return result;
}

MessageReactionCountUpdated::Ptr BotTypeParser::parseJsonAndGetMessageReactionCountUpdated(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<MessageReactionCountUpdated>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->messageId = data.get<std::int32_t>("message_id", 0);
    result->date = data.get<std::uint32_t>("date", 0);
    result->reactions = parseJsonAndGetArray<ReactionCount>(&BotTypeParser::parseJsonAndGetReactionCount, data, "reactions");
    return result;
}

BotCommand::Ptr BotTypeParser::parseJsonAndGetBotCommand(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<BotCommand>());
    result->command = data.get<std::string>("command", "");
    result->description = data.get<std::string>("description", "");
    return result;
}

std::string BotTypeParser::parseBotCommand(const BotCommand::Ptr& object) {
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

BotCommandScope::Ptr BotTypeParser::parseJsonAndGetBotCommandScope(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseBotCommandScope(const BotCommandScope::Ptr& object) {
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

BotCommandScopeDefault::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeDefault(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeDefault>());
    return result;
}

std::string BotTypeParser::parseBotCommandScopeDefault(const BotCommandScopeDefault::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllPrivateChats::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeAllPrivateChats(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllPrivateChats>());
    return result;
}

std::string BotTypeParser::parseBotCommandScopeAllPrivateChats(const BotCommandScopeAllPrivateChats::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllGroupChats::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeAllGroupChats(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllGroupChats>());
    return result;
}

std::string BotTypeParser::parseBotCommandScopeAllGroupChats(const BotCommandScopeAllGroupChats::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeAllChatAdministrators::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeAllChatAdministrators(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeAllChatAdministrators>());
    return result;
}

std::string BotTypeParser::parseBotCommandScopeAllChatAdministrators(const BotCommandScopeAllChatAdministrators::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseBotCommandScope(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseBotCommandScope().
    return result;
}

BotCommandScopeChat::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeChat(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChat>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    return result;
}

std::string BotTypeParser::parseBotCommandScopeChat(const BotCommandScopeChat::Ptr& object) {
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

BotCommandScopeChatAdministrators::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeChatAdministrators(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChatAdministrators>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    return result;
}

std::string BotTypeParser::parseBotCommandScopeChatAdministrators(const BotCommandScopeChatAdministrators::Ptr& object) {
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

BotCommandScopeChatMember::Ptr BotTypeParser::parseJsonAndGetBotCommandScopeChatMember(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetBotCommandScope().
    auto result(std::make_shared<BotCommandScopeChatMember>());
    result->chatId = data.get<std::int64_t>("chat_id", 0);
    result->userId = data.get<std::int64_t>("user_id", 0);
    return result;
}

std::string BotTypeParser::parseBotCommandScopeChatMember(const BotCommandScopeChatMember::Ptr& object) {
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

BotName::Ptr BotTypeParser::parseJsonAndGetBotName(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<BotName>());
    result->name = data.get<std::string>("name", "");
    return result;
}

std::string BotTypeParser::parseBotName(const BotName::Ptr& object) {
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

BotDescription::Ptr BotTypeParser::parseJsonAndGetBotDescription(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<BotDescription>());
    result->description = data.get<std::string>("description", "");
    return result;
}

std::string BotTypeParser::parseBotDescription(const BotDescription::Ptr& object) {
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

BotShortDescription::Ptr BotTypeParser::parseJsonAndGetBotShortDescription(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<BotShortDescription>());
    result->shortDescription = data.get<std::string>("short_description", "");
    return result;
}

std::string BotTypeParser::parseBotShortDescription(const BotShortDescription::Ptr& object) {
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

MenuButton::Ptr BotTypeParser::parseJsonAndGetMenuButton(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseMenuButton(const MenuButton::Ptr& object) {
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

MenuButtonCommands::Ptr BotTypeParser::parseJsonAndGetMenuButtonCommands(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonCommands>());
    return result;
}

std::string BotTypeParser::parseMenuButtonCommands(const MenuButtonCommands::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseMenuButton(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseMenuButton().
    return result;
}

MenuButtonWebApp::Ptr BotTypeParser::parseJsonAndGetMenuButtonWebApp(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonWebApp>());
    result->text = data.get<std::string>("text", "");
    result->webApp = tryParseJson<WebAppInfo>(&BotTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    return result;
}

std::string BotTypeParser::parseMenuButtonWebApp(const MenuButtonWebApp::Ptr& object) {
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

MenuButtonDefault::Ptr BotTypeParser::parseJsonAndGetMenuButtonDefault(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetMenuButton().
    auto result(std::make_shared<MenuButtonDefault>());
    return result;
}

std::string BotTypeParser::parseMenuButtonDefault(const MenuButtonDefault::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseMenuButton(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseMenuButton().
    return result;
}

ChatBoostSource::Ptr BotTypeParser::parseJsonAndGetChatBoostSource(const boost::property_tree::ptree& data) {
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
    result->user = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "user");

    return result;
}

std::string BotTypeParser::parseChatBoostSource(const ChatBoostSource::Ptr& object) {
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

ChatBoostSourcePremium::Ptr BotTypeParser::parseJsonAndGetChatBoostSourcePremium(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourcePremium>());
    return result;
}

std::string BotTypeParser::parseChatBoostSourcePremium(const ChatBoostSourcePremium::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatBoostSource(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatBoostSource().
    return result;
}

ChatBoostSourceGiftCode::Ptr BotTypeParser::parseJsonAndGetChatBoostSourceGiftCode(const boost::property_tree::ptree& /*data*/) {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourceGiftCode>());
    return result;
}

std::string BotTypeParser::parseChatBoostSourceGiftCode(const ChatBoostSourceGiftCode::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseChatBoostSource(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    // The last comma will be erased by parseChatBoostSource().
    return result;
}

ChatBoostSourceGiveaway::Ptr BotTypeParser::parseJsonAndGetChatBoostSourceGiveaway(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetChatBoostSource().
    auto result(std::make_shared<ChatBoostSourceGiveaway>());
    result->giveawayMessageId = data.get<std::int32_t>("giveaway_message_id", 0);
    result->isUnclaimed = data.get<bool>("is_unclaimed", false);
    return result;
}

std::string BotTypeParser::parseChatBoostSourceGiveaway(const ChatBoostSourceGiveaway::Ptr& object) {
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

ChatBoost::Ptr BotTypeParser::parseJsonAndGetChatBoost(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatBoost>());
    result->boostId = data.get<std::string>("boost_id", "");
    result->addDate = data.get<std::uint32_t>("add_date", 0);
    result->expirationDate = data.get<std::uint32_t>("expiration_date", 0);
    result->source = tryParseJson<ChatBoostSource>(&BotTypeParser::parseJsonAndGetChatBoostSource, data, "source");
    return result;
}

std::string BotTypeParser::parseChatBoost(const ChatBoost::Ptr& object) {
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

ChatBoostUpdated::Ptr BotTypeParser::parseJsonAndGetChatBoostUpdated(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatBoostUpdated>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->boost = tryParseJson<ChatBoost>(&BotTypeParser::parseJsonAndGetChatBoost, data, "boost");
    return result;
}

ChatBoostRemoved::Ptr BotTypeParser::parseJsonAndGetChatBoostRemoved(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChatBoostRemoved>());
    result->chat = tryParseJson<Chat>(&BotTypeParser::parseJsonAndGetChat, data, "chat");
    result->boostId = data.get<std::string>("boost_id", "");
    result->removeDate = data.get<std::uint32_t>("remove_date", 0);
    result->source = tryParseJson<ChatBoostSource>(&BotTypeParser::parseJsonAndGetChatBoostSource, data, "source");
    return result;
}

UserChatBoosts::Ptr BotTypeParser::parseJsonAndGetUserChatBoosts(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<UserChatBoosts>());
    result->boosts = parseJsonAndGetArray<ChatBoost>(&BotTypeParser::parseJsonAndGetChatBoost, data, "boosts");
    return result;
}

std::string BotTypeParser::parseUserChatBoosts(const UserChatBoosts::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "boosts", parseArray(&BotTypeParser::parseChatBoost, object->boosts));
    removeLastComma(result);
    result += '}';
    return result;
}

ResponseParameters::Ptr BotTypeParser::parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ResponseParameters>());
    result->migrateToChatId = data.get<std::int64_t>("migrate_to_chat_id", 0);
    result->retryAfter = data.get<std::int32_t>("retry_after", 0);
    return result;
}

std::string BotTypeParser::parseResponseParameters(const ResponseParameters::Ptr& object) {
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

InputMedia::Ptr BotTypeParser::parseJsonAndGetInputMedia(const boost::property_tree::ptree& data) {
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
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");

    return result;
}

std::string BotTypeParser::parseInputMedia(const InputMedia::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "media", object->media);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));

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

InputMediaPhoto::Ptr BotTypeParser::parseJsonAndGetInputMediaPhoto(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaPhoto>());
    result->hasSpoiler = data.get<bool>("has_spoiler", false);
    return result;
}

std::string BotTypeParser::parseInputMediaPhoto(const InputMediaPhoto::Ptr& object) {
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

InputMediaVideo::Ptr BotTypeParser::parseJsonAndGetInputMediaVideo(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseInputMediaVideo(const InputMediaVideo::Ptr& object) {
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

InputMediaAnimation::Ptr BotTypeParser::parseJsonAndGetInputMediaAnimation(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaAnimation>());
    result->thumbnail = data.get<std::string>("thumbnail", "");
    result->width = data.get<std::int32_t>("width", 0);
    result->height = data.get<std::int32_t>("height", 0);
    result->duration = data.get<std::int32_t>("duration", 0);
    result->hasSpoiler = data.get<bool>("has_spoiler", false);
    return result;
}

std::string BotTypeParser::parseInputMediaAnimation(const InputMediaAnimation::Ptr& object) {
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

InputMediaAudio::Ptr BotTypeParser::parseJsonAndGetInputMediaAudio(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaAudio>());
    result->thumbnail = data.get<std::string>("thumbnail", "");
    result->duration = data.get<std::int32_t>("duration", 0);
    result->performer = data.get<std::string>("performer", "");
    result->title = data.get<std::string>("title", "");
    return result;
}

std::string BotTypeParser::parseInputMediaAudio(const InputMediaAudio::Ptr& object) {
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

InputMediaDocument::Ptr BotTypeParser::parseJsonAndGetInputMediaDocument(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMedia().
    auto result(std::make_shared<InputMediaDocument>());
    result->thumbnail = data.get<std::string>("thumbnail", "");
    result->disableContentTypeDetection = data.get<bool>("disable_content_type_detection", false);
    return result;
}

std::string BotTypeParser::parseInputMediaDocument(const InputMediaDocument::Ptr& object) {
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

Sticker::Ptr BotTypeParser::parseJsonAndGetSticker(const boost::property_tree::ptree& data) {
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
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    result->emoji = data.get<std::string>("emoji", "");
    result->setName = data.get<std::string>("set_name", "");
    result->premiumAnimation = tryParseJson<File>(&BotTypeParser::parseJsonAndGetFile, data, "premium_animation");
    result->maskPosition = tryParseJson<MaskPosition>(&BotTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->customEmojiId = data.get<std::string>("custom_emoji_id", "");
    result->needsRepainting = data.get<bool>("needs_repainting", true);
    result->fileSize = data.get<std::int32_t>("file_size", 0);
    return result;
}

std::string BotTypeParser::parseSticker(const Sticker::Ptr& object) {
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

StickerSet::Ptr BotTypeParser::parseJsonAndGetStickerSet(const boost::property_tree::ptree& data) {
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
    result->stickers = parseJsonAndGetArray<Sticker>(&BotTypeParser::parseJsonAndGetSticker, data, "stickers");
    result->thumbnail = tryParseJson<PhotoSize>(&BotTypeParser::parseJsonAndGetPhotoSize, data, "thumbnail");
    return result;
}

std::string BotTypeParser::parseStickerSet(const StickerSet::Ptr& object) {
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
    appendToJson(result, "stickers", parseArray(&BotTypeParser::parseSticker, object->stickers));
    appendToJson(result, "thumbnail", parsePhotoSize(object->thumbnail));
    removeLastComma(result);
    result += '}';
    return result;
}

MaskPosition::Ptr BotTypeParser::parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<MaskPosition>());
    result->point = data.get<std::string>("point", "");
    result->xShift = data.get<float>("x_shift", 0);
    result->yShift = data.get<float>("y_shift", 0);
    result->scale = data.get<float>("scale", 0);
    return result;
}

std::string BotTypeParser::parseMaskPosition(const MaskPosition::Ptr& object) {
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

InputSticker::Ptr BotTypeParser::parseJsonAndGetInputSticker(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InputSticker>());
    result->sticker = data.get<std::string>("sticker", "");
    result->format = data.get<std::string>("format", "");
    result->emojiList = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "emoji_list");
    result->maskPosition = tryParseJson<MaskPosition>(&BotTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->keywords = parseJsonAndGetArray<std::string>(
        [] (const boost::property_tree::ptree& innerData)->std::string {
        return innerData.get<std::string>("");
    }, data, "keywords");
    return result;
}

std::string BotTypeParser::parseInputSticker(const InputSticker::Ptr& object) {
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

InlineQuery::Ptr BotTypeParser::parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InlineQuery>());
    result->id = data.get<std::string>("id", "");
    result->from = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "from");
    result->query = data.get<std::string>("query", "");
    result->offset = data.get<std::string>("offset", "");
    result->chatType = data.get<std::string>("chat_type", "");
    result->location = tryParseJson<Location>(&BotTypeParser::parseJsonAndGetLocation, data, "location");
    return result;
}

std::string BotTypeParser::parseInlineQuery(const InlineQuery::Ptr& object) {
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

InlineQueryResultsButton::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultsButton(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<InlineQueryResultsButton>());
    result->text = data.get<std::string>("text", "");
    result->webApp = tryParseJson<WebAppInfo>(&BotTypeParser::parseJsonAndGetWebAppInfo, data, "web_app");
    result->startParameter = data.get<std::string>("start_parameter", "");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultsButton(const InlineQueryResultsButton::Ptr& object) {
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

InlineQueryResult::Ptr BotTypeParser::parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) {
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
    result->replyMarkup = tryParseJson<InlineKeyboardMarkup>(&BotTypeParser::parseJsonAndGetInlineKeyboardMarkup, data, "reply_markup");

    return result;
}

std::string BotTypeParser::parseInlineQueryResult(const InlineQueryResult::Ptr& object) {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "id", object->id);
    appendToJson(result, "reply_markup", parseInlineKeyboardMarkup(object->replyMarkup));

    // Single type
    if (object->type == InlineQueryResultArticle::TYPE) {
        result += parseInlineQueryResultArticle(std::static_pointer_cast<InlineQueryResultArticle>(object));
    } else if (object->type == InlineQueryResultContact::TYPE) {
        result += parseInlineQueryResultContact(std::static_pointer_cast<InlineQueryResultContact>(object));
    } else if (object->type == InlineQueryResultGame::TYPE) {
        result += parseInlineQueryResultGame(std::static_pointer_cast<InlineQueryResultGame>(object));
    } else if (object->type == InlineQueryResultLocation::TYPE) {
        result += parseInlineQueryResultLocation(std::static_pointer_cast<InlineQueryResultLocation>(object));
    } else if (object->type == InlineQueryResultVenue::TYPE) {
        result += parseInlineQueryResultVenue(std::static_pointer_cast<InlineQueryResultVenue>(object));
    }else if (object->type == InlineQueryResultCachedSticker::TYPE) {
        result += parseInlineQueryResultCachedSticker(std::static_pointer_cast<InlineQueryResultCachedSticker>(object));
    }
    // Use dynamic_cast to distinguish duplicate types
    else if (object->type == InlineQueryResultPhoto::TYPE) {
        if (auto cachedPhoto = std::dynamic_pointer_cast<InlineQueryResultCachedPhoto>(object)) {
            result += parseInlineQueryResultCachedPhoto(cachedPhoto);
        } else if (auto photo = std::dynamic_pointer_cast<InlineQueryResultPhoto>(object)) {
            result += parseInlineQueryResultPhoto(photo);
        }
    } else if (object->type == InlineQueryResultGif::TYPE) {
        if (auto cachedGif = std::dynamic_pointer_cast<InlineQueryResultCachedGif>(object)) {
            result += parseInlineQueryResultCachedGif(cachedGif);
        } else if (auto gif = std::dynamic_pointer_cast<InlineQueryResultGif>(object)) {
            result += parseInlineQueryResultGif(gif);
        }
    } else if (object->type == InlineQueryResultVideo::TYPE) {
        if (auto cachedVideo = std::dynamic_pointer_cast<InlineQueryResultCachedVideo>(object)) {
            result += parseInlineQueryResultCachedVideo(cachedVideo);
        } else if (auto video = std::dynamic_pointer_cast<InlineQueryResultVideo>(object)) {
            result += parseInlineQueryResultVideo(video);
        }
    } else if (object->type == InlineQueryResultAudio::TYPE) {
        if (auto cachedAudio = std::dynamic_pointer_cast<InlineQueryResultCachedAudio>(object)) {
            result += parseInlineQueryResultCachedAudio(cachedAudio);
        } else if (auto audio = std::dynamic_pointer_cast<InlineQueryResultAudio>(object)) {
            result += parseInlineQueryResultAudio(audio);
        }
    } else if (object->type == InlineQueryResultVoice::TYPE) {
        if (auto cachedVoice = std::dynamic_pointer_cast<InlineQueryResultCachedVoice>(object)) {
            result += parseInlineQueryResultCachedVoice(cachedVoice);
        } else if (auto voice = std::dynamic_pointer_cast<InlineQueryResultVoice>(object)) {
            result += parseInlineQueryResultVoice(voice);
        }
    } else if (object->type == InlineQueryResultMpeg4Gif::TYPE) {
        if (auto cachedMpeg4Gif = std::dynamic_pointer_cast<InlineQueryResultCachedMpeg4Gif>(object)) {
            result += parseInlineQueryResultCachedMpeg4Gif(cachedMpeg4Gif);
        } else if (auto mpeg4Gif = std::dynamic_pointer_cast<InlineQueryResultMpeg4Gif>(object)) {
            result += parseInlineQueryResultMpeg4Gif(mpeg4Gif);
        }
    } else if (object->type == InlineQueryResultDocument::TYPE) {
        // Document类型也有冲突
        if (auto cachedDocument = std::dynamic_pointer_cast<InlineQueryResultCachedDocument>(object)) {
            result += parseInlineQueryResultCachedDocument(cachedDocument);
        } else if (auto document = std::dynamic_pointer_cast<InlineQueryResultDocument>(object)) {
            result += parseInlineQueryResultDocument(document);
        }
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InlineQueryResultArticle::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultArticle>());
    result->title = data.get<std::string>("title", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->url = data.get<std::string>("url", "");
    result->hideUrl = data.get<bool>("hide_url", false);
    result->description = data.get<std::string>("description", "");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
    return result;
}

std::string BotTypeParser::parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) {
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

InlineQueryResultPhoto::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) {
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
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultGif::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) {
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
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultMpeg4Gif::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) {
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
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVideo::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultVideo>());
    result->videoUrl = data.get<std::string>("video_url", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->videoWidth = data.get<std::int32_t>("video_width", 0);
    result->videoHeight = data.get<std::int32_t>("video_height", 0);
    result->videoDuration = data.get<std::int32_t>("video_duration", 0);
    result->description = data.get<std::string>("description", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "video_width", object->videoWidth);
    appendToJson(result, "video_height", object->videoHeight);
    appendToJson(result, "video_duration", object->videoDuration);
    appendToJson(result, "description", object->description);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultAudio::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultAudio>());
    result->audioUrl = data.get<std::string>("audio_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->performer = data.get<std::string>("performer", "");
    result->audioDuration = data.get<std::int32_t>("audio_duration", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "audio_duration", object->audioDuration);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVoice::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultVoice>());
    result->voiceUrl = data.get<std::string>("voice_url", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->voiceDuration = data.get<std::int32_t>("voice_duration", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "voice_duration", object->voiceDuration);
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultDocument::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultDocument>());
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->documentUrl = data.get<std::string>("document_url", "");
    result->mimeType = data.get<std::string>("mime_type", "");
    result->description = data.get<std::string>("description", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
    return result;
}

std::string BotTypeParser::parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
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

InlineQueryResultLocation::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultLocation>());
    result->latitude = data.get<float>("latitude", 0);
    result->longitude = data.get<float>("longitude", 0);
    result->title = data.get<std::string>("title", "");
    result->horizontalAccuracy = data.get<float>("horizontal_accuracy", 0);
    result->livePeriod = data.get<std::int32_t>("live_period", 0);
    result->heading = data.get<std::int32_t>("heading", 0);
    result->proximityAlertRadius = data.get<std::int32_t>("proximity_alert_radius", 0);
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
    return result;
}

std::string BotTypeParser::parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object) {
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

InlineQueryResultVenue::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data) {
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
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
    return result;
}

std::string BotTypeParser::parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object) {
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

InlineQueryResultContact::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultContact>());
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->vcard = data.get<std::string>("vcard", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    result->thumbnailUrl = data.get<std::string>("thumbnail_url", "");
    result->thumbnailWidth = data.get<std::int32_t>("thumbnail_width", 0);
    result->thumbnailHeight = data.get<std::int32_t>("thumbnail_height", 0);
    return result;
}

std::string BotTypeParser::parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object) {
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

InlineQueryResultGame::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultGame>());
    result->gameShortName = data.get<std::string>("game_short_name", "");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object) {
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

InlineQueryResultCachedPhoto::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedPhoto>());
    result->photoFileId = data.get<std::string>("photo_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedGif::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedGif>());
    result->gifFileId = data.get<std::string>("gif_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedMpeg4Gif::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedMpeg4Gif>());
    result->mpeg4FileId = data.get<std::string>("mpeg4_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedSticker::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedSticker>());
    result->stickerFileId = data.get<std::string>("sticker_file_id", "");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object) {
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

InlineQueryResultCachedDocument::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedDocument>());
    result->title = data.get<std::string>("title", "");
    result->documentFileId = data.get<std::string>("document_file_id", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedVideo::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedVideo>());
    result->videoFileId = data.get<std::string>("video_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedVoice::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedVoice>());
    result->voiceFileId = data.get<std::string>("voice_file_id", "");
    result->title = data.get<std::string>("title", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object) {
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
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedAudio::Ptr BotTypeParser::parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInlineQueryResult().
    auto result(std::make_shared<InlineQueryResultCachedAudio>());
    result->audioFileId = data.get<std::string>("audio_file_id", "");
    result->caption = data.get<std::string>("caption", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&BotTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");
    return result;
}

std::string BotTypeParser::parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result std::string.
    std::string result;
    appendToJson(result, "audio_file_id", object->audioFileId);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "caption_entities", parseArray(&BotTypeParser::parseMessageEntity, object->captionEntities));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InputMessageContent::Ptr BotTypeParser::parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseInputMessageContent(const InputMessageContent::Ptr& object) {
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

InputTextMessageContent::Ptr BotTypeParser::parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputTextMessageContent>());
    result->messageText = data.get<std::string>("message_text", "");
    result->parseMode = data.get<std::string>("parse_mode", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&BotTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->linkPreviewOptions = tryParseJson<LinkPreviewOptions>(&BotTypeParser::parseJsonAndGetLinkPreviewOptions, data, "link_preview_options");
    return result;
}

std::string BotTypeParser::parseInputTextMessageContent(const InputTextMessageContent::Ptr& object) {
    if (!object) {
        return "";
    }
    // This function will be called by parseInputMessageContent()
    std::string result;
    appendToJson(result, "message_text", object->messageText);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "entities", parseArray(&BotTypeParser::parseMessageEntity, object->entities));
    appendToJson(result, "link_preview_options", parseLinkPreviewOptions(object->linkPreviewOptions));
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputLocationMessageContent::Ptr BotTypeParser::parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object) {
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

InputVenueMessageContent::Ptr BotTypeParser::parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object) {
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

InputContactMessageContent::Ptr BotTypeParser::parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputContactMessageContent>());
    result->phoneNumber = data.get<std::string>("phone_number", "");
    result->firstName = data.get<std::string>("first_name", "");
    result->lastName = data.get<std::string>("last_name", "");
    result->vcard = data.get<std::string>("vcard", "");
    return result;
}

std::string BotTypeParser::parseInputContactMessageContent(const InputContactMessageContent::Ptr& object) {
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

InputInvoiceMessageContent::Ptr BotTypeParser::parseJsonAndGetInputInvoiceMessageContent(const boost::property_tree::ptree& data) {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(std::make_shared<InputInvoiceMessageContent>());
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->payload = data.get<std::string>("payload", "");
    result->providerToken = data.get<std::string>("provider_token", "");
    result->currency = data.get<std::string>("currency", "");
    result->prices = parseJsonAndGetArray<LabeledPrice>(&BotTypeParser::parseJsonAndGetLabeledPrice, data, "prices");
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
    result->sendPhoneNumberToProvider = data.get<bool>("send_phone_number_to_provider", false);
    result->sendEmailToProvider = data.get<bool>("send_email_to_provider", false);
    result->isFlexible = data.get<bool>("is_flexible", false);
    return result;
}

std::string BotTypeParser::parseInputInvoiceMessageContent(const InputInvoiceMessageContent::Ptr& object) {
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
    appendToJson(result, "prices", parseArray(&BotTypeParser::parseLabeledPrice, object->prices));
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
    appendToJson(result, "send_phone_number_to_provider", object->sendPhoneNumberToProvider);
    appendToJson(result, "send_email_to_provider", object->sendEmailToProvider);
    appendToJson(result, "is_flexible", object->isFlexible);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

ChosenInlineResult::Ptr BotTypeParser::parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<ChosenInlineResult>());
    result->resultId = data.get<std::string>("result_id", "");
    result->from = tryParseJson<User>(&BotTypeParser::parseJsonAndGetUser, data, "from");
    result->location = tryParseJson<Location>(&BotTypeParser::parseJsonAndGetLocation, data, "location");
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    result->query = data.get<std::string>("query", "");
    return result;
}

std::string BotTypeParser::parseChosenInlineResult(const ChosenInlineResult::Ptr& object) {
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

SentWebAppMessage::Ptr BotTypeParser::parseJsonAndGetSentWebAppMessage(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<SentWebAppMessage>());
    result->inlineMessageId = data.get<std::string>("inline_message_id", "");
    return result;
}

std::string BotTypeParser::parseSentWebAppMessage(const SentWebAppMessage::Ptr& object) {
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

LabeledPrice::Ptr BotTypeParser::parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<LabeledPrice>());
    result->label = data.get<std::string>("label", "");
    result->amount = data.get<std::int32_t>("amount", 0);
    return result;
}

std::string BotTypeParser::parseLabeledPrice(const LabeledPrice::Ptr& object) {
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

Invoice::Ptr BotTypeParser::parseJsonAndGetInvoice(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Invoice>());
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->startParameter = data.get<std::string>("start_parameter", "");
    result->currency = data.get<std::string>("currency", "");
    result->totalAmount = data.get<std::int32_t>("total_amount", 0);
    return result;
}

std::string BotTypeParser::parseInvoice(const Invoice::Ptr& object) {
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

GenericReply::Ptr BotTypeParser::parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) {
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

std::string BotTypeParser::parseGenericReply(const GenericReply::Ptr& object) {
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

}
