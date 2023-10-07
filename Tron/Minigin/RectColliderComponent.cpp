#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

namespace dae
{
	RectColliderComponent::RectColliderComponent(GameObject* go, Rectf rectCollider) : BaseComponent(go), m_RectCollider{rectCollider}
	{

	}

	RectColliderComponent::~RectColliderComponent()
	{


	}
	


	CollisionHitInfo RectColliderComponent::OnCollision(Rectf collision)
	{
		CollisionHitInfo collisionInfo;


		auto rectCol = collision;



		//create vertices
		Point2f colLeftBot{ rectCol.left, rectCol.bottom };
		Point2f colRightBot{ rectCol.left + rectCol.width, rectCol.bottom };
		Point2f colRightTop{ rectCol.left + rectCol.width, rectCol.bottom + rectCol.height };
		Point2f colLeftTop{ rectCol.left, rectCol.bottom + rectCol.height };

		std::vector<Point2f> vertices{ colLeftBot,colRightBot,colRightTop, colLeftTop };


		Point2f midTop{ m_RectCollider.left + m_RectCollider.width / 2, m_RectCollider.bottom - m_RectCollider.height };
		Point2f midBot{ m_RectCollider.left + (m_RectCollider.width / 2), m_RectCollider.bottom };
		Point2f midLeft{ m_RectCollider.left, m_RectCollider.bottom - (m_RectCollider.height / 2) };
		Point2f midRight{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom - (m_RectCollider.height / 2) };
		Point2f leftBot{ m_RectCollider.left, m_RectCollider.bottom };
		Point2f leftTop{ m_RectCollider.left, m_RectCollider.bottom - m_RectCollider.height };
		Point2f rightTop{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom - m_RectCollider.height };
		Point2f rightBot{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom };


		float rayOffSet = 4.0f;


		if (utils::Raycast(vertices, Point2f{ leftBot.x, leftBot.y - rayOffSet }, Point2f{ midBot.x, midBot.y - rayOffSet }, collisionInfo.leftColBot))
		{
			collisionInfo.leftColBotIsHit = true;
			collisionInfo.hit = true;
		}
		else if (utils::Raycast(vertices, Point2f{ leftTop.x, leftTop.y + rayOffSet }, Point2f{ midTop.x, midTop.y + rayOffSet }, collisionInfo.leftColTop))
		{
			collisionInfo.leftColTopIsHit = true;
			collisionInfo.hit = true;
		}

		//right col

		if (utils::Raycast(vertices, Point2f{ rightBot.x, rightBot.y - rayOffSet }, Point2f{ midBot.x, midBot.y - rayOffSet }, collisionInfo.rightColBot))
		{
			collisionInfo.rightColBotIsHit = true;
			collisionInfo.hit = true;

		}
		else if (utils::Raycast(vertices, Point2f{ rightTop.x, rightTop.y + rayOffSet }, Point2f{ midTop.x, midTop.y + rayOffSet }, collisionInfo.rightColTop))
		{
			collisionInfo.rightColTopIsHit = true;
			collisionInfo.hit = true;
		}
		//bot col
		if (utils::Raycast(vertices, Point2f{ leftBot.x + rayOffSet, leftBot.y }, Point2f{ midLeft.x + rayOffSet, midLeft.y }, collisionInfo.botColLeft))
		{
			collisionInfo.botColLeftIsHit = true;
			collisionInfo.hit = true;
		}
		else if (utils::Raycast(vertices, Point2f{ rightBot.x - rayOffSet, rightBot.y }, Point2f{ midRight.x - rayOffSet,midRight.y }, collisionInfo.botColRight))
		{
			
			collisionInfo.botColRightIsHit = true;
			collisionInfo.hit = true;
		}
		//top col 
		if (utils::Raycast(vertices, Point2f{ leftTop.x + rayOffSet, leftTop.y }, Point2f{ midLeft.x + rayOffSet, midLeft.y }, collisionInfo.topColLeft))
		{
			
			collisionInfo.topColLeftIsHit = true;
			collisionInfo.hit = true;
		}
		else if (utils::Raycast(vertices, Point2f{ rightTop.x - rayOffSet, rightTop.y }, Point2f{ midRight.x - rayOffSet, midRight.y }, collisionInfo.topColRight))
		{
			
			collisionInfo.topColRightIsHit = true;
			collisionInfo.hit = true;
		}

	

		return collisionInfo;


	}




	void RectColliderComponent::SetXPosition(float x)
	{
		m_RectCollider.left = x;
		
	}

	void RectColliderComponent::SetYPosition(float y)
	{

		m_RectCollider.bottom = y;
	}

	void RectColliderComponent::SetPosition(float x, float y)
	{
		m_RectCollider.left = x;
		m_RectCollider.bottom = y;
	}


	Point2f RectColliderComponent::GetPosition() const
	{
		return Point2f{ m_RectCollider.left, m_RectCollider.bottom};
	}
	void RectColliderComponent::Move(float xOffSet, float yOffSet)
	{
		SetPosition(m_RectCollider.left + xOffSet, m_RectCollider.bottom + yOffSet);
	}
	Rectf RectColliderComponent::GetRectCollider()
	{
		return m_RectCollider;
	}
}