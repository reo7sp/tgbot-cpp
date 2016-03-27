//
// Created by Andrea Giove on 27/03/16.
//

#ifndef TGBOT_INLINEQUERYRESULTMPEG4GIF_H
#define TGBOT_INLINEQUERYRESULTMPEG4GIF_H

namespace TgBot {

/**
 * Represents a link to a video animation (H.264/MPEG-4 AVC video without sound).
 * @ingroup types
 */
class InlineQueryResultMpeg4Gif : public InlineQueryResult {
public:
	static const std::string TYPE = "mpeg4_gif";

	typedef std::shared_ptr<InlineQueryResultMpeg4Gif> Ptr;

	InlineQueryResultMpeg4Gif() : type(TYPE) {};

	/**
	 * A valid URL for the MP4 file.
	 */
	std::string mpeg4Url;

	/**
	 * Optional. Video width.
	 */
	int32_t mpeg4Width;

	/**
	 * Optional. Video height.
	 */
	int32_t mpeg4Height;

	/**
	 * Optional. Caption of the MPEG-4 file to be sent.
	 */
	std::string caption;


};
}

#endif //TGBOT_INLINEQUERYRESULTMPEG4GIF_H
