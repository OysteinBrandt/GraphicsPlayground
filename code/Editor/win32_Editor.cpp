#include <Windows.h>
#include <Windowsx.h>
#include "IORedirect.h"
#include "Editor.h"
#include <Rendering/WindowSize.h>

static bool running{ true };
HDC global_deviceContext;
Editor *global_editor = nullptr;
engine::render::WindowSize<int> global_windowSize{};

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

void mainLoop(Editor &editor, int width, int height)
{
	try
	{
		editor.update();
		editor.render(static_cast<float>(width), static_cast<float>(height));
	}
	catch (...)
	{
		// TODO: Handle exception
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
		global_windowSize.startX = LOWORD(lParam);
		global_windowSize.startY = HIWORD(lParam);
	}break;

	case WM_CREATE:
	{
		PAINTSTRUCT paint;
		HDC deviceContext = BeginPaint(window, &paint);
		//int x = paint.rcPaint.left;
		//int y = paint.rcPaint.top;
		//int width = paint.rcPaint.right - paint.rcPaint.left;
		//int height = paint.rcPaint.bottom - paint.rcPaint.top;
		global_deviceContext = deviceContext;
		setupPixelFormat(deviceContext);
		HGLRC renderContext = wglCreateContext(deviceContext);
		wglMakeCurrent(deviceContext, renderContext);
	}break;

	case WM_SIZE:
	{
		global_windowSize.width = LOWORD(lParam);
		global_windowSize.height = HIWORD(lParam);
		glViewport(0, 0, global_windowSize.width, global_windowSize.height);
	}break;

	case WM_CLOSE:
	{
		// TODO: Handle this with a message to the user?
		running = false;
	} break;

	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
	}break;

	case WM_DESTROY:
	{
		OutputDebugStringA("WM_DESTROY\n");
		// TODO: Handle this as an error - recreate window?
		running = false;
	}break;

	case WM_PAINT:
	{
		if (global_editor != nullptr)
			mainLoop(*global_editor, global_windowSize.width, global_windowSize.height);
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
			int mouseX = GET_X_LPARAM(lParam);
			int mouseY = GET_Y_LPARAM(lParam);
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

	//global_windowSize.width = 800;
	//global_windowSize.height = 600;

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

	global_windowSize.startX = window.left;
	global_windowSize.startY = window.top;
	global_windowSize.width  = window.right - window.left;
	global_windowSize.height = window.bottom - window.top;

	Editor editor{ global_windowSize };
	global_editor = &editor;
	while (running)
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