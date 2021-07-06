#pragma once

#include <string>

namespace dmon {
    auto syslog(const std::string& identifier) -> void;
}
