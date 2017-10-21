#pragma once

#include "Input.h"
#include "Engine.h"

#include <memory>
#include <iostream>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

namespace obr
{
	class Application
	{
	private:
		
		const int SCREEN_WIDTH  = 640;
		const int SCREEN_HEIGHT = 480;
		int m_clip;

		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		Engine m_engine;

		Input m_input;

		std::vector<SDL_Texture*> m_textures;

	public:

		DllExport Application();
		DllExport ~Application();

		DllExport int start();

	private:

		void logSDLError(std::ostream &os, const std::string &msg);
		
		SDL_Texture* loadTexture(const std::string &filePath, SDL_Renderer *renderer);
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);
		void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);

		void renderSDLStuff();
		void setWindowIcon(SDL_Window *window, const std::string iconPath);
	};
}