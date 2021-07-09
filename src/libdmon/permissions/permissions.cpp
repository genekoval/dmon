#include "permissions.h"

#include <ext/except.h>
#include <fmt/format.h>
#include <grp.h>
#include <unistd.h>

namespace dmon {
    auto drop_groups() -> void {
        setgroups(0, nullptr);
    }

    auto set_group(const ext::group& group) -> void {
        const auto gid = group.gid();

        if (setgid(gid) == -1) {
            throw ext::system_error(fmt::format(
                "could not set group ID to '{}'",
                gid
            ));
        }
    }

    auto set_groups_for(const ext::user& user) -> void {
        constexpr auto initial_size = 8;

        auto groups = std::unique_ptr<gid_t[]>(new gid_t[initial_size]);
        auto ngroups = initial_size;

        auto ret = getgrouplist(
            user.name().data(),
            user.gid(),
            groups.get(),
            &ngroups
        );

        if (ret == -1) {
            groups = std::unique_ptr<gid_t[]>(new gid_t[ngroups]);

            getgrouplist(
                user.name().data(),
                user.gid(),
                groups.get(),
                &ngroups
            );
        }

        if (setgroups(ngroups, groups.get()) == -1) {
            throw ext::system_error(fmt::format(
                "could not set groups for '{}'", user.name()
            ));
        }
    }

    auto set_user(const ext::user& user) -> void {
        const auto uid = user.uid();

        if (setuid(uid) == -1) {
            throw ext::system_error(fmt::format(
                "could not set user ID to '{}'",
                uid
            ));
        }
    }
}
