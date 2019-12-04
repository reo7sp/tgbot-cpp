#ifndef TGBOT_HTTPPARAMETER_H
#define TGBOT_HTTPPARAMETER_H

#include <string>
#include <utility>
#include <vector>
#include <functional>

#include <boost/lexical_cast.hpp>

namespace TgBot {

/**
 * @brief This class represents argument in POST http requests.
 *
 * @ingroup net
 */
class HttpReqArg {

public:
    template<typename T>
    HttpReqArg(std::string name, const T& value, bool isFile = false, std::string mimeType = "text/plain", std::string fileName = "") :
            name(std::move(name)), value(boost::lexical_cast<std::string>(value)), isFile(isFile), mimeType(std::move(mimeType)), fileName(std::move(fileName))
    {
    }

    /**
     * @brief Name of an argument.
     */
    std::string name;

    /**
     * @brief Value of an argument.
     */
    std::string value;

    /**
     * @brief Should be true if an argument value hold some file contents
     */
    bool isFile = false;

    /**
     * @brief Mime type of an argument value. This field makes sense only if isFile is true.
     */
    std::string mimeType = "text/plain";

    /**
     * @brief Should be set if an argument value hold some file contents
     */
    std::string fileName;
};

}


#endif //TGBOT_HTTPPARAMETER_H
