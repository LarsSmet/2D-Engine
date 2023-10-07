#include "MiniginPCH.h"
#include "PhysicsComponent.h"

namespace dae
{

	PhysicsComponent::PhysicsComponent(GameObject* go, TransformComponent* transformComp, RectColliderComponent* colliderComp) : BaseComponent{ go }, m_pTransformComp{ transformComp }, m_pColliderComp{ colliderComp }, m_Velocity{ 0,0 }
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{


	
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		//move transform(go with visual) and collider(collision) depending on the velocity
		
		

		m_pTransformComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);
		m_pColliderComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);

		

	}



	std::shared_ptr <RectColliderComponent> PhysicsComponent::GetColliderComponent() const
	{
		return m_pColliderComp;
	}

	void PhysicsComponent::SetVelocity(Velocity velocity)
	{
		m_Velocity = velocity;
	}

	void PhysicsComponent::SetXVelocity(float xVelocity)
	{
		m_Velocity.x = xVelocity;
	}

	void PhysicsComponent::SetYVelocity(float yVelocity)
	{
		m_Velocity.y = yVelocity;
	}

	Velocity PhysicsComponent::GetVelocity() const
	{
		return m_Velocity;
	}


	TransformComponent* PhysicsComponent::GetTransformComp() const
	{
		return m_pTransformComp;
	}

	void PhysicsComponent::HandleLevelCollision()
	{



	}

	bool PhysicsComponent::HandleCollision(Rectf collision)
	{


		auto colInfo = m_pColliderComp->OnCollision(collision);

		if (colInfo.hit)
		{

		}

		if (!colInfo.hit)
		{
			return false;
		}

		if (colInfo.leftColBotIsHit)
		{
			auto hitPoint = colInfo.leftColBot.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x);
			m_pColliderComp->SetXPosition(hitPoint.x );

		}
		else if (colInfo.leftColTopIsHit)
		{
			auto hitPoint = colInfo.leftColTop.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x );
			m_pColliderComp->SetXPosition(hitPoint.x );

		}
		else if (colInfo.rightColBotIsHit)
		{
			auto hitPoint = colInfo.rightColBot.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width );
			m_pColliderComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width );

		}
		else if (colInfo.rightColTopIsHit)
		{
			auto hitPoint = colInfo.rightColTop.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width );
			m_pColliderComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width );
		}

		////vertical
		if (colInfo.botColLeftIsHit)
		{
			auto hitPoint = colInfo.botColLeft.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y - m_pColliderComp->GetRectCollider().height );
			m_pColliderComp->SetYPosition(hitPoint.y );

		}
		else if (colInfo.botColRightIsHit)
		{
			auto hitPoint = colInfo.botColRight.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y - m_pColliderComp->GetRectCollider().height );
			m_pColliderComp->SetYPosition(hitPoint.y );
		}
		else if (colInfo.topColLeftIsHit)
		{
			auto hitPoint = colInfo.topColLeft.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y );
			m_pColliderComp->SetYPosition(hitPoint.y + m_pColliderComp->GetRectCollider().height );
		}
		else if (colInfo.topColRightIsHit)
		{
			auto hitPoint = colInfo.topColRight.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y );
			m_pColliderComp->SetYPosition(hitPoint.y + m_pColliderComp->GetRectCollider().height );
		}

		return true;
	}


	
}


