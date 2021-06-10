#include "Button_Input.h"

void Button_Input::Init(const SDL_Rect & rt, const std::string & dscrtpn, const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	Button::Init(rt);

	const SDL_Rect * pos = getPOS();

	text.setTEXT(dscrtpn);
	text.loadFont("lazy.ttf", pos->h / 2, { 255, 0, 0, 255 });
	text.loadFromText(dscrtpn, { 255, 0, 0, 255 });

	textPOS.x = FRAME_SIZE + pos->x;
	textPOS.y = pos->y - FRAME_SIZE;
	textPOS.w = text.getWidth();
	textPOS.h = text.getHeight();

	text.set_position(textPOS);

	Init_InputArea(dm, scaleW, scaleH);
}

void Button_Input::render(SDL_Renderer * rn)
{
	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, getPOS());
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);

	Button::render(rn);
	text.render(rn, textPOS.x, text.getWidth());

	input_area.render(rn);
}

void Button_Input::events()
{
	mouse_handler();
	if (Button::getState() == Button_State::SELECTED)
		input_area.events();
}

void Button_Input::setInput_Destricption(const std::string & dscrtpn)
{
	text.setTEXT(dscrtpn);
}

void Button_Input::onClick()
{
	Button::onClick();
}

void Button_Input::onMouseOver()
{
}

void Button_Input::Init_InputArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	const SDL_Rect * pos = getPOS();
	SDL_Rect rt;

	rt.x = std::ceil(double(pos->x) * scaleW);
	rt.h = std::ceil(double(pos->h / 2) * scaleH);
	rt.y = std::ceil(double(pos->y + pos->h - rt.h) * scaleH);
	rt.w = std::ceil(double(pos->x + pos->w - rt.x) * scaleW);

	input_area.Init(rt, rt.h, { 255, 0, 0, 255 });
	input_area.loadTX("data/input2.png");
}