#include "logger.h"

#include <array>
#include <syslog.h>

namespace dmon {
    constexpr auto levels = std::array {
        LOG_EMERG,
        LOG_ALERT,
        LOG_CRIT,
        LOG_ERR,
        LOG_WARNING,
        LOG_NOTICE,
        LOG_INFO,
        LOG_DEBUG,
        LOG_DEBUG};

    auto get_level(timber::level level) -> int {
        return levels[static_cast<std::underlying_type_t<timber::level>>(level
        )];
    }

    auto syslog_logger(const timber::log& log) noexcept -> void {
        syslog(get_level(log.log_level), "%s", log.message.c_str());
    }
}
