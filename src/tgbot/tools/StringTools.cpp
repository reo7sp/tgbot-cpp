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

#include "StringTools.h"

#include <stdlib.h>
#include <iomanip>

using namespace std;

namespace StringTools {

bool startsWith(const string& str1, const string& str2) {
    string::const_iterator it1(str1.begin());
    string::const_iterator end1(str1.end());
    string::const_iterator it2(str2.begin());
    string::const_iterator end2(str2.end());
    while (it1 != end1 && it2 != end2) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

bool endsWith(const string& str1, const string& str2) {
    string::const_iterator it1(str1.end());
    string::const_iterator start1(str1.begin());
    string::const_iterator it2(str2.begin());
    string::const_iterator end2(str2.end());
    while (it1 != start1 && it2 != end2) {
        if (*it1 != *it2) {
            return false;
        }
        --it1;
        ++it2;
    }
    return true;
}

void split(const string& str, char delimiter, vector<string>& dest) {
    istringstream stream(str);
    string s;
    while (getline(stream, s, delimiter)) {
        dest.push_back(s);
    }
}

string generateRandomString(size_t length) {
    static const string chars("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-=[]\\;',./!@#$%^&*()_+{}|:\"<>?`~");
    static const size_t charsLen = chars.length();
    string result;
    for (int i = 0; i < length; ++i) {
        result += chars[rand() % charsLen];
    }
    return result;
}

string urlEncode(const string& value) {
    static const string legitPunctuation = "-_.~!*()'";
    ostringstream result;
    result.fill('0');
    result << hex;
    for (const char& c : value) {
        if (isalnum(c) || legitPunctuation.find(c) != legitPunctuation.npos) {
            result << c;
        } else if (c == ' ') {
            result << '+';
        } else {
            result << '%' << setw(2) << int((unsigned char) c);
        }
    }

    return result.str();
}

}
