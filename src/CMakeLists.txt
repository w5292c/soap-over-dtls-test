find_package ( PkgConfig REQUIRED )

pkg_check_modules ( GLIB2_0       glib-2.0        REQUIRED )

include_directories ( ${GLIB2_0_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS} )

set ( SRC_TOP "${CMAKE_SOURCE_DIR}/src/" )

set ( SRC_SERVER
  ${SRC_TOP}/server-main.c
)

set ( SRC_CLIENT
  ${SRC_TOP}/client-main.c
)

add_executable ( soaps-server ${SRC_SERVER} )
target_link_libraries ( soaps-server )

add_executable ( soaps-client ${SRC_CLIENT} )
target_link_libraries ( soaps-client )

install ( TARGETS soaps-server DESTINATION bin )
