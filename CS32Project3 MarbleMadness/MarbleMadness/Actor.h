#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h" // remember to decide what should be constant and what needs to be included

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* sw, int ID, int x, int y, bool isVisible, bool isActive, int dir);
	virtual void doSomething();
	inline int getKey() const { // check if this is allowed
		int key;
		m_world->getKey(key);
		return key;
	}
	inline bool canMoveTo(double x, double y) { 
		return m_world->canMoveTo(x, y);
	}
	inline bool isActive() { 
		return m_active;
	}
	inline void setAlive(bool alive) {
		m_alive = alive;
	}
	virtual bool move(int dir);
	void shoot(int dir);
	inline virtual bool isAlive() {
		return m_alive;
	}
	inline void setActive(bool active) {
		m_active = active;
	}
	inline StudentWorld* getWorld() {
		return m_world; // is this against a rule or something idk im kinda lazy to check probably tho oh well
	}
	inline virtual void damage() {}
	inline void updateTick() {
		m_tickcount++;
	}
	inline int getTickCount() {
		return m_tickcount;
	}
	inline void setAttackable(bool attackable) {
		m_attackable = attackable;
	}
	inline bool isAttackable() {
		return m_attackable;
	}
	inline bool isPushable() {
		return m_pushable; // double check if this is allowed
	}
	inline void setPushable(bool pushable) {
		m_pushable = pushable;
	}
	inline bool isFillable() {
		return m_fillable; // double check
	}
	inline void setFillable(bool fillable) {
		m_fillable = fillable;
	}
	inline bool isGoodie() {
		return m_goodie;
	}
	inline void setGoodie(bool goodie) { // check if allowed
		m_goodie = goodie;
	}
	inline bool canSteal() {
		return m_canSteal;
	}
	inline void setCanSteal(bool canSteal) { // check if allowed
		m_canSteal = canSteal;
	}
private:
	StudentWorld* m_world;
	int m_tickcount = 0;
	bool m_active;
	bool m_alive = true;
	bool m_attackable = false;
	bool m_pushable = false;
	bool m_fillable = false;
	bool m_goodie = false;
	bool m_canSteal = false;
};

class Attackable : public Actor {
public:
	Attackable(StudentWorld* sw, int ID, int x, int y, bool isVisible, bool isActive, int health, int dir = 0)
		: Actor(sw, ID, x, y, isVisible, isActive, dir) {
		m_health = health;
		setAttackable(true);
	}
	inline void setHealth(double health) {
		m_health = health;
	}
	virtual inline void damage() {
		m_health -= 2;
		if (m_health <= 0) {
			setAlive(false);
			setVisible(false); // check if this is true for player idk
		}
	}
	inline double getHealth() {
		return m_health;
	}
private:
	double m_health;
};

class Goodie : public Actor {
public:
	Goodie(StudentWorld* sw, int ID, int x, int y);
	void pickUpGoodie(int score);
private:
};

class Pea : public Actor { // need to fix so pea does not attack pit...
public:
	Pea(StudentWorld* sw, int x, int y, int dir); // fix
	void doSomething();
	bool move(int dir);
private:
};

class Wall : public Actor {
public:
	Wall(StudentWorld* sw, int x, int y);
private:
};

class Robot : public Attackable {
public:
	Robot(StudentWorld* sw, int ID, int x, int y,  int health, int dir);
	virtual void damage();
	inline int getTicksPerMove() {
		return m_ticksPerMove;
	}
	bool canShoot(int dir);
private:
	int m_ticksPerMove;
};

class ThiefBot : public Robot
{
public:
	ThiefBot(StudentWorld* sw, int x, int y, int ID);
	void action();
	virtual void doSomething(); // add virtual to everything for good style
private:
	int m_distanceBeforeTurning;
	int m_squaresMoved = 0;
};
class MeanThiefBot : public ThiefBot
{
public:
	MeanThiefBot(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class Exit : public Actor {
public:
	Exit(StudentWorld* sw, int x, int y);
	void doSomething();
private:
	bool m_played = false;
};

class Avatar : public Attackable {  // what if player shoots pea when standing next to wall? 
public:
	Avatar(StudentWorld* sw, int x, int y);
	void doSomething();
	inline int getAmmo() const {
		return m_ammo;
	}
	inline void addAmmo(int ammo) {
		m_ammo += ammo;
	}
	bool move(int dir);
	virtual void damage();
private:
	int m_ammo = 20;
};

class RageBot : public Robot {
public:
	RageBot(StudentWorld* sw, int x, int y, int dir);
	void doSomething();
private:
	
};

class ThiefBotFactory : public Actor {
public:
	ThiefBotFactory(StudentWorld* sw, int x, int y, bool meanBot);
	virtual void doSomething();
private:
	bool m_meanBot;
};

class Marble : public Attackable {
public:
	Marble(StudentWorld* sw, int x, int y);
private:
};

class Pit : public Actor {
public:
	Pit(StudentWorld* sw, int x, int y);
	void doSomething();
private:
};

class Crystal : public Goodie {
public:
	Crystal(StudentWorld* sw, int x, int y);
	void doSomething();
private:
};

class RestoreHealth : public Goodie {
public:
	RestoreHealth(StudentWorld* sw, int x, int y);
	void doSomething();
private:
};

class ExtraLife : public Goodie {
public:
	ExtraLife(StudentWorld* sw, int x, int y);
	void doSomething();
private:
};

class Ammo : public Goodie {
public:
	Ammo(StudentWorld* sw, int x, int y);
	void doSomething();
private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
