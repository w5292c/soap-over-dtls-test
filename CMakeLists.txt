cmake_minimum_required ( VERSION 2.6 )

project ( soaps C )

set ( CMAKE_C_FLAGS "-Wall -Werror -Wextra -Wpedantic -std=gnu11" )

add_subdirectory ( src )

set ( CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE 1 )

set ( CPACK_PACKAGE_VENDOR "w5292c" )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Playing with minimal SoAP over DTLS implementation" )
set ( CPACK_PACKAGE_VERSION "0.0.1" )
set ( CPACK_PACKAGE_NAME "soaps" )
set ( CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexander Chumakov" )
set ( CPACK_GENERATOR "DEB" )
set ( CPACK_DEBIAN_PACKAGE_DEPENDS "" )

include ( CPack )
