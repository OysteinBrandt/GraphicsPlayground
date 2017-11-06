#include <Windows.h>

static bool running{ true };


void setPixelFormat(HDC deviceContext)
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor{};
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24; // TODO: Check that this works, may be 32 instead
	pixelFormatDescriptor.cRedBits = 0;
	pixelFormatDescriptor.cRedShift = 0;
	pixelFormatDescriptor.cGreenBits = 0;
	pixelFormatDescriptor.cGreenShift = 0;
	pixelFormatDescriptor.cBlueBits = 0;
	pixelFormatDescriptor.cBlueShift = 0;
	pixelFormatDescriptor.cAlphaBits = 0;
	pixelFormatDescriptor.cAlphaShift = 0;
	pixelFormatDescriptor.cAccumBits = 0;
	pixelFormatDescriptor.cAccumRedBits = 0;
	pixelFormatDescriptor.cAccumGreenBits = 0;
	pixelFormatDescriptor.cAccumBlueBits = 0;
	pixelFormatDescriptor.cAccumAlphaBits = 0;
	pixelFormatDescriptor.cDepthBits = 16; // TODO: Specifies the depth of the depth (z-axis) buffer
	pixelFormatDescriptor.cStencilBits = 0;
	pixelFormatDescriptor.cAuxBuffers = 0;
	pixelFormatDescriptor.iLayerType = 0;
	pixelFormatDescriptor.bReserved = 0;
	pixelFormatDescriptor.dwLayerMask = 0;
	pixelFormatDescriptor.dwVisibleMask = 0;
	pixelFormatDescriptor.dwDamageMask = 0;

	const int format = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
	SetPixelFormat(deviceContext, format, &pixelFormatDescriptor);
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
	}break;

	case WM_SIZE:
	{
		OutputDebugStringA("WM_SIZE\n");
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
		// TODO: Handle this as an error - recreate window?
		running = false;
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		/*HDC deviceContext =*/ BeginPaint(window, &paint);
		//int x = paint.rcPaint.left;
		//int y = paint.rcPaint.top;
		//int width = paint.rcPaint.right - paint.rcPaint.left;
		//int height = paint.rcPaint.bottom - paint.rcPaint.top;

		//PatBlt(deviceContext, x, y, width, height, BLACKNESS);
		//TextOutA(deviceContext, width / 2, height / 2, "OMG lulz!", 9);

		EndPaint(window, &paint);
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
	WNDCLASSEX windowClass = {};

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	windowClass.lpfnWndProc = mainWindowCallback;
	windowClass.hInstance = instance;
	//windowClass.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_APPLICATION));
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "GraphicsPlaygroundEditorWindowClass";
	//windowClass.hIconSm = LoadIcon(windowClass.instance, MAKEINTRESOURCE(IDI_APPLICATION));

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

	while (running)
	{
		MSG message;
		BOOL messageResult = messageResult = GetMessage(&message, 0, 0, 0);
		if (messageResult > 0)
		{
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