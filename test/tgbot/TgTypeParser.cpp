#include <memory>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "tgbot/TgTypeParser.h"
#include "tgbot/types/InputSticker.h"

using namespace std;
using namespace TgBot;

BOOST_AUTO_TEST_SUITE(tTgTypeParser)

// Regression tests for https://github.com/reo7sp/tgbot-cpp/issues/346 —
// string arrays were emitted as `[a,b]` (unquoted identifiers) instead of
// `["a","b"]`, producing invalid JSON and breaking sticker creation.

BOOST_AUTO_TEST_CASE(parseInputStickerEmojiListIsJsonArray) {
    TgTypeParser parser;
    auto sticker = make_shared<InputSticker>();
    sticker->sticker = "file_id_abc";
    sticker->format = "static";
    sticker->emojiList = {"smile", "heart"};

    const string json = parser.parseInputSticker(sticker);

    BOOST_CHECK(json.find(R"("emoji_list":["smile","heart"])") != string::npos);
    // The pre-fix output emitted the array as `[smile,heart]` — assert no regression.
    BOOST_CHECK(json.find("[smile,heart]") == string::npos);
}

BOOST_AUTO_TEST_CASE(parseInputStickerEscapesJsonSpecialsInEmoji) {
    TgTypeParser parser;
    auto sticker = make_shared<InputSticker>();
    sticker->sticker = "id";
    sticker->format = "static";
    sticker->emojiList = {R"(a"b)", R"(c\d)"};

    const string json = parser.parseInputSticker(sticker);

    BOOST_CHECK(json.find(R"("a\"b")") != string::npos);
    BOOST_CHECK(json.find(R"("c\\d")") != string::npos);
}

BOOST_AUTO_TEST_CASE(parseInputStickerOmitsEmptyKeywords) {
    // Empty arrays should not appear in the output at all, matching the
    // behaviour of the previous `appendToJson(... parseArray(...))` pattern.
    TgTypeParser parser;
    auto sticker = make_shared<InputSticker>();
    sticker->sticker = "id";
    sticker->format = "static";
    sticker->emojiList = {"a"};
    // keywords is default-constructed empty

    const string json = parser.parseInputSticker(sticker);

    BOOST_CHECK(json.find("keywords") == string::npos);
}

BOOST_AUTO_TEST_SUITE_END()
