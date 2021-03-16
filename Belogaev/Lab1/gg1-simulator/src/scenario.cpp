#include <iostream>
#include <memory>
#include <random>
#include "packet-generator.h"
#include "simulator.h"
#include "stats.h"

void ConnectCallbacksToServer(Stats& stats, std::shared_ptr<Server> server)
{
  std::function<void(size_t, double)> updateQueueSizeHist = std::bind(&Stats::cb_updateQueueSizeHist, &stats, std::placeholders::_1, std::placeholders::_2);
  std::function<void(bool, double)> updateTotalBusyTime = std::bind(&Stats::cb_updateTotalBusyTime, &stats, std::placeholders::_1, std::placeholders::_2);
  std::function<void(double)> updateLastQueueChange = std::bind(&Stats::cb_updateLastQueueChange, &stats, std::placeholders::_1);
  std::function<void()> updateTotalDiscardedPackets = std::bind(&Stats::cb_updateTotalDiscardedPackets, &stats);
  std::function<void(double, double)> updateSumServiceTime = std::bind(&Stats::cb_updateSumServiceTime, &stats, std::placeholders::_1, std::placeholders::_2);
  std::function<void(double, double, double)> updateSumWaitingTime = std::bind(&Stats::cb_updateSumWaitingTime, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  std::function<void()> updateTotalServedPackets = std::bind(&Stats::cb_updateTotalServedPackets, &stats);
  std::function<void(double)> updateAvgQueueSize = std::bind(&Stats::cb_updateAvgQueueSize, &stats, std::placeholders::_1);
  std::function<void()> updatePLR = std::bind(&Stats::cb_updatePLR, &stats);
  std::function<void(int, double, bool)> printStats = std::bind(&Stats::cb_printStats, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  // std::function<void(size_t, double)> updateQueueSizeHist = std::bind(&cb_updateQueueSizeHist, stats, std::placeholders::_1, std::placeholders::_2);
  server->ConnectToTraceToQueue_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
  server->ConnectToTraceToQueue_bd(updateTotalBusyTime);
  server->ConnectToTraceToQueue_d(updateLastQueueChange);
  server->ConnectToTraceToQueue_np(updateTotalDiscardedPackets);

  server->ConnectToTraceToQueue_dd(updateSumServiceTime);
  server->ConnectToTraceToQueue_td(updateSumWaitingTime);
  server->ConnectToTraceToQueue_np(updateTotalServedPackets);
  server->ConnectToTraceToQueue_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
  server->ConnectToTraceToQueue_bd(updateTotalBusyTime);
  server->ConnectToTraceToQueue_d(updateLastQueueChange);

  server->ConnectToTraceToQueue_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
  server->ConnectToTraceToQueue_bd(updateTotalBusyTime);
  server->ConnectToTraceToQueue_d(updateAvgQueueSize);
  server->ConnectToTraceToQueue_np(updatePLR);
  server->ConnectToTraceToQueue_id(printStats);
}

int main(int argc, char** argv)
{
  if (argc < 6)
  {
    std::cout << "Usage: ./scenario seed lambda mu simTime queueSize" << std::endl;
    return -1;
  }
  int seed = atoi (argv[1]);
  // if (seed != 0)
  // {
  //   std::mt19937 gen;
  //   gen.seed(time(0)); //mb later it will be in use
  //   seed = gen()
  // }
  double lambda = atof (argv[2]);
  double mu = atof (argv[3]);
  time_t simTime = atof (argv[4]);
  int queueSize = atoi (argv[5]);

  if (queueSize <= 0)
  {
      queueSize = 0; // infinite queue size
  }

  std::exponential_distribution<double>::param_type params1 (lambda);
  std::exponential_distribution<double>::param_type params2 (mu);
  PacketGenerator<std::exponential_distribution<double>, std::exponential_distribution<double>> packetGen(params1, params2);
  //
  // std::discrete_distribution<int>::param_type params2 {0.,mu};
  // PacketGenerator<std::exponential_distribution<double>, std::discrete_distribution<int>> packetGen(params1, params2);


  Stats stats = Stats();
  std::shared_ptr<Server> server (new Server (queueSize, stats));
  ConnectCallbacksToServer(stats, server);
  packetGen.SetServer (server);

  Simulator sim;
  sim.SetStop (simTime);
  sim.SetSeed (seed);

  packetGen.Start ();
  sim.Run ();
}
