#pragma once
#include "BaseComponent.h"
#include "utils.h"

namespace dae
{

	class Texture2D;

	class RenderComponent final : public BaseComponent
	{

	public:
		RenderComponent(GameObject* go, bool hasRotation,SDL_Point* rotationPoint);
		~RenderComponent();
		void Update(float deltaTime) override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		std::shared_ptr<Texture2D> GetTexture() const;

		void RotateForward(double angleIncrease);

		
		void SetRotation(double angle);
		void SetRotatePoint(Point2f point);

		bool HasRotation() const;
		double GetAngle() const;
		SDL_Point* GetRotationPoint();

	private:


		bool m_HasRotation = false;
		double m_Angle = 0;
		SDL_Point* m_pRotationPoint;
		std::shared_ptr<Texture2D> m_Texture{};

	};

}

