#pragma once

#include <unordered_map>
#include <glog/logging.h>
#include <google/protobuf/service.h>
#include "monitor_info.pb.h"

namespace monitor {
class RpcManagerImpl : public monitor::proto::GrpcManager {
 public:
  RpcManagerImpl();

  virtual ~RpcManagerImpl();

  void SetMonitorInfo(::google::protobuf::RpcController* controller,
                      const ::monitor::proto::MonitorInfo* request,
                      ::google::protobuf::Empty* response,
                      ::google::protobuf::Closure* done);
  void GetMonitorInfo(::google::protobuf::RpcController* controller,
                      const ::google::protobuf::Empty* request,
                      ::monitor::proto::MonitorInfo* response,
                      ::google::protobuf::Closure* done);

 private:
  monitor::proto::MonitorInfo monitor_infos_;
};

}  // namespace monitor
