#include "Enemy_TEST2.h"
#include "Video_Info.h"

Texture Enemy_TEST2::tX{};

Enemy_TEST2::Enemy_TEST2(const int & x, const int & y, SDL_RendererFlip flip) :
	Enemy_OBJ{ x, y, flip }
{
	render_position.w = std::round(width * Video_Info::get_scaleW());
	render_position.h = std::round(height * Video_Info::get_scaleH());

	id = Enemy_ID::TEST2;
}

void Enemy_TEST2::render()
{
	tX.render(nullptr, &render_position, flip);
}

void Enemy_TEST2::setTexture(const std::string & bg)
{
	tX.loadFromFile(bg);
}

void Enemy_TEST2::onMouseOver()
{

}

void Enemy_TEST2::onClick()
{

}