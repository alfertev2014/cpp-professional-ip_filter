cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(
        /W4
    )
else()
    add_compile_options(
        -Wall -Wextra -Wno-unused-parameter -pedantic
    )
endif()

option(WITH_TEST "Whether to build tests" ON)

configure_file(version.h.in version.h)

add_library(ip_filter_lib ip_filter.cpp)

add_executable(ip_filter main.cpp)
target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(ip_filter PRIVATE ip_filter_lib)

if(WITH_TEST)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
        ip_filter_test
        test.cpp
    )
    target_link_libraries(
        ip_filter_test
        ip_filter_lib
        gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(ip_filter_test)

endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)