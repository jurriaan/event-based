#include "observer.h"
#include "abstract_event_component.h"
#include "connect_observer.h"

#ifndef EVENTBASEDEVENTCOMPONENT
#define EVENTBASEDEVENTCOMPONENT
namespace event_based
{
  class ConnectableEventComponent
  {
      AbstractEventComponent &component;
      size_t port;

    public:
      explicit ConnectableEventComponent(AbstractEventComponent &component, size_t port);
      friend std::shared_ptr<ConnectObserver> operator+(ConnectableEventComponent &&a, ConnectableEventComponent &&b);
  };

  template <size_t inputs, size_t outputs>
  class EventComponent : public AbstractEventComponent
  {
      event_based::Observer *observer[outputs];

    public:
      EventComponent();

      void attach(event_based::Observer *observer, size_t port) override;
      void process(size_t port, event_based::Message &message) override;

    protected:
      event_based::Message last_message[inputs];
      virtual size_t handle_input(size_t port, event_based::Message &message) = 0;
  };

  template <size_t inputs, size_t outputs>
  void EventComponent<inputs, outputs>::process(size_t port, Message &message)
  {
    last_message[port] = message;

    auto output = handle_input(port, message);
    if(observer[output])
      observer[output]->notify(message);
  }

  template <size_t inputs, size_t outputs>
  void EventComponent<inputs, outputs>::attach(event_based::Observer *observer, size_t port)
  {
    this->observer[port] = observer;
  }

  template <size_t inputs, size_t outputs>
  EventComponent<inputs, outputs>::EventComponent()
  {
    for (size_t i = 0; i < inputs; ++i)
      last_message[i] = Message(2, arma::fill::eye);
    for (size_t i = 0; i < outputs; ++i)
      observer[i] = 0;
  }

}
#endif
