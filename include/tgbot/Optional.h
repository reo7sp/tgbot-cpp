#ifndef TGBOT_OPTIONAL_H
#define TGBOT_OPTIONAL_H

#include <boost/optional.hpp>

namespace TgBot {

template<typename T>
  using Optional = boost::optional<T>;

// use for: OptionalPtr<std::shared/unique_ptr<TYPE>>
// for pointers, we assume optional value == nullptr (or not owned, etc)
template<typename T>
  using OptionalPtr = T;

template<typename T>
  using Required = T;

}

#endif //TGBOT_OPTIONAL_H
