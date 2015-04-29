#include "observable.h"
#ifndef EVENTBASEDABSTRACTEVENTCOMPONENT
#define EVENTBASEDABSTRACTEVENTCOMPONENT
namespace event_based
{
  class ConnectableEventComponent;
  class AbstractEventComponent : public Observable
  {
    public:
      virtual void process(size_t port, event_based::Message &message) = 0;
      ConnectableEventComponent operator()(size_t port);
  };

}
#endif
