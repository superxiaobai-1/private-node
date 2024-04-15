#include <QApplication>
#include <memory>
#include <thread>
#include "monitor_widget.h"
#include "rpc_client/rpc_client.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  monitor::proto::MonitorInfo monitor_info;
  monitor::RpcClient* rpc_client = nullptr;
  std::unique_ptr<std::thread> thread_;
  thread_ = std::make_unique<std::thread>([&]() {
    EventLoop loop;
    rpc_client = new monitor::RpcClient(&loop, "172.25.9.117");
    loop.loop();
  });

  monitor::MonitorWidget monitor_widget;
  QWidget* widget = monitor_widget.ShowAllMonitorWidget("test");
  widget->show();

  std::thread data_update_thread([&]() {
    while (true) {
      if (rpc_client) {
        rpc_client->GetMonitorInfo(&monitor_info);
        monitor_widget.UpdateData(monitor_info);
        monitor_info.Clear();
        std::this_thread::sleep_for(std::chrono::seconds(2));
      }
    }
  });

  thread_->detach();
  data_update_thread.detach();

  return app.exec();
}
