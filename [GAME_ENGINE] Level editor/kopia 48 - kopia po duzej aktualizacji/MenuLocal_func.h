#pragma once
#include <string>

namespace MenuLocal_functions {
	namespace Menu_options {
		void button_Save();
		bool button_SaveAs(std::string str);
		bool button_Load(std::string str);
		void button_Exit();
	}
}