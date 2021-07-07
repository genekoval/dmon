#pragma once

#include <filesystem>

namespace dmon {
    struct options {
        std::string_view identifier;
        std::filesystem::path pidfile;
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
