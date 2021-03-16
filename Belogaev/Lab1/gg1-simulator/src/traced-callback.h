#pragma once

#include "packet.h"
#include "simulator.h"
#include <memory>
#include <vector>
template<typename... Ts>
class TracedCallback
{
public:
  TracedCallback(): m_callbackVector (){};
  void Connect (std::function<void (Ts...)>& cb)
  {
    m_callbackVector.push_back(cb);
  };
//void operator() (Ts... args) const;
//  ~TracedCallback();

  typedef std::vector<std::function<void (Ts...)>> CallbackVector;
  CallbackVector m_callbackVector;
};
