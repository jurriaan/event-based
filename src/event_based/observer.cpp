#include <cstddef>
#include "observer.h"

namespace event_based
{
  Observer::Observer(Observable &component, size_t port)
  {
    this->observable_port = port;
    component.attach(this, port);
  }
}
