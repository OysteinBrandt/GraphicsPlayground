#include "Vec3.h"
#include <sstream>
#include <iomanip>

namespace math
{
  std::ostream& Vec3::print(std::ostream &stream) const
  {
    stream << std::setprecision(1) << "(" << std::setw(5) << x << ", " << std::setw(5) << y << ", " << std::setw(5) << z << ")";
    return stream;
  }
}