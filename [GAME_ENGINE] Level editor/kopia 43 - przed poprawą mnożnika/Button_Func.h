#pragma once
#include "Button.h"

template<typename Function>
class Button_Func : public Button // Bool button Func
{
public:
	Button_Func(const SDL_Rect & pos, const std::string & texture, Function on_click);

	void events();
	void render();
private:
	void onClick();
	void onMouseOver();
private:
	Function function;
};

template<typename Function>
inline Button_Func<Function>::Button_Func(const SDL_Rect & pos, const std::string & texture, Function on_click) :
	Button{ pos, texture }, function{ on_click }
{}

template<typename Function>
inline void Button_Func<Function>::events()
{
	Button::events();
}

template<typename Function>
inline void Button_Func<Function>::render()
{
	Button::render();
}

template<typename Function>
inline void Button_Func<Function>::onClick()
{
	if ((*function)())
}

template<typename Function>
inline void Button_Func<Function>::onMouseOver()
{

}