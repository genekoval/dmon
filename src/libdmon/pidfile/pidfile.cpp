#include "pidfile.h"

#include <cmath>
#include <ext/except.h>
#include <fmt/format.h>
#include <fstream>
#include <limits>
#include <signal.h>
#include <sstream>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {
    /**
     * Permissions to apply to the directory containing the pidfile.
     */
    constexpr auto directory_permissions =
        fs::perms::owner_all |
        fs::perms::group_read |
        fs::perms::group_exec |
        fs::perms::others_read |
        fs::perms::others_exec;

    /**
     * Permissions to apply to the pidfile.
     */
    constexpr auto file_permissions =
        fs::perms::owner_read |
        fs::perms::owner_write |
        fs::perms::group_read |
        fs::perms::others_read;

    /**
     * The maximum number of digits a PID can have.
     */
    constexpr auto pid_max_digits = static_cast<std::size_t>(
        std::log(std::numeric_limits<pid_t>::max()) / std::log(10)
    ) + 1;

    auto read_pidfile(const std::filesystem::path& pidfile) -> pid_t {
        if (!fs::exists(pidfile)) {
            throw std::system_error(
                ENOENT,
                std::generic_category(),
                fmt::format("cannot access pidfile '{}'", pidfile.string())
            );
        }

        // Leave room for a null character at the end.
        auto buffer = std::array<char, pid_max_digits + 1>();
        buffer.fill('\0');

        auto file = std::ifstream(pidfile);
        file.getline(buffer.data(), pid_max_digits);

        const auto pid = std::atoi(buffer.data());
        if (pid == 0) {
            throw std::runtime_error(
                fmt::format(
                    "Failed to parse PID value in pidfile: {}",
                    pidfile.string()
                )
            );
        }

        return pid;
    }
}

namespace dmon {
    auto kill(int pid, int signal) -> void {
        if (::kill(pid, signal) < 0) {
            throw ext::system_error(fmt::format(
                "Failed to send signal ({}) to process with PID ({})",
                signal,
                pid
            ));
        }
    }

    auto kill(const std::filesystem::path& pidfile, int signal) -> void {
        kill(read_pidfile(pidfile), signal);
    }

    auto make_pidfile(const fs::path& pidfile) -> void {
        if (fs::create_directories(pidfile.parent_path())) {
            fs::permissions(pidfile.parent_path(), directory_permissions);
        }

        auto file = std::ofstream(pidfile);
        file << getpid() << std::endl;

        fs::permissions(pidfile, file_permissions);
    }
}
