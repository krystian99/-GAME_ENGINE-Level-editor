#pragma once
#include <vector>
#include "Button.h"
#include <SDL_render.h>
#include "Texture.h"
#include <string>

class Menu_local : public Button // to te¿ jest przycisk i powinien dziedziczyæ po klasie Button
{
	class Script { // test skryptu
	public:
		void run(); // wykonaj to co ma zrobiæ


	private:
		bool finished{ false }, running{ false };
	};
public:
	Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool can_hide, int expand);

	void render();
	void events();

	void operator=(const std::vector<Button*> & Buttons);
protected:
	void on_mouseL1hit() override;

	void on_Deactivate() override;
	void on_Activate() override;
private:
	void script_run();
	void script_leave();
private:
	std::vector<Button*> buttons;

	bool script_finished{ true };

	//Texture tX;

	bool can_hide;

	int button_height;

	Button * current_button{ nullptr };
};