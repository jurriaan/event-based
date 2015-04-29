#include "neutron_beam_splitter.h"
using namespace event_based;
NeutronBeamSplitter::NeutronBeamSplitter(double alpha, double reflection)
  : BeamSplitter(alpha), reflection(reflection)
{
  setup_transformation_matrix();
}

NeutronBeamSplitter::NeutronBeamSplitter(double alpha, double reflection, InternalState initial_state)
  : BeamSplitter(alpha, initial_state), reflection(reflection)
{
  setup_transformation_matrix();
}

void NeutronBeamSplitter::setup_transformation_matrix()
{
  complex_type t(sqrt(1 - reflection), 0);
  complex_type r(0, sqrt(reflection));
  tr_matrix = ComplexMatrix();
  tr_matrix <<   t <<   r <<  0.0 <<  0.0 << arma::endr
            <<   r <<   t <<  0.0 <<  0.0 << arma::endr
            << 0.0 << 0.0 <<    t <<    r << arma::endr
            << 0.0 << 0.0 <<    r <<    t;
}
