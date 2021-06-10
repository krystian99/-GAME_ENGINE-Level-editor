#include "LevelCreator.h"
#include "Mouse.h"
#include "Setup.h"
#include "Button_ChangeSB_resources.h"

LevelCreator::LevelCreator() :
	sbStatic{ ButtonType_LC::STATIC },
	sbDynamic{ ButtonType_LC::DYNAMIC },
	sbKey{ ButtonType_LC::KEY },
	cur_ScrollBar{ CurrentScrollBar::DYNAMIC },
	editArea_state{ EditArea_LC_state::NONE },
	edition_area{},
	button_movingMAP{ edition_area.get_editState(), EditArea_LC_state::MOVING_MAP },
	button_selectingOBJ{ edition_area.get_editState(), EditArea_LC_state::SELECTING_OBJ },
	DynamicCHNG{ cur_ScrollBar, CurrentScrollBar::DYNAMIC },
	StaticCHNG{ cur_ScrollBar, CurrentScrollBar::STATIC },
	KeyCHNG{ cur_ScrollBar, CurrentScrollBar::KEY },
	TEST_CHNG{ cur_ScrollBar, CurrentScrollBar::TEST },
	testing{ edition_area.get_editState(), edition_area.get_mainState() },
	bt_deleteOBJ{ edition_area.get_editState() },
	bt_select{ edition_area.get_editState(), EditArea_LC_state::SELECTING_OBJ }
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

bool LevelCreator::loadLevel(const std::string & level_name)
{
	return edition_area.loadLevel_test(level_name);
}

void LevelCreator::newLevel(const std::string & level_name)
{
	edition_area.createLevel_test(level_name);
}

void LevelCreator::events(SDL_Renderer * rn)
{
	events_ButtonsChangeSB();
	events_ScrollBar();
	edition_area.events(rn);
	testing.events();
	bt_deleteOBJ.events();
	input_test.events();
	//load_test.events();
	save_test.events();
	bt_select.events();

	if (save_test.is_clicked())
		edition_area.saveLevel();
	/*if (load_test.is_clicked())
		edition_area.loadLevel();*/
}

void LevelCreator::render(SDL_Renderer * rn)
{
	render_ButtonsChangeSB(rn);
	render_ScrollBars(rn);
	edition_area.render(rn);
	testing.render(rn);
	bt_deleteOBJ.render(rn);
	input_test.render(rn);
	//load_test.render(rn);
	save_test.render(rn);
	bt_select.render(rn);
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
	testing.setRenderTEXT("files/lazy.ttf", "TEST"/* BUTTON"*/, 30, { 0, 0, 255, 255 });
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

void LevelCreator::Init_LoadSaveButtons(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH) // inicjuje tak¿e przycisk SELECT
{
	save_test.loadTX("data/textures/saveTX.png");

	int x, y;
	int w, h;
	SDL_Rect pos;

	x = dm->w - round(scaleW * 250);
	w = round(50 * scaleW);
	y = round(10 * scaleH);
	h = round(50 * scaleH);
	pos = { x, y, w, h };
	save_test.Init(pos);
}

void LevelCreator::Init_InputButton(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	SDL_Rect pos;
	pos.x = dm->w - round(scaleW * 500);
	pos.y = round(10 * scaleH);
	pos.w = round(100 * scaleW);
	pos.h = round(100 * scaleH);

	SDL_Color color = { 255, 0, 0, 255 };
	input_test.loadTX("data/input.png");
	input_test.Init(pos, "INPUT", dm, scaleW, scaleH);

	pos.x -= pos.w;
	pos.w = round(100 * scaleW);
	pos.h = round(50 * scaleH);
	bt_select.Init(pos);
	bt_select.loadTX("data/textures/select.png");
}

void LevelCreator::events_ScrollBar()
{
	switch (cur_ScrollBar)
	{
	case CurrentScrollBar::DYNAMIC:
		sbDynamic.events();
		break;
	case CurrentScrollBar::STATIC:
		sbStatic.events();
		break;
	case CurrentScrollBar::KEY:
		sbKey.events();
		break;
	}
}

void LevelCreator::events_ButtonsChangeSB()
{
	DynamicCHNG.events();
	StaticCHNG.events();
	KeyCHNG.events();
	TEST_CHNG.events();
}

void LevelCreator::render_ScrollBars(SDL_Renderer * rn)
{
	switch (cur_ScrollBar)
	{
	case CurrentScrollBar::DYNAMIC:
		sbDynamic.render(rn);
		break;
	case CurrentScrollBar::STATIC:
		sbStatic.render(rn);
		break;
	case CurrentScrollBar::KEY:
		sbKey.render(rn);
		break;
	}
}

void LevelCreator::render_ButtonsChangeSB(SDL_Renderer * rn)
{
	StaticCHNG.render(rn);
	DynamicCHNG.render(rn);
	KeyCHNG.render(rn);
	TEST_CHNG.render(rn);
}