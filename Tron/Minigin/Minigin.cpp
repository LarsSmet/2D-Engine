#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include <chrono>
#include <memory>

#include "TextComponent.h"
#include "Font.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
//#include "PlayerComponent.h"


#include "SoundSystem.h"



using namespace std;
namespace dae
{

	

	void PrintSDLVersion()
	{
		SDL_version compiled{};
		SDL_version linked{};

		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);
		printf("We compiled against SDL version %d.%d.%d ...\n",
			compiled.major, compiled.minor, compiled.patch);
		printf("We are linking against SDL version %d.%d.%d.\n",
			linked.major, linked.minor, linked.patch);


	}

	void dae::Minigin::Initialize()
	{
		PrintSDLVersion();
		ResourceManager::GetInstance().Init("../Data/");
		SceneManager::GetInstance();

#if _DEBUG
		ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDLSoundSystem()));
#else
		ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		m_Window = SDL_CreateWindow(
			"Programming 4 assignment",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			480,
			653,
			SDL_WINDOW_OPENGL
		);
		if (m_Window == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		Renderer::GetInstance().Init(m_Window);
	}


	void dae::Minigin::Cleanup()
	{
		Renderer::GetInstance().Destroy();
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
		SDL_Quit();
	}

	void dae::Minigin::Run()
	{


			dae::InputManager& inputManager = dae::InputManager::GetInstance();

			auto& renderer = Renderer::GetInstance();
			auto& sceneManager = SceneManager::GetInstance();
		
			auto lastTime = chrono::high_resolution_clock::now();
			//float lag = 0.0f;

			//float fixedTimeStep = 0.02f;
			

			bool doContinue = true;

			//gameloop
			while (doContinue)
			{
				const auto currentTime = chrono::high_resolution_clock::now();
				float deltaTime = chrono::duration<float>(currentTime - lastTime).count(); //time diffrence between frames

				lastTime = currentTime;
				//lag += deltaTime;

				doContinue = inputManager.ProcessInput();
			
				//while (lag >= MsPerFrame) //only called every MSPerFrame(16)
				//{
				//	FixedUpdate(fixedTimeStep);
				//	lag -= fixedTimeStep;
				//}


				sceneManager.Update(deltaTime);
				renderer.Render();




			

			}



		

		ServiceLocator::DeleteSoundSystem();



		Cleanup();
	}

	//void dae::Minigin::FixedUpdate(float fixedTimeStep)
	//{
	//	//should call fixedupdate on gameobjects in scene but i didn't implement it
	//	fixedTimeStep;
	//}

}