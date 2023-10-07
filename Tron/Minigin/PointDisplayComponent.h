#pragma once
#include "BaseComponent.h"
#include "Observer.h"
//#include "PlayerComponent.h"

namespace dae
{

	class TextComponent;

	class PointsDisplayComponent final: public BaseComponent, public Observer
	{
	public:

		PointsDisplayComponent(GameObject* go, TextComponent* textComp/*, PlayerComponent* peterPepperComponent*/);
		void onNotify(Event event);
		void Update(float);


	private:

		TextComponent* m_pTextComp;



		//PlayerComponent* m_PlayerComp;



	};

}
