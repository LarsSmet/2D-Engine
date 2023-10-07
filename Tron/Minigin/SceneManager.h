#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();

		Scene& GetCurrentScene();

		int GetCurrentSceneIndex();

		void GoToNextScene();

		

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		int m_CurrentScene{ 0 };

	};
}
