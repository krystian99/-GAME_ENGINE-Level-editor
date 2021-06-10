#pragma once
#include "Enemy_OBJ.h"

namespace Enemy_Types // tworzy nowe egzemlarze klasy - dzi�ki temu, w ka�dym egzemlarzu szablonu s� niezale�ne sk�adowe statyczne(static)
{
	// domy�lne rozmiary obiekt�w
	using Enemy_Test = Enemy_OBJ<Enemy_ID::TEST, 20, 40>; // alias typu szablonowego
	using Enemy_Test2 = Enemy_OBJ<Enemy_ID::TEST2, 20, 40>;
	using Enemy_Test3 = Enemy_OBJ<Enemy_ID::TEST3, 20, 40>;
}