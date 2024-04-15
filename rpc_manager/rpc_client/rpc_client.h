#pragma once

#include <fcntl.h>
#include <cassert>
#include <glog/logging.h>
#include "network/EventLoop.h"
#include "network/InetAddress.h"
#include "network/TcpClient.h"
#include "network/TcpConnection.h"
#include "rpc_framework/RpcChannel.h"

#include <stdio.h>
#include <unistd.h>
#include <memory>

#include "monitor_info.pb.h"
using namespace network;
namespace monitor {
class RpcClient {
 public:
  RpcClient(EventLoop* loop, const std::string& ip);
  ~RpcClient();
  void SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info);
  void GetMonitorInfo(monitor::proto::MonitorInfo* monito_info);
  void connect() { client_.connect(); }
  void Closure();
  void onConnection(const TcpConnectionPtr& conn);

 private:
  EventLoop* loop_;
  TcpClient client_;
  RpcChannelPtr channel_;
  monitor::proto::GrpcManager::Stub stub_;
  monitor::proto::MonitorInfo monito_info_;
};
}  // namespace monitor
