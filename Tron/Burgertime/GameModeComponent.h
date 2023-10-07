#pragma once
#include "BaseComponent.h" 
#include "Observer.h" 

namespace dae
{

	class GameModeComponent final : public BaseComponent, public Observer
	{

	public:
		GameModeComponent(GameObject* go);
		~GameModeComponent();

		void Update(float elapsedSec);

		void onNotify(Event event) override;

	private:

	};

}