#include "Buttons_OBJ_create.h"
#include "Buttons_Functions_header.h"
#include "Enemy_Test.h"

void Buttons_OBJ_create::Enemy::create_TEST()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST, &Enemy_Test::getTexture());
}