#pragma once
#include "Button_TEXT.h"
#include <string>
#include "InputArea.h"

class Button_Input : public Button_TEXT
{
public:
	Button_Input() {}
	~Button_Input() {}

	void Init(const SDL_Rect & rt, const std::string & dscrtpn, const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void render(SDL_Renderer * rn);

	const std::string & getStrInput() const { return input_area.getStr(); }

	bool input_Is_empty() { return input_area.is_empty(); }

	void events();
private:
	void Init_InputArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void setInput_Destricption(const std::string & dscrtpn);

	void onClick();
	void onMouseOver();
private:
	InputArea input_area;
};

