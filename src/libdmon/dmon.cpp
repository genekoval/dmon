#include "environment/environment.hpp"
#include "permissions/permissions.h"
#include "pidfile/pidfile.h"
#include "syslog/syslog.h"

#include <dmon/dmon.h>

#include <ext/except.h>
#include <ext/unix.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {
    constexpr mode_t mask = 0027;
}

namespace dmon {
    auto daemonize(const options& opts) -> bool {
        /*
            Fork from the calling process and create the daemon
        */

        // Fork off of the parent process
        auto pid = fork();
        if (pid < 0) {
            throw ext::system_error("Failed to fork off of the parent process");
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
            throw ext::system_error("Failed to fork off for the second time");
        }
        if (pid > 0) return false;

        /*
            Set up the daemon
        */

        // Close all open file descriptors
        for (auto fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd) { close(fd); }

        syslog(opts.identifier);

        umask(mask);

        const auto wd = opts.working_directory.value_or(opts.user.home());
        fs::current_path(wd == "/dev/null" ? "/" : wd);

        make_pidfile(opts.pidfile);

        // Assign privileges
        if (opts.set_supplementary_groups) set_groups_for(opts.user);
        else drop_groups();

        set_group(opts.group);
        set_user(opts.user);

        set_env(opts.user);

        return true;
    }
}
