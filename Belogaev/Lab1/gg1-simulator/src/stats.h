#pragma once
#include <iostream>
#include <map>


class Stats
{
public:
  double sumServiceTime;
  int totalServedPackets;
  double sumWaitingTime;
  double lastQueueChange;
  std::map<size_t, double> queueSizeHist;
  double totalBusyTime;
  int totalDiscardedPackets;
  double avgQueueSize;
  double plr;

  Stats ()
  : sumServiceTime (0),
    totalServedPackets (0),
    sumWaitingTime (0),
    lastQueueChange (0),
    totalBusyTime (0),
    totalDiscardedPackets(0),
    avgQueueSize(0),
    plr(0)
  {
  }

  void cb_updateAdded(size_t size, double time, bool is_empty, int max_size, int q_size)
  {
    queueSizeHist[size] += time - lastQueueChange;
    totalBusyTime += (!is_empty) ? (time - lastQueueChange) : 0;
    lastQueueChange = time;

    if (q_size == max_size && max_size != 0)
    {
      totalDiscardedPackets++;
    }
  }

  void cb_updateRemoved(double arrival, double service, double time, size_t size, bool is_empty)
  {
    sumServiceTime +=  time - arrival;
    sumWaitingTime += time - arrival - service;
    totalServedPackets++;

    queueSizeHist[size] += time - lastQueueChange;
    totalBusyTime += (!is_empty) ? (time - lastQueueChange) : 0;
    lastQueueChange = time;

  }

  void cb_updateDestructed(size_t size, double time, bool is_empty, int max_size, bool verbose)
  {
    queueSizeHist[size] += time - lastQueueChange;
    totalBusyTime += (!is_empty) ? (time - lastQueueChange) : 0;

    for (int i = 0; i <= max_size; i++)
    {
      avgQueueSize += i * queueSizeHist[i] / time;
    }

    plr = (static_cast<double>(totalDiscardedPackets))/(totalDiscardedPackets + totalServedPackets);

    if (verbose)
    {
      std::cout << "====================PRINT QUEUE STATS======================" << std::endl;
      std::cout << "Total served packets: " << totalServedPackets << std::endl;
      std::cout << "Average service time: " << sumServiceTime / totalServedPackets << std::endl;
      std::cout << "Average waiting time: " << sumWaitingTime / totalServedPackets << std::endl;
      std::cout << "Average queue size: "   << avgQueueSize << std::endl;
      std::cout << "Utilization: " << totalBusyTime / time << std::endl;
      std::cout << "PLR: " << plr << std::endl;
      std::cout << "Qsize: "  << max_size << std::endl;
      std::cout << "===========================================================" << std::endl;
    }
    else
    {
      std::cout << totalServedPackets << ' ' << sumServiceTime / totalServedPackets << ' '
        << sumWaitingTime / totalServedPackets << ' ' << avgQueueSize << ' ' << totalBusyTime / time << ' '
        << plr << ' ' << max_size << std::endl;
    }
  }
};
