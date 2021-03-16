#pragma once
#include "stats.h"
#include "queue.h"
#include <memory>

class Server
{
public:
  Server (int qSize, Stats stats);
  void AddPacket (std::shared_ptr<Packet> packet);

  void ConnectToTraceToQueue_d (std::function<void(double)>& callback){
    m_queue.ConnectToTrace_d(callback);
  }

  void ConnectToTraceToQueue_np (std::function<void()>& callback){
    m_queue.ConnectToTrace_np(callback);
  }

  void ConnectToTraceToQueue_bd (std::function<void(bool, double)>& callback){
    m_queue.ConnectToTrace_bd(callback);
  }

  void ConnectToTraceToQueue_sd (std::function<void(size_t, double)>& callback){
    m_queue.ConnectToTrace_sd(callback);
  }

  void ConnectToTraceToQueue_dd (std::function<void(double, double)>& callback){
    m_queue.ConnectToTrace_dd(callback);
  }

  void ConnectToTraceToQueue_td (std::function<void(double, double, double)>& callback){
    m_queue.ConnectToTrace_td(callback);
  }

  void ConnectToTraceToQueue_id (std::function<void(int, double, bool)>& callback){
    m_queue.ConnectToTrace_id(callback);
  }

private:
  Queue m_queue;
};
