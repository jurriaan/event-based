#include "phase_shifter.h"
using namespace event_based;

PhaseShifter::PhaseShifter()
  : EventComponent()
{
  set_phase(0);
}

PhaseShifter::PhaseShifter(double phase)
  : EventComponent()
{
  set_phase(phase);
}

void PhaseShifter::set_phase(double phase)
{
  this->phase = phase;
  phase_shifter = std::polar(1.0, phase);
}

size_t PhaseShifter::handle_input(size_t port, event_based::Message &message)
{
  message *= phase_shifter;
  return port;
}
