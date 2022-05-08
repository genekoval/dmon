#pragma once

#include <ext/unix.h>

namespace dmon {
    auto kill(const std::filesystem::path& pidfile, int signal) -> void;

    auto make_pidfile(
        const std::filesystem::path& pidfile,
        const ext::user& user,
        const ext::group& group
    ) -> void;
}
