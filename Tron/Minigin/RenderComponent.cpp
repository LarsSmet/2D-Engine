#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"


dae::RenderComponent::RenderComponent(GameObject* go, bool hasRotation, SDL_Point* rotationPoint) : BaseComponent{go}, m_HasRotation{ hasRotation }, m_Angle{0}, m_pRotationPoint{ rotationPoint }
{

}

dae::RenderComponent::~RenderComponent()
{
	delete m_pRotationPoint;
	m_pRotationPoint = nullptr;
}
void dae::RenderComponent::Update(float deltaTime)
{
	deltaTime;
	
	
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture() const
{
	return m_Texture;

	
}

void dae::RenderComponent::RotateForward(double angleIncrease)
{
	m_Angle += angleIncrease;
}

void dae::RenderComponent::SetRotation(double angle)
{
	m_Angle = angle;
}

void dae::RenderComponent::SetRotatePoint(Point2f point)
{
	m_pRotationPoint->x = int(point.x);
	m_pRotationPoint->y = int(point.y);
}

bool dae::RenderComponent::HasRotation() const
{
	return m_HasRotation;
}

double dae::RenderComponent::GetAngle() const
{
	return m_Angle;
}

SDL_Point* dae::RenderComponent::GetRotationPoint()
{
	return m_pRotationPoint;
}
