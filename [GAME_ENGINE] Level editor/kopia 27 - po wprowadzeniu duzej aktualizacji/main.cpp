#include <SDL.h>
#include "Setup.h"
#include "Error.h"
#include "Environment.h"
#include <iostream>

int main(int argc, char*argv[]) 
{
	try {
		Setup setup_game; // inicjuje grafikê, okno itd.

		Environment engine; // odpowiada za zdarzenia, renderowania i pilnowania operacji oraz przekierowywania
		engine.run();
	}
	catch (const std::string & str)
	{
		using std::cout;
		using std::endl;

		cout << str << endl;
	}
	SDL_Quit();
	return 0;
}