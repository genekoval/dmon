#pragma once

#include <filesystem>

namespace dmon {
    struct options {
        std::string identifier;
        std::filesystem::perms mask = std::filesystem::perms::none;
        std::filesystem::path working_directory = "/";
    };

    /**
     * Forks the current process and creates a daemon.
     *
     * @return true if the current process is a daemon; false otherwise
     */
    auto daemonize(const options& opts) -> bool;
}
