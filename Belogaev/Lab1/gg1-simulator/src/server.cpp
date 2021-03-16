#include "server.h"

Server::Server (int qSize, Stats stats)
{
    m_queue.SetMaxQueueSize(qSize);
    // std::function<void(size_t, double)> updateQueueSizeHist = std::bind(&Stats::cb_updateQueueSizeHist, &stats, std::placeholders::_1, std::placeholders::_2);
    // std::function<void(bool, double)> updateTotalBusyTime = std::bind(&Stats::cb_updateTotalBusyTime, &stats, std::placeholders::_1, std::placeholders::_2);
    // std::function<void(double)> updateLastQueueChange = std::bind(&Stats::cb_updateLastQueueChange, &stats, std::placeholders::_1);
    // std::function<void()> updateTotalDiscardedPackets = std::bind(&Stats::cb_updateTotalDiscardedPackets, &stats);
    // std::function<void(double, double)> updateSumServiceTime = std::bind(&Stats::cb_updateSumServiceTime, &stats, std::placeholders::_1, std::placeholders::_2);
    // std::function<void(double, double, double)> updateSumWaitingTime = std::bind(&Stats::cb_updateSumWaitingTime, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    // std::function<void()> updateTotalServedPackets = std::bind(&Stats::cb_updateTotalServedPackets, &stats);
    // std::function<void(double)> updateAvgQueueSize = std::bind(&Stats::cb_updateAvgQueueSize, &stats, std::placeholders::_1);
    // std::function<void()> updatePLR = std::bind(&Stats::cb_updatePLR, &stats);
    // std::function<void(int, double, bool)> printStats = std::bind(&Stats::cb_printStats, &stats, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    // std::function<void(size_t, double)> updateQueueSizeHist = std::bind(&cb_updateQueueSizeHist, stats, std::placeholders::_1, std::placeholders::_2);
    // m_queue.ConnectToTrace_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
    // m_queue.ConnectToTrace_bd(updateTotalBusyTime);
    // m_queue.ConnectToTrace_d(updateLastQueueChange);
    // m_queue.ConnectToTrace_np(updateTotalDiscardedPackets);
    //
    // m_queue.ConnectToTrace_dd(updateSumServiceTime);
    // m_queue.ConnectToTrace_td(updateSumWaitingTime);
    // m_queue.ConnectToTrace_np(updateTotalServedPackets);
    // m_queue.ConnectToTrace_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
    // m_queue.ConnectToTrace_bd(updateTotalBusyTime);
    // m_queue.ConnectToTrace_d(updateLastQueueChange);
    //
    // m_queue.ConnectToTrace_sd(updateQueueSizeHist);//&cb_updateQueueSizeHist
    // m_queue.ConnectToTrace_bd(updateTotalBusyTime);
    // m_queue.ConnectToTrace_d(updateAvgQueueSize);
    // m_queue.ConnectToTrace_np(updatePLR);
    // m_queue.ConnectToTrace_id(printStats);
}

void
Server::AddPacket (std::shared_ptr<Packet> p)
{
  m_queue.AddPacket (p);
}
