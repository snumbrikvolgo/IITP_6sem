#include <iostream>
#include <memory>
#include <random>
#include "packet-generator.h"
#include "simulator.h"
#include "stats.h"

void ConnectCallbacksToServer(Stats& stats, std::shared_ptr<Server> server)
{
  std::function<void(size_t, double, bool, int, int)> updateAdded = std::bind(&Stats::cb_updateAdded, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5 );
  std::function<void(double, double, double, size_t, bool)> updateRemoved = std::bind(&Stats::cb_updateRemoved, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5 );
  std::function<void(size_t, double, bool, int, bool)> updateDestructed = std::bind(&Stats::cb_updateDestructed, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5 );
  server->ConnectToTraceToQueueAdded(updateAdded);
  server->ConnectToTraceToQueueRemoved(updateRemoved);
  server->ConnectToTraceToQueueDestructed(updateDestructed);
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
