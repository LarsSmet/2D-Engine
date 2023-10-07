#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "Event.h"
#include <iostream>

namespace dae
{

	LivesDisplayComponent::LivesDisplayComponent(GameObject* go, TextComponent* textComp/*,*/ /*PlayerComponent* peterPepperComponent*/) : BaseComponent{ go }, m_pTextComp { textComp }/* m_PlayerComp{ peterPepperComponent }*/
	{

	}

	void LivesDisplayComponent::onNotify(Event event)
	{
		if (m_pTextComp == nullptr)
		{
			return;
		}


		switch (event)
		{
		case Event::PlayerDied:
		

			//m_pTextComp->SetText("Lives: " +  std::to_string( m_PlayerComp->GetLives()));
	
			break;
		case Event::EnemyDied:
			break;
		case Event::BurgerDropped:
			break;
	
		}

	}

	void LivesDisplayComponent::Update(float)
	{
	}

}