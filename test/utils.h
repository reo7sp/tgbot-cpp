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

#ifndef TGBOT_UTILS_H
#define TGBOT_UTILS_H

#include <string>

#include <boost/lexical_cast.hpp>

std::string diff(const std::string& test, const std::string& expected);

template<typename T>
std::string diff(const T& test, const T& expected, std::string (*toStringFunc)(const typename T::value_type&)) {
    std::string result;
    result += "\n*** BEGIN ***   Count: t=";
    result += boost::lexical_cast<std::string>(test.size());
    result += " e=";
    result += boost::lexical_cast<std::string>(expected.size());
    result += '\n';

    typename T::const_iterator iter1 = test.begin();
    typename T::const_iterator end1 = test.end();
    typename T::const_iterator iter2 = expected.begin();
    typename T::const_iterator end2 = expected.end();
    bool r1, r2;
    std::string s1, s2;
    size_t i = 0;
    do {
        r1 = iter1 != end1;
        r2 = iter2 != end2;
        if (r1) {
            s1 = toStringFunc(*iter1++);
        }
        if (r2) {
            s2 = toStringFunc(*iter2++);
        }
        if (r1 && r2 && s1 == s2) {
            result += boost::lexical_cast<std::string>(i);
            result += " [=] ";
            result += s1;
            result += "\n";
        } else {
            if (r1) {
                result += boost::lexical_cast<std::string>(i);
                result += " [t] ";
                result += s1;
                result += "\n";
            }
            if (r2) {
                result += boost::lexical_cast<std::string>(i);
                result += " [e] ";
                result += s2;
                result += "\n";
            }
        }
        ++i;
    } while (r1 || r2);

    result += "*** END ***\n";
    return result;
}

#endif //TGBOT_UTILS_H
