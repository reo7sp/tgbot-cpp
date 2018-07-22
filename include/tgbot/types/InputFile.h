/*
 * Copyright (c) 2015 Oleg Morozenkov
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

#ifndef TGBOT_CPP_INPUTFILE_H
#define TGBOT_CPP_INPUTFILE_H

#include <string>
#include <memory>
#include <utility>

namespace TgBot {

/**
 * @brief This object represents the contents of a file to be uploaded.
 * 
 * @ingroup types
 */
class InputFile {

public:
    typedef std::shared_ptr<InputFile> Ptr;

    /**
     * @brief Contents of a file.
     */
    std::string data;

    /**
     * @brief Mime type of a file.
     */
    std::string mimeType;

    /**
     * @brief File name.
     */
    std::string fileName;

    /**
     * @brief Creates new InputFile::Ptr from an existing file.
     */
    static InputFile::Ptr fromFile(const std::string& filePath, const std::string& mimeType);
};

}

#endif //TGBOT_CPP_INPUTFILE_H
