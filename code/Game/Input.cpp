#include "Input.h"
#include "SDL_events.h"

#include <iostream>

namespace obr {

Input::Input()
{
}


Input::~Input()
{
}

bool Input::handleEvents(int &clip)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return false;

		if (event.type == SDL_MOUSEMOTION)
			std::cout << "mouse pos: (" << event.motion.x << ", " << event.motion.y << ")" << std::endl;

		if (event.type == SDL_MOUSEBUTTONDOWN)
			break;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				clip = 0;
				break;

			case SDLK_2:
				clip = 1;
				break;

			case SDLK_3:
				clip = 2;
				break;

			case SDLK_4:
				clip = 3;
				break;

			case SDLK_ESCAPE:
				return false;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
			return false;
	}

	return true;
}

}