//
// Created by Oleg Morozenkov on 25.01.17.
//

#include "tgbot/tools/FileTools.h"

#include <fstream>
#include <sstream>

using namespace std;

namespace FileTools {

string read(const string& filePath) {
    ifstream in(filePath, ios::in | ios::binary);
    in.exceptions(ifstream::failbit | ifstream::badbit);
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return contents.str();
}

void write(const string& content, const string& filePath) {
    ofstream out(filePath, ios::out | ios::binary);
    out.exceptions(ofstream::failbit | ofstream::badbit);
    out << content;
    out.close();
}

};
