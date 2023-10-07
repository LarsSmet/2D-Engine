#pragma once
#include <structs.h>
#include <GameObject.h>
#include "PlayerComponent.h"
#include <Scene.h>
#include "RenderComponent.h"
#include "BulletComponent.h"
//#include "EnemyComponent.h"

namespace dae
{
	class EnemyComponent;

	class GunComponent final: public BaseComponent
	{
	public:


		GunComponent(GameObject* go, PlayerComponent* playerComp, EnemyComponent* enemyComp);
		~GunComponent();


		void Update(float elapsedSec);
		void Move();
		void Shoot();
		void RotateGun();

	private:


		Point2f m_RotationPos;
		Point2f m_ShootPos;
		Point2f m_VectorStartPos;

		PlayerComponent* m_pPlayerComp;
		EnemyComponent* m_pEnemyComp;
		

		

		RenderComponent* m_pRenderComp;

	

		GunOwner m_GunOwner;

		float m_CurrentCooldown;
		float m_MaxCooldown;
		bool m_OnCooldown;

		double m_RotationSpeed;

	};


}

