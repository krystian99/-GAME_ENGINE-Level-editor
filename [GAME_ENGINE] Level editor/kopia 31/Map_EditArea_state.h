#pragma once

enum class Map_EditArea_state { NONE, PLACING_OBJECTS, MOVING_MAP, SELECTING_OBJECTS };
enum class Selecting_Obj_state { NONE, SINGLE, MULTI };
enum class Object_orient { RIGHT, LEFT };
enum class OBJ_type { NONE, ENEMY, PLAYER, GRAVITY_LINE };