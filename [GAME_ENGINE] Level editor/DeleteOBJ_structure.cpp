#include "DeleteOBJ_structure.h"

void DeleteOBJ_structure::events()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		auto& enemy = enemies[i];

		if (enemy->is_mouseKey_1hit(Mouse_key::L_BUTTON))
		{
			std::swap(enemies.back(), enemy);
			enemies.pop_back();
			break;
		}

	}
}
