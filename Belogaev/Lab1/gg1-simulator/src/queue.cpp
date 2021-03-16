#include "queue.h"
#include <iostream>
#include <functional>
#include <string>

Queue::Queue ()
{
  m_verbose = false;
}

int
Queue::GetQueueSize ()
{
  return m_queue.size ();
}

int
Queue::GetMaxQueueSize ()
{
  return maxQueueSize;
}

void
Queue::SetMaxQueueSize (int qSize)
{
  maxQueueSize = qSize;
}

void
Queue::SetVerbose (bool verbose)
{
  m_verbose = verbose;
}

void
Queue::AddPacket (std::shared_ptr<Packet> packet)
{
  m_added.m_callbackVector[0](m_queue.size(), Simulator::Now(), m_queue.empty(),GetMaxQueueSize(), GetQueueSize());
  if (GetQueueSize() == GetMaxQueueSize() && GetMaxQueueSize() != 0)
    {
        return;
    }
 //infinite queue is supported too
  m_queue.push_back (packet);
  if (m_queue.size () == 1)
  {
    std::function <void ()> callback = std::bind (&Queue::RemoveFirstPacket, this);
    Simulator::Schedule (packet->GetServiceTime (), callback);
  }
}

void
Queue::RemoveFirstPacket ()
{
  m_removed.m_callbackVector[0](m_queue.front()->GetArrivalTime(), m_queue.front()->GetServiceTime(), Simulator::Now(), m_queue.size(), m_queue.empty());

  m_queue.erase (m_queue.begin ());
  if (!m_queue.empty ())
  {
    std::function <void ()> callback = std::bind (&Queue::RemoveFirstPacket, this);
    Simulator::Schedule (m_queue.front()->GetServiceTime (), callback);
  }
}

Queue::~Queue ()
{
  m_destructed.m_callbackVector[0](m_queue.size(), Simulator::Now(), m_queue.empty(), GetMaxQueueSize(), m_verbose);
  m_queue.clear ();
}
