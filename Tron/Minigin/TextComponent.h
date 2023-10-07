#include "BaseComponent.h"
#include "MiniginPCH.h"


namespace dae
{
	class Font;
	class RenderComponent;
	class GameObject;


	class TextComponent final : public BaseComponent
	{


	public:


		TextComponent(GameObject* go, const std::string& text, const std::shared_ptr<Font>& font, RenderComponent* renderComp, SDL_Color color);
		~TextComponent();
		void Update(float deltaTime) override;
		std::string& GetText();
		void SetText(std::string text);




	private:

		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		RenderComponent* m_pRenderComp;
		bool m_NeedsUpdate;

		SDL_Color m_Color;
	};

}