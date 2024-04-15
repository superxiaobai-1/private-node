// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_POLLER_EPOLLPOLLER_H
#define MUDUO_NET_POLLER_EPOLLPOLLER_H

#include "network/EventLoop.h"
#include <map>
#include <vector>
struct epoll_event;
namespace network {
class Channel;
///
/// IO Multiplexing with epoll(4).
///
class Poller {
public:
  typedef std::vector<Channel *> ChannelList;
  Poller(EventLoop *loop);
  ~Poller();

  void poll(int timeoutMs, ChannelList *activeChannels);
  void updateChannel(Channel *channel);
  void removeChannel(Channel *channel);

  void assertInLoopThread() const { ownerLoop_->assertInLoopThread(); }
  bool hasChannel(Channel *channel) const;

private:
  EventLoop *ownerLoop_;
  static const int kInitEventListSize = 16;

  static const char *operationToString(int op);

  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
  void update(int operation, Channel *channel);

  typedef std::vector<struct epoll_event> EventList;

  int epollfd_;
  EventList events_;

  typedef std::map<int, Channel *> ChannelMap;
  ChannelMap channels_;
};

} // namespace network
#endif // MUDUO_NET_POLLER_EPOLLPOLLER_H
