#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(float deltaTime)
{


	m_Scenes[m_CurrentScene]->Update(deltaTime);


	
}

void dae::SceneManager::Render()
{
	

	m_Scenes[m_CurrentScene]->Render();

}

dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_Scenes[m_CurrentScene]; 
}

int dae::SceneManager::GetCurrentSceneIndex()
{
	return m_CurrentScene; 
}


void dae::SceneManager::GoToNextScene()
{
	
	
	
	if (m_CurrentScene == int(m_Scenes.size() -1))
	{
		
		m_CurrentScene = 0;
	}
	else
	{
		++m_CurrentScene;
	}


	//still have to clear scene from old prefabs before loading
	m_Scenes[m_CurrentScene]->LoadPrefabs();



}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}




