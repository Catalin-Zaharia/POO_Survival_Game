#pragma once
#include "utils.h"
#include <string>
class unit
{
	loc currentLoc;
	unsigned int hp, armor, dmg, atkSpd;
	bool usable;
protected:
	std::string name= "";
public:
	unit();
	unit(int locX, int locY, int hp, int armor, int dmg, int atkSpd, bool usable= false, std::string name="");
	unit(const unit &obj);
	~unit();
	void setUsing(bool value);
	void setHp(int x);
	void setArmor(int x);
	void setDmg(int x);
	void setAtkSpd(float x);
	virtual void setName(std::string name="");
	std::string Name();
	int Hp();
	int Armor();
	int Dmg();
	int AtkSpd();
	bool isAlive();

	template <class T>
	friend loc getLocation(T *obj);
	template <class T>
	friend void setLocation(T *obj, int locX, int locY);

	virtual void move();

	virtual void dealDamage(unit& enemy);
	virtual void engage(unit& enemy);
	
	void remove();
};

class fighter ://bonus armor
	public unit
{
public:
	fighter();
	void move();
	void setName(std::string name = "");
};

class thief ://moves twice each round
	public unit
{
public:
	thief();
	void setName(std::string name = "");
	void move();
};

class archer ://attacks ignore armor
	public unit
{
public:
	archer();
	void dealDamage(unit& enemy);
	void setName(std::string name = "");
};

