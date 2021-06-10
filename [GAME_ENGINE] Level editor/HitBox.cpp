#include "HitBox.h"
#include <SDL_render.h>
#include "Renderer.h"

HitBox::HitBox(int x, int y, int w, int h, SDL_Color color)
{
	render_color = color;
	data.box = { x, y, w, h };
}

HitBox::HitBox(SDL_Rect hit, SDL_Color color)
{
	data.box = hit;
	render_color = color;
}

void HitBox::render()
{
	Renderer::set_renderColor(render_color);
	SDL_RenderDrawRect(Renderer::get(), &data.box);
	Renderer::set_defaultColor();
}

void HitBox::set_rangeOf_frames(int From, int To)
{
	data.frame_range = { From, To };
}