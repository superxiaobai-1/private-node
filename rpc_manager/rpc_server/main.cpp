#include "network/EventLoop.h"
#include "rpc_framework/RpcServer.h"

#include <cassert>
#include <glog/logging.h>
#include "rpc_manager.h"

// constexpr char kServerPortInfo[] = "0.0.0.0:50051";
// void InitServer() {
//   grpc::ServerBuilder builder;
//   builder.AddListeningPort(kServerPortInfo,
//   grpc::InsecureServerCredentials());

//   monitor::GrpcManagerImpl grpc_server;
//   builder.RegisterService(&grpc_server);

//   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
//   server->Wait();

//   return;
// }
using namespace network;
using namespace monitor;
int main(int argc, char *argv[]) {
  LOG(INFO) << "pid = " << getpid();
  EventLoop loop;
  InetAddress listenAddr(9981);
  monitor::RpcManagerImpl impl;
  RpcServer server(&loop, listenAddr);
  server.registerService(&impl);
  server.start();
  loop.loop();
  google::protobuf::ShutdownProtobufLibrary();


}