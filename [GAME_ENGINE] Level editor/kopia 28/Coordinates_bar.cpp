#include "Coordinates_bar.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Video_Info.h"

Coordinates_bar::Coordinates_bar(const SDL_Rect & pos, const SDL_Rect * rt, const SDL_Rect * ru) :
	cord{ rt }, cord2{ ru }
{
	x = Mouse::getX();
	y = Mouse::getY();

	position.x = round(pos.x * Video_Info::get_scaleW());
	position.y = round(pos.y * Video_Info::get_scaleH());
	position.w = round(pos.w * Video_Info::get_scaleW());
	position.h = round(pos.h * Video_Info::get_scaleH());

	text_to_render = std::unique_ptr<Text>{ new Text{ position.x + 50, position.y + 10, "data/fonts/standard_font.ttf", 20,{ 255 } } };

	state = CoordinateBar_state::OTHER;
}

Coordinates_bar::Coordinates_bar(const SDL_Rect & pos)
{
	x = Mouse::getX();
	y = Mouse::getY();

	position.x = round(pos.x * Video_Info::get_scaleW());
	position.y = round(pos.y * Video_Info::get_scaleH());
	position.w = round(pos.w * Video_Info::get_scaleW());
	position.h = round(pos.h * Video_Info::get_scaleH());

	text_to_render = std::unique_ptr<Text>{ new Text{ position.x + 50, position.y + 10, "data/fonts/standard_font.ttf", 20,{ 255 } } };

	state = CoordinateBar_state::STANDARD;
}

void Coordinates_bar::events()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	switch (state)
	{
	case CoordinateBar_state::OTHER:
		static double scaleX, scaleY;

		scaleX = double(mX - cord->x) / cord->w;
		scaleY = double(mY - cord->y) / cord->h;
		x = cord2->x + round(cord2->w * scaleX);
		y = cord2->y + round(cord2->h * scaleY);
		break;
	case CoordinateBar_state::STANDARD:
		x = mX;
		y = mY;
		break;
	}
	update_text();
}

void Coordinates_bar::render()
{
	text_to_render->render(0, text_to_render->getWidth());
}

void Coordinates_bar::update_text()
{
	render_text = "x: " + std::to_string(x) + "    " + " y: " + std::to_string(y);

	text_to_render->update(render_text);
}