#include "server.h"

Server::Server (int qSize, Stats stats)
{
    m_queue.SetMaxQueueSize(qSize);
}

void
Server::AddPacket (std::shared_ptr<Packet> p)
{
  m_queue.AddPacket (p);
}
