#include <Windows.h>
//#include <Windowsx.h>
#include "IORedirect.h"
#include "Editor.h"
#include <Rendering/WindowSize.h>
#include <iostream>

static bool global_running{ true };
HDC global_deviceContext;
Editor *global_editor = nullptr;
engine::render::WindowParam global_windowInfo;

void setupPixelFormat(HDC deviceContext)
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor{};
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24; // TODO: Check that this works, may be 32 instead
	pixelFormatDescriptor.cDepthBits = 16; // TODO: Specifies the depth of the depth (z-axis) buffer
	const int format = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
	SetPixelFormat(deviceContext, format, &pixelFormatDescriptor);
}

void mainLoop()
{
	try
	{
		global_editor->update();
		global_editor->render(static_cast<float>(global_windowInfo.size.width), 
													static_cast<float>(global_windowInfo.size.height));
	}
	catch (const std::exception &e)
	{
		// TODO: Handle exception
		OutputDebugStringA("Exception caught during game loop:\n");
		OutputDebugStringA(e.what());
		std::cout << "Exception caught during game loop:\n" << e.what() << std::endl;
		DebugBreak();
	}
	SwapBuffers(global_deviceContext);
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
		global_windowInfo.size.startX = LOWORD(lParam);
		global_windowInfo.size.startY = HIWORD(lParam);
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
		global_windowInfo.size.width = LOWORD(lParam);
		global_windowInfo.size.height = HIWORD(lParam);
		glViewport(0, 0, global_windowInfo.size.width, global_windowInfo.size.height);
	}break;

	case WM_CLOSE:
	{
		// TODO: Handle this with a message to the user?
		global_running = false;
	} break;

	case WM_ACTIVATEAPP:
	{
		global_windowInfo.hasFocus = !global_windowInfo.hasFocus;
	}break;

	case WM_DESTROY:
	{
		OutputDebugStringA("WM_DESTROY\n");
		// TODO: Handle this as an error - recreate window?
		global_running = false;
	}break;

	case WM_PAINT:
	{
		if (global_editor != nullptr)
			mainLoop();
	}break;

#pragma region Input
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		if (wParam == 'W')
		{

		}
		else if (wParam == 'A') {}
		else if (wParam == 'S') {}
		else if (wParam == 'D') {}
	}break;

	case WM_MOUSEMOVE:
	{
		switch (wParam)
		{
		case MK_LBUTTON:
		{
			// TODO: Consider replacing #include <Windowsx.h> and retrieve mouse input differently.
			//int mouseX = GET_X_LPARAM(lParam);
			//int mouseY = GET_Y_LPARAM(lParam);
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
	windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
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
		MessageBoxA(NULL, "Call to RegisterClassEx failed!", "Win32 Guided Tour", NULL);

		return 1;
	}

	HWND windowHandle = CreateWindowEx(
		0,
		windowClass.lpszClassName,
		"Editor",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
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
		MessageBoxA(NULL, "Call to CreateWindow failed!", "Win32 Guided Tour", NULL);
		return 1;
	}

	ShowWindow(windowHandle, nCmdShow);
	UpdateWindow(windowHandle);

	RECT window;
	GetWindowRect(windowHandle, &window);

	global_windowInfo.size.startX = window.left;
	global_windowInfo.size.startY = window.top;
	global_windowInfo.size.width  = window.right - window.left;
	global_windowInfo.size.height = window.bottom - window.top;

	try
	{
		static Editor editor{ global_windowInfo };
		global_editor = &editor;
	}
	catch (const std::exception &e)
	{
		// TODO: Handle exception
		OutputDebugStringA("Exception caught during construction:\n");
		OutputDebugStringA(e.what());
		std::cout << "Exception caught during construction:\n" << e.what() << std::endl;
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