
set(SOURCES
  RpcChannel.cc 
  RpcServer.cc
  RpcCodec.cc
)

add_library(rpc_framework ${SOURCES})


target_include_directories(rpc_framework PUBLIC
  ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(rpc_framework
    PUBLIC
    network
    rpc_proto
    protobuf
    z
    glog
)

# if(TCMALLOC_LIBRARY)
#   target_link_libraries(rpc_framework tcmalloc_and_profiler)
# endif()

install(TARGETS  rpc_framework DESTINATION  ${PROJECT_BINARY_DIR}/lib)


