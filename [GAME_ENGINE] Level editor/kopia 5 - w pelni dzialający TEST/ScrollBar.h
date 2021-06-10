#pragma once
#include "Button.h"
#include <vector>
#include "Texture.h"

// v19:
// - poprawiono liczne bugi
// v20:
// - je�eli przyciski zajmuj� wi�ksz� powierzchni�(buttons_pos) ni� powiechnia scrollbara(bar_POS), to pokazywana
// jest tylko ta cz��, kt�ra mie�ci si� w wymiatach scrollBara.
// v21 - wyeliminowano b��d zwi�zany ze z�ym przesuwaniem przycisk�w k�kiem myszki
// v22 (02.27.2016):
// - poprawiono przesuwanie przycisk�w
// - dodano renderowanie cz�ci przycisku, gdy nie mie�ci� si� w ciele scrollbara
// - usuni�to liczne bugi
// - poprawiono tak�e g�rny(poziomy) scrollbar

enum class SB_Orientation : char { HORIZONTAL, VERTICAL };

class ScrollBar
{
	enum class Mouse_Wheel_Dir : char { UP, DOWN };
public:
	ScrollBar(ButtonType type, SB_Orientation orientation);

	void Init(const SDL_Rect & position);

	bool isButtonClicked();

	void render(SDL_Renderer * rn);

	void events(SDL_Event *);
	~ScrollBar() {}
private:
	//void loadTX();
	void buttons_events(); // zdarzenia przycisk�w

	void buttons_render(SDL_Renderer * rn);
	void buttons_render_horizontal(SDL_Renderer * rn, Button & bt); // horizontal
	void buttons_render_vertical(SDL_Renderer * rn, Button & bt); // vertical

	void mouse_handler();

	void load_images();

	// Ustawia pozycje przycisk�w
	void setButtonsPOS_horizontal(int size = 0);
	void setButtonsPOS_vertical(int size = 0);

	void setButtonsPOS(const int & size);

	void setWidthHeight(const int & width, const int & height); // Ustawia rozmiar ca�kowity Scroll Bar'a

	void switch_move_orient(const int & size);

	void moveHorizontal(const int & size); // przesun przyciski o podany rozmiar
	void moveVertical(const int & size); // przesun przyciski o podany rozmiar

	void setStartButtonPOS();
private:
	SDL_Rect barPOS; // Pozycja Scroll Bar'a

	struct Buttons_POS { // ca�kowite rozmiary
		int currentStartX, currentStartY;
		int currentEndX, currentEndY;
	};
	Buttons_POS buttons_pos;

	Texture tX;

	Mouse_Wheel_Dir mouse_wheelDir;

	static const int MOVE_SIZE = 30; // o ile pixeli maj� przesuwa� si� przyciski
	static const int FRAME_SIZE = 10; // ilo�� pixeli odst�pu mi�dzy pocz�tkiem scrollbara, a ko�cem scrollbara

	std::vector<Button> buttons;

	SB_Orientation orientation;

	ButtonType button_type;
};