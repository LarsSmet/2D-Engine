#pragma once
#include "windows.h"
#include <iostream>
#include "GameObject.h"
//#include "PlayerComponent.h"

#include "SoundSystem.h"
//#include "PhysicsComponent.h"

namespace dae
{

	class Command
	{
	public:

		virtual ~Command() = default;
		virtual void Execute() = 0;

	};

}