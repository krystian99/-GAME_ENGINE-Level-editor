#pragma once
#include <SDL_rect.h>

class Base_OBJ
{
public:
	//virtual void events();
	void events();

	bool is_clicked() const { return clicked; }
	bool mouse_is_over() const { return mouse_over; }

	bool is_selected() const { return selected; }

	void set_selectState(bool st);
	void switch_selected_state();

	static bool set_size_multiplier(double size);
	static void update_multiplierUP();
	static void update_multiplierDOWN();
	static const double & get_multiplier() { return SIZE_MULTIPLIER; }

	static void reset_multiplier();

	const SDL_Rect & get_renderPOS() const { return render_position; }

	void update_renderPOS(const int & render_X, const int & render_Y);
	void update_about(const int & render_X = 0, const int & render_Y = 0);
	void set_renderPOS(const int & x, const int & y, const int & w, const int & h);

	int left() const { return render_position.x; }
	int right() const { return render_position.x + render_position.w; }
	int up() const { return render_position.y; }
	int down() const { return render_position.y + render_position.h; }

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

	bool selected{ false }; // czy wybrany obiekt

	bool mouse_over{ false };
	bool l_bt_pressing{ false };
};