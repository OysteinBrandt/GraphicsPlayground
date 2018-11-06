#include <Windows.h>
#include <Windowsx.h>
#include "IORedirect.h"
#include "Editor/Editor.h"
#include <iostream>

static bool global_running{ true };
HDC global_deviceContext;
Editor *global_editor = nullptr;
ApplicationParam global_applicationParam;

void setupPixelFormat(HDC deviceContext)
{
  PIXELFORMATDESCRIPTOR pixelFormatDescriptor{};
  pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pixelFormatDescriptor.nVersion = 1;
  pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
  pixelFormatDescriptor.cColorBits = 32; // TODO: Check that this works, 24 instead?
  pixelFormatDescriptor.cDepthBits = 24; // TODO: Specifies the depth of the depth (z-axis) buffer, 16 instead?

  // TODO: Proper logging of results
  const int format = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
  if (format == 0)
    std::cerr << "ChoosePixelFormat failed\n";

  if (SetPixelFormat(deviceContext, format, &pixelFormatDescriptor) == FALSE)
    std::cerr << "SetPixelFormat failed\n";
}

void mainLoop()
{
  try
  {
    global_editor->update();
  }
  catch (const std::exception& e)
  {
    const std::string when{ "Exception caught during update loop:\n" };
    OutputDebugStringA(when.c_str());
    OutputDebugStringA(e.what());
    std::cout << when << e.what() << std::endl;
    DebugBreak();
  }

  try
  {
    global_editor->render(static_cast<float>(global_applicationParam.window.size.width),
      static_cast<float>(global_applicationParam.window.size.height));
  }
  catch (const std::exception& e)
  {
    const std::string when{ "Exception caught during render loop:\n" };
    OutputDebugStringA(when.c_str());
    OutputDebugStringA(e.what());
    std::cout << when << e.what() << std::endl;
    DebugBreak();
  }

  SwapBuffers(global_deviceContext);
}

void keyEvent(unsigned int key, bool isPressed)
{
  if (key == 'W')
    global_applicationParam.input.keyboard.W.isDown = isPressed;
  else if (key == 'A')
    global_applicationParam.input.keyboard.A.isDown = isPressed;
  else if (key == 'S')
    global_applicationParam.input.keyboard.S.isDown = isPressed;
  else if (key == 'D')
    global_applicationParam.input.keyboard.D.isDown = isPressed;
}

LRESULT CALLBACK
mainWindowCallback(HWND window,
  UINT message,
  WPARAM wParam,
  LPARAM lParam)
{
  LRESULT result{ 0 };
  switch (message)
  {
  case WM_MOVE:
  {
    global_applicationParam.window.size.startX = LOWORD(lParam);
    global_applicationParam.window.size.startY = HIWORD(lParam);
  }break;

  case WM_CREATE:
  {
    PAINTSTRUCT paint;
    HDC deviceContext = BeginPaint(window, &paint);
    global_deviceContext = deviceContext;
    setupPixelFormat(deviceContext);
    HGLRC renderContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderContext);
  }break;

  case WM_SIZE:
  {
    global_applicationParam.window.size.width = LOWORD(lParam);
    global_applicationParam.window.size.height = HIWORD(lParam);
    glViewport(0, 0, global_applicationParam.window.size.width, global_applicationParam.window.size.height);
  }break;

  case WM_CLOSE:
  {
    // TODO: Handle this with a message to the user?
    global_running = false;
  } break;

  case WM_ACTIVATEAPP:
  {
    global_applicationParam.window.hasFocus = !global_applicationParam.window.hasFocus;
  }break;

  case WM_DESTROY:
  {
    OutputDebugStringA("WM_DESTROY\n");
    // TODO: Handle this as an error - recreate window?
    global_running = false;
  }break;

  case WM_ERASEBKGND:
  {
    // Do nothing as our default result is 0.
  }break;

  case WM_PAINT:
  {
    if (global_editor != nullptr)
      mainLoop();
  }break;

#pragma region Input
  case WM_SYSKEYDOWN:
  case WM_SYSKEYUP:
  {}break;
  case WM_KEYDOWN:
  {
    // TODO: Make sure that key press is interpreted correctly after window manipulation.
    // Consider resetting input between each update
    keyEvent(wParam, true);
  }break;
  case WM_KEYUP:
  {
    keyEvent(wParam, false);
  }break;

  case WM_LBUTTONDOWN:
  {
    global_applicationParam.input.mouse.leftButtonDown = true;
  }break;

  case WM_LBUTTONUP:
  {
    global_applicationParam.input.mouse.leftButtonDown = false;
  }break;

  case WM_MOUSEMOVE:
  {
    // TODO: Consider replacing #include <Windowsx.h> and retrieve mouse input differently.
    global_applicationParam.input.mouse.x = GET_X_LPARAM(lParam);
    global_applicationParam.input.mouse.y = GET_Y_LPARAM(lParam);
    switch (wParam)
    {
    case MK_LBUTTON:
    {
    }break;

    case MK_CONTROL:
    case MK_MBUTTON:
    case MK_RBUTTON:
    case MK_SHIFT:
    case MK_XBUTTON1:
    case MK_XBUTTON2:
    {

    }break;

    default:
      break;
    }
  }
#pragma endregion


  default:
    result = DefWindowProc(window, message, wParam, lParam);
    break;
  }

  return result;
}

int CALLBACK
WinMain(HINSTANCE instance,
  HINSTANCE /*hPrevInstance*/,
  LPSTR /*lpCmdLine*/,
  int nCmdShow)
{
  redirectIOToConsole();

  WNDCLASSEX windowClass = {};

  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = mainWindowCallback;
  windowClass.hInstance = instance;
  windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  windowClass.lpszMenuName = NULL;
  windowClass.lpszClassName = "GraphicsPlaygroundEditorWindowClass";
  windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&windowClass))
  {
    // TODO: Logging
    MessageBoxA(NULL, "Failed to register window class!", "Error", MB_ICONERROR);

    return 1;
  }

  HWND windowHandle = CreateWindowEx(
    0,
    windowClass.lpszClassName,
    "Editor",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    0,
    0,
    instance,
    0);

  if (!windowHandle)
  {
    // TODO: Logging
    MessageBoxA(NULL, "Failed to create window!", "Error", MB_ICONERROR);
    return 1;
  }

  ShowWindow(windowHandle, nCmdShow);
  UpdateWindow(windowHandle);

  RECT window;
  GetWindowRect(windowHandle, &window);

  global_applicationParam.window.size.startX = window.left;
  global_applicationParam.window.size.startY = window.top;
  global_applicationParam.window.size.width = window.right - window.left;
  global_applicationParam.window.size.height = window.bottom - window.top;

  try
  {
    static Editor editor{ global_applicationParam };
    global_editor = &editor;	// TODO: Fix, could be usable even though exception occured
  }
  catch (const std::exception &e)
  {
    const std::string when{ "Exception caught during construction:\n" };
    OutputDebugStringA(when.c_str());
    OutputDebugStringA(e.what());
    std::cout << when << e.what() << std::endl;
    DebugBreak();
  }

  while (global_running)
  {
    MSG message;
    BOOL messageResult = PeekMessage(&message, 0, 0, 0, PM_REMOVE);
    if (messageResult > 0)
    {
      //mainLoop(editor, windowWidth, windowHeight);
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
    else
    {
      // TODO: Handle -1 return error?
      //return (int)message.wParam;
      break;
    }
  }

  return 0;
}