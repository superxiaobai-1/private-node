#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <glog/logging.h>
#include "monitor/cpu_load_monitor.h"
#include "monitor/cpu_softirq_monitor.h"
#include "monitor/cpu_stat_monitor.h"
#include "monitor/mem_monitor.h"
#include "monitor/monitor_inter.h"
#include "monitor/net_monitor.h"
#include "network/EventLoopThreadPool.h"
#include "rpc_client/rpc_client.h"
#include "monitor_info.pb.h"

int main() {
  std::vector<std::shared_ptr<monitor::MonitorInter>> runners_;
  runners_.emplace_back(new monitor::CpuSoftIrqMonitor());
  runners_.emplace_back(new monitor::CpuLoadMonitor());
  runners_.emplace_back(new monitor::CpuStatMonitor());
  runners_.emplace_back(new monitor::MemMonitor());
  runners_.emplace_back(new monitor::NetMonitor());

  char* name = getenv("USER");

  std::unique_ptr<std::thread> thread_ = nullptr;

  EventLoop loop;
  monitor::RpcClient rpc_client_(&loop, "172.25.9.117");
  monitor::proto::MonitorInfo monitor_info;
  monitor_info.set_name(std::string(name));

  thread_ = std::make_unique<std::thread>([&]() {
    while (true) {
      for (auto& runner : runners_) {
        runner->UpdateOnce(&monitor_info);
      }

      rpc_client_.SetMonitorInfo(monitor_info);
      monitor_info.Clear();
      std::this_thread::sleep_for(std::chrono::seconds(3));
    }
  });

  thread_->detach();
  loop.loop();
  return 0;
}
