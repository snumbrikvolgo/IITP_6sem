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
  std::map<int, double> queueSizeHist;
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

  void cb_updateQueueSizeHist(size_t size, double time)
  {
    queueSizeHist[size] += time - lastQueueChange;
  }

  void cb_updateTotalBusyTime(bool is_empty, double time)
  {
    totalBusyTime += (!is_empty) ? (time - lastQueueChange) : 0;
  }

  void cb_updateLastQueueChange(double time)
  {
    lastQueueChange = time;
  }

  void cb_updateTotalDiscardedPackets()
  {
    totalDiscardedPackets++;
  }

  void cb_updateSumServiceTime(double arrival, double time )
  {
    sumServiceTime +=  time - arrival;
  }
  void cb_updateSumWaitingTime(double arrival,  double service, double time )
  {
    sumWaitingTime += time - arrival - service;
  }
  void cb_updateTotalServedPackets()
  {
    totalServedPackets++;
  }
  void cb_updateAvgQueueSize(double time)
  {
    for (const auto& it : queueSizeHist)
    {
      avgQueueSize += it.first * it.second / time;
    }
  }

  void cb_updatePLR()
  {
    plr = (static_cast<double>(totalDiscardedPackets))/(totalDiscardedPackets + totalServedPackets);
  }

  void cb_printStats(int max_size, double time, bool verbose)
  {
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

// void cb_updateQueueSizeHist(Stats& stats, size_t size, double time)
// {
//   stats.queueSizeHist[size] += time - stats.lastQueueChange;
// }
//
// void cb_updateTotalBusyTime(Stats& stats, bool is_empty, double time)
// {
//   stats.totalBusyTime += (!is_empty) ? (time - stats.lastQueueChange) : 0;
// }
//
// void cb_updateLastQueueChange(Stats& stats, double time)
// {
//   stats.lastQueueChange = time;
// }
//
// void cb_updateTotalDiscardedPackets(Stats& stats, double time)
// {
//   stats.totalDiscardedPackets++;
// }
//
// void cb_updateSumServiceTime(Stats& stats, double arrival, double time )
// {
//   stats.sumServiceTime +=  time - arrival;
// }
// void cb_updateSumWaitingTime(Stats& stats, double arrival,  double service, double time )
// {
//   stats.sumWaitingTime += time - arrival - service;
// }
// void cb_updateTotalServedPackets(Stats& stats)
// {
//   stats.totalServedPackets++;
// }
// void cb_updateAvgQueueSize(Stats& stats, double time)
// {
//   for (const auto& it : stats.queueSizeHist)
//   {
//     stats.avgQueueSize += it.first * it.second / time;
//   }
// }
//
// void cb_updatePLR(Stats& stats)
// {
//   stats.plr = (static_cast<double>(stats.totalDiscardedPackets))/(stats.totalDiscardedPackets + stats.totalServedPackets);
// }
//
// void cb_printStats(Stats& stats, int max_size, double time, bool verbose)
// {
//   if (verbose)
//   {
//     std::cout << "====================PRINT QUEUE STATS======================" << std::endl;
//     std::cout << "Total served packets: " << stats.totalServedPackets << std::endl;
//     std::cout << "Average service time: " << stats.sumServiceTime / stats.totalServedPackets << std::endl;
//     std::cout << "Average waiting time: " << stats.sumWaitingTime / stats.totalServedPackets << std::endl;
//     std::cout << "Average queue size: "   << stats.avgQueueSize << std::endl;
//     std::cout << "Utilization: " << stats.totalBusyTime / time << std::endl;
//     std::cout << "PLR: " << stats.plr << std::endl;
//     std::cout << "Qsize: "  << max_size << std::endl;
//     std::cout << "===========================================================" << std::endl;
//   }
//   else
//   {
//     std::cout << stats.totalServedPackets << ' ' << stats.sumServiceTime / stats.totalServedPackets << ' '
//       << stats.sumWaitingTime / stats.totalServedPackets << ' ' << stats.avgQueueSize << ' ' << stats.totalBusyTime / time << ' '
//       << stats.plr << ' ' << max_size << std::endl;
//   }
// }
