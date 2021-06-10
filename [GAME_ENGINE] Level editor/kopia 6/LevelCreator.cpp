#include "LevelCreator.h"
#include "Mouse.h"
#include "Exceptions.h"

LevelCreator::LevelCreator(const SDL_DisplayMode * dm) :
	sbStatic{ ButtonType::STATIC, SB_Orientation::VERTICAL },
	sbDynamic{ ButtonType::DYNAMIC, SB_Orientation::VERTICAL },
	sbKey{ ButtonType::KEY, SB_Orientation::HORIZONTAL }
{
	sbStatic.Init({ 0, 100, 100, dm->h - 200 });
	sbDynamic.Init({ dm->w - 100, 100, 100, dm->h - 200 });
	sbKey.Init({ 100 , 0, dm->w - 200, 100 });
}

void LevelCreator::setPosition(const SDL_DisplayMode * dm)
{

}
