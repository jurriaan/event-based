#include "event_component.h"

#ifndef EVENTBASEDBEAMSPLITTER
#define EVENTBASEDBEAMSPLITTER

namespace event_based
{
  typedef Vector InternalState;
  typedef ComplexVector InputVector;
  class BeamSplitter : public EventComponent<2, 2>
  {
      double alpha;
      InternalState state;
      std::random_device rd;
      std::mt19937_64 generator;
      std::uniform_real_distribution<double> distribution;

    public:
      explicit BeamSplitter(double alpha = 0.98);
      explicit BeamSplitter(double alpha, InternalState initial_state);
      size_t handle_input(size_t port, event_based::Message &message) override;

    protected:
      ComplexMatrix tr_matrix;
      virtual void setup_transformation_matrix();

    private:
      InternalState random_state();
      InputVector input_vector() const;
      size_t random_step(ComplexVector vector);
  };
}

#endif
