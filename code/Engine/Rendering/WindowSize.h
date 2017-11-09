#pragma once

namespace engine::render
{
	template<typename T>
	struct WindowSize
	{
		T startX;
		T startY;
		T width;
		T height;
	};
}