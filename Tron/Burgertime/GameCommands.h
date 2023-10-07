#pragma once
#include "Command.h"
#include "PlayerComponent.h"
#include "GunComponent.h"
namespace dae
{

	class GameCommands
	{
	};

	class MoveCommand : public Command
	{

	public:


		MoveCommand(PlayerComponent* playerComp, float xSpeed, float ySpeed) : m_PlayerComp{ playerComp }, m_Velocity{ xSpeed, ySpeed }
		{

		};


		~MoveCommand() {};


		void Execute()
		{

			


		


			auto physComp = m_PlayerComp->GetPhysicsComp();

			if (m_Velocity.y < 0)
			{
			
			}
			if (m_Velocity.y > 0)
			{
			
			}



			

			physComp->SetVelocity(m_Velocity);
		

		}


	private:

		Velocity m_Velocity;
		PlayerComponent* m_PlayerComp;

	};



	class ShootCommand : public Command
	{

	public:


		ShootCommand(GunComponent* gunComp) : m_GunComp{ gunComp }
		{

		};
		~ShootCommand() {};

		void Execute()
		{
			
			m_GunComp->Shoot();
		}

	private:

		GunComponent* m_GunComp;

	};



	class RotateGunCommand : public Command
	{

	public:


		RotateGunCommand(GunComponent* gunComp) : m_GunComp{ gunComp }
		{

		};
		~RotateGunCommand() {};

		void Execute()
		{
			
			m_GunComp->RotateGun();
		}

	private:

		GunComponent* m_GunComp;

	};

	class SkipLevelCommand : public Command
	{

	public:


		SkipLevelCommand() 
		{

		};
		~SkipLevelCommand() {};

		void Execute()
		{
			SceneManager::GetInstance().GoToNextScene();
			
		}

	private:

	

	};


}