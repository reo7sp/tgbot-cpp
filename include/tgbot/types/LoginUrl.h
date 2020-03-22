#ifndef TGBOT_CPP_LOGINURL_H
#define TGBOT_CPP_LOGINURL_H

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

    /**
     * @brief This object represents a Poll.
     *
     * @ingroup types
     */
    class LoginUrl{
    public:
        typedef std::shared_ptr<LoginUrl> Ptr;

        /**
         * @brief UAn HTTP URL to be opened with user authorization data added to the query string when the button is pressed..
         */
        std::string url;

        /**
         * @brief Optional. New text of the button in forwarded messages.
         */
        std::string forward_text;

        /**
         * @brief Optional. Username of a bot, which will be used for user authorization.
         */
        std::string bot_username;

        /**
         * @brief Optional. Pass True to request the permission for your bot to send messages to the user.
         */
        bool request_write_access;
    };

}

#endif //TGBOT_CPP_LOGINURL_H
