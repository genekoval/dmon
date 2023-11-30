#include "syslog.h"
#include "logger.h"

#include <syslog.h>

namespace {
    constexpr auto default_facility = LOG_DAEMON;

    constexpr auto default_options = LOG_PID;
}

namespace dmon {
    auto syslog(std::string_view identifier) -> void {
        openlog(identifier.data(), default_options, default_facility);
        timber::log_handler = &syslog_logger;
    }
}
