#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>
#include "PhysicsComponent.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"

namespace dae
{
	GunComponent::GunComponent(GameObject* go, PlayerComponent* playerComp, EnemyComponent* enemyComp ): BaseComponent{ go }, m_CurrentCooldown{0}, m_MaxCooldown{2}, m_OnCooldown{false}, m_RotationSpeed{1.25},
		m_pPlayerComp{playerComp}, m_pEnemyComp{enemyComp}
	{
		m_pRenderComp = m_Owner->GetComponent<RenderComponent>();
		
		
		if (m_pEnemyComp != nullptr)
		{
			m_GunOwner = GunOwner::enemy;
		}
		else if (m_pPlayerComp != nullptr)
		{
			m_GunOwner = GunOwner::player;
		}


	

		
		

	}

	GunComponent::~GunComponent()
	{
	}
	void GunComponent::Update(float elapsedSec)
	{
		if (m_OnCooldown && m_CurrentCooldown <= 0 )
		{
			m_OnCooldown = false;
			
		}
		else if(m_OnCooldown && m_CurrentCooldown > 0)
		{
			m_CurrentCooldown -= elapsedSec;
		}
		

		//if not enemy
		if (m_GunOwner == GunOwner::player) 
		{
			Move();
		
		}
	
		elapsedSec;
	}

	void GunComponent::Move()
	{
		glm::vec2 ownerTransformPos;

		if (m_GunOwner == GunOwner::player)
		{
			ownerTransformPos = m_pPlayerComp->GetPhysicsComp()->GetTransformComp()->GetPosition();
		}
		else if (m_GunOwner == GunOwner::enemy)
		{
			ownerTransformPos = m_pEnemyComp->GetPhysicsComp()->GetTransformComp()->GetPosition();
		}

		m_Owner->SetPosition(ownerTransformPos.x + 10, ownerTransformPos.y - 3);

		//middle of tank
		m_RotationPos = Point2f{ ownerTransformPos.x + 16, ownerTransformPos.y + 19 };
		m_pRenderComp->SetRotatePoint(Point2f{ 6, 22 });

	}


	void GunComponent::Shoot()
	{
		if (m_OnCooldown)
		{
			
		}
		else
		{
			m_CurrentCooldown = m_MaxCooldown;
			m_OnCooldown = true;



			//do direction
			float degreeOffset = -90;
			auto radians = glm::radians(float(m_pRenderComp->GetAngle()) + degreeOffset);
			float directionX = glm::cos(radians);
			float directionY = glm::sin(radians);



			glm::vec2 directionVec{ directionX, directionY };


			auto absoluteVecX = glm::abs(directionVec.x);
			auto absoluteVecY = glm::abs(directionVec.y);



			//because of -90 x and y are swapped for absolute vec
			float offSetX = -3;
			float offSetY = 19;

			Point2f shootPos;
			shootPos.x = m_RotationPos.x + offSetX * absoluteVecY + offSetY * directionX;
			shootPos.y = m_RotationPos.y + offSetX * absoluteVecX + offSetY * directionY;



			auto bullet = std::make_shared<GameObject>(shootPos.x, shootPos.y, "BULLET");
			RenderComponent* renderComponent = new RenderComponent{ bullet.get(), false , nullptr };
			renderComponent->SetTexture("Bullet.png");
			bullet->AddComponent(renderComponent);

			auto texture = renderComponent->GetTexture()->GetSDLTexture();
			SDL_Point size;
			SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
			Rectf bulletShape{ shootPos.x,shootPos.y + float(size.y), float(size.x),float(size.y) };
			RectColliderComponent* bulletCollider = new RectColliderComponent{ bullet.get(), bulletShape };
			PhysicsComponent* physicsComp = new PhysicsComponent{ bullet.get(), bullet->GetTransformComp(), bulletCollider };
			bullet->AddComponent(physicsComp);
			

			auto tileMap = SceneManager::GetInstance().GetCurrentScene().GetTileMap()->GetComponent<TileMapComponent>();//TODO: Maybe remove get and just take shared ptr?

			BulletComponent* bulletComponent = new BulletComponent{ bullet.get(), physicsComp, tileMap, m_GunOwner };
			float speed = 150.0f;
			//set velocity based on calculations for direction from pos under shoot pos
			bulletComponent->SetVelocity(Velocity{ directionVec.x * speed, directionVec.y * speed });
			bullet->AddComponent(bulletComponent);
			SceneManager::GetInstance().GetCurrentScene().LateAdd(bullet);


			
			
			

		}
		


	}
	void GunComponent::RotateGun()
	{
		


		
		m_pRenderComp->RotateForward(m_RotationSpeed);

	}



}