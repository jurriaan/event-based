#include "observer.h"

#ifndef EVENTBASEDCOUNTOBSERVER
#define EVENTBASEDCOUNTOBSERVER
namespace event_based
{
  class CountObserver : public Observer
  {
      size_t d_count = 0;
    public:
      using Observer::Observer;
      void notify(event_based::Message &message) override;
      size_t count() const;
      void reset();
  };

  inline void CountObserver::notify(event_based::Message &message)
  {
    ++d_count;
  }

  inline size_t CountObserver::count() const
  {
    return d_count;
  }

  inline void CountObserver::reset()
  {
    d_count = 0;
  }
}

#endif
