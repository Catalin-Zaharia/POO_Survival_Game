#pragma once
#include "units.h"
#include <string>
class item
{
	loc currentLoc;
	std::string name = "";
	const int type=0;
public:
	item();
	~item();

	void remove();

	virtual void setName(std::string name = "");
	std::string Name();

	virtual void effect(unit* obj)=0;

	template <class T>
	friend loc getLocation(T* obj);
	template <class T>
	friend void setLocation(T* obj, int locX, int locY);
};

class healthPotion : public item {
	const int type = 1;
public:
	healthPotion();
	~healthPotion();

	void effect(unit *obj);
};

class damagePotion : public item {
	const int type = 2;
public:
	damagePotion();
	~damagePotion();

	void effect(unit* obj);
};

class speedPotion : public item {
	const int type = 3;
public:
	speedPotion();
	~speedPotion();

	void effect(unit* obj);
};

