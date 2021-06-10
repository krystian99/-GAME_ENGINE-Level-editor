#include <SDL.h>
#include "Setup.h"
#include "Error.h"
#include "Engine.h"
#include <fstream>

int main(int argc, char*argv[]) 
{
	try {
		Setup setup_game; // inicjuje grafikê, okno, statyczne dane itd.

		Engine engine; // odpowiada za zdarzenia, renderowania i pilnowania operacji oraz przekierowywania
		engine.run(); // uruchamia pêtlê g³ówn¹
	}
	catch (const std::string & str)
	{
		std::ofstream log_exception{ "log_error.txt", std::ios_base::out };

		if (log_exception.is_open()) {

			//using std::cerr;
			using std::endl;

			//cerr << str << endl;
			log_exception << str << endl;
			//system("pause");
		}
		log_exception.close();
	}
	catch (...) {
		std::ofstream log_exception{ "log_error.txt", std::ios_base::out };

		if (log_exception.is_open()) {

			//using std::cerr;
			using std::endl;

			//cerr << str << endl;
			log_exception << "Something went wrong and program has aborted!" << endl;
			//system("pause");
		}
		log_exception.close();
	}
	SDL_Quit();
	return 0;
}