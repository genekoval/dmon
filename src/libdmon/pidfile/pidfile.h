#pragma once

#include <ext/unix.h>

namespace dmon {
    auto make_pidfile(const std::filesystem::path& pidfile) -> void;
}
