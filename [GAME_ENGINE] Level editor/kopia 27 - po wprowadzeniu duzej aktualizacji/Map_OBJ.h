#pragma once
#include <SDL_rect.h>

struct MapOBJ_data {
	int mapX, mapY;
};

class Map_OBJ
{
public:
	Map_OBJ() {}

	void set_mapPOS(const int & X, const int & Y);
	void setRenderPos(const int & render_X, const int & render_Y);

	const bool & is_clicked() const { return clicked; }

	void events();
	void render();

	virtual MapOBJ_data & getData() = 0;

	const int & getX() const { return mapX; }
	const int & getY() const { return mapY; }

	~Map_OBJ() {}
protected:
	SDL_Rect render_position;

	int mapX, mapY;
	bool clicked;
};

