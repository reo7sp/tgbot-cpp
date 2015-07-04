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

#ifndef TGBOT_CPP_STRINGTOOLS_H
#define TGBOT_CPP_STRINGTOOLS_H

#include <vector>
#include <string>
#include <sstream>

namespace StringTools {

bool startsWith(const std::string& str1, const std::string& str2);
bool endsWith(const std::string& str1, const std::string& str2);
void split(const std::string& str, char delimiter, std::vector<std::string>& dest);
std::string generateRandomString(size_t length);
std::string urlEncode(const std::string& value);

inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    split(str, delimiter, result);
    return result;
}

}

#endif //TGBOT_CPP_STRINGTOOLS_H
