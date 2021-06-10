#pragma once

enum class Map_state { NONE, PLACING_OBJECTS, MOVING_MAP, MOVING_OBJECT, SELECTING_OBJECTS, DELETE_OBJECTS };
enum class Map_Functions { NONE, PLACING_OBJECTS, MOVING_MAP, SELECTING_OBJECTS, DELETE_OBJECTS };
enum class Map_Update_state { NONE, UPDATED_OBJECTS_SIZE, MODULE_CHANGED };
enum class Selecting_Obj_state { NONE, SINGLE, MULTI };
enum class Object_orient { RIGHT, LEFT };
enum class Current_MapModule { BLOCK_PLACER, ENEMIES_PLACER, INTERACT_OBJ_PLACER };
enum class OBJ_type { NONE, ENEMY, PLAYER, GRAVITY_LINE };