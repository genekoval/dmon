#include "pidfile.h"

#include <fstream>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {
    /**
     * Permissions to apply to the pidfile.
     */
    constexpr auto permissions =
        fs::perms::owner_read |
        fs::perms::owner_write |
        fs::perms::group_read |
        fs::perms::others_read;
}

namespace dmon {
    auto make_pidfile(const fs::path& pidfile) -> void {
        {
            auto file = std::ofstream(pidfile);
            file.imbue(std::locale::classic());
            file << getpid() << std::endl;
        }

        fs::permissions(pidfile, permissions);
    }
}
