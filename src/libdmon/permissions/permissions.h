#pragma once

#include <ext/unix.h>

namespace dmon {
    auto drop_groups() -> void;

    auto set_group(const ext::group& group) -> void;

    auto set_groups_for(const ext::user& user) -> void;

    auto set_user(const ext::user& user) -> void;
}
