#pragma once

namespace Buttons_OBJ_create {
	namespace Enemy {
		void create_medium(); // musz¹ byæ komentarze - 100HP
		void create_heavy(); // 400 HP

		template <typename ID>
		void create_enemy(ID id);

		void create_TEST();
		void create_TEST2();
		void create_TEST3();
		void create_TEST4();

		void create_BOSS_1();

		// 1500 HP
	}
	namespace Other {
		void create_DOOR();
		void create_LADDER();
	}
}