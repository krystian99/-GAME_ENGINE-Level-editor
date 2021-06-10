#pragma once
#include <SDL_rect.h>

struct Frame_range {
	int From, To;
};

struct HitBox_data { // dane niezbêdne do zapisania w plikach konfiguracyjnych
	Frame_range frame_range;
	SDL_Rect box;

	SDL_Rect animationPOS;
};

class HitBox
{
public:
	HitBox(int x, int y, int w, int h, SDL_Color color);
	HitBox(SDL_Rect hit, SDL_Color color);

	const HitBox_data & getData() const { return data; }

	void render();

	void set_rangeOf_frames(int From, int To); // tylko zakresy równomierne - nie mog¹ byæ raz tu raz tu np.: 1-20. Ale ju¿ nie: 1-3, 4, 8-19;
private:
	SDL_Rect renderPOS; // , animationPOS;

	//SDL_Rect box; // pozycja hitBoxa
	SDL_Color render_color;

	HitBox_data data;
};