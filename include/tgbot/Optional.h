#ifndef TGBOT_OPTIONAL_H
#define TGBOT_OPTIONAL_H

#include <boost/optional.hpp>

namespace TgBot {

// Optional via boost::optional
template<typename T>
    using Optional = boost::optional<T>;

// Optional is nullptr (for std::shared/unique_ptr<> etc)
template<typename T>
    using OptionalNullPtr = T;

template<typename T>
    using Required = T;

}

#endif //TGBOT_OPTIONAL_H
