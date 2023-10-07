#pragma once
#include "windows.h" 
#include "Command.h"
#include <utility>
#include <map>
#include <memory>
#include "Singleton.h"
#include "Command.h"
#include <vector>


namespace dae
{

	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		ArrowUp = 0x0001,
		ArrowDown = 0x0002,
		ArrowLeft = 0x0004,
		ArrowRight = 0x0008,
		

		Start = 0x0010,
		Back = 0x0020,
		
		None = 0,
	};



	enum class ActionState
	{
		Up,
		Down,
		Hold
		

	};

	struct ControllerAction //got some help from Laurens Krikilion for the controlleraction part
	{
		ActionState state{};
		ControllerButton button{};
		int controllerIndex = 0;

	

		bool operator<(const ControllerAction& lhs) const //https://stackoverflow.com/questions/41911931/operator-overloading-of-c-stl-map-with-custom-classes
		{
			return std::tie(state, button, controllerIndex) < std::tie(lhs.state, lhs.button, lhs.controllerIndex);
		}
	};

	struct KeyBoardAction 
	{
		ActionState state{};
		SDL_Scancode key{};

		bool operator<(const KeyBoardAction& lhs) const
		{
			return std::tie(state, key) < std::tie(lhs.state, lhs.key);
		}

	};



	class InputManager final : public Singleton<InputManager>
	{

		
		
		using ControllerCommandsMap = std::map<ControllerAction, std::shared_ptr<Command>>;
		using KeyBoardCommandsMap = std::map<KeyBoardAction, std::shared_ptr<Command>>;


	public:

		InputManager();
		~InputManager();


		bool ProcessInput();
	
		
		void HandleControllerInput(int currentController);
		void HandleKeyBoardInput();
		void BindKey(ControllerAction key, std::shared_ptr<Command> command);
		void BindKey(KeyBoardAction key, std::shared_ptr<Command> command);

		void ClearInputCommands();
		

	private:

		class Impl;
		std::unique_ptr<Impl> m_Impl;

		bool IsUpThisFrame(unsigned int button,  int currentController) const;
		bool IsDownThisFrame(unsigned int button,  int currentController) const;
		bool IsHeld(unsigned int button,  int currentController) const;

		bool IsUpThisFrame(SDL_Keycode key) const;
		bool IsDownThisFrame(SDL_Keycode key) const;
		bool IsHeld(SDL_Keycode key) const;
	};



}