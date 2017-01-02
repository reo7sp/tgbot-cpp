//
// Created by Konstantin Kukin on 26/12/16.
//

#ifndef TGBOT_INPUTCONTACTMESSAGECONTENT_H
#define TGBOT_INPUTCONTACTMESSAGECONTENT_H

#include <memory>
#include <string>

namespace TgBot {

/**
* Represents the content of a contact message to be sent as the result of an inline query.
* @ingroup types
*/
class InputContactMessageContent : public InputMessageContent {
public:
	typedef std::shared_ptr<InputContactMessageContent> Ptr;

	InputContactMessageContent() :
		InputMessageContent("InputContactMessageContent")
	{}

	/**
	* Contact's phone number
	*/
	std::string phoneNumber;

	/**
	* Contact's first name
	*/
	std::string firstName;

	/**
	* Optional. Contact's last name
	*/
	std::string lastName;

	virtual ~InputContactMessageContent() { }
};
}

#endif //TGBOT_INPUTCONTACTMESSAGECONTENT_H
