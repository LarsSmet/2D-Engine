#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include "PlayerComponent.h"
#include "AIStates.h"
#include "Subject.h"


namespace dae
{
	class AIStates;
	class GunComponent;
	

	class EnemyComponent final: public BaseComponent, Subject
	{

	public:

		EnemyComponent(GameObject* go, PhysicsComponent* physComp, bool isRecognizer/*, PlayerComponent* playerComp*/);
		~EnemyComponent();
		virtual void Update(float elapsedSec) override;

		void HandleAI();

		void SetVelocity(Velocity newVelocity);


		PhysicsComponent* GetPhysicsComp();

		void ResetVelocity();

		Velocity GetVelocity();

		glm::vec2 GetEnemyCenter();

		void Kill();



		void DealDamage(int dmg);
	private:

		

		PhysicsComponent* m_pPhysicsComponent;


		TileMapComponent* m_pTileMapComponent;

		std::vector<std::shared_ptr<Cell>> m_CellsToCheck;

		std::shared_ptr<Cell> m_CurrentCell;

		
		PlayerComponent* m_pPlayerComponent;

		GunComponent* m_pGunComponent;

		AIState* m_pAIState;

		
		Velocity m_Velocity;


		std::vector<std::shared_ptr<GameObject>> m_Players;

		bool m_HasDoneFirstUpdate;

		void OnFirstUpdate();

		bool m_IsDying;


		bool m_IsRecognizer;

		int m_Health;

		float m_Speed;

	};





}