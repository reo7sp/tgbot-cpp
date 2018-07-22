/*
 *
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

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <tgbot/tools/StringTools.h>

#include "utils.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(tStringTools)

BOOST_AUTO_TEST_CASE(startsWith) {
    BOOST_CHECK(StringTools::startsWith("abc123", "abc"));
    BOOST_CHECK(!StringTools::startsWith("abc123", "aac"));
    BOOST_CHECK(!StringTools::startsWith("abc123", "Xabc"));
    BOOST_CHECK(!StringTools::startsWith("abc123", "abcX"));
    BOOST_CHECK(!StringTools::startsWith("abc", "abc123"));
}

BOOST_AUTO_TEST_CASE(endsWith) {
    BOOST_CHECK(StringTools::endsWith("abc123", "123"));
    BOOST_CHECK(!StringTools::endsWith("abc123", "113"));
    BOOST_CHECK(!StringTools::endsWith("abc123", "X123"));
    BOOST_CHECK(!StringTools::endsWith("abc123", "123X"));
    BOOST_CHECK(!StringTools::endsWith("123", "abc123"));
}

BOOST_AUTO_TEST_CASE(split) {
    BOOST_CHECK(StringTools::split("123 456 789", ' ') == vector<string>({"123", "456", "789"}));
    BOOST_CHECK(StringTools::split("aaa", ' ') == vector<string>({"aaa"}));
}

BOOST_AUTO_TEST_CASE(urlEncode) {
    string t = StringTools::urlEncode("`1234567890-qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>? ");
    string e = "%601234567890-qwertyuiop%5B%5D%5Casdfghjkl%3B%27zxcvbnm%2C.%2F~%21%40%23%24%25%5E%26%2A%28%29_%2BQWERTYUIOP%7B%7D%7CASDFGHJKL:ZXCVBNM%3C%3E%3F%20";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(urlDecode) {
    string t = StringTools::urlDecode("%601234567890-qwertyuiop%5b%5d%5casdfghjkl%3b%27zxcvbnm%2c.%2f~%21%40%23%24%25%5e%26%2a%28%29_%2bQWERTYUIOP%7b%7d%7cASDFGHJKL%3aZXCVBNM%3c%3e%3f%20");
    string e = "`1234567890-qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>? ";
    BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_SUITE_END()
