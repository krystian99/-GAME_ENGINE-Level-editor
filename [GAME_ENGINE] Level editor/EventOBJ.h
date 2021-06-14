#pragma once
#include "Event_handlerOBJ.h"

template <typename T>
class EventOBJ : public Event_handlerOBJ
{
	using Func = void (*)(T*);
public:
	EventOBJ(T* obj, Func func);
	~EventOBJ();
private:
	T* obj;
	Func func;
};

template<typename T>
inline EventOBJ<T>::EventOBJ(T* obj, Func func)
{
	this->obj = obj;
	this->func = func;
}

template<typename T>
inline EventOBJ<T>::~EventOBJ()
{
	func(obj);
}
