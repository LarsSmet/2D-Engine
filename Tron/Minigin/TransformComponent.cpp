#include "MiniginPCH.h"
#include "TransformComponent.h"



namespace dae
{

	

	TransformComponent::TransformComponent(GameObject* go, float xPos, float yPos):BaseComponent(go), m_Position{xPos, yPos}
	{

	}
	void TransformComponent::Update(float deltaTime)
	{
		deltaTime;
	}

	void TransformComponent::SetXPosition( float x)
	{
		m_Position.x = x;
	
	}
	void TransformComponent::SetYPosition(  float y)
	{

		m_Position.y = y;

	
	}

	void TransformComponent::SetPosition( float x,  float y)
	{
		m_Position.x = x;
		m_Position.y = y;
		
	
	}

	void TransformComponent::Move(float xOffSet, float yOffSet)
	{
		
		SetPosition(m_Position.x + xOffSet, m_Position.y + yOffSet);
	}

	glm::vec2 TransformComponent::GetPosition() const
	{

		return m_Position;
	}

}