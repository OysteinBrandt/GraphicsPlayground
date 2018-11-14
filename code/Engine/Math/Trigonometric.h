#pragma once

#ifndef _ENGINE_TRIGONOMETRIC_H_
#define _ENGINE_TRIGONOMETRIC_H_

#include "Constants.h"
#include "Engine/Utilities/TypeTraits.h"

namespace math {

  using Degrees = NamedType<float, struct DegreeTag, Printable, Assignment, Comparison, Arithmetic>;
  using Radians = NamedType<float, struct RadianTag, Printable, Assignment, Comparison, Arithmetic>;

  constexpr Radians to_radians(const Degrees& degrees)
  {
    return Radians(degrees.get() * PI / 180.f);
  }

}

constexpr math::Degrees operator "" _degrees(long double d)
{
  return math::Degrees(static_cast<float>(d));
}

#endif