#ifndef EVENTBASEDOBSERVABLE
#define EVENTBASEDOBSERVABLE
namespace event_based
{
  class Observer;
  class Observable
  {
    public:
      virtual void attach(event_based::Observer *observer, size_t port) = 0;
      virtual void detach(size_t port) = 0;
  };
}
#endif
