#pragma once

enum class LevelEditor_state { 
	NONE, CREATE_NEW_LEVEL, SAVE_CURRENT_LEVEL, SAVE_AS, LOAD_LEVEL, PLACING_OBJECTS, MOVING_MAP, SELECTING_OBJECTS,
	SET_TEMP_OBJ, // ustala wymiary tymczasowego obiektu
	IS_IN_LOCAL_MENU // Czy klikniêty przycisk Level lub inne
};