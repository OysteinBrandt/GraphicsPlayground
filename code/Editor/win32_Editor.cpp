#include <Windows.h>
#include "IORedirect.h"
#include "Editor.h"

static bool running{ true };
HDC global_deviceContext;
int windowWidth{ 800 };
int windowHeight{ 600 };
Editor *global_editor = nullptr;

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
	case WM_CREATE:
	{
		OutputDebugStringA("WM_CREATE\n");
		PAINTSTRUCT paint;
		HDC deviceContext = BeginPaint(window, &paint);
		global_deviceContext = deviceContext;
		setupPixelFormat(deviceContext);
		HGLRC renderContext = wglCreateContext(deviceContext);
		wglMakeCurrent(deviceContext, renderContext);
	}break;

	case WM_SIZE:
	{
		OutputDebugStringA("WM_SIZE\n");
		windowWidth = LOWORD(lParam);
		windowHeight = HIWORD(lParam);
		glViewport(0, 0, windowWidth, windowHeight);
	}break;

	case WM_CLOSE:
	{
		// TODO: Handle this with a message to the user?
		OutputDebugStringA("WM_CLOSE\n");
		running = false;

		//// De-select the rendering context
		//wglMakeCurrent(hdc, NULL);
		//// Release the rendering context
		//wglDeleteContext(hrc);
		//// Release the device context
		//EndPaint(hwnd, &ps);
		//PostQuitMessage(0);
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
		//OutputDebugStringA("WM_PAINT\n");
		if (global_editor != nullptr)
			mainLoop(*global_editor, windowWidth, windowHeight);
		//PAINTSTRUCT paint;
		//HDC deviceContext = BeginPaint(window, &paint);
		//int x = paint.rcPaint.left;
		//int y = paint.rcPaint.top;
		//int width = paint.rcPaint.right - paint.rcPaint.left;
		//int height = paint.rcPaint.bottom - paint.rcPaint.top;
		//PatBlt(deviceContext, x, y, width, height, BLACKNESS);
		//EndPaint(window, &paint);
	}break;

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
		windowWidth,
		windowHeight,
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

	Editor editor;
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
			break;
		}

	}

	return 0;
	//return (int)message.wParam;
}