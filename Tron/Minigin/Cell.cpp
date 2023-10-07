#include "MiniginPCH.h"
#include "Cell.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{

	Cell::Cell()
	{
	}

	Cell::~Cell()
	{
	/*	if (m_pColliderComp != nullptr)
		{
			delete m_pColliderComp;
			m_pColliderComp = nullptr;
		}*/

		//if (m_HasCollision)
		//{
		//	delete m_pColliderComp;
		//	m_pColliderComp = nullptr;
		//}

		//delete m_pColliderComp;
			//m_pColliderComp = nullptr;

	}

	void Cell::Render()
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_Pos.x, m_Pos.y);
	}

	void Cell::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		
	}

	void Cell::SetCollision(bool hasCol, RectColliderComponent colliderComp)
	{
		m_HasCollision = hasCol;

		if (hasCol)
		{
			m_pColliderComp = std::make_shared<RectColliderComponent>(colliderComp);
		}
		
	}

	void Cell::SetCollision(bool hasCol, Rectf collider)
	{
		m_HasCollision = hasCol;

		if (hasCol)
		{
			m_RectCollider = collider;
		}

	}



	void Cell::SetCollision(bool hasCol)
	{
		m_HasCollision = hasCol;
	}

	void Cell::SetPos(float x, float y)
	{

		m_Pos.x = x;
		m_Pos.y = y;

	}

	bool Cell::HasCollision()
	{
		return m_HasCollision;
	}

	void Cell::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}

	void Cell::SetType(CellType type)
	{
		m_CellType = type;
	}

	void Cell::SetDirections(bool canGoUp, bool canGoDown, bool canGoLeft, bool canGoRight)
	{
		m_CanGoUp = canGoUp;
		m_CanGoDown = canGoDown;
		m_CanGoLeft = canGoLeft;
		m_CanGoRight = canGoRight;

	}

	Point2f Cell::GetPosition()
	{
		return m_Pos;
	}

	Point2f Cell::GetSize()
	{
		return Point2f{ m_Width , m_Height };
	}
	

	Rectf Cell::GetRectCollider()
	{
		return m_RectCollider;
	}

	CellType Cell::GetCellType()
	{
		return m_CellType;
	}

	bool Cell::CanGoUp()
	{
		return m_CanGoUp;
	}

	bool Cell::CanGoDown()
	{
		return m_CanGoDown;
	}

	bool Cell::CanGoLeft()
	{
		return m_CanGoLeft;
	}

	bool Cell::CanGoRight()
	{
		return m_CanGoRight;
	}


}
