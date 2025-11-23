#
# IDE support for headers
#

set(MF_HEADERS_DIR "${CMAKE_CURRENT_LIST_DIR}/../include")
#set(MF_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../src")

file(GLOB MF_HEADERS "${MF_HEADERS_DIR}/jhoyt/media-framework/*.hpp")
#file(GLOB MF_DETAIL_HEADERS "${ASL_SOURCE_DIR}/detail/*.hpp")

set(MF_ALL_HEADERS ${MF_HEADERS} ${MF_DETAIL_HEADERS})

source_group("Header Files\\media-framework" FILES ${MF_HEADERS})
#source_group("Header Files\\media-framework\\details" FILES ${MF_DETAIL_HEADERS})
