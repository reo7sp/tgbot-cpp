#ifndef MAXBOT_FILETOOLS_H
#define MAXBOT_FILETOOLS_H

#include "maxbot/export.h"

#include <string>

/**
 * @ingroup tools
 */
namespace FileTools {

/**
 * Reads whole file to string.
 * @param filePath Path to a file
 * @throws exception of type std::ifstream::failure if reading fails
 * @return string with file contents
 */
MAXBOT_API
std::string read(const std::string& filePath);

/**
 * Save file to disk.
 * @param filePath Path to a file
 * @throws exception of type std::ifstream::failure if writing fails
*/
MAXBOT_API
void write(const std::string& content, const std::string& filePath);

}


#endif //MAXBOT_FILETOOLS_H
