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

  void ConnectToTrace_d (std::function<void(double)>& callback){
    m_singleDouble.Connect(callback);
  }

  void ConnectToTrace_np (std::function<void()>& callback){
    m_noParam.Connect(callback);
  }

  void ConnectToTrace_bd (std::function<void(bool, double)>& callback){
    m_boolDouble.Connect(callback);
  }

  void ConnectToTrace_sd (std::function<void(size_t, double)>& callback){
    m_sizeDouble.Connect(callback);
  }

  void ConnectToTrace_dd (std::function<void(double, double)>& callback){
    m_doubleDouble.Connect(callback);
  }

  void ConnectToTrace_td (std::function<void(double, double, double)>& callback){
    m_trippleDouble.Connect(callback);
  }

  void ConnectToTrace_id (std::function<void(int, double, bool)>& callback){
    m_intDoubleBool.Connect(callback);
  }

  // template<typename... Ts>
  // void ConnectToTrace(std::string TraceName, std::function<void(Ts...)>& callback)
  // {
  //   if (TraceName == "singleDouble")
  //   {
  //     m_singleDouble.Connect(callback);
  //   }
  //   else if (TraceName == "noParam")
  //   {
  //     m_noParam.Connect(callback);
  //   }
  //   else if (TraceName == "boolDouble")
  //   {
  //     m_boolDouble.Connect(callback);
  //   }
  //   else if (TraceName == "sizeDouble")
  //   {
  //     m_sizeDouble.Connect(callback);
  //   }
  //   else if (TraceName == "doubleDouble")
  //   {
  //     m_doubleDouble.Connect(callback);
  //   }
  //   else if (TraceName == "trippleDouble")
  //   {
  //     m_trippleDouble.Connect(callback);
  //   }
  //   else if (TraceName == "intDoubleBool")
  //   {
  //     m_intDoubleBool.Connect(callback);
  //   }
  // }

  // struct stats_t
  // {
  //   double sumServiceTime;
  //   int totalServedPackets;
  //   double sumWaitingTime;
  //   double lastQueueChange;
  //   std::map<int, double> queueSizeHist;
  //   double totalBusyTime;
  //   int totalDiscardedPackets;
      // double plr;
      // double avgQueueSize;
  //
  //   stats_t ()
  //   : sumServiceTime (0),
  //     totalServedPackets (0),
  //     sumWaitingTime (0),
  //     lastQueueChange (0),
  //     totalBusyTime (0),
  //     totalDiscardedPackets(0),
  // plr(0),
  // avgQueueSize(0)
  //   {
  //   }
  // };

private:
  int maxQueueSize;
  std::vector<std::shared_ptr<Packet>> m_queue;
  // stats_t m_stats;
  bool m_verbose;

  TracedCallback<double> m_singleDouble;
  TracedCallback<> m_noParam;
  TracedCallback<bool, double> m_boolDouble;
  TracedCallback<size_t, double> m_sizeDouble;
  TracedCallback<double, double> m_doubleDouble;
  TracedCallback<double, double, double> m_trippleDouble;
  TracedCallback<int, double, bool> m_intDoubleBool;
};
