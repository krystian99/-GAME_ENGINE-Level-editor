#pragma once
#include <queue>
#include <SDL_events.h>

using namespace std;

class Event_handler
{
	using FUNCTION = void(*)();
public:
	void push(FUNCTION f);
private:
	queue<FUNCTION> events;
	SDL_Event event_handler;
};