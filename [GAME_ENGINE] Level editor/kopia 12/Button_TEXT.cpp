#include "Button_TEXT.h"

/*void Button_TEXT::setPOS_TEXT(const SDL_Rect & rt)
{
	textPOS = rt;
	text.set_position(rt);
}*/

void Button_TEXT::setRenderTEXT(std::string ttf_path, std::string renderedText, int height, SDL_Color color)
{
	text.setTEXT(renderedText);
	text.loadFont(ttf_path, height, color);

	const SDL_Rect * pos = getPOS();

	textPOS = { pos->x + FRAME_SIZE, pos->y, text.getWidth(), pos->h };

	text.set_position(textPOS);
}
