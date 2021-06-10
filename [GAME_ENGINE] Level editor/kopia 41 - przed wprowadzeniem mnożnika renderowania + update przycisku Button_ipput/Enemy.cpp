#include "Enemy.h"

void Enemy::render()
{
	tX->render(nullptr, &render_position, flip);
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

	return data;
}