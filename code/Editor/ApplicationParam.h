#pragma once

namespace details
{
  /**************************************************************/

  template<typename T>
  struct WindowSize
  {
    T startX;
    T startY;
    T width;
    T height;
  };

  /**************************************************************/

  struct Window
  {
    WindowSize<int> size{};
    bool hasFocus{ false };
  };

  /**************************************************************/

  struct Key
  {
    bool isDown{ false };

    bool operator()()
    {
      return isDown;
    }
  };

  /**************************************************************/

  struct Keyboard
  {
    Key W;
    Key A;
    Key S;
    Key D;
  };

  /**************************************************************/

  struct Mouse
  {
    int x{};
    int y{};
    int delta_x{};
    int delta_y{};
    bool leftButtonDown{ false };
    bool rightButtonDown{ false };

    bool isInside(const details::Window& /*window*/) const
    {
#if 1 // TODO: Remove this function if it turns out we do not need this check
      return true;
#else
      // This only makes sense to do if we do not retrieve mouse position in WM_MOUSEMOVE
      return (x > window.size.startX && x < (window.size.startX + window.size.width) &&
              y > window.size.startY && y < (window.size.startY + window.size.height));
#endif
    }

  };

  /**************************************************************/

  struct Input
  {
    Keyboard keyboard;
    Mouse mouse;
  };

  /**************************************************************/
}

struct ApplicationParam
{
  details::Input input;
  details::Window window;
};