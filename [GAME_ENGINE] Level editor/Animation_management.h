#pragma once
#include <SDL_rect.h>
#include <vector>
#include "HitBox.h"
#include <string>
#include "Texture.h"
#include "Text.h"
#include "Module_base.h"

struct Frame_data {
	HitBox_data data;
};

class Animation_management : public Module_base // ustala hiboxy dla kazdej klatki animacji
{
public:
	Animation_management();

	void events();
	void events_indp();

	void render();
private:
	void set_hitbox();

	void mouse_handler_indp();
	void mouse_handler_dpnd();

	void keyboard_handler_indp();
	void keyboard_handler_dpnd();

	void set_NewConfig();
	void load_Config();

	void set_animation(const std::string & str);
private:
	SDL_Rect animBG_area;

	SDL_Rect edit_area;

	Texture animation;

	SDL_Rect hitbox_area; // jak na razie tylko do obszaru renderowania(pozniej co do animacji) -> prowadzone s¹ testy

	bool l_buttonPress{ false };
	bool mod_lcntrl_Z_PRESS{ false };
	bool is_hitBox_Set{ false };

	SDL_Rect preview, preview_area;

	int current_frame;

	Text frame_ofALL;

	std::vector<HitBox> hitboxes; // hitboxy(miejsca kolizji obiektów)

	int frame_width, frame_height;
};