include(FetchContent)

cmake_policy(PUSH)
cmake_policy(SET CMP0150 NEW)

set(FMT_INSTALL ON)

FetchContent_Declare(ext
    GIT_REPOSITORY ../libext.git
    GIT_TAG        76265c1325028676ae3219505bb362a0b28ad1ea # 0.3.0

)

FetchContent_Declare(timber
    GIT_REPOSITORY ../timber.git
    GIT_TAG        9e6fd332fc3dc80a14ad8d5476a268ea867714f0 # 0.4.0
)

FetchContent_MakeAvailable(ext timber)

cmake_policy(POP)
