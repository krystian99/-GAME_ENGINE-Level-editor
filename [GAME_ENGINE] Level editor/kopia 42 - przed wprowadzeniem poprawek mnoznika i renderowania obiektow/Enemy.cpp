#include "Enemy.h"

void Enemy::render()
{
	// test
	SDL_Rect temp_render, temp_map;
	temp_render = render_position;
	temp_map = mapPOS;

	temp_render.w = std::round(temp_render.w * SIZE_MULTIPLIER);
	temp_render.h = std::round(temp_render.h * SIZE_MULTIPLIER);

	temp_map.w = std::round(temp_map.w * SIZE_MULTIPLIER);
	temp_map.h = std::round(temp_map.h * SIZE_MULTIPLIER);

	tX->render(nullptr, &temp_render, flip);
	// end test
	
	
	//tX->render(nullptr, &render_position, flip); // przed aktualizacja
}

void Enemy::render(const SDL_Rect & tX_area, const SDL_Rect & destination_area)
{
	tX->render(&tX_area, &destination_area, flip);
}

void Enemy::events()
{
	Dynamic_OBJ::events();
}

const Texture & Enemy::getTX() const
{
	return *tX;
}

const Enemy_data & Enemy::getData()
{
	data.flip = flip;
	data.id = id_enemy;
	data.mapPOS = mapPOS;
	//data.mapPOS.w = std::round(mapPOS.w * SIZE_MULTIPLIER);
	//data.mapPOS.h = std::round(mapPOS.h * SIZE_MULTIPLIER);

	return data;
}

void Enemy::onClick()
{

}