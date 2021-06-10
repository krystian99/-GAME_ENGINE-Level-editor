#pragma once


class Map_module // interfejs bazowy modu�ow mapy - jest bardzo potrzebny. Zwi�ksza czytelno�� kodu w klasie Map oraz polepsza
				 // elastycznosc projektu. Najwa�niejsz� kwesti� by projekt ten by� rozszerzalny.
{
public:
	virtual void objects_events() = 0; // klikni�cie na obiekt itd.
	virtual void objects_events_indp() = 0;

	virtual void placing_object_events(int map_x, int map_y, int render_x, int render_y) = 0; // umieszczanie obiektow po klikni�ciu lewego klawisza myszy
	virtual void single_objectSelecting_events() = 0;
	virtual void deleting_objects_events() = 0;

	void set_objectsRender_Active(bool b) { active_rendering = true; }
	bool is_objectRender_active() const { return active_rendering; } // czy mo�e renderowa� obiekty

	void set_viewActive(bool b) { active_rendering = true; }
protected: // zadeklaruj potrzebne metody do 
	virtual void on_placingEvents() {}
	virtual void on_movingEvents() {}
	virtual void on_selectingEvents() {}

	virtual void on_Map_mouseL_1hit() {}
private:
	bool active_rendering{ true }; // czy renderowanie obiektow jest aktywne
};