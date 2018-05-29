/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2016 Konstantin Kukin
 * Copyright (c) 2018 JellyBrick
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_INPUTMEDIA_H
#define TGBOT_INPUTMEDIA_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents the content of a media message to be sent. 
 * 
 * @ingroup types
 */
class InputMedia {
public:
	typedef std::shared_ptr<InputMedia> Ptr;

    enum class TYPE : uint8_t {
        PHOTO,
        VIDEO
    };

    /**
     * @brief Type of the result, It should be one of TYPE::PHOTO/TYPE::VIDEO
     */
    TYPE type;

    /**
     * @brief File to send. Pass a file_id to send a file that exists on the Telegram servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or pass "attach://<file_attach_name>" to upload a new one using multipart/form-data under <file_attach_name> name.
     */
    std::string media;

    /**
     * @brief Optional. Caption of the photo to be sent, 0-200 characters
     */
    std::string caption;

    /**
     * @brief Optional. Send Markdown or HTML, if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in the media caption.
     */
    std::string parseMode;
    
    /**
     * @brief Optional. Video width
     */
    int32_t width = 0;

    /**
     * @brief Optional. Video height
     */
    int32_t height = 0;

    /**
     * @brief Optional. Video duration
     */
    int32_t duration = 0;

    /**
     * @brief Optional. Pass True, if the uploaded video is suitable for streaming
     */
    bool supportsStreaming = false;
};
}

#endif //TGBOT_INPUTMEDIA_H
