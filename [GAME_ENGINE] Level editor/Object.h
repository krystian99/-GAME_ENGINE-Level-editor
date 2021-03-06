#pragma once
#include <SDL_render.h>
#include "Mouse.h"
#include "Keyboard.h"

class Object // przechwytywanie zdarze? myszy i klawiatury -> opakowany interfejs, kt?ry mo?e zosta? wykorzystany przez wszystkie obiekty
{
public:
	// czy klikni?to ten konkrenty przycisk na obiekcie?
	bool is_mouseKey_1hit(Mouse_key key) const { return key == mouse_key; };
	bool is_keyboardKey_1hit(Key key) const { return key == keyboard_key; }

	// Czy myszka jest na pozycji tego obiektu?
	bool is_mouseOver() const { return mouse_over; }

	void events(); // nie ma potrzeby ustawiaonia tej funkcji jako wirtualnej, bo klasa ta nie b?dzie s?u?y?a jako interfejs polimorficzny -> jednak, by dzia?a?y funkcje tutaj zawarte, musi by? wywo?ana ta metoda w klasie pochodnej

	void mouseOver_deactivate(); // deaktywuj flag? mouse_over -> r?czne wymuszenie deaktywacji

	void update_position(int renderX, int renderY);
	void update_about(int x_udpt, int y_updt); // dodaj podan? ilo?? do x i y
	void set_scaled_position(SDL_Rect pos);
	void set_position(SDL_Rect pos);
	SDL_Rect getPOS() const { return position; }

	int left() const { return position.x; }
	int right() const { return position.x + position.w; }
	int up() const { return position.y; }
	int down() const { return position.y + position.h; }

	virtual ~Object() {}
protected:
	// ?adna z funkcji nie jest czysto-wirtualna, by zachowa? elastyczno?? hierarchii klas.
	// Je?eli dana klasa pochodna potrzebuje tej konkretnej metody wirtualnej, to mo?e j? przes?oni?. Je?eli nie ma takiej metody
	// to trzeba j? zdefiniowa? tutaj i przeci??y? w klasie pochodnej niezale?nie od hierarchii klas np. B : A, C : B:
	// je?eli B nie ma przesloni?tej metody z klasy A, kt?ra potrzebna jest w klasie C, to nie musimy tego robi?, wystarczy ze klasa
	// bazowa klasy B dziedziczy po klasie udostp?niaj?cej te metody i problem jest rozwi?zany.

	// Pozostaje tylko kwestia uruchamiania funkcji spoza wszelkich klas -> na ten moment zostanie wdro?ona ta wersja i przetestowana.

	// gdy przycisk myszy raz naci?ni?ty
	virtual void on_mouseL1hit() {}
	virtual void on_mouseR1hit() {}
	virtual void on_mouseW1hit() {} // k??ko nacisniete raz przyci?ni?te

	virtual void on_mouseOver() {} // gdy myszka na pozycji obiektu
	virtual void on_mouseOut() {} // gdy myszka nie jest ju? na pozycji przycisku

	// gdy trzymany przez jaki? czas przycisk myszy
	virtual void on_mouseL_press() {}
	virtual void on_mouseR_press() {}
	virtual void on_mouseW_press() {}
private: // funkcje
	void reset_states();

	void mouseEvents_1hit();
	void keyboardEvents_1hit();

	void mouse_handler();
	void keyboard_handler();
private:
	SDL_Rect position;
	bool mouse_over;

	Mouse_key mouse_key;
	Key keyboard_key;
};