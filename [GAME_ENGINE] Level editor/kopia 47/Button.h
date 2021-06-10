#pragma once
#include "Texture.h"

class Button // musi zostaæ w przysz³oœci zmienione - jak na razie zajmuje siê wa¿niejszymi sprawami(14.07.2016r.) 
{
protected:
	using Function = void(*)();
public:
	Button(const SDL_Rect & pos);
	Button(const SDL_Rect & pos, const std::string & texture);
	Button(const std::string & texture);
	Button(const std::string & texture, Function on_click);
	Button(const std::string & texture, Function on_click, Function on_mouse_over);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click, Function on_mouse_over);

	virtual void render();
	virtual void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	virtual void events();

	const SDL_Rect & getPOS() const { return position; }

	bool is_clicked() const { return clicked; }
	bool is_mouseOver() const { return mouse_over; }
	bool is_selected() const { return selected; }

	const Texture & getTX() const { return tX; } // zwróæ texturê w celu uzyskania informacji o szerokoœci lub d³ugoœci

	void reset();

	void set_texture(const std::string & path);

	void update_position(const int & renderX, const int & renderY);
	void set_position(const SDL_Rect & pos);

	virtual ~Button() {}
private:
	void mouse_handler();
protected:
	virtual void onMouseOver();
	virtual void onClick();
protected:
	Texture tX; // background texture
	SDL_Rect position{}; // pozycja do renderowania
private:
	Function on_click_func{ nullptr };
	Function on_mouse_over_func{ nullptr };

	bool clicked{ false };
	
	bool selected{ false };

	bool mouse_over{ false };

	bool l_bt_pressing{ false };
};

/*class Button_v2 { // zostanie wdro¿one w przysz³oœci i bêdzie to g³ówna klasa bazowa
public:
	virtual void render() = 0;
	virtual void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area) = 0;

	virtual void setPOS(SDL_Rect) = 0; // wyznaczanie pozycji w dalszym etapie

	virtual bool is_mouseL1hit() = 0;
	virtual bool is_mouseR1hit() = 0;

	virtual bool is_mouseOver() = 0;

	virtual SDL_Rect getPOS() = 0;

	virtual void events() = 0;
};*/

/*class Button_v3 { // inna alternatywa -> pe³ne wsparcie dla myszki(przycisi podstawowe, bez ¿adnych dodatkowych po bokach itd.)
public:
	Button_v3(SDL_Rect pos, std::string tX_name);
	virtual void events() // obsluguje zdarzenia klawiatury i myszy. Obsluguje tak¿e inne zdarzenia przez klasy pochodne
	{
		reset_states();
		if (is_mouseOver) {
			if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
				&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
			{

			}
		}
	}
	virtual void render(); // klasa pochodna mo¿e renderowaæ inne dane -> np. tekst lub kilka warstw tekstur
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area); // renderowanie czêœciowe

	// sprawdzenie czy myszka znajduje siê na pozycji przycisku -> dla klas pochodnych, by mo¿na by³o bez potrzeby pisania warunków 
	// sprawdziæ t¹ funkcja i wykonaæ inne zdarzenia, które ró¿ni¹ siê
	bool is_mouseOver() const { 
		return mouse_over;

		if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
			&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
		{
			return true;
		}
		else
			return false;
	}

	// czy klikniêto któryœ z klawiszów myszy na obiekcie
	bool is_mouseL1hit() const { return mouseL_hit1; }
	bool is_mouseR1hit() const { return mouseL_hit1; }
	bool is_middleMouse_1hit() const { return middleMouse_1hit; }
	//bool is_mouseL_pressed() const { return mouseL_pressed; }

	// to 
	bool is_mouseR_pressed() const { return mouseR_pressed; }
	bool is_middleMouse_1hit() const { return middleMouse_1hit; }
	bool is_middleMouse_pressed() const { return middleMouse_pressed; }

	void set_position(SDL_Rect pos);
	SDL_Rect getPOS() const { return position; }
protected:
	// tylko jedno klikniêcie przycisku i zerowanie stanów
	virtual void on_mouseL1hit() = 0;
	virtual void on_mouseR1hit() = 0;
	virtual void on_mouseW1hit() = 0; // kó³ko myszki przyciœniête

	// gdy trzymany przez jakiœ czas przycisk myszy
	virtual void on_mouseL_press() = 0;
	virtual void on_mouseR_press() = 0;
	virtual void on_mouseW_press() = 0; // kó³ko myszki przyciœniête
private:
	void reset_states() {
		mouse_over = false;
		mouseL_hit1 = mouseR_hit1 = middleMouse_1hit = false;
		//mouseL_pressed = mouseR_pressed = middleMouse_pressed = false;
	}
private:
	SDL_Rect position;

	Texture backgroundTX; // t³o 

	bool mouse_over{ false };

	bool mouseL_hit1{ false }, mouseR_hit1{ false }, middleMouse_1hit{ false };// klikniêta raz myszka

	//bool middleMouse_pressed{ false };

	//bool mouseL_pressed{ false }, mouseR_pressed{ false }; // wciœniêty klawisz myszy i trzymany
};

class ButtonFunc : public Button_v3 {
public:
	ButtonFunc(SDL_Rect pos, std::string tX_name) : Button_v3{ pos, tX_name }
	{

	}
protected:
	// tylko jedno klikniêcie przycisku i zerowanie stanów
	void on_mouseL1hit() override;
	void on_mouseR1hit() override;
	void on_mouseW1hit() override; // kó³ko myszki przyciœniête

								   // gdy trzymany przez jakiœ czas przycisk myszy
	void on_mouseL_press() override;
	void on_mouseR_press() override;
	void on_mouseW_press() override; // kó³ko myszki przyciœniête
};*/