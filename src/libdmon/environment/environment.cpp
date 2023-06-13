#include "environment.hpp"

#include <ext/except.h>
#include <fmt/format.h>

namespace {
    auto set_env(std::string_view name, std::string_view value) -> void {
        if (setenv(name.data(), value.data(), 1) == -1) {
            throw ext::system_error(fmt::format(
                "Failed to set environment variable {}={}",
                name,
                value
            ));
        }
    }
}

namespace dmon {
    auto set_env(const ext::user& user) -> void {
        ::set_env("USER", user.name());
        ::set_env("HOME", user.home());
        ::set_env("SHELL", user.shell());
    }
}
