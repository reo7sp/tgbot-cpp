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
	if (!in) {
		throw system_error(errno, system_category());
	}
	ostringstream contents;
	contents << in.rdbuf();
	in.close();
	return contents.str();
}

bool write(const string& content, const string& filePath) {
	ofstream out(filePath, ios::out | ios::binary);
	if (!out) {
		return false;
	}
	out << content;
	out.close();
	return true;
}

};
