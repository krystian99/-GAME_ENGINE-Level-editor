#pragma once
#include <vector>
#include "Button.h"
#include <SDL_render.h>
#include "Texture.h"
#include <string>
#include "Timer.h"

// Aby mo¿na by³o uogulniæ i stworzyæ klasê Script, trzeba najpierw przetestowaæ wykonanie skryptu dla pojedyñczego obiektu Menu_local.

enum class Script_state { SCRIPT_ENTERING, SCRIPT_LEAVING, NONE };
enum class MenuLocal_state { IN_IN_SCRIPT, NONE };

class Script { // test skryptu
			   // v1 -> mo¿na spokojnie usun¹æ timer'a je¿eli synchronizacja pionowa(V-sync) jest w³¹czona
public:
	Script(int speed) : move_speed{ speed }, move_speedY{ speed } // speed -> przesuniêcie danego przycisku
	{}

	void run();
	void leave(); // odwróæ sytuacjê skryptu - tutaj w przypadku menu_local wartosc

	bool is_finished() const { return finished; }

	int get_moveSpeedX() const { return script_state == Script_state::SCRIPT_ENTERING ? move_speedX : -move_speedX; }
	int get_moveSpeedY() const { return script_state == Script_state::SCRIPT_ENTERING ? move_speedY : -move_speedY; }

	void entering_events(std::vector<Button*> & buttons);
	void leaving_events(std::vector<Button*> & buttons);

	void events_buttons(std::vector<Button*> & buttons);
	void render_buttons(std::vector<Button*> & buttons, const int & render_fromY);

	void set_startPOS(int start);
	void set_endPOS(int end);
private:
	void move_buttons(std::vector<Button*> & buttons, int size);
private:
	Script_state script_state{ Script_state::NONE };
	int move_speed, move_speedX{ 0 }, move_speedY{ 0 };
	int start_posY, end_posY; // start_pos 
	bool finished{ false }, running{ false };
};

class Menu_local : public Button // to te¿ jest przycisk i powinien dziedziczyæ po klasie Button(teraz ju¿ dziedziczy)
{
public:
	Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool can_hide, int expand);

	void render();
	void events();

	const Script & get_scriptInfo() const { return script_test; }

	void events_indp();

	void operator=(const std::vector<Button*> & Buttons);
protected:
	void on_mouseL1hit() override;

	void on_Deactivate() override;
	void on_Activate() override;
private:
	std::vector<Button*> buttons;

	bool script_runned{ false };

	//Texture tX;

	Script script_test;
	MenuLocal_state stateMain{ MenuLocal_state::NONE };

	bool can_hide;

	int button_height;

	Button * current_button{ nullptr };
};