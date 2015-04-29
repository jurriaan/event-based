#include "beam_splitter.h"

#ifndef EVENTBASEDNEUTRONBEAMSPLITTER
#define EVENTBASEDNEUTRONBEAMSPLITTER

namespace event_based
{
  class NeutronBeamSplitter : public BeamSplitter
  {
      double reflection;

    public:
      explicit NeutronBeamSplitter(double alpha = 0.98, double reflection = 0.2);
      explicit NeutronBeamSplitter(double alpha, double reflection, InternalState initial_state);

    protected:
      void setup_transformation_matrix() override;
  };
}

#endif
