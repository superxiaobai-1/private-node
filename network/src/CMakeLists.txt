include(CheckFunctionExists)

check_function_exists(accept4 HAVE_ACCEPT4)
if(NOT HAVE_ACCEPT4)
  set_source_files_properties(SocketsOps.cc PROPERTIES COMPILE_FLAGS "-DNO_ACCEPT4")
endif()

set(net_SRCS
  Acceptor.cc
  Buffer.cc
  Channel.cc
  Connector.cc
  EventLoop.cc
  EventLoopThread.cc
  EventLoopThreadPool.cc
  InetAddress.cc
  Poller.cc
  Socket.cc
  SocketsOps.cc
  TcpClient.cc
  TcpConnection.cc
  TcpServer.cc
  util.cc
  )

add_library(network ${net_SRCS})
target_link_libraries(network  glog)
target_include_directories(network PUBLIC
  ../include
  )


install(TARGETS  network DESTINATION  ${PROJECT_BINARY_DIR}/lib)

# set(HEADERS
#   include/Buffer.h
#   include/Callbacks.h
#   include/Channel.h
#   include/Endian.h
#   include/EventLoop.h
#   include/EventLoopThread.h
#   include/EventLoopThreadPool.h
#   include/InetAddress.h
#   include/TcpClient.h
#   include/TcpConnection.h
#   include/TcpServer.h
#   )
# install(FILES ${HEADERS} DESTINATION include/muduo/net)


