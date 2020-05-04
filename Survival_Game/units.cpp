#include "Game.h"
#include <iostream>
#include <string>
//unit methods

unit::unit()
{
	this->currentLoc.locX = 0;
	this->currentLoc.locY = 0;
	this->hp = 100;
	this->armor = 0;
	this->dmg = 0;
	this->atkSpd = 1;
	this->usable = false;
}

unit::unit(int locX, int locY, int hp, int armor, int dmg, int atkSpd, bool usable, std::string name)
{
	this->currentLoc.locX = locX;
	this->currentLoc.locY = locY;
	this->hp = hp;
	this->armor = armor;
	this->dmg = dmg;
	this->atkSpd = atkSpd;
	this->usable = usable;
	this->name = name;
}

unit::unit(const unit& obj)
{
	this->currentLoc = obj.currentLoc;
	this->hp = obj.hp;
	this->armor = obj.armor;
	this->dmg = obj.dmg;
	this->atkSpd = obj.atkSpd;
	this->usable = obj.usable;
	this->name = obj.name;
}

unit::~unit()
{
	if (this->usable) {
		if (!this->isAlive()) {
			std::cout << this->Name() << " has died in battle. " << '\n';
		}
		else {
			std::cout << this->Name() << " lives to see another day. " << '\n';
		}
	}
}

void unit::setUsing(bool value)
{
	this->usable = value;
}


void unit::setHp(int x) { 
	if (x < 0) { this->hp = 0; }
	else if (x > 100) { this->hp = 100; }
	else { this->hp = x; }
}

void unit::setArmor(int x) {
	if (x < 0) { this->armor = 0; }
	else if (x > 100) { this->armor = 100; }
	else { this->armor = x; }
}

void unit::setDmg(int x) {
	if (x > 0) { this->dmg = x; }
	else { this->dmg = 0; }
}

void unit::setAtkSpd(float x) {
	this->atkSpd = x*10000; 
}

void unit::setName(std::string name)
{
	if (name == "")
		this->name = "unit" + std::to_string(randNum(1, 1000));
	else
		this->name = name;
}

std::string unit::Name()
{
	return this->name;
}

int unit::Hp() { return this->hp; }

int unit::Armor() { return this->armor; }

int unit::Dmg() { return this->dmg; }

int unit::AtkSpd() { return this->atkSpd; }

bool unit::isAlive()
{
	if (this->Hp()>0)
	return true;
	return false;
}

void unit::move()
{
	if (this->isAlive()) {
		this->currentLoc.locX += 1;
		this->currentLoc.locY -= 2;
	}
}

void unit::dealDamage(unit& enemy) {
	int damage = this->Dmg();
	if (enemy.Armor() > 0) {
		enemy.setArmor(enemy.Armor() - damage);
	}
	else {
		enemy.setHp(enemy.Hp() - damage);
	}
}

void unit::engage(unit& enemy)
{
	if (this->isAlive() and enemy.isAlive()) {
		std::cout << this->Name() << " and " << enemy.Name() << " meet in combat" << '\n';
		int aSpd1 = this->AtkSpd(), aSpd2 = enemy.AtkSpd(), battleTime;
		this->dealDamage(enemy);
		enemy.dealDamage(*this);
		while (this->isAlive() and enemy.isAlive()) {
			battleTime = minim(aSpd1, aSpd2);
			if (battleTime % aSpd1 == 0) {
				this->dealDamage(enemy);
				aSpd1 += this->AtkSpd();
			}
			if (battleTime % aSpd2 == 0) {
				enemy.dealDamage(*this);
				aSpd2 += enemy.AtkSpd();
			}
		}
		if (!enemy.isAlive()) {
			enemy.remove();
		}
		if (!this->isAlive()) {
			this->remove();
		}
	}
}


void unit::remove()
{
	std::cout << this->Name() << " was slain." << '\n';
	this->setDmg(0);
	this->setHp(0);
	setLocation(this, -1, -1);
}

//
//

fighter::fighter()
{
	this->setArmor(100);
	this->setAtkSpd(1.2);
	this->setDmg(25);
}

void fighter::setName(std::string name)
{
	if (name == "")
		this->name = "Fighter" + std::to_string(randNum(1, 1000));
	else
		this->name = name;
}

thief::thief()
{
	this->setArmor(30);
	this->setAtkSpd(0.7);
	this->setDmg(16);
}

void thief::setName(std::string name)
{
	if (name == "")
		this->name = "Thief" + std::to_string(randNum(1, 1000));
	else
		this->name = name;
}

void thief::move()//nimble
{
	this->unit::move();
	this->unit::move();
}

archer::archer()
{
	this->setArmor(50);
	this->setAtkSpd(1);
	this->setDmg(21);
}

void archer::setName(std::string name)
{
	if (name == "")
		this->name = "Archer" + std::to_string(randNum(1, 1000));
	else
		this->name = name;
}

void archer::dealDamage(unit& enemy)//35% dmg ignores armor
{
	float damage = this->Dmg();
	if (enemy.Armor() > 0) {
		float armorDmg = damage * 0.65, hpDmg = damage * 0.35;
		enemy.setArmor(enemy.Armor() - armorDmg);
		enemy.setHp(enemy.Hp() - hpDmg);
	}
	else {
		enemy.setHp(enemy.Hp() - damage);
	}
}