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

    /**
     * Sends the specified signal to the process with the PID contained in
     * the specified pidfile.
     *
     * @param pidfile Path to the desired process's pidfile
     * @param sig The signal to send
     */
    auto signal(const std::filesystem::path& pidfile, int sig) -> void;

    /**
     * Sends a termination request to the process with the PID contained in
     * the specified pidfile and removes the pidfile.
     *
     * @param pidfile Path to the desired process's pidfile
     */
    auto stop(const std::filesystem::path& pidfile) -> void;
}
