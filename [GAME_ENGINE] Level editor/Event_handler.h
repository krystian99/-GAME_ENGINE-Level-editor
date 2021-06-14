#pragma once
#include <queue>
#include <SDL_events.h>
#include "Test_event_render.h"
#include "LevelCreator.h"

using namespace std;

using FUNCTION_VOID_NO_ARG = void(*)();

class Function
{
public:
	Function(FUNCTION_VOID_NO_ARG f);
	void run();
private:
	FUNCTION_VOID_NO_ARG function;
};

class Event_handler
{
public:
	static void push(Function f);

	static bool empty() { return events.empty(); }

	// zdejmij element z kolejki zdarzeñ i uruchom odpowiednie instrukcje
	static void process();

	static void pop() { events.pop(); }
private:
	static queue<Function> events;
	static SDL_Event event_handler;
};
