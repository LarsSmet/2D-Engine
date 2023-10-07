#include "pch.h"
#include "EnemyComponent.h"
#include <glm/gtx/norm.hpp>
#include <utils.cpp>
#include "GunComponent.h"
#include "ScoreComponent.h"
#include <SoundSystem.h>
#include "GameModeComponent.h"



namespace dae
{

	EnemyComponent::EnemyComponent(GameObject* go, PhysicsComponent* physComp, bool isRecognizer/*, PlayerComponent* playerComp*/) :
		BaseComponent{ go }, m_pPhysicsComponent{ physComp }, m_pTileMapComponent{nullptr}/*, m_pPlayerComponent{ playerComp }*/, m_HasDoneFirstUpdate{false},
		m_IsDying{false}, m_IsRecognizer{isRecognizer}, m_Health{}

	{
		if (m_IsRecognizer)
		{
			m_Health = 1;
			m_Speed = 60;
		}
		else
		{
			m_Health = 3;
			m_Speed = 30;
		}
	}

	

	EnemyComponent::~EnemyComponent()
	{
		delete m_pAIState;
		m_pAIState = nullptr;

	}

	void EnemyComponent::Update(float elapsedSec)
	{
		if (!m_HasDoneFirstUpdate)
		{
			OnFirstUpdate();
		}

		auto enemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto enemyRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

		//offset needed to make sure it is in the cell, because sometimes the collision would make it so that it would be in another cell
		float offSet = 5;
		enemyPos.x += offSet;
		enemyPos.y += offSet;

		

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(enemyRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });
		}
		else
		{
			
		}

		auto childGun = m_Owner->GetChildAt(0);//TODO: replace with actual child
		if (childGun != nullptr)
		{
			auto gunComp = childGun->GetComponent<GunComponent>();


		


			AIState* state = m_pAIState->Update(this, gunComp);




			if (state != nullptr)
			{
				delete m_pAIState;
				m_pAIState = state;
				state->OnEnter(this, gunComp);
			}

		}


		


		m_pPhysicsComponent->Update(elapsedSec);

		


		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{

			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				m_pPhysicsComponent->HandleCollision(m_CellsToCheck[i]->GetRectCollider());



			}
		}


	



	}

	void EnemyComponent::OnFirstUpdate()
	{
		m_HasDoneFirstUpdate = true;

		m_pTileMapComponent = SceneManager::GetInstance().GetCurrentScene().GetTileMap()->GetComponent<TileMapComponent>();

		auto enemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });
		auto enemyrRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		m_pTileMapComponent->GetCellsAroundRect(enemyrRectCol, m_CellsToCheck);
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });

		auto players = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("PLAYER");
		auto observers = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("OBSERVER");

		for (const auto& observer : observers)
		{
			auto scoreComp = observer->GetComponent<ScoreComponent>();
			
			if (scoreComp != nullptr)
			{
				m_Observers.emplace_back(scoreComp);
			}
			else
			{
				auto gameModeComp = observer->GetComponent<GameModeComponent>();

				if (gameModeComp != nullptr)
				{
					m_Observers.emplace_back(gameModeComp);
				}

			}
			

			
		}

		

		m_pPlayerComponent = players[0]->GetComponent<PlayerComponent>();

		m_pAIState = new MoveState(m_pPlayerComponent);

	}


	void EnemyComponent::HandleAI()
	{
		//Check raycast up, down, left right
		//go over all pos where no raycast hit

		//if no raycast, compare pos to best pos


		//positions to compare

		bool botHit = false;
		bool topHit = false;
		bool leftHit = false;
		bool rightHit = false;

		auto enemyWidth = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider().height;

		glm::vec2 enemyCenter = GetEnemyCenter();

		glm::vec2 topPosToCompare{ enemyCenter.x, enemyCenter.y - enemyHeight/2 };
		glm::vec2 botPosToCompare{ enemyCenter.x, enemyCenter.y + enemyHeight/2 };
		glm::vec2 leftPosToCompare{ enemyCenter.x - enemyWidth / 2, enemyCenter.y };
		glm::vec2 rightPosToCompare{ enemyCenter.x + enemyWidth / 2, enemyCenter.y };
 


		for (size_t i = 0; i < m_CellsToCheck.size(); i++) //check the col for surrounding cells and store them if hit
		{
			if (m_CellsToCheck[i]->HasCollision())
			{

				auto hitInfo = m_pPhysicsComponent->GetColliderComponent()->OnCollision(m_CellsToCheck[i]->GetRectCollider());

				if (hitInfo.botColLeftIsHit || hitInfo.botColRightIsHit) 
				{
					botHit = true;
				}

				if (hitInfo.topColLeftIsHit || hitInfo.topColRightIsHit)
				{
					topHit = true;
				}

				if (hitInfo.leftColBotIsHit || hitInfo.leftColTopIsHit)
				{
					leftHit = true;
				}

				if (hitInfo.rightColBotIsHit || hitInfo.rightColTopIsHit)
				{
					rightHit = true;
				}
			

			}


		}

		
		float bestDistance = FLT_MAX;

		auto playerCenter = m_pPlayerComponent->GetPlayerCenter();
		Velocity newVelocity{};

		if (!topHit)
		{
			float distance = glm::distance2(topPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 0, -1};
			}
			
		}

		if (!botHit)
		{
			float distance = glm::distance2(botPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 0, 1 };
			}
		}

		if (!leftHit)
		{
			float distance = glm::distance2(leftPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ -1, 0 };
			}
		}


		if (!rightHit)
		{
			float distance = glm::distance2(rightPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 1, 0 };
			}
		}

		

		newVelocity.x *= m_Speed;
		newVelocity.y *= m_Speed;

		SetVelocity(newVelocity);

	}



	

	void EnemyComponent::SetVelocity(Velocity newVelocity)
	{
		m_pPhysicsComponent->SetVelocity(newVelocity);
		m_Velocity = newVelocity;
		
	}

	PhysicsComponent* EnemyComponent::GetPhysicsComp()
	{
		
			return m_pPhysicsComponent;
		
	}

	glm::vec2 EnemyComponent::GetEnemyCenter()
	{
		auto enemyPhysComp = GetPhysicsComp();
		auto enemyPos = enemyPhysComp->GetTransformComp()->GetPosition();
		auto enemyWidth = enemyPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = enemyPhysComp->GetColliderComponent()->GetRectCollider().height;
		return { enemyPos.x + enemyWidth / 2, enemyPos.y + enemyHeight / 2 };
	}

	void EnemyComponent::Kill()
	{
		if (m_IsRecognizer)
		{
			Notify(Event::RecognizerDied);
		}
		else
		{
			Notify(Event::BlueTankdied);
		}

		auto& ss = ServiceLocator::GetSoundSystem();


		const char* path = "../Data/DeathSound.wav";
		int volume = 10;
		ss.PlaySoundRequest(SoundRequest{ path, volume });


		auto bullets = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("BULLET");

		for (const auto& bullet : bullets)
		{
			auto bulletComp = bullet->GetComponent<BulletComponent>();

			if (bulletComp != nullptr)
			{
				bulletComp->SetEnemiesAreChecked(false);
			}
		}

		m_Observers.clear();
		m_Owner->Destroy();
	}

	void EnemyComponent::DealDamage(int dmg)
	{
		m_Health -= dmg;

		if (m_Health <= 0)
		{
			Kill();
		}
	}

}
