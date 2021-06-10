#pragma once
#include "Texture.h"

class Button // musi zosta� w przysz�o�ci zmienione - jak na razie zajmuje si� wa�niejszymi sprawami(14.07.2016r.) 
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

	const Texture & getTX() const { return tX; } // zwr�� textur� w celu uzyskania informacji o szeroko�ci lub d�ugo�ci

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

/*class Button_v2 { // zostanie wdro�one w przysz�o�ci i b�dzie to g��wna klasa bazowa
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

/*class Button_v3 { // inna alternatywa -> pe�ne wsparcie dla myszki(przycisi podstawowe, bez �adnych dodatkowych po bokach itd.)
public:
	Button_v3(SDL_Rect pos, std::string tX_name);
	virtual void events() // obsluguje zdarzenia klawiatury i myszy. Obsluguje tak�e inne zdarzenia przez klasy pochodne
	{
		reset_states();
		if (is_mouseOver) {
			if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
				&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
			{

			}
		}
	}
	virtual void render(); // klasa pochodna mo�e renderowa� inne dane -> np. tekst lub kilka warstw tekstur
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area); // renderowanie cz�ciowe

	// sprawdzenie czy myszka znajduje si� na pozycji przycisku -> dla klas pochodnych, by mo�na by�o bez potrzeby pisania warunk�w 
	// sprawdzi� t� funkcja i wykona� inne zdarzenia, kt�re r�ni� si�
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

	// czy klikni�to kt�ry� z klawisz�w myszy na obiekcie
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
	// tylko jedno klikni�cie przycisku i zerowanie stan�w
	virtual void on_mouseL1hit() = 0;
	virtual void on_mouseR1hit() = 0;
	virtual void on_mouseW1hit() = 0; // k�ko myszki przyci�ni�te

	// gdy trzymany przez jaki� czas przycisk myszy
	virtual void on_mouseL_press() = 0;
	virtual void on_mouseR_press() = 0;
	virtual void on_mouseW_press() = 0; // k�ko myszki przyci�ni�te
private:
	void reset_states() {
		mouse_over = false;
		mouseL_hit1 = mouseR_hit1 = middleMouse_1hit = false;
		//mouseL_pressed = mouseR_pressed = middleMouse_pressed = false;
	}
private:
	SDL_Rect position;

	Texture backgroundTX; // t�o 

	bool mouse_over{ false };

	bool mouseL_hit1{ false }, mouseR_hit1{ false }, middleMouse_1hit{ false };// klikni�ta raz myszka

	//bool middleMouse_pressed{ false };

	//bool mouseL_pressed{ false }, mouseR_pressed{ false }; // wci�ni�ty klawisz myszy i trzymany
};

class ButtonFunc : public Button_v3 {
public:
	ButtonFunc(SDL_Rect pos, std::string tX_name) : Button_v3{ pos, tX_name }
	{

	}
protected:
	// tylko jedno klikni�cie przycisku i zerowanie stan�w
	void on_mouseL1hit() override;
	void on_mouseR1hit() override;
	void on_mouseW1hit() override; // k�ko myszki przyci�ni�te

								   // gdy trzymany przez jaki� czas przycisk myszy
	void on_mouseL_press() override;
	void on_mouseR_press() override;
	void on_mouseW_press() override; // k�ko myszki przyci�ni�te
};*/