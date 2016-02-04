find_package ( PkgConfig REQUIRED )

pkg_check_modules ( GLIB2_0       glib-2.0        REQUIRED )

include_directories ( ${GLIB2_0_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS} )

set ( SRC_TOP "${CMAKE_SOURCE_DIR}/src/" )
set ( TINYDTLS_TOP "${CMAKE_SOURCE_DIR}/external/tinydtls/" )
set ( MICROCOAP_TOP "${CMAKE_SOURCE_DIR}/external/microcoap/" )

set ( SRC_SERVER
  ${SRC_TOP}/server-main.c
)

set ( SRC_CLIENT
  ${SRC_TOP}/client-main.c
)

set ( SRC_COAP
  ${MICROCOAP_TOP}/coap.c
  ${MICROCOAP_TOP}/endpoints.c
)

add_executable ( soaps-server ${SRC_SERVER} ${SRC_COAP} )
target_link_libraries ( soaps-server )

add_executable ( soaps-client ${SRC_CLIENT} ${SRC_COAP} )
target_link_libraries ( soaps-client )

install ( TARGETS soaps-server DESTINATION bin )
