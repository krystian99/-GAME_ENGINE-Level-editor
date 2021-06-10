#include "Animation_management.h"
#include "Renderer.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "Animation_manager.h"

Animation_management::Animation_management() :
	frame_ofALL{ 400, 660, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	current_frame{ 1 }
{
	edit_area = { 400, 300, 320, 320 };
	Video_Info::set_scaledSize(edit_area); // przeskalowanie do innych ekranow

	preview = { 800, 500, 120, 120 };
	Video_Info::set_scaledSize(preview);
}

void Animation_management::events()
{
	keyboard_handler_dpnd();
	mouse_handler_dpnd();


}

void Animation_management::events_indp()
{
	switch (Animation_manager::get_mngState()) {
	case AnimConfig_mngState::NEW_CONFIG:
		set_NewConfig();
		Animation_manager::set_mngState(AnimConfig_mngState::NONE);
		break;
	case AnimConfig_mngState::LOAD_CONFIG:
		load_Config();
		Animation_manager::set_mngState(AnimConfig_mngState::NONE);
		break;
	}

	mouse_handler_indp();
	keyboard_handler_indp();
}

void Animation_management::render()
{
	Renderer::set_renderColor({ 0, 255, 0, 255 });
	SDL_RenderDrawRect(Renderer::get(), &edit_area);
	Renderer::set_defaultColor();

	animation.render(&animBG_area, &edit_area);

	if (Mouse::is_pressedL())
	{
		static const auto & point = Mouse::get_clickedPoint();
		if (point.x >= edit_area.x && point.x <= edit_area.x + edit_area.w
			&& point.y >= edit_area.y && point.y <= edit_area.y + edit_area.h)
		{
			Renderer::set_renderColor({ 0, 255 });
			SDL_RenderDrawRect(Renderer::get(), &hitbox_area);
			Renderer::set_defaultColor();
		}
	}
	for (auto & hitbox : hitboxes)
		hitbox.render();

	frame_ofALL.render();

	// [preview test] - pozniej bedzie opcja play, stop itd. oraz ustalenie liczby klatek na sekunde(FPS) - teraz jest tyle ile czestotliwosc odswiezania ekranu

	Renderer::set_renderColor({ 0, 255, 255, 255 });
	SDL_RenderDrawRect(Renderer::get(), &preview);
	Renderer::set_defaultColor();

	if (preview_area.x + frame_width < animation.getWidth())
		preview_area.x += frame_width;
	else {
		preview_area.x = 0;
	}
	animation.render(&preview_area, &preview);
	// [/preview test]
}

void Animation_management::set_hitbox()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	if (mX < Mouse::get_clickedPoint().x)
	{
		hitbox_area.x = mX;
		hitbox_area.w = Mouse::get_clickedPoint().x - mX;
	}
	else {
		hitbox_area.x = Mouse::get_clickedPoint().x;
		hitbox_area.w = mX - Mouse::get_clickedPoint().x;
	}
	if (mY < Mouse::get_clickedPoint().y) {
		hitbox_area.y = mY;
		hitbox_area.h = Mouse::get_clickedPoint().y - mY;
	}
	else {
		hitbox_area.y = Mouse::get_clickedPoint().y;
		hitbox_area.h = mY - Mouse::get_clickedPoint().y;
	}
}

void Animation_management::mouse_handler_indp()
{
	if (Mouse::getX() >= edit_area.x && Mouse::getX() <= edit_area.x + edit_area.w
		&& Mouse::getY() >= edit_area.y && Mouse::getY() <= edit_area.y + edit_area.h)
	{
		if (Mouse::is_pressedL()) {
			static const auto & point = Mouse::get_clickedPoint();
			if (point.x >= edit_area.x && point.x <= edit_area.x + edit_area.w
				&& point.y >= edit_area.y && point.y <= edit_area.y + edit_area.h)
			{
				is_hitBox_Set = true;
				set_hitbox();
			}
			else
				is_hitBox_Set = false;
			l_buttonPress = true;
		}
		else if (!Mouse::is_pressedL() && l_buttonPress && is_hitBox_Set) {
			hitboxes.push_back({ hitbox_area,{ 255 } });
			l_buttonPress = false;
		}
	}
}

void Animation_management::mouse_handler_dpnd()
{
	if (Mouse::getX() >= edit_area.x && Mouse::getX() <= edit_area.x + edit_area.w
		&& Mouse::getY() >= edit_area.y && Mouse::getY() <= edit_area.y + edit_area.h)
	{
		if (Mouse::getWheelState() != Mouse_wheel::NONE) {
			if (Mouse::getWheelState() == Mouse_wheel::UP) {
				if (animBG_area.x + frame_width < animation.getWidth()) {
					animBG_area.x += frame_width;
					current_frame++;
				}
				else {
					animBG_area.x = 0;
					current_frame = 1;
				}
			}
			else if (Mouse::getWheelState() == Mouse_wheel::DOWN) {
				if (animBG_area.x - frame_width >= 0) {
					animBG_area.x -= frame_width;
					current_frame--;
				}
				else {
					animBG_area.x = animation.getWidth() - frame_width;
					current_frame = Animation_manager::get_framesDigit();
				}
			}
			frame_ofALL.update(std::to_string(current_frame) + '/' + std::to_string(Animation_manager::get_framesDigit()));
		}
	}
}

void Animation_management::keyboard_handler_indp()
{
	static const Uint8 * key = SDL_GetKeyboardState(nullptr);

	if (key[SDL_SCANCODE_LCTRL] && key[SDL_SCANCODE_Z])
		mod_lcntrl_Z_PRESS = true;
	else if (!key[SDL_SCANCODE_Z] && mod_lcntrl_Z_PRESS) {
		if (hitboxes.size())
			hitboxes.pop_back();
		mod_lcntrl_Z_PRESS = false;
	}
}

void Animation_management::keyboard_handler_dpnd()
{

}

void Animation_management::set_NewConfig()
{
	set_animation(Animation_manager::get_animPath() + Animation_manager::get_animName() + ".png");
}

void Animation_management::load_Config()
{

}

void Animation_management::set_animation(const std::string & str)
{
	animation.loadFromFile(str);

	frame_width = animation.getWidth() / Animation_manager::get_framesDigit();
	frame_height = animation.getHeight();

	frame_ofALL.update("1/" + std::to_string(Animation_manager::get_framesDigit()));

	preview_area = animBG_area = { 0, 0, frame_width, frame_height };
}