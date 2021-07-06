#include "logger.h"

#include <array>
#include <syslog.h>

namespace dmon {
    constexpr auto levels = std::array {
        LOG_ERR,
        LOG_WARNING,
        LOG_INFO,
        LOG_DEBUG,
        LOG_DEBUG
    };

    auto get_level(timber::level level) -> int {
        return levels[
            static_cast<std::underlying_type_t<timber::level>>(level)
        ];
    }

    auto syslog_logger(const timber::log& log) noexcept -> void {
        const auto message = log.stream.str();
        syslog(get_level(log.log_level), message.c_str());
    }
}
