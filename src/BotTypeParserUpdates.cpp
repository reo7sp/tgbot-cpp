#include "maxbot/BotTypeParserUpdates.h"

namespace MaxBot {

Updates::Ptr BotTypeParserUpdates::parseJsonAndGetUpdates(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Updates>());
    result->marker = data.get<std::int32_t>("marker", 0);
    result->updates = parseJsonAndGetArray<Update>(&BotTypeParserUpdates::parseJsonAndGetUpdate, data, "updates");
    return result;
}

Update::Ptr BotTypeParserUpdates::parseJsonAndGetUpdate(const boost::property_tree::ptree& data) {
    auto result(std::make_shared<Update>());
    result->update_type = data.get<std::string>("update_type", "");
    result->timestamp = data.get<std::int64_t>("timestamp", 0);
	if (result->update_type == "bot_added")
		result->_data = parseJsonAndGetUpdateBotAddedToChat(data);
	else if (result->update_type == "bot_started")
		result->_data = parseJsonAndGetUpdateBotStarted(data);
	else if (result->update_type == "bot_stopped")
		result->_data = parseJsonAndGetUpdateBotStopped(data);
	else if (result->update_type == "bot_removed")
		result->_data = parseJsonAndGetUpdateBotRemovedFromChat(data);
	else if (result->update_type == "chat_title_changed")
		result->_data = parseJsonAndGetUpdateChatTitleChanged(data);
	else if (result->update_type == "dialog_cleared")
		result->_data = parseJsonAndGetUpdateDialogCleared(data);
	else if (result->update_type == "dialog_muted")
		result->_data = parseJsonAndGetUpdateDialogMuted(data);
	else if (result->update_type == "dialog_unmuted")
		result->_data = parseJsonAndGetUpdateDialogUnmuted(data);
	else if (result->update_type == "dialog_removed")
		result->_data = parseJsonAndGetUpdateDialogRemoved(data);
	else if (result->update_type == "message_callback")
		result->_data = parseJsonAndGetUpdateMessageCallback(data);
	else if (result->update_type == "message_created")
		result->_data = parseJsonAndGetUpdateMessageCreated(data);
	else if (result->update_type == "message_edited")
		result->_data = parseJsonAndGetUpdateMessageEdited(data);
	else if (result->update_type == "message_removed")
		result->_data = parseJsonAndGetUpdateMessageRemoved(data);
	else if (result->update_type == "user_added")
		result->_data = parseJsonAndGetUpdateUserAddedToChat(data);
	else if (result->update_type == "user_removed")
		result->_data = parseJsonAndGetUpdateUserRemovedFromChat(data);

    return result;
}

UpdateBotAddedToChat::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateBotAddedToChat(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateBotAddedToChat>();
	result->chat_id = data.get<std::int64_t>("chat_id", 0);
	result->is_channel = data.get<bool>("is_channel", false);
	result->user = parseJsonAndGetUser(data);
    return result;
}

UpdateBotStarted::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateBotStarted(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateBotStarted>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->payload = data.get<std::string>("payload", "");
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateBotStopped::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateBotStopped(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateBotStopped>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateBotRemovedFromChat::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateBotRemovedFromChat(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateBotRemovedFromChat>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->is_channel = data.get<bool>("is_channel", false);
    return result;
}

UpdateChatTitleChanged::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateChatTitleChanged(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateChatTitleChanged>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->title = data.get<std::string>("title", "");
    return result;
}

UpdateDialogCleared::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateDialogCleared(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateDialogCleared>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateDialogMuted::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateDialogMuted(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateDialogMuted>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->muted_until = data.get<std::int64_t>("muted_until", 0);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateDialogUnmuted::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateDialogUnmuted(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateDialogUnmuted>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateDialogRemoved::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateDialogRemoved(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateDialogRemoved>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateMessageCallback::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateMessageCallback(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateMessageCallback>();
    result->callback = parseJsonAndGetCallback(data);
    result->message = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMessage, data, "message");
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateMessageCreated::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateMessageCreated(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateMessageCreated>();
    result->message = parseJsonAndGetMessage(data);
    result->user_locale = data.get<std::string>("user_locale", "");
    return result;
}

UpdateMessageEdited::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateMessageEdited(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateMessageEdited>();
    result->message = parseJsonAndGetMessage(data);
    return result;
}

UpdateMessageRemoved::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateMessageRemoved(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateMessageRemoved>();
    result->message_id = data.get<std::string>("message_id", "");
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user_id = data.get<std::int64_t>("user_id", 0);
    return result;
}

UpdateUserAddedToChat::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateUserAddedToChat(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateUserAddedToChat>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->inviter_id = data.get<std::int64_t>("inviter_id", 0);
    result->is_channel = data.get<bool>("is_channel", false);
    return result;
}

UpdateUserRemovedFromChat::Ptr BotTypeParserUpdates::parseJsonAndGetUpdateUserRemovedFromChat(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UpdateUserRemovedFromChat>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->user = parseJsonAndGetUser(data);
    result->admin_id = data.get<std::int64_t>("admin_id", 0);
    result->is_channel = data.get<bool>("is_channel", false);
    return result;
}

User::Ptr BotTypeParserUpdates::parseJsonAndGetUser(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<User>();
    result->user_id = data.get<std::int64_t>("user_id", 0);
    result->first_name = data.get<std::string>("first_name", "");
    result->last_name = data.get<std::string>("last_name", "");
    result->username = data.get<std::string>("username", "");
    result->is_bot = data.get<bool>("is_bot", false);
    result->last_activity_time = data.get<std::int64_t>("last_activity_time", 0);
    result->name = data.get<std::string>("name", "");
    return result;
}

std::string BotTypeParserUpdates::parseUser(const User::Ptr& object)
{
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    appendToJson(result, "user_id", object->user_id);
    appendToJson(result, "first_name", object->first_name);
    appendToJson(result, "last_name", object->last_name);
    appendToJson(result, "username", object->username);
    appendToJson(result, "is_bot", object->is_bot);
    appendToJson(result, "last_activity_time", object->last_activity_time);
    appendToJson(result, "name", object->name);
    removeLastComma(result);
    result += '}';
    return result;
}

Message::Ptr BotTypeParserUpdates::parseJsonAndGetMessage(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Message>();
    result->sender = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetUser, data, "sender");
    result->recipient = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetRecipient, data, "recipient");
    result->timestamp = data.get<std::int64_t>("timestamp", 0);
    result->link = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetLinkedMessage, data, "link");
    result->body = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMessageBody, data, "body");
    result->stat = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMessageStat, data, "stat");
    result->url = data.get<std::string>("url", "");
    return result;
}

Callback::Ptr BotTypeParserUpdates::parseJsonAndGetCallback(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Callback>();
    result->timestamp = data.get<std::int64_t>("timestamp", 0);
    result->callback_id = data.get<std::string>("callback_id", "");
    result->payload = data.get<std::string>("payload", "");
    result->user = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetUser, data, "user");
    return result;
}

Recipient::Ptr BotTypeParserUpdates::parseJsonAndGetRecipient(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Recipient>();
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->chat_type = data.get<std::string>("chat_type", "");
    result->user_id = data.get<std::int64_t>("user_id", 0);
    return result;
}

MessageStat::Ptr BotTypeParserUpdates::parseJsonAndGetMessageStat(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<MessageStat>();
    result->views = data.get<std::int64_t>("views", 0);
    return result;
}

// --- Attachment payload types ---

AttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<AttachmentPayload>();
    result->url = data.get<std::string>("url", "");
    return result;
}

PhotoAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetPhotoAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<PhotoAttachmentPayload>();
    result->photo_id = data.get<std::int64_t>("photo_id", 0);
    result->token = data.get<std::string>("token", "");
    result->url = data.get<std::string>("url", "");
    return result;
}

MediaAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetMediaAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<MediaAttachmentPayload>();
    result->url = data.get<std::string>("url", "");
    result->token = data.get<std::string>("token", "");
    return result;
}

FileAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetFileAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<FileAttachmentPayload>();
    result->url = data.get<std::string>("url", "");
    result->token = data.get<std::string>("token", "");
    return result;
}

ContactAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetContactAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<ContactAttachmentPayload>();
    result->vcf_info = data.get<std::string>("vcf_info", "");
    result->hash = data.get<std::string>("hash", "");
    result->max_info = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetUser, data, "max_info");
    return result;
}

StickerAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetStickerAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<StickerAttachmentPayload>();
    result->url = data.get<std::string>("url", "");
    result->code = data.get<std::string>("code", "");
    return result;
}

ShareAttachmentPayload::Ptr BotTypeParserUpdates::parseJsonAndGetShareAttachmentPayload(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<ShareAttachmentPayload>();
    result->url = data.get<std::string>("url", "");
    result->token = data.get<std::string>("token", "");
    return result;
}

VideoThumbnail::Ptr BotTypeParserUpdates::parseJsonAndGetVideoThumbnail(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<VideoThumbnail>();
    result->url = data.get<std::string>("url", "");
    return result;
}

// --- Attachment types ---

PhotoAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetPhotoAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<PhotoAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetPhotoAttachmentPayload, data, "payload");
    return result;
}

VideoAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetVideoAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<VideoAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMediaAttachmentPayload, data, "payload");
    result->thumbnail = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetVideoThumbnail, data, "thumbnail");
    result->width = data.get<std::int64_t>("width", 0);
    result->height = data.get<std::int64_t>("height", 0);
    result->duration = data.get<std::int64_t>("duration", 0);
    return result;
}

AudioAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetAudioAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<AudioAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMediaAttachmentPayload, data, "payload");
    result->transcription = data.get<std::string>("transcription", "");
    return result;
}

FileAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetFileAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<FileAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetFileAttachmentPayload, data, "payload");
    result->filename = data.get<std::string>("filename", "");
    result->size = data.get<std::int64_t>("size", 0);
    return result;
}

StickerAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetStickerAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<StickerAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetStickerAttachmentPayload, data, "payload");
    result->width = data.get<std::int64_t>("width", 0);
    result->height = data.get<std::int64_t>("height", 0);
    return result;
}

ContactAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetContactAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<ContactAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetContactAttachmentPayload, data, "payload");
    return result;
}

ShareAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetShareAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<ShareAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetShareAttachmentPayload, data, "payload");
    result->title = data.get<std::string>("title", "");
    result->description = data.get<std::string>("description", "");
    result->image_url = data.get<std::string>("image_url", "");
    return result;
}

LocationAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetLocationAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<LocationAttachment>();
    result->latitude = data.get<double>("latitude", 0.0);
    result->longitude = data.get<double>("longitude", 0.0);
    return result;
}

// --- Button types ---

CallbackButton::Ptr BotTypeParserUpdates::parseJsonAndGetCallbackButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<CallbackButton>();
    result->payload = data.get<std::string>("payload", "");
    return result;
}

LinkButton::Ptr BotTypeParserUpdates::parseJsonAndGetLinkButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<LinkButton>();
    result->url = data.get<std::string>("url", "");
    return result;
}

RequestGeoLocationButton::Ptr BotTypeParserUpdates::parseJsonAndGetRequestGeoLocationButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<RequestGeoLocationButton>();
    result->quick = data.get<bool>("quick", false);
    return result;
}

RequestContactButton::Ptr BotTypeParserUpdates::parseJsonAndGetRequestContactButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<RequestContactButton>();
    return result;
}

OpenAppButton::Ptr BotTypeParserUpdates::parseJsonAndGetOpenAppButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<OpenAppButton>();
    result->web_app = data.get<std::string>("web_app", "");
    result->contact_id = data.get<std::int64_t>("contact_id", 0);
    result->payload = data.get<std::string>("payload", "");
    return result;
}

MessageButton::Ptr BotTypeParserUpdates::parseJsonAndGetMessageButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<MessageButton>();
    return result;
}

ClipboardButton::Ptr BotTypeParserUpdates::parseJsonAndGetClipboardButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<ClipboardButton>();
    result->payload = data.get<std::string>("payload", "");
    return result;
}

Button::Ptr BotTypeParserUpdates::parseJsonAndGetButton(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Button>();
    result->type = data.get<std::string>("type", "");
    result->text = data.get<std::string>("text", "");
    if (result->type == "callback")
        result->_data = parseJsonAndGetCallbackButton(data);
    else if (result->type == "link")
        result->_data = parseJsonAndGetLinkButton(data);
    else if (result->type == "request_geo_location")
        result->_data = parseJsonAndGetRequestGeoLocationButton(data);
    else if (result->type == "request_contact")
        result->_data = parseJsonAndGetRequestContactButton(data);
    else if (result->type == "open_app")
        result->_data = parseJsonAndGetOpenAppButton(data);
    else if (result->type == "message")
        result->_data = parseJsonAndGetMessageButton(data);
    else if (result->type == "clipboard")
        result->_data = parseJsonAndGetClipboardButton(data);
    return result;
}

Keyboard::Ptr BotTypeParserUpdates::parseJsonAndGetKeyboard(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Keyboard>();
    result->buttons = parseJsonAndGet2DArray<Button>(&BotTypeParserUpdates::parseJsonAndGetButton, data, "buttons");
    return result;
}

InlineKeyboardAttachment::Ptr BotTypeParserUpdates::parseJsonAndGetInlineKeyboardAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<InlineKeyboardAttachment>();
    result->payload = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetKeyboard, data, "payload");
    return result;
}

Attachment::Ptr BotTypeParserUpdates::parseJsonAndGetAttachment(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<Attachment>();
    result->type = data.get<std::string>("type", "");
    if (result->type == "image")
        result->_data = parseJsonAndGetPhotoAttachment(data);
    else if (result->type == "video")
        result->_data = parseJsonAndGetVideoAttachment(data);
    else if (result->type == "audio")
        result->_data = parseJsonAndGetAudioAttachment(data);
    else if (result->type == "file")
        result->_data = parseJsonAndGetFileAttachment(data);
    else if (result->type == "sticker")
        result->_data = parseJsonAndGetStickerAttachment(data);
    else if (result->type == "contact")
        result->_data = parseJsonAndGetContactAttachment(data);
    else if (result->type == "inline_keyboard")
        result->_data = parseJsonAndGetInlineKeyboardAttachment(data);
    else if (result->type == "share")
        result->_data = parseJsonAndGetShareAttachment(data);
    else if (result->type == "location")
        result->_data = parseJsonAndGetLocationAttachment(data);
    return result;
}

// --- Markup types ---

LinkMarkup::Ptr BotTypeParserUpdates::parseJsonAndGetLinkMarkup(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<LinkMarkup>();
    result->url = data.get<std::string>("url", "");
    return result;
}

UserMentionMarkup::Ptr BotTypeParserUpdates::parseJsonAndGetUserMentionMarkup(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<UserMentionMarkup>();
    result->user_link = data.get<std::string>("user_link", "");
    result->user_id = data.get<std::int64_t>("user_id", 0);
    return result;
}

MarkupElement::Ptr BotTypeParserUpdates::parseJsonAndGetMarkupElement(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<MarkupElement>();
    result->type = data.get<std::string>("type", "");
    result->from = data.get<std::int32_t>("from", 0);
    result->length = data.get<std::int32_t>("length", 0);
	if (result->type == "link")
        result->_data = parseJsonAndGetLinkMarkup(data);
    else if (result->type == "user_mention")
        result->_data = parseJsonAndGetUserMentionMarkup(data);
    return result;
}

MessageBody::Ptr BotTypeParserUpdates::parseJsonAndGetMessageBody(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<MessageBody>();
    result->mid = data.get<std::string>("mid", "");
    result->seq = data.get<std::int64_t>("seq", 0);
    result->text = data.get<std::string>("text", "");
    result->attachments = parseJsonAndGetArray<Attachment>(&BotTypeParserUpdates::parseJsonAndGetAttachment, data, "attachments");
    result->markup = parseJsonAndGetArray<MarkupElement>(&BotTypeParserUpdates::parseJsonAndGetMarkupElement, data, "markup");
    return result;
}

LinkedMessage::Ptr BotTypeParserUpdates::parseJsonAndGetLinkedMessage(const boost::property_tree::ptree& data)
{
    auto result = std::make_shared<LinkedMessage>();
    result->type = data.get<std::string>("type", "");
    result->sender = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetUser, data, "sender");
    result->chat_id = data.get<std::int64_t>("chat_id", 0);
    result->message = tryParseJson(&BotTypeParserUpdates::parseJsonAndGetMessageBody, data, "message");
    return result;
}

}
