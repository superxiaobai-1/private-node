#include "rpc_manager.h"
#include <iostream>

namespace monitor {
RpcManagerImpl::RpcManagerImpl() {}

RpcManagerImpl::~RpcManagerImpl() {}
void RpcManagerImpl::SetMonitorInfo(
    ::google::protobuf::RpcController* controller,
    const ::monitor::proto::MonitorInfo* request,
    ::google::protobuf::Empty* response, ::google::protobuf::Closure* done) {
  monitor_infos_.Clear();
  monitor_infos_ = *request;

  done->Run();
}
void RpcManagerImpl::GetMonitorInfo(
    ::google::protobuf::RpcController* controller,
    const ::google::protobuf::Empty* request,
    ::monitor::proto::MonitorInfo* response,
    ::google::protobuf::Closure* done) {
  *response = monitor_infos_;
  done->Run();
}

}  // namespace monitor
