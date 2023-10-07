#pragma once
#include "Singleton.h"
#include "MiniginPCH.h"
#include "GameObject.h"

namespace dae
{

	class EntityManager final : public Singleton<EntityManager>
	{

	public:

		void AddPlayer(const std::shared_ptr<GameObject>& object);
		void AddEnemy(const std::shared_ptr<GameObject>& object);
		std::vector<std::shared_ptr<GameObject>> GetPlayers();
		std::vector<std::shared_ptr<GameObject>> GetEnemies();

		void RemoveEnemy(const std::shared_ptr<GameObject>& enemy);



	private:
		friend class Singleton<EntityManager>;
		EntityManager() = default;
		
		std::vector<std::shared_ptr<GameObject>> m_pPlayers;
		std::vector<std::shared_ptr<GameObject>> m_pEnemies;

	};

}