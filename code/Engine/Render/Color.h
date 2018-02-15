#pragma once

#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Engine/Math/Vec3.h"

namespace render
{
  enum class Color
  {
    Red,
    Green,
    Blue
  };

  template <typename T>
  struct Color3
  {
    T r;
    T g;
    T b;
  };

  struct Color4
  {
    float r;
    float g;
    float b;
    float a;
  };
}

namespace color
{
  //static render::Color3<float> Red  { 1.f, 0.f, 0.f };
  //static render::Color3<float> Green{ 0.f, 1.f, 0.f };
  //static render::Color3<float> Blue { 0.f, 0.f, 1.f };
  static math::Vec3 Red  { 1.f, 0.f, 0.f };
  static math::Vec3 Green{ 0.f, 1.f, 0.f };
  static math::Vec3 Blue { 0.f, 0.f, 1.f };
}


#endif