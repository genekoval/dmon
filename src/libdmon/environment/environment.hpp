#pragma once

#include <ext/unix.h>

namespace dmon {
    auto set_env(const ext::user& user) -> void;
}
