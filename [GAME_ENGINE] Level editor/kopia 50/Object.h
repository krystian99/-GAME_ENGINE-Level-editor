#pragma once
#include <SDL_render.h>
#include "Mouse.h"
#include "Keyboard.h"

class Object // przechwytywanie zdarzeñ myszy i klawiatury -> opakowany interfejs, który mo¿e zostaæ wykorzystany przez wszystkie obiekty
{
public:
	// czy klikniêto ten konkrenty przycisk na obiekcie?
	bool is_mouseKey_1hit(Mouse_key key) const { return key == mouse_key; };
	bool is_keyboardKey_1hit(Key key) const { return key == keyboard_key; }

	// Czy myszka jest na pozycji tego obiektu?
	bool is_mouseOver() const { return mouse_over; }

	void events(); // nie ma potrzeby ustawiaonia tej funkcji jako wirtualnej, bo klasa ta nie bêdzie s³u¿y³a jako interfejs polimorficzny -> jednak, by dzia³a³y funkcje tutaj zawarte, musi byæ wywo³ana ta metoda w klasie pochodnej

	void update_position(int renderX, int renderY);
	void update_about(int x_udpt, int y_updt); // dodaj podan¹ iloœæ do x i y
	void set_scaled_position(SDL_Rect pos);
	void set_position(SDL_Rect pos);
	SDL_Rect getPOS() const { return position; }

	virtual ~Object() {}
protected:
	// Ka¿da funkcja wirutalna nie jest czysto-wirtualna, by zachowaæ elastycznoœæ hierarchii klas.
	// Je¿eli dana klasa pochodna potrzebuje tej konkretnej metody wirtualnej, to mo¿e j¹ przes³oniæ. Je¿eli nie ma takiej metody
	// to trzeba j¹ zdefiniowaæ tutaj i przeci¹¿yæ w klasie pochodnej niezale¿nie od hierarchii klas np. B : A, C : B:
	// je¿eli B nie ma przesloniêtej metody z klasy A, która potrzebna jest w klasie C, to nie musimy tego robiæ, wystarczy ze klasa
	// bazowa klasy B dziedziczy po klasie udostpêniaj¹cej te metody i problem jest rozwi¹zany.

	// Pozostaje tylko kwestia uruchamiania funkcji spoza wszelkich klas -> na ten moment zostanie wdro¿ona ta wersja i przetestowana.

	// gdy przycisk myszy raz naciœniêty
	virtual void on_mouseL1hit() {}
	virtual void on_mouseR1hit() {}
	virtual void on_mouseW1hit() {} // kó³ko nacisniete raz przyciœniête

	// gdy trzymany przez jakiœ czas przycisk myszy
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