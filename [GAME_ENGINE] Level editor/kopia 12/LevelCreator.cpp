#include "LevelCreator.h"
#include "Mouse.h"
#include "Setup.h"
#include "Button_ChangeSB_resources.h"

LevelCreator::LevelCreator() :
	sbStatic{ ButtonType_LC::STATIC },
	sbDynamic{ ButtonType_LC::DYNAMIC },
	sbKey{ ButtonType_LC::KEY },
	cur_ScrollBar{ CurrentScrollBar::DYNAMIC },
	edition_area{},
	button_movingMAP{ edition_area.get_editState(), EditArea_LC_state::MOVING_MAP },
	button_selectingOBJ{ edition_area.get_editState(), EditArea_LC_state::SELECTING_OBJ },
	DynamicCHNG{ cur_ScrollBar, CurrentScrollBar::DYNAMIC },
	StaticCHNG{ cur_ScrollBar, CurrentScrollBar::STATIC },
	KeyCHNG{ cur_ScrollBar, CurrentScrollBar::KEY },
	TEST_CHNG{ cur_ScrollBar, CurrentScrollBar::TEST },
	testing{ edition_area.get_editState(), edition_area.get_mainState() },
	bt_deleteOBJ{ edition_area.get_editState() }
{}

void LevelCreator::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	Init_buttonTEST(dm, scaleW, scaleH);
	Init_EditArea(dm, scaleW, scaleH);
	Init_buttonDeleteOBJ(dm, scaleW, scaleH);
	Init_ButtonsChangeSB(dm, scaleW, scaleH);
	ScrollBar::Init({ dm->w - int((100 * scaleW)), int(100 * scaleH), int(95 * scaleW), int(dm->h - (200 * scaleH)) }, scaleW, scaleH);
	Init_ScrollBars();
	Init_LoadSaveButtons(dm, scaleW, scaleH);
	Init_InputButton(dm, scaleW, scaleH);
}

void LevelCreator::events(SDL_Renderer * rn)
{
	events_ScrollBar(rn);
	edition_area.events(rn);
	events_ButtonsChangeSB(rn);
	testing.events(rn);
	bt_deleteOBJ.events(rn);
	input_test.events(rn);

	if (save_test.is_clicked())
		edition_area.saveLevel();
	if (load_test.is_clicked())
		edition_area.loadLevel();

	load_test.events(rn);
	save_test.events(rn);
	//Setup::PollEvents();
}

void LevelCreator::Init_ScrollBars()
{
	sbDynamic.InitButtons();
	sbKey.InitButtons();
	sbStatic.InitButtons();
}

void LevelCreator::Init_ButtonsChangeSB(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	SDL_Rect rt;
	int x, y, w, h;

	x = 5 * scaleW;
	w = 200 * scaleW;
	y = 5 * scaleH;
	h = 60 * scaleH;
	rt = { x, y, w ,h };
	DynamicCHNG.Init(rt);

	x += w;
	w = 160 * scaleW;
	rt = { x, y, w, h };
	StaticCHNG.Init(rt);

	x += w;
	w = 100 * scaleW;
	rt = { x, y, w, h };
	KeyCHNG.Init(rt);

	x += w;
	w = 100 * scaleW;
	rt = { x, y, w, h };
	TEST_CHNG.Init(rt);
	using namespace Button_ChangeSB_resources;

	DynamicCHNG.loadTX(Dynamic_backgroundTX);
	StaticCHNG.loadTX(Static_backgroundTX);
	KeyCHNG.loadTX(Key_backgroundTX);
	TEST_CHNG.loadTX(Dynamic_backgroundTX);

	DynamicCHNG.setRenderTEXT(TTF_path, "Dynamic", TTF_size, TTF_color);
	StaticCHNG.setRenderTEXT(TTF_path, "Static", TTF_size, TTF_color);
	KeyCHNG.setRenderTEXT(TTF_path, "Key", TTF_size, TTF_color);
	TEST_CHNG.setRenderTEXT(TTF_path, "TEST", TTF_size, TTF_color);
}

void LevelCreator::Init_buttonTEST(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	testing.Init({ dm->w - int(55 * scaleW), int(5 * scaleH), int(50 * scaleW), int(50 * scaleH) });
	testing.setRenderTEXT("files/lazy.ttf", "TEST BUTTON", 10, { 0, 0, 255, 255 });
}

void LevelCreator::Init_EditArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	edition_area.Init(dm, scaleW, scaleH);
	edition_area.load_MAP("data/levels/level1.png"); // TEST - w nastêpnych wersjach u¿ytkownik bêdzie wpisywa³ nazwê odpowiedniej textury
}

void LevelCreator::Init_buttonDeleteOBJ(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	SDL_Rect pos;
	pos.x = dm->w - int(double(scaleW * 200));
	pos.w = 50 * scaleW;
	pos.y = double(double(10) * scaleH);
	pos.h = 50 * scaleH;

	bt_deleteOBJ.setPosition(pos);

	bt_deleteOBJ.loadTX("data/bt_delete.png");
}

void LevelCreator::Init_LoadSaveButtons(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	load_test.loadTX("data/textures/loadTX.png");
	save_test.loadTX("data/textures/saveTX.png");

	int x, y;
	int w, h;
	SDL_Rect pos;

	x = dm->w - int(double(scaleW * 250));
	w = 50 * scaleW;
	y = double(double(10) * scaleH);
	h = 50 * scaleH;
	pos = { x,y,w,h };
	save_test.Init(pos);

	x -= 2* w;
	pos = { x,y,w,h };
	load_test.Init(pos);
}

void LevelCreator::Init_InputButton(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	SDL_Rect pos;
	pos.x = dm->w - int(double(scaleW * 500));
	pos.y = double(double(10) * scaleH);
	pos.w = double(100) * double(scaleW);
	pos.h = 100 * scaleH;

	SDL_Color color = { 255, 0, 0, 255 };
	input_test.loadTX("data/input.png");
	input_test.Init(pos, "INPUT", dm, scaleW, scaleH);
}

void LevelCreator::events_ScrollBar(SDL_Renderer * rn)
{
	switch (cur_ScrollBar)
	{
	case CurrentScrollBar::DYNAMIC:
		sbDynamic.events(rn);
		break;
	case CurrentScrollBar::STATIC:
		sbStatic.events(rn);
		break;
	case CurrentScrollBar::KEY:
		sbKey.events(rn);
		break;
	case CurrentScrollBar::TEST:
		//TEST.events(rn);
		break;
	}
}

void LevelCreator::events_ButtonsChangeSB(SDL_Renderer * rn)
{
	DynamicCHNG.events(rn);
	StaticCHNG.events(rn);
	KeyCHNG.events(rn);
	TEST_CHNG.events(rn);
}
