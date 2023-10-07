#pragma once
//#include "EnemyComponent.h"
//#include "GunComponent.h"


namespace dae
{
	class EnemyComponent;
	class GunComponent;
	class PlayerComponent;

	class AIState
	{

	public:

		AIState(PlayerComponent* playerComp): m_pPlayerComponent{ playerComp } {};
		virtual ~AIState() {};
		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; return nullptr; };
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; };
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; };

	private:

	protected:
		PlayerComponent* m_pPlayerComponent;

	};

	class EnemyComponent;

	class MoveState : public AIState
	{

	public:

		MoveState(PlayerComponent* playerComp);
		virtual ~MoveState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		



	private:



	};

	class EnemyComponent;

	class ShootState : public AIState
	{

	public:

		ShootState(PlayerComponent* playerComp);
		virtual ~ShootState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;




	private:



	};

	class EnemyComponent;

	class MoveAndShootState : public AIState
	{

	public:

		MoveAndShootState(PlayerComponent* playerComp);
		virtual ~MoveAndShootState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;




	private:



	};


}

