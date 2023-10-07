#include "pch.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Scene.h"

namespace dae
{



	PlayerComponent::PlayerComponent(GameObject* go, PhysicsComponent* physComp/*, TileMapComponent* tileMap*/): BaseComponent{ go }, m_pPhysicsComponent{ physComp }/*, m_pTileMapComponent{tileMap}*/
	{
		auto playerPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
	
		m_CurrentCell = 0;

		m_CurrentScene = -1; //set to -1 because when player obj is created there is no scene yet, so the first time handlescenechange gets called it gets updated
		m_pTileMapComponent = nullptr;

	}

	PlayerComponent::~PlayerComponent()
	{

	}

	void PlayerComponent::Update(float elapsedSec)
	{
		elapsedSec;
		HandleSceneChange();



		m_pPhysicsComponent->Update(elapsedSec);

	


		auto playerPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto playerRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		
		//offset needed to make sure it is in the cell, because sometimes the collision would make it so that it would be in another cell
		float offSet = 5;
		playerPos.x += offSet;
		playerPos.y += offSet;

		

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y}))
		{
		
			m_pTileMapComponent->GetCellsAroundRect(playerRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ playerPos.x, playerPos.y });
		}
		else
		{
			
		}
		

		//if old cell is not new cell, update

		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{
			
			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				if (m_CellsToCheck[i]->GetCellType() == CellType::teleport)
				{
					auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

					float offset = 32; //has to be changed later

					Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


					if (utils::IsOverlapping(rect, m_CellsToCheck[i]->GetRectCollider())) 
					{

						Teleport();

					}

				}
				else
				{

					m_pPhysicsComponent->HandleCollision(m_CellsToCheck[i]->GetRectCollider());
				}
			}
		}


		

	}

	void PlayerComponent::SetState(State newState)
	{
		newState;
	}

	State PlayerComponent::GetState()
	{
		return m_State;
	}
	PhysicsComponent* PlayerComponent::GetPhysicsComp()
	{
		return m_pPhysicsComponent;
	}

	void PlayerComponent::Teleport()
	{
		m_pPhysicsComponent->SetVelocity(Velocity{ 0,0 });

		auto spawnMap = m_pTileMapComponent->GetSpawnMap();

		size_t mapSize = spawnMap.size();

		//random number
		int randomCell = rand() % mapSize;

		//do teleport


		auto posToTeleportTo = spawnMap[randomCell]->GetPosition();

		m_pPhysicsComponent->GetColliderComponent()->SetPosition(posToTeleportTo.x + 1, posToTeleportTo.y +1);
		m_pPhysicsComponent->GetTransformComp()->SetPosition(posToTeleportTo.x +1, posToTeleportTo.y +1);

		
	}

	glm::vec2 PlayerComponent::GetPlayerCenter()
	{
		auto playerPhysComp = GetPhysicsComp();
		auto playerPos = playerPhysComp->GetTransformComp()->GetPosition();
		auto playerWidth = playerPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto playerHeight = playerPhysComp->GetColliderComponent()->GetRectCollider().height;
		return { playerPos.x + playerWidth / 2, playerPos.y + playerHeight / 2 };
		
	
	}

	void PlayerComponent::HandleSceneChange()
	{
		if (m_CurrentScene != SceneManager::GetInstance().GetCurrentSceneIndex())
		{



			
			m_pTileMapComponent = SceneManager::GetInstance().GetCurrentScene().GetTileMap()->GetComponent<TileMapComponent>();

			Teleport();

			m_CurrentScene = SceneManager::GetInstance().GetCurrentSceneIndex();
		
			

		}

	}


}