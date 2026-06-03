#ifndef MAXBOT_CPP_INPUTFILE_H
#define MAXBOT_CPP_INPUTFILE_H

#include "maxbot/export.h"

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief This object represents the contents of a file to be uploaded.
 *
 * @ingroup types
 */
class MAXBOT_API InputFile {

public:
    typedef std::shared_ptr<InputFile> Ptr;

    /**
     * @brief Contents of a file.
     */
    std::string data;

    /**
     * @brief Mime type of a file.
     */
    std::string mimeType;

    /**
     * @brief File name.
     */
    std::string fileName;

    /**
     * @brief Creates new InputFile::Ptr from an existing file.
     */
    static InputFile::Ptr fromFile(const std::string& filePath, const std::string& mimeType);
};

}

#endif //MAXBOT_CPP_INPUTFILE_H
