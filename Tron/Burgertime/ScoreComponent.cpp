#include "pch.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

namespace dae
{

	ScoreComponent::ScoreComponent(GameObject* go, TextComponent* display) : BaseComponent{ go }, m_pTextComponent{display}, m_Score{0}
	{
		m_pTextComponent->SetText(std::to_string(m_Score));
	}


	ScoreComponent::~ScoreComponent()
	{
		delete m_pTextComponent;
		m_pTextComponent = nullptr;
	}

	void ScoreComponent::Update(float elapsedSec)
	{
		
		elapsedSec;
	}

	void ScoreComponent::onNotify(Event event)
	{

		switch (event)
		{
		case Event::PlayerDied:
			
			break;
		case Event::BlueTankdied:
			ChangeScore(100);
			break;
		case Event::RecognizerDied:
			ChangeScore(250);
			break;

		}
		

	}

	void ScoreComponent::ChangeScore(int change)
	{
		m_Score += change;
		m_pTextComponent->SetText(std::to_string(m_Score));

	}


	


}