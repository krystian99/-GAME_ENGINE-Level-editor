#include "Buttons_OBJ_create.h"
#include "Buttons_Functions_header.h"
#include "Enemy_Types.h"

using namespace Enemy_Types;

void Buttons_OBJ_create::Enemy::create_TEST()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST, &Enemy_Test::getTexture());
}

void Buttons_OBJ_create::Enemy::create_TEST2()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST2, &Enemy_Test2::getTexture());
}

void Buttons_OBJ_create::Enemy::create_TEST3()
{
	Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID::TEST3, &Enemy_Test3::getTexture());
}