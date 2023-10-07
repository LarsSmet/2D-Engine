#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include "GameObject.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"


namespace dae
{
	enum class GunOwner
	{
		player,
		enemy
	};

	class PlayerComponent;
	class EnemyComponent;

	class BulletComponent final : public BaseComponent 
	{
	public:
		BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap, GunOwner gunOwner);
		~BulletComponent();

		void Update(float elapsedSec);

		void SetVelocity(Velocity velocity);

	
		void SetEnemiesAreChecked(bool check);



	private:

		PhysicsComponent* m_pPhysicsComponent;
		Velocity m_Velocity;

		int m_BounceCounter;

		TileMapComponent* m_pTileMapComponent;

		std::shared_ptr<Cell> m_CurrentCell;
		std::vector<std::shared_ptr<Cell>> m_CellsToCheck{};




		void HandleBounce();
		void HandleDamage();
		void KillBullet();

		GunOwner m_GunOwner;


		std::vector<PlayerComponent*> m_PlayerComponents;
		std::vector<EnemyComponent*> m_EnemyComponents;



		bool m_EnemiesAreChecked;

		void CheckCurrentEnemies();

	

	};


}
