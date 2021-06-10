#include "Enemy_Test.h"
#include "Video_Info.h"

Texture Enemy_Test::tX{};

Enemy_Test::Enemy_Test(const int & x, const int & y, SDL_RendererFlip flip) :
	Enemy_OBJ{ x, y, flip }
{
	render_position.w = std::round(width * Video_Info::get_scaleW());
	render_position.h = std::round(height * Video_Info::get_scaleH());

	id = Enemy_ID::TEST;
}

void Enemy_Test::render()
{
	tX.render(nullptr, &render_position, flip);
}

void Enemy_Test::setTexture(const std::string & bg)
{
	tX.loadFromFile(bg);
}

void Enemy_Test::onMouseOver()
{
}

void Enemy_Test::onClick()
{

}