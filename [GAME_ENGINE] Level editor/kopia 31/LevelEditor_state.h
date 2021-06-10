#pragma once

enum class LevelEditor_Main_state { // 
	NONE,
	IS_IN_LOCAL_MENU, // lokalne menu LEVEL, OBJECTS, SETTINGS
	IS_EDITING_LEVEL // czy edytowany level - nak�adanie obiekt�w na obszar edycji itd. - zmiana stanu mi�dzy 
};

enum class LevelEditor_Management_state { // stany zarz�dzania levelem - zapis, wczytywanie, tworzenie nowego levela itd.
	NONE, CREATE_NEW_LEVEL, SAVE_CURRENT_LEVEL, SAVE_AS, LOAD_LEVEL
};