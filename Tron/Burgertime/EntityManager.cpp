#include "pch.h"
#include "EntityManager.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"

namespace dae
{

	void EntityManager::AddPlayer(const std::shared_ptr<GameObject>& player)
	{
		if (player->GetComponent<PlayerComponent>() != nullptr)
		{
			m_pPlayers.emplace_back(player);
		}
		else
		{
		
		}

	}

	void EntityManager::AddEnemy(const std::shared_ptr<GameObject>& enemy)
	{

		if (enemy->GetComponent<EnemyComponent>() != nullptr)
		{
			m_pEnemies.emplace_back(enemy);
		}
		else
		{
			
		}

	}

	std::vector<std::shared_ptr<GameObject>> EntityManager::GetPlayers()
	{
		return m_pPlayers;
	}

	std::vector<std::shared_ptr<GameObject>> EntityManager::GetEnemies()
	{
		return m_pEnemies;
	}


	void EntityManager::RemoveEnemy(const std::shared_ptr<GameObject>& enemy)
	{




	
		m_pEnemies.erase(std::remove_if(m_pEnemies.begin(), m_pEnemies.end(), [enemy](const std::shared_ptr<GameObject >& go) {return go == enemy; }), m_pEnemies.end());


	
	


	

	}

}
