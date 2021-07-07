#include "Enemy.h"

const Enemy_data & Enemy::getData()
{
	data.flip = flip;
	data.id = id_enemy;
	data.mapPOS = get_mapPOS();

	return data;
}

void Enemy::on_mouseOver()
{
	Dynamic_OBJ::on_mouseOver();
}

void Enemy::on_mouseOut()
{
	Dynamic_OBJ::on_mouseOut();
}
