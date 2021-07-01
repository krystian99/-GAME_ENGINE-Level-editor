#include "Map_events.h"
#include "Map.h"

void Map_events::events_enemies(Map*map)
{
	for (auto& enemy : map->enemies)
		enemy->events();
}

void Map_events::render_enemies(Map* map)
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& enemy : map->enemies) {
		//auto & pos = enemy->get_renderPOS();
		auto& pos_temp = enemy->get_renderPOS();
		Rect pos;
		pos.set_position(pos_temp);

		if (pos.left() >= map->edit_area.left() && pos.right() <= map->edit_area.right())
			enemy->render(); // renderuj ca³y obiekt
		else if (pos.left() <= map->edit_area.left() && pos.right() >= map->edit_area.left()) {
			temp_pos = { map->edit_area.left() , pos.up(), pos.right() - map->edit_area.left(), pos.getH() };

			auto& tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.getW());

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			if (enemy->is_flipped()) {
				//texture_area.w = tX.getWidth() - texture_area.x;
				texture_area.x = 0;
			}

			enemy->render(texture_area, temp_pos);
		}
		else if (pos.right() >= map->edit_area.right() && pos.left() <= map->edit_area.right()) {
			temp_pos = { pos.left(), pos.up(), map->edit_area.right() - pos.left(), pos.getH() };

			auto& tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.getW());

			texture_area.x = 0;
			texture_area.y = 0;
			texture_area.w = std::round(tX.getWidth() * scale);
			texture_area.h = tX.getHeight();

			if (enemy->is_flipped()) {
				texture_area.x = tX.getWidth() - texture_area.w;
				texture_area.w = tX.getWidth() - texture_area.x;
			}

			enemy->render(texture_area, temp_pos);
		}
	}
}

void Map_events::render_map(Map* map)
{
	map->mapBG.render(&map->mapBG_area.get_position(), &map->edit_area.get_position());

	SDL_SetRenderDrawColor(Renderer::get(), 120, 120, 120, 255);
	SDL_RenderDrawRect(Renderer::get(), &map->edit_area.get_position());
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}