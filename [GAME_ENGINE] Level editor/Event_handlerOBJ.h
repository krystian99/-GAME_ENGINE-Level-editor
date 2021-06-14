#pragma once
class Event_handlerOBJ
{
public:
	virtual ~Event_handlerOBJ(){}
protected:
	virtual void render() {}

	virtual void mouse_events() {}
};