#include "Game.h"
#include <iostream>
item::item()
{
	this->currentLoc.locX = 0;
	this->currentLoc.locY = 0;
}

item::~item()
{
}

void item::remove()
{
	setLocation(this, -1, -1);
}

void item::setName(std::string name)
{
	if (name == "")
		this->name = "item" + std::to_string(randNum(1, 1000));
	else
		this->name = name;
}

std::string item::Name()
{
	return this->name;
}

healthPotion::healthPotion()
{
	
}

healthPotion::~healthPotion()
{
}

void healthPotion::effect(unit* obj)
{
	obj->setHp(obj->Hp()+50);
	std::cout << obj->Name() << " was healed 50 health points" << "\n";
}

damagePotion::damagePotion()
{
}

damagePotion::~damagePotion()
{
}

void damagePotion::effect(unit* obj)
{
	obj->setDmg(obj->Dmg() + 5);
	std::cout << obj->Name() << " got a 5 damage increase" << "\n";
}

speedPotion::speedPotion()
{

}

speedPotion::~speedPotion()
{
}

void speedPotion::effect(unit* obj)
{
	obj->setAtkSpd((float)(obj->AtkSpd() - 1) / 10);
	std::cout << obj->Name() << " now attacks 0.1 seconds faster" << "\n";
}
