#include "TextureManager.h"

TextureManager* TextureManager::s_instance = 0;

TextureManager::TextureManager() : m_scoreTexture(0)
{
	TTF_Init();

	m_font = TTF_OpenFont("arial.ttf", 65);
}


TextureManager::~TextureManager()
{
	delete m_scoreTexture;
	TTF_CloseFont(m_font);
	TTF_Quit();
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == 0)
	{
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture != 0)
	{
		m_textureMap[id] = texture;
		return true;
	}

	return false;
}


void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip, double angle)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::write(char* text, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, text, color);
	m_scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;


	SDL_RenderCopy(renderer, m_scoreTexture, &srcRect, &dstRect);

	SDL_DestroyTexture(m_scoreTexture);

}
