#pragma once
#include "Button_LC.h"
#include <vector>
#include "Texture.h"

// v19:
// - poprawiono liczne bugi
// v20:
// - je¿eli przyciski zajmuj¹ wiêksz¹ powierzchniê(buttons_pos) ni¿ powiechnia scrollbara(bar_POS), to pokazywana
// jest tylko ta czêœæ, która mieœci siê w wymiatach scrollBara.
// v21 - wyeliminowano b³¹d zwi¹zany ze z³ym przesuwaniem przycisków kó³kiem myszki
// v22 (02.27.2016):
// - poprawiono przesuwanie przycisków
// - dodano renderowanie czêœci przycisku, gdy nie mieœci³ siê w ciele scrollbara
// - usuniêto liczne bugi
// - poprawiono tak¿e górny(poziomy) scrollbar
// v23 - ca³kowita przbudowa(koniec testów)

//enum class SB_Orientation : char { HORIZONTAL, VERTICAL }; // jak przesuwaæ przyciski

class ScrollBar // klasa bazowa
{
	enum class Mouse_Wheel_Dir : char { UP, DOWN };
public:
	ScrollBar(ButtonType_LC type);

	static void Init(const SDL_Rect & position, const double & scaleW, const double & scaleH);

	void InitButtons();

	void render(SDL_Renderer * rn);

	void events();

	~ScrollBar() {}
private:
	void buttons_events(); // zdarzenia przycisków

	void buttons_render(SDL_Renderer * rn);
	void buttons_render_vertical(SDL_Renderer * rn, Button_LC & bt); // vertical

	void mouse_handler();

	void load_images();

	// Ustawia pozycje przycisków
	void setButtonsPOS_horizontal(int size = 0);
	void setButtonsPOS_vertical(int size = 0);

	void setButtonsPOS(const int & size);

	void setWidthHeight(const int & width, const int & height); // Ustawia rozmiar ca³kowity przycisków

	void setButtons_LC();

	void moveHorizontal(const int & size); // przesun przyciski o podany rozmiar
	void moveVertical(const int & size); // przesun przyciski o podany rozmiar

	void setStartButtonPOS();
private:
	static SDL_Rect barPOS; // Pozycja Scroll Bar'a

	static int button_width;
	static int button_height;

	struct Buttons_POS { // ca³kowite rozmiary
		int currentStartX, currentStartY;
		int currentEndX, currentEndY;
	};
	Buttons_POS buttons_pos;

	static Texture background;

	Mouse_Wheel_Dir mouse_wheelDir;

	static const int MOVE_SIZE = 30; // o ile pixeli maj¹ przesuwaæ siê przyciski
	static const int FRAME_SIZE = 10; // iloœæ pixeli odstêpu miêdzy pocz¹tkiem scrollbara, a koñcem scrollbara

	std::vector<Button_LC> buttons;

	//SB_Orientation orientation;

	ButtonType_LC button_type;
};