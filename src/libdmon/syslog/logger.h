#pragma once

#include <timber/timber>

namespace dmon {
    auto syslog_logger(const timber::log& log) noexcept -> void;
}
