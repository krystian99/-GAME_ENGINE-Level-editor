#include "Buttons_Functions_header.h"
#include "Buttons_Map_Functions.h"

void Buttons_Map_Functions::onClick::delete_button()
{
	Map_EditArea_manager::setMain_state(Map_EditArea_state::DELETE_OBJECTS);
}

void Buttons_Map_Functions::onClick::single_select_button()
{
	Map_EditArea_manager::setMain_state(Map_EditArea_state::SELECTING_OBJECTS);
	Map_EditArea_manager::setSelect_state(Selecting_Obj_state::SINGLE);
}

void Buttons_Map_Functions::onClick::multi_select_button()
{
	Map_EditArea_manager::setMain_state(Map_EditArea_state::SELECTING_OBJECTS);
	Map_EditArea_manager::setSelect_state(Selecting_Obj_state::MULTI);
}

void Buttons_Map_Functions::onClick::moveMap_button()
{
	Map_EditArea_manager::setMain_state(Map_EditArea_state::MOVING_MAP);
}