#pragma once
//#include "Transform.h"

#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <vector>
//#include "BaseColliderComponent.h"
//#include "RectangleColliderComponent.h"
#include "utils.h"

namespace dae
{
	class Texture2D;

	
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:

		
		void Update(float deltaTime);
		void Render() const;

		
		void SetPosition(float x, float y);

		void Destroy();
		
		//template <typename T> 
		void AddComponent(BaseComponent* component);
		template <typename T>
		inline T* GetComponent() const 
		{
			for (auto& component : m_Components) 
			{

				T* casted = dynamic_cast<T*>(component);
				if (casted != nullptr)
				{
					return casted;
				}
				else
				{

				}

			}

			return nullptr;

		}
		//template <typename T> 
		template <typename T>
		void RemoveComponent(T*)
		{

			auto comp = GetComponent<T>();

			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());

			delete comp;
			comp = nullptr;

		}



		void SetParent(std::weak_ptr<GameObject> parent);


		std::weak_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;


		void Move(float xOffSet, float yOffSet);
		TransformComponent* GetTransformComp();

		void SetTag(std::string name);
		std::string GetTag();


		GameObject(float xPos, float yPos, std::string tag);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		
		

		std::vector<BaseComponent*> m_Components{};
	


		std::weak_ptr<GameObject> m_pParent;
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		std::shared_ptr<TransformComponent> m_TransformComp;

		

		std::string m_Tag;
		

		void RemoveChild(std::shared_ptr<GameObject> childToRemove);
		void AddChild(std::shared_ptr<GameObject> go);

	};
}
