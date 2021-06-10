#include "CoordinateBar_mouse.h"
#include "Renderer.h"
#include "Video_Info.h"

CoordinateBar_mouse::CoordinateBar_mouse(const SDL_Rect & pos)
{
	position.x = round(pos.x * Video_Info::get_scaleW());
	position.y = round(pos.y * Video_Info::get_scaleH());
	position.w = round(pos.w * Video_Info::get_scaleW());
	position.h = round(pos.h * Video_Info::get_scaleH());

	text_to_render = std::unique_ptr<Text>{ new Text{ pos.x + 50, pos.y + 10, "data/fonts/standard_font.ttf", 20,{ 255, 255, 255, 255 } } };
}

void CoordinateBar_mouse::events()
{
	update_text();
}

void CoordinateBar_mouse::render()
{
	text_to_render->render(0, text_to_render->getWidth());
}

void CoordinateBar_mouse::set(const SDL_Rect * rt, const SDL_Rect * ru)
{
	cord = rt;
	cord2 = ru;
}

void CoordinateBar_mouse::update_text()
{
	render_text = "x: " + std::to_string(Mouse::getX()) + "    " + " y: " + std::to_string(Mouse::getY());

	text_to_render->update(render_text);
}