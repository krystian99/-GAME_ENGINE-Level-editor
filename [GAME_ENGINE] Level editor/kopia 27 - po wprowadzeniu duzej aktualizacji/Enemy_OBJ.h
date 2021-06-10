#pragma once
#include <SDL_render.h>
#include <string>
#include "Texture.h"

struct Enemy_data {
	int map_x, map_y;
	SDL_RendererFlip flip;
};
class Enemy_OBJ
{
public:
	Enemy_OBJ(const int & x1, const int & y1);

	static const int w = 30;
	static const int h = 50;

	void setPOS(const SDL_Rect & rt);
	void set_mapPOS(const int & X, const int & Y);
	void setRenderPos(const int & render_X, const int & render_Y);

	const bool & is_clicked() const { return clicked; }

	void events();
	void render();

	const int & getX() const { return x; }
	const int & getY() const { return y; }

	const Enemy_data & getData() const { return data; }

	static void setTexture(const std::string & bg);
private:
	void mouse_handler();
private:
	SDL_Rect render_position;

	bool clicked;

	Enemy_data data;

	static Texture TX;

	int x, y; // pozycja wzglêdem textury
};