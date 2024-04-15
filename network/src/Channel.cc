// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "network/Channel.h"
#include "network/EventLoop.h"
#include <cassert>
#include <sstream>

#include <poll.h>


namespace network {

Channel::Channel(EventLoop *loop, int fd__)
    : loop_(loop), fd_(fd__), events_(0), revents_(0), index_(-1),
      event_handling_(false), addedToLoop_(false) {}

Channel::~Channel() {
  assert(!event_handling_);
  assert(!addedToLoop_);
  if (loop_->isInLoopThread()) {
    assert(!loop_->hasChannel(this));
  }
}

void Channel::update() {
  addedToLoop_ = true;
  loop_->updateChannel(this);
}

void Channel::remove() {
  assert(isNoneEvent());
  addedToLoop_ = false;
  loop_->removeChannel(this);
}

void Channel::handleEvent() {
  event_handling_ = true;
  if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {

    if (closeCallback_)
      closeCallback_();
  }

  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
    if (readCallback_)
      readCallback_();
  }
  if (revents_ & POLLOUT) {
    if (writeCallback_)
      writeCallback_();
  }

  if (revents_ & (POLLERR | POLLNVAL)) {
    if (errorCallback_)
      errorCallback_();
  }
  event_handling_ = false;
}
} // namespace network