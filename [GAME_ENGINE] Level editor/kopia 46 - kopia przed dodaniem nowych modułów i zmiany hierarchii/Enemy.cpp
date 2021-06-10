#include "Enemy.h"

const Enemy_data & Enemy::getData()
{
	data.flip = flip;
	data.id = id_enemy;
	data.mapPOS = mapPOS;

	return data;
}