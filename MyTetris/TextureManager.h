#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <iostream>



class TextureManager
{
public:
	static TextureManager* getInstance()
	{
		if (s_instance == 0)
		{
			s_instance = new TextureManager();
		}

		return s_instance;
	}
	bool load(std::string filename, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0);
	void write(char* text, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Color color);

private:
	static TextureManager* s_instance;

	TTF_Font* m_font;
	SDL_Texture* m_scoreTexture;

	TextureManager();
	~TextureManager();
	std::map<std::string, SDL_Texture*> m_textureMap;

};

