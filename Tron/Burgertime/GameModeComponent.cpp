#include "pch.h"
#include "GameModeComponent.h"
#include "EnemyComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EntityManager.h"

namespace dae
{
	GameModeComponent::GameModeComponent(GameObject* go) : BaseComponent(go)
	{

	}

	GameModeComponent::~GameModeComponent()
	{
	}
	void GameModeComponent::Update(float elapsedSec)
	{
		elapsedSec;
	}
	void GameModeComponent::onNotify(Event event)
	{

		switch (event)
		{
		case Event::PlayerDied:
			break;
		case Event::BlueTankdied:

		
			if (SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("ENEMY").size() == 1) //if no enemies left go to next scene
			{
				SceneManager::GetInstance().GoToNextScene();
			}

			break;
		case Event::RecognizerDied:

			if (SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("ENEMY").size() == 1) //if no enemies left go to next scene
			{
				SceneManager::GetInstance().GoToNextScene();
			}

			break;
		
		}

	}
}