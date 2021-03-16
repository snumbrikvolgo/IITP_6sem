#pragma once

#include "packet.h"
#include "simulator.h"
#include "traced-callback.h"
#include <memory>
#include <vector>

class Queue
{
public:
  Queue ();
  int GetQueueSize ();
  void SetMaxQueueSize(int qSize);
  int GetMaxQueueSize();
  void SetVerbose (bool verbose);
  void AddPacket (std::shared_ptr<Packet>);
  void RemoveFirstPacket ();
  ~Queue ();


  void ConnectToTraceAdded(std::function<void(size_t, double, bool, int, int)>& callback)
  {
    m_added.Connect(callback);
  }
  void ConnectToTraceRemoved(std::function<void(double, double, double, size_t, bool)>& callback)
  {
    m_removed.Connect(callback);
  }
  void ConnectToTraceDestructed(std::function<void(size_t, double, bool, int, bool)>& callback)
  {
    m_destructed.Connect(callback);
  }

private:
  int maxQueueSize;
  std::vector<std::shared_ptr<Packet>> m_queue;
  bool m_verbose;

  TracedCallback<size_t, double, bool, int, int> m_added;
  TracedCallback<double, double, double, size_t, bool> m_removed;
  TracedCallback<size_t, double, bool, int, bool> m_destructed;
};
