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
}

namespace dmon {
    auto make_pidfile(
        const fs::path& pidfile,
        const ext::user& user,
        const ext::group& group
    ) -> void {
        const auto directory = pidfile.parent_path();

        if (fs::create_directories(directory)) {
            fs::permissions(directory, directory_permissions);
            ext::chown(directory, user, group);
        }

        {
            auto file = std::ofstream(pidfile);
            file << getpid() << std::endl;
        }

        fs::permissions(pidfile, file_permissions);
    }
}
