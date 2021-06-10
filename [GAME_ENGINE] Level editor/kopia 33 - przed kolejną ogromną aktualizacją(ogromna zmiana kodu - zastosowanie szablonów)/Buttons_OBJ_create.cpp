#include "Buttons_OBJ_create.h"
#include "Buttons_Functions_header.h"
#include "Enemy_Test.h"
#include "Enemy_TEST2.h"

void Buttons_OBJ_create::Enemy::create_TEST()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST, &Enemy_Test::getTexture());
}

void Buttons_OBJ_create::Enemy::create_TEST2()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST2, &Enemy_TEST2::getTexture());
}
