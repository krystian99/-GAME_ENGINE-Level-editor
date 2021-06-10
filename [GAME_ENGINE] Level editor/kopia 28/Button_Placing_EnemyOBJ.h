#pragma once
#include "Enemy_ID.h"
#include "Button_PlacingOBJ.h"

class Button_Placing_EnemyOBJ : public Button_PlacingOBJ
{
public:
	Button_Placing_EnemyOBJ(Enemy_ID id, const SDL_Rect & pos);

	void events();
	void render();

	//const Enemy_ID & get_objID() const { return enemy_id; }

	~Button_Placing_EnemyOBJ() {}
protected:
	void onMouseOver();
	void onClick();
private:
	Enemy_ID enemy_id;
};