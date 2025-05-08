
add_executable(simple_client
    simple_client.cpp
)
find_package(Qt5 REQUIRED COMPONENTS Core Network)

# Link with SDKlib.
target_link_libraries(simple_client PRIVATE MEGA::SDKlib
    Qt5::Core
    Qt5::Network)

# Adjust compilation flags for warnings and errors
target_platform_compile_options(
    TARGET simple_client
    WINDOWS /we4800 # Implicit conversion from 'type' to bool. Possible information loss
    UNIX $<$<CONFIG:Debug>:-ggdb3> -Wall -Wextra -Wconversion
)

if(ENABLE_SDKLIB_WERROR)
    target_platform_compile_options(
        TARGET simple_client
        WINDOWS /WX
        UNIX $<$<CONFIG:Debug>: -Werror>
    )
endif()

# Starting on Xcode 15: https://gitlab.kitware.com/cmake/cmake/-/issues/25297
if(APPLE AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS "15.0")
    target_link_options(simple_client PRIVATE LINKER:-no_warn_duplicate_libraries)
endif()
