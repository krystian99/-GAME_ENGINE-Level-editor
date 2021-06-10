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

enum class SB_Orientation : char { HORIZONTAL, VERTICAL };

class ScrollBar
{
	enum class Mouse_Wheel_Dir : char { UP, DOWN };
public:
	ScrollBar(ButtonType type, SB_Orientation orientation);

	bool isButtonClicked();

	//bool scrollBarUse() const { return sb_use; }

	void SetPOSition(SDL_Rect );

	//void start_render(SDL_Renderer * rn);

	void render(SDL_Renderer * rn);

	void events(SDL_Event *);
	~ScrollBar() {}
private:
	//void loadTX();
	void Init(const SDL_Rect & rt);

	void mouse_handler();

	void load_images();

	// Ustawia pozycje przycisk�w
	void setButtonsPOS_horizontal(int size = 0);
	void setButtonsPOS_vertical(int size = 0);

	void setButtonsPOS(const int & size);

	void setWidthHeight(const int & width, const int & height); // Ustawia rozmiar ca�kowity Scroll Bar'a

	void switch_orientation(const int & size);

	void setHorizontal(const int & size);
	void setVertical(const int & size);

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

	static const int MOVE_SIZE = 50; // o ile pixeli maj� przesuwa� si� przyciski
	static const int FRAME_SIZE = 10; // ilo�� pixeli odst�pu mi�dzy pocz�tkiem scrollbara, a ko�cem scrollbara

	std::vector<Button> buttons;

	SB_Orientation orientation;

	ButtonType button_type;
};