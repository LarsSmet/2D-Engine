#pragma once
#include "BaseComponent.h" 
#include "Observer.h" 
//#include "TextComponent.h"



namespace dae
{

	class TextComponent;

	class ScoreComponent final : public BaseComponent, public Observer
	{

	public:
		ScoreComponent(GameObject* go, TextComponent* display);
		~ScoreComponent();

		void Update(float elapsedSec);

		void onNotify(Event event) override;

	private:

		void ChangeScore(int change);

		int m_Score;

		TextComponent* m_pTextComponent;

	};

}