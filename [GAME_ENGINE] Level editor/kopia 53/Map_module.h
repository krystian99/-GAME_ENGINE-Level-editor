#pragma once


class Map_module // interfejs bazowy modu³ow mapy - jest bardzo potrzebny. Zwiêksza czytelnoœæ kodu w klasie Map oraz polepsza
				 // elastycznosc projektu. Najwa¿niejsz¹ kwesti¹ by projekt ten by³ rozszerzalny.
{
public:
	virtual void objects_events() = 0; // klikniêcie na obiekt itd.
	virtual void objects_events_indp() = 0;

	virtual void placing_object_events(int map_x, int map_y, int render_x, int render_y) = 0; // umieszczanie obiektow po klikniêciu lewego klawisza myszy
	virtual void single_objectSelecting_events() = 0;
	virtual void deleting_objects_events() = 0;

	void set_objectsRender_Active(bool b) { active_rendering = true; }
	bool is_objectRender_active() const { return active_rendering; } // czy mo¿e renderowaæ obiekty

	void set_viewActive(bool b) { active_rendering = true; }
protected: // zadeklaruj potrzebne metody do 
	virtual void on_placingEvents() {}
	virtual void on_movingEvents() {}
	virtual void on_selectingEvents() {}

	virtual void on_Map_mouseL_1hit() {}
private:
	bool active_rendering{ true }; // czy renderowanie obiektow jest aktywne
};