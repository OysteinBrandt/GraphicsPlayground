#pragma once

namespace input::MenuChoise
{
	enum MenuChoise
	{
		CameraForward =				0x00000001,
		CameraBackward =			0x00000002,
		CameraLeft =					0x00000004,
		CameraRight =					0x00000008,
		Accelerate =					0x00000010,
		RotateLeft =					0x00000020,
		RotateRight =					0x00000040,
		MouseLButtonDown =		0x00000080,
		RKeyDown =						0x00000100,
		FKeyDown =						0x00000200,
		MAX =									0x00000400
	};
}