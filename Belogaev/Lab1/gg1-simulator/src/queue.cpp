#include "queue.h"
// #include "traced-callback.cpp" //////////!!!!!!!
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
  //
  // m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange;
  // m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;
  // m_stats.lastQueueChange = Simulator::Now ();

  m_sizeDouble.m_callbackVector[0](m_queue.size(), Simulator::Now());
  m_boolDouble.m_callbackVector[0](m_queue.empty(), Simulator::Now());
  m_singleDouble.m_callbackVector[0](Simulator::Now());

  // std::function <void ()> cb = std::bind (&Statistics::Enqueue, this);
  // m_tcb.push_back(cb(packet));
  if (GetQueueSize() == GetMaxQueueSize() && GetMaxQueueSize() != 0)
    {
        m_noParam.m_callbackVector[0]();
        //m_stats.totalDiscardedPackets++;
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
  // m_stats.sumServiceTime += Simulator::Now () - m_queue.front()->GetArrivalTime ();
  // m_stats.sumWaitingTime += Simulator::Now () - m_queue.front()->GetArrivalTime () - m_queue.front()->GetServiceTime ();
  // m_stats.totalServedPackets ++;
  // m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange;
  // m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;
  // m_stats.lastQueueChange = Simulator::Now ();

  m_doubleDouble.m_callbackVector[0](m_queue.front()->GetArrivalTime(), Simulator::Now());
  m_trippleDouble.m_callbackVector[0](m_queue.front()->GetArrivalTime(), m_queue.front()->GetServiceTime(), Simulator::Now());
  m_noParam.m_callbackVector[1]();
  m_sizeDouble.m_callbackVector[0](m_queue.size(), Simulator::Now());
  m_boolDouble.m_callbackVector[0](m_queue.empty(), Simulator::Now());
  m_singleDouble.m_callbackVector[0](Simulator::Now());

  m_queue.erase (m_queue.begin ());
  //std::cout << m_queue.size() << std::endl;
  if (!m_queue.empty ())
  {
    std::function <void ()> callback = std::bind (&Queue::RemoveFirstPacket, this);
    Simulator::Schedule (m_queue.front()->GetServiceTime (), callback);
  }
}

Queue::~Queue ()
{
  // m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange;
  // m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;

  m_sizeDouble.m_callbackVector[0](m_queue.size(), Simulator::Now());
  m_boolDouble.m_callbackVector[0](m_queue.empty(), Simulator::Now());

  //double avgQueueSize = 0;
  // for (const auto& it : m_stats.queueSizeHist)
  // {
  //   avgQueueSize += it.first * it.second / Simulator::Now();
  // }
  m_singleDouble.m_callbackVector[1](Simulator::Now());

  //double plr = (static_cast<double>(m_stats.totalDiscardedPackets))/(m_stats.totalDiscardedPackets + m_stats.totalServedPackets);
  m_noParam.m_callbackVector[2]();
  m_intDoubleBool.m_callbackVector[0](GetMaxQueueSize(), Simulator::Now(), m_verbose);

  // if (m_verbose)
  // {
  //   // std::cout << "====================PRINT QUEUE STATS======================" << std::endl;
  //   // std::cout << "Total served packets: " << m_stats.totalServedPackets << std::endl;
  //   // std::cout << "Average service time: " << m_stats.sumServiceTime / m_stats.totalServedPackets << std::endl;
  //   // std::cout << "Average waiting time: " << m_stats.sumWaitingTime / m_stats.totalServedPackets << std::endl;
  //   // std::cout << "Average queue size: "   << avgQueueSize << std::endl;
  //   // std::cout << "Utilization: " << m_stats.totalBusyTime / Simulator::Now () << std::endl;
  //   // std::cout << "PLR: " << plr << std::endl;
  //   // std::cout << "Qsize: "  << GetMaxQueueSize() << std::endl;
  //   // std::cout << "===========================================================" << std::endl;
  // }
  // else
  // {
  //       m_destructed.m_callbackVector[4](GetMaxQueueSize(), Simulator::Now());
  //   //  std::cout << "m_stats.totalDiscardedPackets " << m_stats.totalDiscardedPackets << std::endl;
  //   std::cout << m_stats.totalServedPackets << ' ' << m_stats.sumServiceTime / m_stats.totalServedPackets << ' '
  //     << m_stats.sumWaitingTime / m_stats.totalServedPackets << ' ' << avgQueueSize << ' ' << m_stats.totalBusyTime / Simulator::Now () << ' '
  //     << plr << ' ' << GetMaxQueueSize() << std::endl;
  // }
  m_queue.clear ();
}
