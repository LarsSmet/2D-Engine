#include "pch.h"
#include "AIStates.h"
#include "EnemyComponent.h"
#include "GunComponent.h"
#include <glm/gtx/norm.hpp>

namespace dae
{
	//Move state

	MoveState::MoveState(PlayerComponent* playerComp) : AIState{ playerComp }
	{

	}

	MoveState::~MoveState()
	{
	}

	AIState* MoveState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{

		enemyComp->HandleAI();
		gunComp->Move();



		

	


		
		glm::vec2 playerCenter = m_pPlayerComponent->GetPlayerCenter();

		
		glm::vec2 enemyCenter = enemyComp->GetEnemyCenter();

		auto distance = glm::distance2(playerCenter, enemyCenter);
		if (distance <= 15000.0f && distance > 7000)
		{
			
			return new MoveAndShootState{ m_pPlayerComponent };
		}
		else if (distance <= 7000)
		{
			
			return new ShootState{ m_pPlayerComponent };
		}

		return nullptr;
		
		
	
	}

	void MoveState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		

		enemyComp; gunComp;
	}

	void MoveState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}


	//Shoot state


	ShootState::ShootState(PlayerComponent* playerComp) : AIState{ playerComp }
	{
	}

	ShootState::~ShootState()
	{
	}

	AIState* ShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
	

		glm::vec2 playerCenter = m_pPlayerComponent->GetPlayerCenter();

		glm::vec2 enemyCenter = enemyComp->GetEnemyCenter();

		auto distance = glm::distance2(playerCenter, enemyCenter);

		gunComp->RotateGun();
		gunComp->Shoot();

		

		if (distance > 15000.0f)
		{
			
			return new MoveState{ m_pPlayerComponent };
		}
		if (distance <= 15000.0f && distance > 7000)
		{
			
			return new MoveAndShootState{ m_pPlayerComponent };
		}
	
		



		enemyComp; gunComp;
		return nullptr;
	}

	void ShootState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		



		enemyComp->SetVelocity(Velocity{ 0,0 });
		gunComp;
	}

	void ShootState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	//MoveAndShoot state

	MoveAndShootState::MoveAndShootState(PlayerComponent* playerComp) : AIState{ playerComp }
	{

	}

	MoveAndShootState::~MoveAndShootState()
	{
	}

	AIState* MoveAndShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp->HandleAI();
		gunComp->Move();

		glm::vec2 playerCenter = m_pPlayerComponent->GetPlayerCenter();

		glm::vec2 enemyCenter = enemyComp->GetEnemyCenter();

		auto distance = glm::distance2(playerCenter, enemyCenter);

		gunComp->RotateGun();
		gunComp->Shoot();

		if (distance > 15000.0f)
		{
			
			return new MoveState{ m_pPlayerComponent };
		}
		else if (distance <= 7000)
		{
			
			return new ShootState{ m_pPlayerComponent };
		}


		

		return nullptr;
	}

	void MoveAndShootState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	void MoveAndShootState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

}