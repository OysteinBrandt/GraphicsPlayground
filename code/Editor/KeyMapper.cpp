#include "KeyMapper.h"

#if defined _WIN32 || defined __CYGWIN__
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
		}

		assert(false);
		return MenuChoise::MAX;
	}

}
#else
	#if __GNUC__ >= 4
	#else
	#pragma warning Unknown I/O mapping semantics.
	#endif
#endif