#
# Get the library version as defined in `version.hpp` and place it in MF_VERSION.
#
function(extract_mf_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/jhoyt/mf/version.hpp" file_contents)
    string(REGEX MATCH "k_version_major = ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from jhoyt/mf/version.hpp")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "k_version_minor = ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from jhoyt/mf/version.hpp")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "k_version_patch = ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from jhoyt/mf/version.hpp")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(MF_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(MF_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(MF_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(MF_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()
