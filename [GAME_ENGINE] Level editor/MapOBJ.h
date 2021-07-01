#pragma once
#include "Rect.h"
#include "Texture.h"
#include "Object.h"

/*struct MapOBJ_data {
	SDL_Rect mapPOS;
};*/

class MapOBJ : public Object
{
public:
	MapOBJ(){}
	MapOBJ(const Rect & render_position, const Rect & map_position);

	virtual void events();

	virtual void render();

	void set_mapPOS(int x, int y);
	void set_mapPOS(int x, int y, int w, int h);

	void set_mapX(int x);
	void set_mapY(int y);

	bool is_clicked() const { return clicked; }

	bool is_selected() const { return selected; }

	void set_selectState(bool st);
	void switch_selected_state();

	void update_mapPOS(int x, int y);

	void update_mapX(int X) { mapPOS.updateX(X); }
	void update_mapY(int Y) { mapPOS.updateY(Y); }

	int left_map() const { return mapPOS.left(); }
	int right_map() const { return mapPOS.right(); }
	int up_map() const { return mapPOS.up(); }
	int down_map() const { return mapPOS.down(); }

	int get_mapH() const { return mapPOS.getH(); }
	int get_mapW() const { return mapPOS.getW(); }

	SDL_Rect get_mapPOS() const { return mapPOS.get_position(); }

	static bool set_size_multiplier(double size);
	static void update_multiplierUP();
	static void update_multiplierDOWN();
	static const double& get_multiplier() { return SIZE_MULTIPLIER; }

	static void reset_multiplier();
protected:
	virtual void on_mouseL1hit() {}
	virtual void on_mouseR1hit() {}
	virtual void on_mouseW1hit() {} // k�ko nacisniete raz przyci�ni�te

	virtual void on_mouseOver() {} // gdy myszka na pozycji obiektu
	virtual void on_mouseOut() {} // gdy myszka nie jest ju� na pozycji przycisku

	// gdy trzymany przez jaki� czas przycisk myszy
	virtual void on_mouseL_press() {}
	virtual void on_mouseR_press() {}
	virtual void on_mouseW_press() {}
private:
	static double SIZE_MULTIPLIER;

	static constexpr double MULTIPLIER_ADD = 0.2;

	bool clicked{ false };

	Rect mapPOS{};

	bool selected{ false }; // czy wybrany obiekt
};
