#pragma once
#include "Button.h"

template<typename Return_type>
class Button_Func<bool> : public Button // Bool button Func
{
public:
	Button_Func(const SDL_Rect & pos, const std::string & texture, Function on_click);

	void events();
	void render();
protected:

private:
	Function function;
};

template<typename Return_type>
inline Button_Func<bool>::Button_Func(const SDL_Rect & pos, const std::string & texture, Function on_click)
{

}

template <typename Return_type>
class Button_Func<void> : public Button {

};