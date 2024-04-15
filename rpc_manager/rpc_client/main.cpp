#pragma once

#include <fcntl.h>
#include <cassert>
#include <glog/logging.h>
#include "network/EventLoop.h"
#include "network/InetAddress.h"
#include "network/TcpClient.h"
#include "network/TcpConnection.h"
#include "rpc_client.h"
#include "rpc_framework/RpcChannel.h"

#include <stdio.h>
#include <unistd.h>
using namespace network;
using namespace monitor;
int main(int argc, char *argv[]) {
  // google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "pid = " << getpid();
  if (argc > 1) {
    EventLoop loop;
    InetAddress serverAddr(argv[1], 9981);

    RpcClient rpcClient(&loop, serverAddr);
    rpcClient.connect();
    loop.loop();
  } else {
    printf("Usage: %s host_ip\n", argv[0]);
  }
  google::protobuf::ShutdownProtobufLibrary();
}
