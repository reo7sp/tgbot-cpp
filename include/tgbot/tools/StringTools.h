#ifndef TGBOT_CPP_STRINGTOOLS_H
#define TGBOT_CPP_STRINGTOOLS_H

#include "tgbot/export.h"

#include <cstddef>
#include <vector>
#include <string>
#include <sstream>

/**
 * @ingroup tools
 */
namespace StringTools {

/**
 * Checks if first string is starting with second string
 * @param str1 First string
 * @param str2 Second string
 */
TGBOT_API
bool startsWith(const std::string& str1, const std::string& str2);

/**
 * Checks if first string is ending with second string
 * @param str1 First string
 * @param str2 Second string
 */
TGBOT_API
bool endsWith(const std::string& str1, const std::string& str2);

/**
 * Splits string to smaller substrings which have between them a delimiter. Resulting substrings won't have delimiter.
 * @param str Source string
 * @param delimiter Delimiter
 * @param dest Array to which substrings will be saved.
 */
TGBOT_API
void split(const std::string& str, char delimiter, std::vector<std::string>& dest);

/**
 * Generates pseudo random string. It's recommended to call srand before this method.
 * @param length Length of resulting string.
 */
TGBOT_API
std::string generateRandomString(std::size_t length);

/**
 * Performs url encode.
 * @param value Source url string
 * @param additionalLegitChars Optional. String of chars which will be not encoded in source url string.
 * @return Encoded url string
 */
TGBOT_API
std::string urlEncode(const std::string& value, const std::string& additionalLegitChars = "");

/**
 * Performs url decode.
 * @param value Encoded url string
 * @return Decoded url string
 */
TGBOT_API
std::string urlDecode(const std::string& value);

/**
 * Splits string to smaller substrings which have between them a delimiter. Resulting substrings won't have delimiter.
 * @param str Source string
 * @param delimiter Delimiter
 * @return Array of substrings
 */
inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    split(str, delimiter, result);
    return result;
}

}

#endif //TGBOT_CPP_STRINGTOOLS_H
