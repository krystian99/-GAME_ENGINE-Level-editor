#pragma once

enum class Map_state { NONE, PLACING_OBJECTS, MOVING_MAP, SELECTING_OBJECTS, DELETE_OBJECTS };
enum class Map_Functions { NONE, PLACING_OBJECTS, MOVING_MAP, SELECTING_OBJECTS, DELETE_OBJECTS };
enum class Map_Update_state { NONE, UPDATED_OBJECTS_SIZE };
enum class Selecting_Obj_state { NONE, SINGLE, MULTI };
enum class Object_orient { RIGHT, LEFT };
enum class OBJ_type { NONE, ENEMY, PLAYER, GRAVITY_LINE };