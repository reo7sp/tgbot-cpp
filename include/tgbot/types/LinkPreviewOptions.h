#ifndef TGBOT_LINKPREVIEWOPTIONS_H
#define TGBOT_LINKPREVIEWOPTIONS_H

#include <memory>
#include <string>
#include <boost/optional.hpp>

namespace TgBot {

/**
 * @brief Describes the options used for link preview generation.
 *
 * @ingroup types
 */
class LinkPreviewOptions {

public:
    typedef std::shared_ptr<LinkPreviewOptions> Ptr;

    /**
     * @brief Optional. True, if the link preview is disabled
     */
    boost::optional<bool> isDisabled;

    /**
     * @brief Optional. URL to use for the link preview.
     *
     * If empty, then the first URL found in the message text will be used
     */
    boost::optional<std::string> url;

    /**
     * @brief Optional. True, if the media in the link preview is supposed to be shrunk; ignored if the URL isn't explicitly specified or media size change isn't supported for the preview
     */
    boost::optional<bool> preferSmallMedia;

    /**
     * @brief Optional. True, if the media in the link preview is supposed to be enlarged; ignored if the URL isn't explicitly specified or media size change isn't supported for the preview
     */
    boost::optional<bool> preferLargeMedia;

    /**
     * @brief Optional. True, if the link preview must be shown above the message text; otherwise, the link preview will be shown below the message text
     */
    boost::optional<bool> showAboveText;
};
}

#endif //TGBOT_LINKPREVIEWOPTIONS_H
