#pragma once
#include <SDL_render.h>
#include "Mouse.h"
#include "Keyboard.h"

class Object : public Rect // przechwytywanie zdarzeñ myszy i klawiatury -> opakowany interfejs, który mo¿e zostaæ wykorzystany przez wszystkie obiekty
{
public:
	Object(){}
	Object(Rect render_position) : 
		Rect{ render_position }
	{}
	Object(int x, int y, int w, int h) :
		Rect{ x, y, w, h }
	{}

	// czy klikniêto ten konkrenty przycisk na obiekcie?
	bool is_mouseKey_1hit(Mouse_key key) const { return is_mouseOver() && Mouse::pressedOnce(key); }
	bool is_keyboardKey_1hit(Key key) const { return is_mouseOver() && key == Keyboard::get_currentKey(); }

	// Czy myszka jest na pozycji tego obiektu?
	bool is_mouseOver() const { return mouse_over; }

	void events(); // nie ma potrzeby ustawiaonia tej funkcji jako wirtualnej, bo klasa ta nie bêdzie s³u¿y³a jako interfejs polimorficzny -> jednak, by dzia³a³y funkcje tutaj zawarte, musi byæ wywo³ana ta metoda w klasie pochodnej

	void mouseOver_deactivate(); // deaktywuj flagê mouse_over -> rêczne wymuszenie deaktywacji

	virtual ~Object() {}
protected:
	// ¯adna z funkcji nie jest czysto-wirtualna, by zachowaæ elastycznoœæ hierarchii klas.
	// Je¿eli dana klasa pochodna potrzebuje tej konkretnej metody wirtualnej, to mo¿e j¹ przes³oniæ. Je¿eli nie ma takiej metody
	// to trzeba j¹ zdefiniowaæ tutaj i przeci¹¿yæ w klasie pochodnej niezale¿nie od hierarchii klas np. B : A, C : B:
	// je¿eli B nie ma przesloniêtej metody z klasy A, która potrzebna jest w klasie C, to nie musimy tego robiæ, wystarczy ze klasa
	// bazowa klasy B dziedziczy po klasie udostpêniaj¹cej te metody i problem jest rozwi¹zany.

	// Pozostaje tylko kwestia uruchamiania funkcji spoza wszelkich klas -> na ten moment zostanie wdro¿ona ta wersja i przetestowana.

	// gdy przycisk myszy raz naciœniêty
	virtual void on_mouseL1hit() {}
	virtual void on_mouseR1hit() {}
	virtual void on_mouseW1hit() {} // kó³ko nacisniete raz przyciœniête

	virtual void on_mouseWheel_down_1hit() {}
	virtual void on_mouseWheel_up_1hit(){}

	virtual void on_mouseOver() {} // gdy myszka na pozycji obiektu
	virtual void on_mouseOut() {} // gdy myszka nie jest ju¿ na pozycji przycisku

	// gdy trzymany przez jakiœ czas przycisk myszy
	virtual void on_mouseL_press() {}
	virtual void on_mouseR_press() {}
	virtual void on_mouseW_press() {}

	// klawisze klawiatury wcisniete na obiekcie
	virtual void on_keyboardKey_A_1hit(){}
	virtual void on_keyboardKey_B_1hit(){}
	virtual void on_keyboardKey_C_1hit(){}
	virtual void on_keyboardKey_D_1hit(){}
	virtual void on_keyboardKey_E_1hit() {}
	virtual void on_keyboardKey_F_1hit() {}
	virtual void on_keyboardKey_G_1hit() {}
	virtual void on_keyboardKey_H_1hit() {}
	virtual void on_keyboardKey_I_1hit() {}
	virtual void on_keyboardKey_J_1hit() {}
	virtual void on_keyboardKey_K_1hit() {}
	virtual void on_keyboardKey_L_1hit() {}
	virtual void on_keyboardKey_M_1hit() {}
	virtual void on_keyboardKey_N_1hit() {}
	virtual void on_keyboardKey_O_1hit() {}
	virtual void on_keyboardKey_P_1hit() {}
	virtual void on_keyboardKey_Q_1hit() {}
	virtual void on_keyboardKey_R_1hit() {}
	virtual void on_keyboardKey_S_1hit() {}
	virtual void on_keyboardKey_T_1hit() {}
	virtual void on_keyboardKey_U_1hit() {}
	virtual void on_keyboardKey_V_1hit() {}
	virtual void on_keyboardKey_W_1hit() {}
	virtual void on_keyboardKey_X_1hit() {}
	virtual void on_keyboardKey_Y_1hit() {}
	virtual void on_keyboardKey_Z_1hit() {}

	virtual void on_keyboardKey_DELETE_1hit() {}
private:
	void keyboardEvents_1hit();

	void mouse_handler();
	void keyboard_handler();
private:
	bool mouse_over;
};