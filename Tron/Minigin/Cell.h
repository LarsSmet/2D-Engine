#pragma once
#include "Texture2D.h"
#include "RectColliderComponent.h"

namespace dae
{
	enum class CellType
	{
		spawnable,
		unspawnable,
		teleport

	};

	class Cell 
	{


	public:

		Cell();
		~Cell();


		void Render();
		void SetTexture(const std::string& filename);
		void SetCollision(bool hasCol, RectColliderComponent colliderComp);
		void SetCollision(bool hasCol, Rectf collider);
		void SetCollision(bool hasCol);
		void SetPos(float x, float y);
		bool HasCollision();
		void SetSize(float width, float height);
		void SetType(CellType type);

		void SetDirections(bool canGoUp, bool canGoDown, bool canGoLeft, bool canGoRight);

		Point2f GetPosition();

		Point2f GetSize();

		//std::shared_ptr<RectColliderComponent> GetCollider();

		Rectf GetRectCollider();

		CellType GetCellType();



		bool CanGoUp();
		bool CanGoDown();
		bool CanGoLeft();
		bool CanGoRight();




	private:

		int m_Id;
		bool m_HasCollision;

		Point2f m_Pos;

		float m_Width;
		float m_Height;

		std::shared_ptr<dae::Texture2D> m_Texture;

		std::shared_ptr < RectColliderComponent> m_pColliderComp;

		Rectf m_RectCollider;


		CellType m_CellType;


		bool m_CanGoUp;
		bool m_CanGoDown;
		bool m_CanGoLeft;
		bool m_CanGoRight;


		//render


	};

}