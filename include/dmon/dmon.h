#pragma once

#include <ext/unix.h>
#include <filesystem>
#include <optional>

namespace dmon {
    struct options {
        const ext::group& group;
        std::string_view identifier;
        std::filesystem::path pidfile;
        bool set_supplementary_groups = true;
        const ext::user& user;
        std::filesystem::path working_directory = "/";
    };

    /**
     * Forks the current process and creates a daemon.
     *
     * @return true if the current process is a daemon; false otherwise
     */
    auto daemonize(const options& opts) -> bool;
}
