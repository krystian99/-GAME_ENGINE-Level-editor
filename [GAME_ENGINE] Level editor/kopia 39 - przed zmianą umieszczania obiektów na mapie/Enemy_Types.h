#pragma once
#include "Enemy_OBJ.h"

namespace Enemy_Types // tworzy nowe egzemlarze klasy - dzi�ki temu, w ka�dym egzemlarzu szablonu s� niezale�ne sk�adowe statyczne(static)
{
	using Enemy_Test = Enemy_OBJ<Enemy_ID::TEST, 70, 80>; // alias typu szablonowego
	using Enemy_Test2 = Enemy_OBJ<Enemy_ID::TEST2, 70, 80>;
	using Enemy_Test3 = Enemy_OBJ<Enemy_ID::TEST3, 70, 80>;
}