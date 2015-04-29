#include <armadillo>

#ifndef EVENTBASEDTYPES
#define EVENTBASEDTYPES

namespace event_based
{
  typedef std::complex<double> complex_type;
  typedef arma::cx_vec Message;
  typedef arma::vec Vector;
  typedef arma::cx_vec ComplexVector;
  typedef arma::cx_mat ComplexMatrix;
}

#endif
