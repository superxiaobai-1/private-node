#
# Dependencies
#
# find_package(Threads)

#
# Sources
#
set(SOURCES
    # main.cpp
    rpc_client.cpp
)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
# add_executable(client ${SOURCES})
add_library(client  ${SOURCES})
target_link_libraries(client
    PUBLIC
    monitor_proto
    network 
    rpc_framework 
)
target_include_directories(client PUBLIC
  ${PROJECT_SOURCE_DIR}/proto_rpc
  ${PROJECT_SOURCE_DIR}/network/include
)


# INSTALL(TARGETS client
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
