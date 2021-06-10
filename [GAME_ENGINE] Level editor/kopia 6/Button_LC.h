#pragma once
#include "Button.h"
#include <string>

enum class ButtonType_LC { DYNAMIC, STATIC, KEY };

class Button_LC : public Button
{
public:
	Button_LC();
	Button_LC(std::string(*point)(int x, int y), std::string pathTX);

	void generateCode() const;

	~Button_LC();
private:
	std::string(*pointer)(int x, int y);
};

