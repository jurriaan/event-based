#include "connect_observer.h"
#include "event_component.h"

namespace event_based
{
  ConnectObserver::ConnectObserver(Observable &component, size_t port, AbstractEventComponent &observer, size_t observer_port)
    : Observer(component, port), observer(observer), observer_port(observer_port)
  {
  }

  inline void ConnectObserver::notify(event_based::Message &message)
  {
    observer.process(observer_port, message);
  }

  std::shared_ptr<ConnectObserver> operator+(ConnectableEventComponent &&a, ConnectableEventComponent &&b)
  {
    return std::shared_ptr<ConnectObserver>(new ConnectObserver(a.component, a.port, b.component, b.port));
  }
}
