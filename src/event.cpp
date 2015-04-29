#include "types.h"
#include "event_component.h"
#include "observer.h"
#include "count_observer.h"
#include "beam_splitter.h"
#include <boost/progress.hpp>


const size_t runs    = 500;
const size_t repeats = 200000;
const double p0      = 0.5;
const double PI      = 3.141592653589793238463;
using namespace event_based;
using namespace std;
int main ()
{
  event_based::BeamSplitter split(0.98);
  event_based::CountObserver obs(split, 0);
  std::random_device rd;
  std::mt19937_64 generator(rd());
  std::uniform_real_distribution<double> distribution;
  event_based::ComplexVector messages[2];
  boost::progress_display progress(runs, std::cerr);
  for (size_t i = 0; i < runs; ++i)
  {
    auto angle = distribution(generator) * 2 * PI;
    messages[0] = ComplexVector();
    messages[0] << cos(angle) << sin(angle);
    auto angle2 = distribution(generator) * 2 * PI;
    messages[1] = ComplexVector();
    messages[1] << cos(angle2) << sin(angle2);
    angle = (fmod(angle - angle2, 2 * PI));
    if (angle < 0)
      angle += 2*PI;
    angle *= 180.0/PI;

    for (size_t j = 0; j < repeats; ++j)
    {
      auto port = p0 > distribution(generator) ? 0 : 1;
      ComplexVector message = ComplexVector(messages[port]);
      split.process(port, message);
    }

    std::cout << angle << ", " << static_cast<double>(obs.count())/repeats << std::endl;
    obs.reset();
    ++progress;
  }
  cerr << "done\n";
}
