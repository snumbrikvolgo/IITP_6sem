#pragma once
#include "stats.h"
#include "queue.h"
#include <memory>

class Server
{
public:
  Server (int qSize, Stats stats);
  void AddPacket (std::shared_ptr<Packet> packet);

  void ConnectToTraceToQueueAdded(std::function<void(size_t, double, bool, int, int)>& callback)
  {
    m_queue.ConnectToTraceAdded(callback);
  }
  void ConnectToTraceToQueueRemoved(std::function<void(double, double, double, size_t, bool)>& callback)
  {
    m_queue.ConnectToTraceRemoved(callback);
  }
  void ConnectToTraceToQueueDestructed(std::function<void(size_t, double, bool, int, bool)>& callback)
  {
    m_queue.ConnectToTraceDestructed(callback);
  }
private:
  Queue m_queue;
};
