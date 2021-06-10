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
	virtual void events();

	bool is_clicked() const { return clicked; }
	bool mouse_is_over() const { return mouse_over; }

	bool is_selected() const { return selected; }

	void set_selectState(bool st);
	void switch_selected_state();

	static bool set_size_multiplier(double size);
	static void update_multiplierUP();
	static void update_multiplierDOWN();
	static const double & get_multiplier() { return SIZE_MULTIPLIER; }

	const SDL_Rect & get_renderPOS() const { return render_position; }

	void update_renderPOS(const int & render_X, const int & render_Y);
	void set_renderPOS(const int & x, const int & y, const int & w, const int & h);

	virtual ~Base_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
private:
	void mouse_handler();
protected:
	SDL_Rect render_position; // pozycja renderowania

	static double SIZE_MULTIPLIER;

	static constexpr double MULTIPLIER_ADD = 0.2;
private:
	bool clicked;

	bool selected; // czy wybrany obiekt

	bool mouse_over;
	bool l_bt_pressing;
};