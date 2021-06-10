#pragma once
#include <SDL_rect.h>

class Base_OBJ
{
public:
	Base_OBJ() :
		clicked{ false },
		l_bt_pressing{ false },
		mouse_over{ false },
		selected{ false }
	{}

	virtual void render() = 0;
	virtual void events() = 0;

	bool is_clicked() const { return clicked; }
	bool mouse_is_over() const { return mouse_over; }

	bool is_selected() const { return selected; }

	void set_selectState(bool st);
	void switch_selected_state();

	const SDL_Rect & get_renderPOS() const { return render_position; }

	void update_renderPOS(const int & render_X, const int & render_Y);
	void set_position(const int & render_X, const int & render_Y);
	void set_renderPOS(const int & x, const int & y, const int & w, const int & h);

	virtual ~Base_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
private:
	void mouse_handler();
protected:
	SDL_Rect render_position; // pozycja renderowania
private:
	bool clicked;

	bool selected; // czy wybrany obiekt

	bool mouse_over;
	bool l_bt_pressing;
};