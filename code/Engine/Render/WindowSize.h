#pragma once

namespace engine::render
{
  namespace details
  {
    template<typename T>
    struct WindowSize
    {
      T startX;
      T startY;
      T width;
      T height;
    };
  }

  struct WindowParam
  {
    details::WindowSize<int> size{};
    bool hasFocus{ false };
  };
}