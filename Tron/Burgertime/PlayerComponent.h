#pragma once
#include "BaseComponent.h"
#include <RectColliderComponent.h>
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include <SceneManager.h>


namespace dae
{
	enum class State
	{
		normal,
		moving
	};

	class PlayerComponent final : public BaseComponent
	{

	public:

		PlayerComponent(GameObject* go, PhysicsComponent* physComp);
		~PlayerComponent();

		virtual void Update(float elapsedSec);


		void SetState(State newState);

		State GetState();

		PhysicsComponent* GetPhysicsComp();

		void Teleport();

		glm::vec2 GetPlayerCenter();

		void HandleSceneChange();


	private:


		

		PhysicsComponent* m_pPhysicsComponent;
	


		TileMapComponent* m_pTileMapComponent;
		State m_State;

		std::vector<std::shared_ptr<Cell>> m_CellsToCheck;

		std::shared_ptr<Cell> m_CurrentCell;

		int m_CurrentScene;

		int m_Health;

	};


}

