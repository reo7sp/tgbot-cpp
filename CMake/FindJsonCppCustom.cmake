# FindJsonCpp.cmake

# Try to locate the jsoncpp package using pkg-config
find_package(PkgConfig QUIET)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(JSONCPP_PKG jsoncpp)

    if (JSONCPP_PKG_FOUND)
        # Create the jsoncpp imported target
        if (NOT TARGET JsonCpp::JsonCpp)
            add_library(JsonCpp::JsonCpp SHARED IMPORTED)
            set_target_properties(JsonCpp::JsonCpp PROPERTIES
                IMPORTED_LOCATION "${JSONCPP_PKG_LIBRARY_DIRS}/libjsoncpp.so"
                INTERFACE_INCLUDE_DIRECTORIES "${JSONCPP_PKG_INCLUDE_DIRS}"
            )

            # Optionally, set any additional properties, such as dependencies or version
            message(STATUS "Found JsonCpp: ${JSONCPP_PKG_LIBRARY_DIRS}/libjsoncpp.so")
        endif()

    else()
        message(FATAL_ERROR "Pkg-config found, but JsonCpp not found via pkg-config.")
    endif()
else()
    message(FATAL_ERROR "Pkg-config not found, cannot locate JsonCpp.")
endif()
