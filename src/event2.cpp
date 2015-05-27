#include "event_based/types.h"
#include "event_based/event_component.h"
#include "event_based/observer.h"
#include "event_based/count_observer.h"
#include "event_based/connect_observer.h"
#include "event_based/phase_shifter.h"
#include "event_based/neutron_beam_splitter.h"
#include <boost/progress.hpp>

using namespace event_based;
using namespace std;
const size_t runs = 100;
const size_t repeats = 10000000;
const double PI = 3.141592653589793238463;
const double alpha = 0.99;
const Message input = {{0.5,0.5},{0.5,0.5}};


int main ()
{
  std::random_device rd;
  std::mt19937_64 generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 2* PI);
  NeutronBeamSplitter bs0(alpha);
  NeutronBeamSplitter bs1(alpha);
  NeutronBeamSplitter bs2(alpha);
  NeutronBeamSplitter bs3(alpha);
  PhaseShifter xi0;
  PhaseShifter xi1;
  CountObserver obs1(bs3, 0);
  CountObserver obs2(bs3, 1);

  bs0(0) + bs1(0);
  bs1(1) + xi0(0);
  xi0(0) + bs3(1);

  bs0(1) + bs2(1);
  bs2(0) + xi1(0);
  xi1(0) + bs3(0);

  boost::progress_display progress(runs, std::cerr);

  for (size_t i = 0; i < runs; ++i)
  {
    auto angle = distribution(generator);
    xi0.set_phase(angle);
    auto angle2 = distribution(generator);
    xi1.set_phase(angle2);

    angle = (fmod(angle - angle2, 2 * PI));
    if(angle < 0)
      angle += 2*PI;
    angle *= 180.0/PI;

    Message message;
    for (size_t j = 0; j < repeats; ++j)
    {
      message = input;
      bs0.process(0, message);
    }

    std::cout << angle << ", " << obs1.count() << ", " << obs2.count() << std::endl;
    obs1.reset();
    obs2.reset();
    ++progress;
  }

  cerr << "done\n";
}
