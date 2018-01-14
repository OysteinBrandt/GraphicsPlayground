
#include "Mat3.h"
#include <cmath>

// TODO (obr): Replace cassert with platform independent assert
#include <cassert>

namespace math {

  Mat3 Mat3::rotate(float radians, Mat3::Axis axis)
  {
    auto cosine = cos(radians);
    auto sine = sin(radians);

    switch (axis)
    {
    case Mat3::Axis::X:
      assert("Not implemented!");
      return Mat3();
      break;

    case Mat3::Axis::Y:
      assert("Not implemented!");
      return Mat3();
      break;

    case Mat3::Axis::Z:
      return Mat3{ cosine,  -sine, 0,
                     sine, cosine, 0,
                        0,      0, 1 };
      break;

    default:
      assert("Not a valid axis!");
      return Mat3();
      break;
    }
  }

}