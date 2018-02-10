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
    Key D;
    Key S;
  };

  /**************************************************************/

  struct Mouse
  {
    int x;
    int y;
    bool leftButtonDown;
    bool rightButtonDown;

    bool isInside(const details::Window& window) const
    {
      return (x > window.size.startX && x < (window.size.startX + window.size.width) &&
              y > window.size.startY && y < (window.size.startY + window.size.height));
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