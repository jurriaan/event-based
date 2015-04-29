#include "event_component.h"
#ifndef EVENTBASEDPHASESHIFTER
#define EVENTBASEDPHASESHIFTER
namespace event_based
{
  class PhaseShifter : public EventComponent<1, 1>
  {
      double phase;
      complex_type phase_shifter;

    public:
      PhaseShifter();
      PhaseShifter(double phase);
      void set_phase(double phase);
      size_t handle_input(size_t port, event_based::Message &message) override;
  };
}
#endif
