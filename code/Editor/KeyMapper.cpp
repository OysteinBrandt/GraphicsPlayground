#include "KeyMapper.h"

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // TODO: Make platform specific (ie. prefix this file win32_ and make other cpp files for other platforms)
#include <cassert> // TODO: Rewrite ?

#include "MenuChoise.h"

namespace input
{
	int KeyMapper::getKeyFor(int action) const
	{
		switch (action)
		{
			case MenuChoise::Accelerate:
				return VK_UP;
			case MenuChoise::RotateLeft:
				return VK_LEFT;
			case MenuChoise::RotateRight:
				return VK_RIGHT;
			case MenuChoise::CameraForward:
				return 'W';
			case MenuChoise::CameraBackward:
				return 'S';
			case MenuChoise::CameraLeft:
				return 'A';
			case MenuChoise::CameraRight:
				return 'D';
			case MenuChoise::MouseLButtonDown:
				return VK_LBUTTON;
			case MenuChoise::RKeyDown:
				return 'R';
			case MenuChoise::FKeyDown:
				return 'F';
		}

		assert(false);
		return MenuChoise::MAX;
	}

}
#elif __linux__
	#pragma warning Unknown I/O mapping semantics.
#elif defined(__APPLE__) && defined(__MACH__)
	#pragma warning Unknown I/O mapping semantics.
#endif