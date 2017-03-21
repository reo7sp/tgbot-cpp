//
// Created by Oleg Morozenkov on 25.01.17.
//

#include "tgbot/tools/FileTools.h"

#include <fstream>
#include <sstream>

using namespace std;

namespace FileTools {

std::string read(const std::string& filePath) {
	ifstream in(filePath, ios::in | ios::binary);
	if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		return contents.str();
	}
	throw errno;
}

bool write(const std::string& content, const std::string& filePath) {
	ofstream out(filePath, ios::out | ios::binary);
	if (out) {
		out << content;
		out.close();
		return true;
	}
	return false;
}

};
