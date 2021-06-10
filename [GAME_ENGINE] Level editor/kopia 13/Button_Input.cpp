#include "Button_Input.h"

void Button_Input::Init(const SDL_Rect & rt, const std::string & dscrtpn, const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	Button::Init(rt);

	const SDL_Rect * pos = getPOS();

	text.setTEXT(dscrtpn);
	text.loadFont("lazy.ttf", pos->h / 2, { 255, 0, 0, 255 });

	textPOS.x = FRAME_SIZE + pos->x;
	textPOS.y = pos->y;
	textPOS.w = text.getWidth();
	textPOS.h = text.getHeight();

	text.set_position(textPOS);

	Init_InputArea(dm, scaleW, scaleH);
}

void Button_Input::events(SDL_Renderer * rn)
{
	//const SDL_Rect * pos = getPOS();

	Button::render(rn);

	/*//TEST
	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, getPOS());
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);
	//END TEST*/
	text.render(rn, textPOS.x, text.getWidth());

	mouse_handler();

	if (Button::getState() == Button_State::SELECTED)
		input_area.get();
	input_area.events(rn);
}

void Button_Input::setInput_Destricption(const std::string & dscrtpn)
{
	text.setTEXT(dscrtpn);
	//description = dscrtpn;
}

void Button_Input::onClick()
{
}

void Button_Input::onMouseOver()
{
}

void Button_Input::Init_InputArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	const SDL_Rect * pos = getPOS();
	SDL_Rect rt;

	rt.x = double(pos->x) * scaleW;
	rt.h = double(pos->h / 2) * scaleH;
	rt.y = double(pos->y + pos->h - rt.h) * scaleH;
	rt.w = double(pos->x + pos->w - rt.x) * scaleW;

	input_area.Init(rt, rt.h, { 255, 0, 0, 255 });
	input_area.loadTX("data/input2.png");
}
