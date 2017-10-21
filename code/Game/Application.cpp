
#include "Application.h"
#include "SDL.h"

#include <iostream>

namespace obr
{
/**************************************************************************************/

Application::Application() : m_clip{0}
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		logSDLError(std::cout, "SDL_Init");

	/* 
		On Apple's OS X you must set the NSHighResolutionCapable Info.plist property to YES, 
		otherwise you will not receive a High DPI OpenGL canvas. 
	*/

	//SDL_Rect displaySize{};
	//if (SDL_GetDisplayBounds(0, &displaySize) != 0)
	//	logSDLError(std::cout, "SDL_GetDisplayBounds");

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
	m_window = SDL_CreateWindow("Graphics playground", 700, 250, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
	if (!m_window)
	{
		logSDLError(std::cout, "SDL_CreateWindow");
		return;
	}

	const std::string icoPath = "D:/src/GraphicsPlayground/Resources/Icons/app.ico";
	setWindowIcon(m_window, icoPath);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer)
	{
		SDL_DestroyWindow(m_window);
		logSDLError(std::cout, "SDL_CreateRenderer");
		return;
	}

	const std::string imagePath = "D:/src/GraphicsPlayground/Resources/Textures/sprite_sheet.bmp";
	//const std::string imagePath = "D:/src/GraphicsPlayground/Resources/Textures/UV-24-bit.bmp";
	//const std::string imagePath = "D:/src/GraphicsPlayground/Resources/Textures/background.bmp";
	//const std::string imagePath2 = "D:/src/GraphicsPlayground/Resources/Textures/smiley.bmp";

	m_textures.push_back( loadTexture(imagePath, m_renderer) );
	//m_textures.push_back( loadTexture(imagePath2, m_renderer) );
}

/**************************************************************************************/

Application::~Application()
{
	for (auto *tex : m_textures)
		SDL_DestroyTexture(tex);

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

/**************************************************************************************/

int Application::start()
{
	if (!m_window || !m_renderer)
		return 1;

	while (true)
	{
		if (!m_input.handleEvents(m_clip))
			break;
		
		renderSDLStuff();

		m_engine.update();
		m_engine.render();
	
	}

	return 0;
}

/**************************************************************************************/

void Application::logSDLError(std::ostream &os, const std::string &msg) 
{
	os << msg.c_str() << " error: " << SDL_GetError() << std::endl;
}

/**************************************************************************************/

SDL_Texture* Application::loadTexture(const std::string &filePath, SDL_Renderer *renderer) 
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(filePath.c_str());
	if (loadedImage != nullptr) 
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		
		if (texture == nullptr) 
			logSDLError(std::cout, "CreateTextureFromSurface");
	}
	else
		logSDLError(std::cout, "LoadBMP");

	return texture;
}

/**************************************************************************************/

void Application::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip)
{
	SDL_RenderCopy(renderer, texture, clip, &dst);
}

/**************************************************************************************/

void Application::renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect dst{x, y, 0, 0};
	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else 
		SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);

	renderTexture(texture, renderer, dst, clip);
}

/**************************************************************************************/

void Application::renderSDLStuff()
{
	SDL_SetRenderDrawColor(m_renderer, 55, 55, 55, 55);
	SDL_RenderClear(m_renderer);

	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(m_renderer, &outlineRect);


	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(m_renderer, SCREEN_WIDTH / 2, i);
	}

	int iW = 100, iH = 100;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	SDL_Rect clips[4];
	for (int i = 0; i < 4; ++i)
	{
		clips[i].x = i / 2 * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
	}

	renderTexture(m_textures[0], m_renderer, x, y, &clips[m_clip]);

	SDL_RenderPresent(m_renderer);
}

void Application::setWindowIcon(SDL_Window *window, const std::string iconPath)
{
	/*
	Uint16 pixels[16 * 16] = {  // ...or with raw pixel data:
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
		0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
		0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
		0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
		0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
		0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
		0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
		0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
		0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
		0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
		0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
		0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
		0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
		0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
		0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
		0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
		0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
		0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
		0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
		0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
		0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
	};
	SDL_Surface *loadedIcon = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000);
	*/
	SDL_Surface *loadedIcon = SDL_LoadBMP(iconPath.c_str());
	if (!loadedIcon)
		logSDLError(std::cout, "SDL_LoadBMP");
	else
	{
		SDL_SetWindowIcon(window, loadedIcon);
		SDL_FreeSurface(loadedIcon);
	}
}

}