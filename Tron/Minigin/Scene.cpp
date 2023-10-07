#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "TileMapComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void Scene::AddTileMap(const std::shared_ptr<GameObject>& object)
{
	if (object->GetComponent<TileMapComponent>() != nullptr)
	{
		m_TileMap = object;


	}


}

std::shared_ptr<GameObject> Scene::GetTileMap()
{
	return m_TileMap;
}



void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}


	//add gameobjects
	if (!m_LateObjectsToAdd.empty()) //if we have gameobjects to add
	{
		for (const auto& objectToAdd: m_LateObjectsToAdd)
		{
			m_Objects.emplace_back(objectToAdd);
		}
		m_LateObjectsToAdd.clear();

	}


	if (!m_LateObjectsToRemove.empty()) //if we have gameobjects to remove
	{
		//https://stackoverflow.com/questions/799314/difference-between-erase-and-remove
		// https://makeinjava.com/stl-erase-remove-idiom-c-example/
		//!emove doesn't delete -> puts element on the end of the vector and size stays the same!
		

		auto startOfErase = m_Objects.end(); //use this instead of m_Objects.end in remove if.
		//this tracks the startpos of the erase, cant use something like a regular for loop with a counter
		//because if the object is not found, remove if returns iterator to last element of the vector and the counter would still increase


		for (const auto& objectToRemove : m_LateObjectsToRemove)
		{
			//only checks until startpos of the erase, if new element to delete to remove has been found, change the startpos of the erase
			startOfErase = std::remove_if(m_Objects.begin(), startOfErase, [objectToRemove](const std::shared_ptr<GameObject >& go){return go == objectToRemove;});
				

				

		}

		m_Objects.erase(startOfErase, m_Objects.end()); //remove all objects an once instead of seperately

		m_LateObjectsToRemove.clear();

	}


}

void Scene::LateAdd(const std::shared_ptr<GameObject>& object)
{
	m_LateObjectsToAdd.emplace_back(object);
}

void Scene::LateRemove(const std::shared_ptr<GameObject>& object)
{


	size_t childCount = object->GetChildCount();

	if (childCount > 0) //if object has children, remove them
	{
		for (size_t i = 0; i < childCount; ++i)
		{
			object->GetChildAt(int(i))->Destroy();
		}
	}


	m_LateObjectsToRemove.emplace_back(object);

}


void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}



std::vector<std::shared_ptr<GameObject>> Scene::GetObjectsOfTag( std::string tag)
{
	
	std::vector<std::shared_ptr<GameObject>> objects;
	
	for (const auto& objectToCheck : m_Objects) //todo: replace with find_if later?
	{
		if (objectToCheck->GetTag() == tag)
		{
			objects.emplace_back(objectToCheck);
		}
	}

	return objects;

}

void dae::Scene::AddPrefabToReload(std::function<void()> prefab)
{
	m_PrefabToReload.emplace_back(prefab);
}

void dae::Scene::LoadPrefabs()
{
	for (const auto& prefab : m_PrefabToReload)
	{
		prefab();

	}

}



