#include "observer.h"
#include "abstract_event_component.h"

#ifndef EVENTBASEDCONNECTOBSERVER
#define EVENTBASEDCONNECTOBSERVER
namespace event_based
{
  class AbstractEventComponent;
  class ConnectObserver : public Observer
  {
      AbstractEventComponent &observer;
      size_t observer_port;
    public:
      ConnectObserver(Observable &component, size_t port, AbstractEventComponent &observer, size_t observer_port);
      void notify(event_based::Message &message) override;
  };

}

#endif
