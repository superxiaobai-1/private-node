#include "rpc_client.h"
#include <thread>
using namespace network;
namespace monitor {
RpcClient::RpcClient(EventLoop* loop, const std::string& ip)
    : loop_(loop),
      client_(loop_, InetAddress(ip, 9981), "RpcClient"),
      channel_(new RpcChannel()),
      stub_(get_pointer(channel_)) {
  client_.setConnectionCallback(std::bind(&RpcClient::onConnection, this, _1));
  client_.setMessageCallback(
      std::bind(&RpcChannel::onMessage, get_pointer(channel_), _1, _2));
  client_.connect();
}
RpcClient::~RpcClient() {}

void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info) {
  ::google::protobuf::Empty* response;
  // monitor_info.set_name(std::string("name"));
  stub_.SetMonitorInfo(
      NULL, &monito_info, response,
      google::protobuf::NewCallback(this, &RpcClient::Closure));
}

void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monito_info) {
  ::google::protobuf::Empty request;
  stub_.GetMonitorInfo(
      nullptr, &request, monito_info,
      google::protobuf::NewCallback(this, &RpcClient::Closure));
}
void RpcClient::onConnection(const TcpConnectionPtr& conn) {
  if (conn->connected()) {
    // conn->setTcpNoDelay(true);
    channel_->setConnection(conn);
  } else {
    RpcClient::connect();
    // loop_->quit();
  }
}
void RpcClient::Closure() {
  LOG(INFO) << "33333333333";

  // std::this_thread::sleep_for(std::chrono::seconds(3));

  // ::google::protobuf::Empty* response;

  // // monitor_info.set_name(std::string("name"));
  // // monitor::proto::MonitorInfo monito_info = monito_info_;
  // stub_.SetMonitorInfo(
  //     NULL, &monito_info_, response,
  //     google::protobuf::NewCallback(this, &RpcClient::Closure));
}

}  // namespace monitor
