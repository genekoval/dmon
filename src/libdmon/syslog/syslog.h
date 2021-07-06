#pragma once

#include <string_view>

namespace dmon {
    auto syslog(std::string_view identifier) -> void;
}
