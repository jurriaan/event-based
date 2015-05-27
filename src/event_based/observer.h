#include "types.h"
#include "observable.h"

#ifndef EVENTBASEDOBSERVER
#define EVENTBASEDOBSERVER
namespace event_based
{
  class Observer
  {
    public:
      explicit Observer(Observable &component, size_t port);
      virtual void notify(event_based::Message &message) = 0;
      virtual ~Observer();
    protected:
      size_t observable_port;
      Observable &observable;
  };
}
#endif
