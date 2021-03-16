#include "traced-callback.h"
#include "queue.h"
#include <iostream>
#include <functional>
template<typename... Ts>
TracedCallback<Ts...>::TracedCallback ()
  : m_callbackVector ()
{}

template<typename... Ts>
void
TracedCallback<Ts...>::Connect(std::function<void (Ts...)>& cb)
{
  m_callbackVector.push_back(cb);
}

// template<typename... Ts>
// void
// TracedCallback<Ts...>::operator() (Ts... args) const
// {
//  for (typename CallbackVector::const_iterator i = m_callbackVector.begin ();
//       i != m_callbackVector.end (); i++)
//    {
//      (*i)(args...);
//    }
// }
