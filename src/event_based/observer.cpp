#include <cstddef>
#include "observer.h"

namespace event_based
{
  Observer::Observer(Observable &component, size_t port)
    : observable(component)
  {
    observable_port = port;
    observable.attach(this, port);
  }

  Observer::~Observer()
  {
    observable.detach(observable_port);
  }
}
