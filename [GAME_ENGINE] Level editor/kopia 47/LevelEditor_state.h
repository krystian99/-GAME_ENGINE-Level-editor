#pragma once

enum class LevelEditor_Main_state { // 
	NONE,
	IS_IN_LOCAL_MENU, // lokalne menu LEVEL, OBJECTS, SETTINGS
	IS_EDITING_LEVEL // czy edytowany level - nak³adanie obiektów na obszar edycji itd. - zmiana stanu miêdzy 
};

enum class Current_scrollBar_type {
	DYNAMIC, // gracz i wrogowie -> rozwijalne menu: gracz mo¿e mieæ kilka ubrañ
	BLOCKS, // roznorakie bloki
	WEAPONS, // bronie

};

enum class LevelEditor_Management_state { // stany zarz¹dzania levelem - zapis, wczytywanie, tworzenie nowego levela itd.
	NONE, CREATE_NEW_LEVEL, SAVE_CURRENT_LEVEL, SAVE_AS, LOAD_LEVEL
};