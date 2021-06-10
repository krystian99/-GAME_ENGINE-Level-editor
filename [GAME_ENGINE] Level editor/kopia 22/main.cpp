#include <SDL_main.h>
#include "Exceptions.h"
#include "Environment.h"
#include <iostream>

using namespace std;

int main(int argc, char*argv[]) {
	try {
		Environment LevelEditor;
		LevelEditor.run();
	}
	catch (Error & er)
	{
		cout << er.what() << endl;
	}
	return 0;
}