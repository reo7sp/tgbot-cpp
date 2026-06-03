#pragma once

#include "maxbot/export.h"
#include "maxbot/types/Updates.h"
#include "maxbot/BotTypeParserBase.h"

namespace MaxBot {

class MAXBOT_API BotTypeParserUpdates : public BotTypeParserBase {

public:
    static Updates::Ptr parseJsonAndGetUpdates(const boost::property_tree::ptree& data);

    static Update::Ptr parseJsonAndGetUpdate(const boost::property_tree::ptree& data);
	static UpdateBotAddedToChat::Ptr parseJsonAndGetUpdateBotAddedToChat(const boost::property_tree::ptree& data);
	static UpdateBotStarted::Ptr parseJsonAndGetUpdateBotStarted(const boost::property_tree::ptree& data);
	static UpdateBotStopped::Ptr parseJsonAndGetUpdateBotStopped(const boost::property_tree::ptree& data);
	static UpdateBotRemovedFromChat::Ptr parseJsonAndGetUpdateBotRemovedFromChat(const boost::property_tree::ptree& data);
	static UpdateChatTitleChanged::Ptr parseJsonAndGetUpdateChatTitleChanged(const boost::property_tree::ptree& data);
	static UpdateDialogCleared::Ptr parseJsonAndGetUpdateDialogCleared(const boost::property_tree::ptree& data);
	static UpdateDialogMuted::Ptr parseJsonAndGetUpdateDialogMuted(const boost::property_tree::ptree& data);
	static UpdateDialogUnmuted::Ptr parseJsonAndGetUpdateDialogUnmuted(const boost::property_tree::ptree& data);
	static UpdateDialogRemoved::Ptr parseJsonAndGetUpdateDialogRemoved(const boost::property_tree::ptree& data);
	static UpdateMessageCallback::Ptr parseJsonAndGetUpdateMessageCallback(const boost::property_tree::ptree& data);
	static UpdateMessageCreated::Ptr parseJsonAndGetUpdateMessageCreated(const boost::property_tree::ptree& data);
	static UpdateMessageEdited::Ptr parseJsonAndGetUpdateMessageEdited(const boost::property_tree::ptree& data);
	static UpdateMessageRemoved::Ptr parseJsonAndGetUpdateMessageRemoved(const boost::property_tree::ptree& data);
	static UpdateUserAddedToChat::Ptr parseJsonAndGetUpdateUserAddedToChat(const boost::property_tree::ptree& data);
	static UpdateUserRemovedFromChat::Ptr parseJsonAndGetUpdateUserRemovedFromChat(const boost::property_tree::ptree& data);

	static Message::Ptr parseJsonAndGetMessage(const boost::property_tree::ptree& data);

	static Callback::Ptr parseJsonAndGetCallback(const boost::property_tree::ptree& data);
	static Recipient::Ptr parseJsonAndGetRecipient(const boost::property_tree::ptree& data);
	static MessageStat::Ptr parseJsonAndGetMessageStat(const boost::property_tree::ptree& data);
	static AttachmentPayload::Ptr parseJsonAndGetAttachmentPayload(const boost::property_tree::ptree& data);
	static PhotoAttachmentPayload::Ptr parseJsonAndGetPhotoAttachmentPayload(const boost::property_tree::ptree& data);
	static MediaAttachmentPayload::Ptr parseJsonAndGetMediaAttachmentPayload(const boost::property_tree::ptree& data);
	static FileAttachmentPayload::Ptr parseJsonAndGetFileAttachmentPayload(const boost::property_tree::ptree& data);
	static ContactAttachmentPayload::Ptr parseJsonAndGetContactAttachmentPayload(const boost::property_tree::ptree& data);
	static StickerAttachmentPayload::Ptr parseJsonAndGetStickerAttachmentPayload(const boost::property_tree::ptree& data);
	static ShareAttachmentPayload::Ptr parseJsonAndGetShareAttachmentPayload(const boost::property_tree::ptree& data);
	static VideoThumbnail::Ptr parseJsonAndGetVideoThumbnail(const boost::property_tree::ptree& data);
	static PhotoAttachment::Ptr parseJsonAndGetPhotoAttachment(const boost::property_tree::ptree& data);
	static VideoAttachment::Ptr parseJsonAndGetVideoAttachment(const boost::property_tree::ptree& data);
	static AudioAttachment::Ptr parseJsonAndGetAudioAttachment(const boost::property_tree::ptree& data);
	static FileAttachment::Ptr parseJsonAndGetFileAttachment(const boost::property_tree::ptree& data);
	static StickerAttachment::Ptr parseJsonAndGetStickerAttachment(const boost::property_tree::ptree& data);
	static ContactAttachment::Ptr parseJsonAndGetContactAttachment(const boost::property_tree::ptree& data);
	static ShareAttachment::Ptr parseJsonAndGetShareAttachment(const boost::property_tree::ptree& data);
	static LocationAttachment::Ptr parseJsonAndGetLocationAttachment(const boost::property_tree::ptree& data);
	static CallbackButton::Ptr parseJsonAndGetCallbackButton(const boost::property_tree::ptree& data);
	static LinkButton::Ptr parseJsonAndGetLinkButton(const boost::property_tree::ptree& data);
	static RequestGeoLocationButton::Ptr parseJsonAndGetRequestGeoLocationButton(const boost::property_tree::ptree& data);
	static RequestContactButton::Ptr parseJsonAndGetRequestContactButton(const boost::property_tree::ptree& data);
	static OpenAppButton::Ptr parseJsonAndGetOpenAppButton(const boost::property_tree::ptree& data);
	static MessageButton::Ptr parseJsonAndGetMessageButton(const boost::property_tree::ptree& data);
	static ClipboardButton::Ptr parseJsonAndGetClipboardButton(const boost::property_tree::ptree& data);
	static Button::Ptr parseJsonAndGetButton(const boost::property_tree::ptree& data);
	static Keyboard::Ptr parseJsonAndGetKeyboard(const boost::property_tree::ptree& data);
	static InlineKeyboardAttachment::Ptr parseJsonAndGetInlineKeyboardAttachment(const boost::property_tree::ptree& data);
	static Attachment::Ptr parseJsonAndGetAttachment(const boost::property_tree::ptree& data);
	static LinkMarkup::Ptr parseJsonAndGetLinkMarkup(const boost::property_tree::ptree& data);
	static UserMentionMarkup::Ptr parseJsonAndGetUserMentionMarkup(const boost::property_tree::ptree& data);
	static MarkupElement::Ptr parseJsonAndGetMarkupElement(const boost::property_tree::ptree& data);
	static MessageBody::Ptr parseJsonAndGetMessageBody(const boost::property_tree::ptree& data);
	static LinkedMessage::Ptr parseJsonAndGetLinkedMessage(const boost::property_tree::ptree& data);

    static User::Ptr parseJsonAndGetUser(const boost::property_tree::ptree& data);
    static std::string parseUser(const User::Ptr& object);
};

}
