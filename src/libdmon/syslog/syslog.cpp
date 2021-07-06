#include "logger.h"
#include "syslog.h"

#include <syslog.h>

namespace {
    constexpr auto default_facility = LOG_DAEMON;

    constexpr auto default_options = LOG_PID;
}

namespace dmon {
    auto syslog(const std::string& identifier) -> void {
        openlog(
            identifier.empty() ? nullptr : identifier.c_str(),
            default_options,
            default_facility
        );

        timber::log_handler = &syslog_logger;
    }
}
