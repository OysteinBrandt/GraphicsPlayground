#pragma once

namespace obr {

	class Input
	{
	public:
		Input();
		~Input();

	public:

		bool handleEvents(int &clip);
	};

}