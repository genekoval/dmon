target_sources(dmon
    PRIVATE
        dmon.cpp
)

add_subdirectory(environment)
add_subdirectory(permissions)
add_subdirectory(pidfile)
add_subdirectory(syslog)
