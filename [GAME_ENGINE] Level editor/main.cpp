#include <SDL.h>
#include "Setup.h"
#include "Error.h"
#include "Engine.h"
#include <fstream>

int main(int argc, char*argv[]) 
{
	try {
		// inicjuje grafikê, okno, statyczne dane itd.
		Setup setup_game;

		// odpowiada za zdarzenia, renderowania i pilnowania operacji oraz przekierowywania
		Engine engine;
		// uruchamia pêtlê g³ówn¹
		engine.run();
	}
	catch (const std::string & str)
	{
		std::ofstream log_exception{ "log_error.txt", std::ios_base::out };

		if (log_exception.is_open()) {
			using std::endl;

			log_exception << str << endl;
		}
		log_exception.close();
	}
	catch (...) {
		std::ofstream log_exception{ "log_error.txt", std::ios_base::out };

		if (log_exception.is_open()) {
			using std::endl;

			log_exception << "Something went wrong and program has aborted!" << endl;
		}
		log_exception.close();
	}

	SDL_Quit();

	return 0;
}