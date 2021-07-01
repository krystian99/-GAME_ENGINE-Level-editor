#include "Buttons_Functions_header.h"
#include "Buttons_Map_Functions.h"
#include "singleOBJmove_structure.h"

void Buttons_Map_Functions::onClick::delete_button()
{
	Map_manager::setMain_state(Map_state::DELETE_OBJECTS);
	//singleOBJmove_structure::setState(SingleOBJmove_events::SELECTING);
}

void Buttons_Map_Functions::onClick::single_select_button()
{
	Map_manager::setSelect_state(Selecting_Obj_state::SINGLE);
	Map_manager::setMain_state(Map_state::SELECTING_OBJECTS);
}

void Buttons_Map_Functions::onClick::multi_select_button()
{
	Map_manager::setSelect_state(Selecting_Obj_state::MULTI);
	Map_manager::setMain_state(Map_state::SELECTING_OBJECTS);
}

void Buttons_Map_Functions::onClick::moveMap_button()
{
	Map_manager::setMain_state(Map_state::MOVING_MAP);
}