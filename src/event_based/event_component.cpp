#include "event_component.h"

using namespace event_based;
ConnectableEventComponent AbstractEventComponent::operator()(size_t port)
{
  return ConnectableEventComponent(*this, port);
}


ConnectableEventComponent::ConnectableEventComponent(AbstractEventComponent &component, size_t port)
  : component(component), port(port)
{
}

