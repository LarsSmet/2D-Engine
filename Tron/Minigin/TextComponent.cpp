#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include <iostream>

//dae::TextComponent::TextComponent(GameObject* go,  std::string text,  std::shared_ptr<Font> font, RenderComponent * renderComp, SDL_Color color)
//	: BaseComponent(go), m_Text(text), m_Font(font), m_pRenderComp(renderComp), m_NeedsUpdate(true), m_Color{color}
//{
//
//}


dae::TextComponent::TextComponent(GameObject* go, const std::string& text, const std::shared_ptr<Font>& font, RenderComponent* renderComp, SDL_Color color) : 
	BaseComponent{go}, m_Text{text}, m_Font{font}, m_pRenderComp{renderComp}, m_Color{color}
{
}

dae::TextComponent::~TextComponent()
{

}

void dae::TextComponent::Update(float)
{
	
	

	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);

		if (surf == nullptr)
		{
			//throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			return;
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			//throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			return;
		}
		SDL_FreeSurface(surf);
		m_pRenderComp->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;

	}


}



std::string& dae::TextComponent::GetText()
{

	return m_Text;

}

void dae::TextComponent::SetText(std::string text)
{
	//text;
	m_Text = text;

	
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);

	if (surf == nullptr)
	{
		//throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		return;
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		//throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		return;
	}
	SDL_FreeSurface(surf);
	m_pRenderComp->SetTexture(std::make_shared<Texture2D>(texture));
	m_NeedsUpdate = false;
}
