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

#include "utils.h"

#include <sstream>

using namespace std;
using namespace boost;

string diff(const string& test, const string& expected) {
    string result;
    result += "\n*** BEGIN ***\n";

    istringstream ss1(test);
    istringstream ss2(expected);

    string s1, s2;
    bool r1, r2;
    size_t i = 0;
    do {
        r1 = getline(ss1, s1) ? true : false;
        r2 = getline(ss2, s2) ? true : false;
        if (r1 && r2 && s1 == s2) {
            result += lexical_cast<string>(i);
            result += " [=] ";
            result += s1;
            result += "\n";
        } else {
            if (r1) {
                result += lexical_cast<string>(i);
                result += " [t] ";
                result += s1;
                result += "\n";
            }
            if (r2) {
                result += lexical_cast<string>(i);
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
