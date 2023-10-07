#pragma once
#include "BaseComponent.h"
#include "Cell.h"

namespace dae
{

	

	class TileMapComponent final : public BaseComponent
	{

	public:

		TileMapComponent(GameObject* go, const char* filename);
		~TileMapComponent();



		void ConvertFileToMap();
		void Render();
		std::vector<std::shared_ptr<Cell>> GetCellsAroundRect(Rectf rect);
		void GetCellsAroundRect(Rectf rect, std::vector<std::shared_ptr<Cell>>& vector);

		std::vector<std::shared_ptr<Cell>> GetMap() const;
		std::vector<std::shared_ptr<Cell>> GetCollisionMap() const;
		std::vector<std::shared_ptr<Cell>> GetSpawnMap() const;

		std::shared_ptr<Cell> GetCell(Point2f pos);
		std::shared_ptr<Cell> GetCell(int col, int row);
		int GetCellIndex(int col, int row);
		int GetCellIndex(Point2f pos);

	private:

		void SetDirections();

		const char* m_File;

		std::vector<std::shared_ptr<Cell>> m_Map;
		std::vector<std::shared_ptr<Cell>> m_CollisionMap;
		std::vector<std::shared_ptr<Cell>> m_SpawnMap;
		

		GameObject* m_Go;

		int m_AmountOfRows;
		int m_AmountOfCol;
		
		Point2f m_Pos;

		float m_CellWidth;
		float m_CellHeight;

	};

}