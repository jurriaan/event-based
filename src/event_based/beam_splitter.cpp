#include "beam_splitter.h"
#include <random>
using namespace event_based;

BeamSplitter::BeamSplitter(double alpha)
  : EventComponent(), alpha(alpha), tr_matrix(), rd(), generator(rd()), distribution(0.0, 1.0)
{
  state = random_state();
  setup_transformation_matrix();
}

BeamSplitter::BeamSplitter(double alpha, InternalState initial_state)
  : EventComponent(), alpha(alpha), state(initial_state), tr_matrix(), rd(), generator(rd()), distribution(0.0, 1.0)
{
  setup_transformation_matrix();
}

inline size_t BeamSplitter::handle_input(size_t port, event_based::Message &message)
{
  state = state * alpha;
  state[port] += (1 - alpha);
  auto vec = input_vector();
  vec = tr_matrix * vec;
  auto output = random_step(vec);

  message = arma::normalise(ComplexVector({vec[0 + output], vec[2 + output]}));

  return output;
}

inline size_t BeamSplitter::random_step(ComplexVector vec)
{
  auto first = std::abs(vec[1]);
  auto sec = std::abs(vec[3]);
  auto z = first * first + sec * sec;
  auto r = distribution(generator);
  return z > r ? 1 : 0;
}

inline InternalState BeamSplitter::random_state()
{
  double total = distribution(generator);
  double part = distribution(generator);

  return { total * part, total *(1 - part) };
}

inline InputVector BeamSplitter::input_vector() const
{
  auto s0 = sqrt(state[0]);
  auto s1 = sqrt(state[1]);

  return { last_message[0][0] * s0,
           last_message[1][0] * s1,
           last_message[0][1] * s0,
           last_message[1][1] * s1 };
}

void BeamSplitter::setup_transformation_matrix()
{
  tr_matrix = ComplexMatrix();
  tr_matrix << 1.0 <<  0.0 <<  0.0 << -1.0 << arma::endr
            << 0.0 <<  1.0 << -1.0 <<  0.0 << arma::endr
            << 0.0 <<  1.0 <<  1.0 <<  0.0 << arma::endr
            << 1.0 <<  0.0 <<  0.0 <<  1.0;
  tr_matrix *= pow(0.5, 0.5);
}
