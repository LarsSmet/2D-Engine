#pragma once
#include "Command.h"

struct SDL_Window;
namespace dae
{
	

	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
		//void FixedUpdate(float fixedTimeStep);


	private:
		static const int MsPerFrame = 16; //  1sec/60 = 16 ms
		SDL_Window* m_Window{};



	};
}