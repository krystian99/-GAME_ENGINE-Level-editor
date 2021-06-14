#pragma once
class Event_handlerOBJ
{
public:
	virtual void run() = 0;
protected:
	virtual void render() {}

	virtual void mouse_events() {}
};