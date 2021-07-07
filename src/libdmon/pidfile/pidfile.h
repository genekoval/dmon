#pragma once

#include <filesystem>

namespace dmon {
    auto kill(const std::filesystem::path& pidfile, int signal) -> void;

    auto make_pidfile(const std::filesystem::path& pidfile) -> void;
}
