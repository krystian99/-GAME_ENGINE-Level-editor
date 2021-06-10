#include "Button_Placing_EnemyOBJ.h"
#include "Enemy_Test.h"
#include "LevelEditor_manager.h"

Button_Placing_EnemyOBJ::Button_Placing_EnemyOBJ(Enemy_ID id, const SDL_Rect & pos) :
	Button_PlacingOBJ{ OBJ_TYPES::ENEMY, pos },
	enemy_id{ id }
{
	switch (enemy_id)
	{
	case Enemy_ID::TEST:
		texture = &Enemy_Test::getTexture();
		break;
	}
}

void Button_Placing_EnemyOBJ::events()
{
	Button_PlacingOBJ::events();
}

void Button_Placing_EnemyOBJ::render()
{
	Button_PlacingOBJ::render();
}

void Button_Placing_EnemyOBJ::onMouseOver()
{

}

void Button_Placing_EnemyOBJ::onClick()
{
	Button_PlacingOBJ::onClick();
	LevelEditor_manager::setPlacing_state_asENEMY(enemy_id);
}