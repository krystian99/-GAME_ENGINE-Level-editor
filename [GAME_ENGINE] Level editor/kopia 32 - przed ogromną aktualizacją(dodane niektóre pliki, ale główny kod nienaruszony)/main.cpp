#include <SDL.h>
#include "Setup.h"
#include "Error.h"
#include "Environment.h"
#include <iostream>

int main(int argc, char*argv[]) 
{
	try {
		Setup setup_game; // inicjuje grafik�, okno, statyczne dane itd.

		Environment engine; // odpowiada za zdarzenia, renderowania i pilnowania operacji oraz przekierowywania
		engine.run(); // uruchamia p�tl� g��wn�
	}
	catch (const std::string & str)
	{
		using std::cerr;
		using std::endl;

		cerr << str << endl;
		system("pause");
	}
	SDL_Quit();
	return 0;
}