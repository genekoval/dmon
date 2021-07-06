#include "syslog/syslog.h"

#include <dmon/dmon.h>

#include <ext/except.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace dmon {
    auto daemonize(const options& opts) -> bool {
        // Fork off of the parent process
        auto pid = fork();
        if (pid < 0) {
            throw ext::system_error(
                "Failed to fork off of the parent process"
            );
        }
        if (pid > 0) return false;

        // The child process becomes the session leader
        if (setsid() < 0) {
            throw ext::system_error(
                "Failed to create session and set process group ID"
            );
        }

        // Fork off for the second time
        pid = fork();
        if (pid < 0) {
            throw ext::system_error(
                "Failed to fork off for the second time"
            );
        }
        if (pid > 0) return false;

        umask(static_cast<mode_t>(opts.mask));

        fs::current_path(opts.working_directory);

        // Close all open file descriptors
        for (auto fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd) {
            close(fd);
        }

        // Redirect all logging to syslog
        syslog(opts.identifier);

        return true;
    }
}
