#pragma once
#include "Rect.h"
#include "Texture.h"
#include "Object.h"

struct Size {
	int mapW, mapH; // --||--
	int renderW, renderH; // ka¿dy obiekt egzemlarzu klasy szablonowej posiada jedn¹ kopiê wspó³dzielon¹ ze wszystkimi obiektami
};

struct MapOBJ_data {
	SDL_Rect mapPOS;
};

class MapOBJ : public Object
{
public:
	MapOBJ(){}
	MapOBJ(const Rect & render_position, const Rect & map_position);
	MapOBJ(SDL_Rect map_pos, const Size* sz);
	MapOBJ(const int& x, const int& y, const Size* sz);

	virtual void events();

	virtual void render();

	void set_mapPOS(int x, int y);
	void set_mapPOS(int x, int y, int w, int h);

	void set_mapX(int x);
	void set_mapY(int y);

	int get_mapX() const { return mapPOS.getX(); }
	int get_mapY() const { return mapPOS.getY(); }

	bool is_clicked() const { return clicked; }

	bool is_selected() const { return selected; }

	void set_selectState(bool st);
	void switch_selected_state();

	void update_Size();

	void update_mapPOS(int x, int y);

	void update_mapX(int X) { mapPOS.updateX(X); }
	void update_mapY(int Y) { mapPOS.updateY(Y); }

	int left_map() const { return mapPOS.left(); }
	int right_map() const { return mapPOS.right(); }
	int up_map() const { return mapPOS.up(); }
	int down_map() const { return mapPOS.down(); }

	void set_mapW(int w);
	void set_mapH(int h);

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
	virtual void on_mouseW1hit() {} // kó³ko nacisniete raz przyciœniête

	virtual void on_mouseOver() {} // gdy myszka na pozycji obiektu
	virtual void on_mouseOut() {} // gdy myszka nie jest ju¿ na pozycji przycisku

	// gdy trzymany przez jakiœ czas przycisk myszy
	virtual void on_mouseL_press() {}
	virtual void on_mouseR_press() {}
	virtual void on_mouseW_press() {}
protected:
	static double SIZE_MULTIPLIER;

	static constexpr double MULTIPLIER_ADD = 0.2;
private:

	bool clicked{ false };

	Rect mapPOS{};

	bool selected{ false }; // czy wybrany obiekt

	const Size* object_size;
};
