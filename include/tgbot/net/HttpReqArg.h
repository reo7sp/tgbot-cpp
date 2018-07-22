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

#ifndef TGBOT_HTTPPARAMETER_H
#define TGBOT_HTTPPARAMETER_H

#include <string>
#include <utility>
#include <vector>
#include <functional>

#include <boost/lexical_cast.hpp>

namespace TgBot {

/**
 * @brief This class represents argument in POST http requests.
 * 
 * @ingroup net
 */
class HttpReqArg {

public:
    template<typename T>
    HttpReqArg(std::string name, const T& value, bool isFile = false, std::string mimeType = "text/plain", std::string fileName = "") :
            name(std::move(name)), value(boost::lexical_cast<std::string>(value)), isFile(isFile), mimeType(std::move(mimeType)), fileName(std::move(fileName))
    {
    }

    /**
     * @brief Name of an argument.
     */
    std::string name;

    /**
     * @brief Value of an argument.
     */
    std::string value;

    /**
     * @brief Should be true if an argument value hold some file contents
     */
    bool isFile = false;

    /**
     * @brief Mime type of an argument value. This field makes sense only if isFile is true.
     */
    std::string mimeType = "text/plain";

    /**
     * @brief Should be set if an argument value hold some file contents
     */
    std::string fileName;
};

}


#endif //TGBOT_HTTPPARAMETER_H
