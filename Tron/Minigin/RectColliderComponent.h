#pragma once
#include "BaseComponent.h"
#include "utils.h"
namespace dae
{

	struct CollisionHitInfo
	{
		bool hit = false;

		//left col hitinfo
		utils::HitInfo leftColBot;
		bool leftColBotIsHit = false;
		utils::HitInfo leftColTop;
		bool leftColTopIsHit = false;

		//top col hitinfo
		utils::HitInfo topColLeft;
		bool topColLeftIsHit = false;
		utils::HitInfo topColRight;
		bool topColRightIsHit = false;

		//right col hitinfo
		utils::HitInfo rightColTop;
		bool rightColTopIsHit = false;
		utils::HitInfo rightColBot;
		bool rightColBotIsHit = false;

		//bot col hitinfo
		utils::HitInfo botColRight;
		bool botColRightIsHit = false;
		utils::HitInfo botColLeft;
		bool botColLeftIsHit = false;

	};


	class RectColliderComponent final : public BaseComponent
	{

	public:

		RectColliderComponent(GameObject* go, Rectf rectCollider);
		~RectColliderComponent();

		CollisionHitInfo OnCollision(Rectf collision);

		CollisionHitInfo OnCollision(RectColliderComponent* collision);

		void SetXPosition(float x);
		void SetYPosition(float y);

		void SetPosition(float x, float y);
		Point2f GetPosition() const;
		void Move(float xOffSet, float yOffSet);

		Rectf GetRectCollider();


	private:



		Rectf m_RectCollider;


	};

}

