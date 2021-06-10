#include "CoordinateBar_map.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Video_Info.h"

const SDL_Rect* CoordinateBar_map::edit_area{};
const SDL_Rect* CoordinateBar_map::map_area;

int CoordinateBar_map::x{};
int CoordinateBar_map::y{};

SDL_Rect CoordinateBar_map::position{};
std::string CoordinateBar_map::render_text{};
std::unique_ptr<Text> CoordinateBar_map::text_to_render{};

void CoordinateBar_map::events(bool mouse_over)
{
	if (mouse_over && Mouse::isUpdated()) {
		static const int& mX = Mouse::getX();
		static const int& mY = Mouse::getY();

		static double scaleX, scaleY;

		scaleX = double(mX - edit_area->x) / edit_area->w;
		scaleY = double(mY - edit_area->y) / edit_area->h;
		x = map_area->x + round(map_area->w * scaleX);
		y = map_area->y + round(map_area->h * scaleY);

		update_text();
	}
}

void CoordinateBar_map::render(bool mouse_over)
{
	if (mouse_over)
		text_to_render->render(0, text_to_render->getWidth());
}

void CoordinateBar_map::Init(const SDL_Rect& pos, const SDL_Rect* edit_a, const SDL_Rect* map_a)
{
	edit_area = edit_a;
	map_area = map_a;

	position.x = round(pos.x * Video_Info::get_scaleW());
	position.y = round(pos.y * Video_Info::get_scaleH());
	position.w = round(pos.w * Video_Info::get_scaleW());
	position.h = round(pos.h * Video_Info::get_scaleH());

	text_to_render = std::move(std::unique_ptr<Text>{ new Text{ pos.x + 50, pos.y + 10, "data/fonts/standard_font.ttf", 20,{ 255, 255, 255, 255 } } });
}

void CoordinateBar_map::update_text()
{
	render_text = "x: " + std::to_string(x) + "    " + " y: " + std::to_string(y);

	text_to_render->update(render_text);
}