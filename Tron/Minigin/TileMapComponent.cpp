#include "MiniginPCH.h"
#include "TileMapComponent.h"
#include <fstream>
#include"ResourceManager.h"
#include "GameObject.h"

namespace dae
{
	TileMapComponent::TileMapComponent(GameObject* go, const char* filename): BaseComponent{go}, m_File{filename}, m_Go{go}
	{

	
	}

	TileMapComponent::~TileMapComponent()
	{

		//delete m_File;
		//m_File = nullptr;

	}





	void TileMapComponent::ConvertFileToMap()
	{


		ResourceManager::GetInstance().Init("../Data/");

	

		float cellWidth;
		float cellHeight;

		int value;

		auto transformCompPos = m_Go->GetTransformComp()->GetPosition();

		m_Pos.x = transformCompPos.x;
		m_Pos.y = transformCompPos.y;
		glm::vec2 position{ transformCompPos.x, transformCompPos.y }; //change to transform component later

		

		std::ifstream input(m_File);

		if (!input.is_open())
		{
			/*std::cout << "Opening file failed";*/
			return;
		}

		//first value read is the amount of col, second value is the amount of rows
		//third value is the cell width, fourth value is the cell height
		input >> m_AmountOfCol;
		input >> m_AmountOfRows;
		input >> cellWidth;
		input >> cellHeight;
		m_CellWidth = cellWidth;
		m_CellHeight = cellHeight;

		//create nested for loops to intialize each cell

		for (int row = 0; row < m_AmountOfRows; ++row)
		{
			for (int col = 0; col < m_AmountOfCol; ++col)
			{
				std::shared_ptr<Cell> cellToAdd = std::make_shared<Cell>();

				//set size
				cellToAdd->SetSize(cellWidth, cellHeight);
			

				//set pos

				float xPos = (col * cellWidth) + position.x;
				float yPos = (row * cellHeight) + position.y;

				cellToAdd->SetPos(xPos, yPos);


				//get input for col
				input >> value;


				

				switch (value)
				{
				case 0:
					cellToAdd->SetType(CellType::spawnable);
					break;
				case 1:
					cellToAdd->SetType(CellType::unspawnable);
					break;
				case 2:
					cellToAdd->SetType(CellType::teleport);
					break;
				}





				input >> value;
			



				switch (value)
				{
				case 5:
					//set to road
					cellToAdd->SetTexture("RoadTile.png");
					cellToAdd->SetCollision(false);
					if (cellToAdd->GetCellType() == CellType::spawnable)
					{
						m_SpawnMap.emplace_back(cellToAdd);
					}
					break;
				case 6:
					//set to wall
					cellToAdd->SetTexture("WallTile.png");
				//	cellToAdd->SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					cellToAdd->SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(cellToAdd);
					break;
				case 7:
					//set to tele[prt
					cellToAdd->SetTexture("Teleport.png");
					//cellToAdd->SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					cellToAdd->SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(cellToAdd); //maybe change this?
					break;
				}



	
				m_Map.emplace_back(cellToAdd);





			}
		}

		input.close();


		for (size_t i = 0; i < m_Map.size(); ++i)
		{
			auto cell = m_Map[i];
			auto cellPos = cell->GetPosition();

			if (cell->HasCollision())
			{
				cell->SetDirections(false, false, false, false);
				//cell->SetDirections(true, true, true, true); //set everything back to false when it works with collision
			}
			else
			{
				bool canGoUp = false;
				bool canGoDown = false;
				bool canGoLeft = false;
				bool canGoRight = false;

				//offset to make sure it is inside the cell, without it it sometimes gives a diff result a because of the collision when selecting a direction
				float offSet = 0;

				//left direction
				if (GetCell(Point2f{ cellPos.x + offSet - m_CellWidth, cellPos.y + offSet })->HasCollision())
				{
				
					canGoLeft = false;
				}
				else
				{
					canGoLeft = true;
				}

				//right direction
				if (GetCell(Point2f{ cellPos.x + offSet + m_CellWidth, cellPos.y + offSet })->HasCollision())
				{
					canGoRight = false;
					
				}
				else
				{

					canGoRight = true;
					
				}


				//top direction
				if (GetCell(Point2f{ cellPos.x + offSet, cellPos.y + offSet - m_CellHeight })->HasCollision())
				{
					canGoUp = false;
				}
				else
				{
					canGoUp = true;
				}


				//bot direction
				if (GetCell(Point2f{ cellPos.x + offSet, cellPos.y + m_CellHeight + offSet })->HasCollision())
				{
					canGoDown = false;
				}
				else
				{
					canGoDown = true;
				}

				cell->SetDirections(canGoUp, canGoDown, canGoLeft, canGoRight);

			}


		}

	}



	void TileMapComponent::Render()
	{

		for (size_t i = 0; i < m_Map.size(); ++i)
		{
			m_Map[i]->Render();
		}

	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetMap() const
	{
		return m_Map;

	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetCollisionMap() const
	{
		return m_CollisionMap;
	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetSpawnMap() const
	{
		return m_SpawnMap;
	}

	std::shared_ptr<Cell> TileMapComponent::GetCell(Point2f pos)
	{
		//grid doesnt necessarily have to start at 0,0 in the console
		pos.x -= m_Pos.x;

		pos.y -= m_Pos.y;




		

		return GetCell(int(pos.x / m_CellWidth) , int(pos.y / m_CellHeight));
	}

	std::shared_ptr<Cell> TileMapComponent::GetCell(int col, int row)
	{
		if (col < 0)
		{
			col = 0;
		}

		if (col >= m_AmountOfCol)
		{
			col = m_AmountOfCol - 1;
		}

		if (row < 0)
		{
			row = 0;
		}

		if (row >= m_AmountOfRows)
		{
			row = m_AmountOfRows - 1;
		}


		int index = row * m_AmountOfCol + col;


		return m_Map[index];


		 
	}

	void TileMapComponent::GetCellsAroundRect(Rectf rect, std::vector<std::shared_ptr<Cell>>& vectorOfCells)
	{
		//TODO: Change this so it is calculated or emplace it instead if it exceeds the size. depending if it hurts the performance or not
		//vectorOfCells.resize(30);

		//add the offset to get cells around + dont forget - instea dof + for height
		Point2f leftTop{rect.left - m_CellWidth, rect.bottom - rect.height - m_CellHeight};
		Point2f rightTop{rect.left + rect.width + m_CellWidth, rect.bottom - rect.height - m_CellHeight};
		Point2f leftBot{rect.left - m_CellWidth, rect.bottom + m_CellHeight};

		//Point2f rightBot{}

		int leftTopIndex = GetCellIndex(leftTop);
		int rightTopIndex = GetCellIndex(rightTop);
		int leftBotIndex = GetCellIndex(leftBot);

		//get the amount of cells between left and right corner
		int amountOfCols = (rightTopIndex  - leftTopIndex) + 1;
		int amountOfRows = (leftBotIndex - leftTopIndex) / m_AmountOfCol + 1;

		//put current element to 0 to overwrite
		int currentElement = 0;
		int currentIndex = leftTopIndex;

	

		for (int row = 0; row < amountOfRows; ++row)
		{
			currentIndex = leftTopIndex + m_AmountOfCol * row;

			for (int col = 0; col < amountOfCols; ++col)
			{
		
				if (currentElement >= int(vectorOfCells.size()))
				{
					vectorOfCells.emplace_back(m_Map[currentIndex]);
				}
				else
				{
					
					vectorOfCells[currentElement] = m_Map[currentIndex];
				}
			
				
			

					++currentIndex;
					++currentElement;
			}
			
			


		}
		
	

		


	}

	int TileMapComponent::GetCellIndex(int col, int row)
	{
		if (col < 0)
		{
			col = 0;
		}

		if (col >= m_AmountOfCol)
		{
			col = m_AmountOfCol - 1;
		}

		if (row < 0)
		{
			row = 0;
		}

		if (row >= m_AmountOfRows)
		{
			row = m_AmountOfRows - 1;
		}


		int index = row * m_AmountOfCol + col;
		return index;
	}


	int  TileMapComponent::GetCellIndex(Point2f pos)
	{
		pos.x -= m_Pos.x;

		pos.y -= m_Pos.y;






		return GetCellIndex(int(pos.x / m_CellWidth), int(pos.y / m_CellHeight));
	}

	void TileMapComponent::SetDirections()
	{
		
		//take cell
		//get neighbor, check if has col
		//if has col
		//direction is false

	}



}