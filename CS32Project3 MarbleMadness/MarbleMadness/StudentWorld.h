#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>

class Actor;
class Avatar;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool canMoveTo(double x, double y);
	~StudentWorld();
	inline void addActor(Actor* actor) {
		m_actors.push_back(actor);
	}
	virtual Avatar* getPlayer() {
		return m_avatar;   // i think this is allowed?
	}
	inline void decreaseCrystals() {
		m_numCrystals--;
	}
	inline int getCrystals() {
		return m_numCrystals;
	}
	bool damageAll(int x, int y);
	bool eliminateMarble(int x, int y);
	void moveMarble(int x, int y, int dir);
	bool hasObstacles(int x, int y, int dir, int x2, int y2);
	bool hasGoodie(int x, int y);
	inline void setCompleted(bool completed) {
		m_completed = completed;
	}
	bool canGenerateThiefBots(int x1, int y1, int x2, int y2, int x, int y);
	void removeDead();
private:
	std::vector<Actor*> m_actors;
	Avatar* m_avatar;
	Level* m_level = nullptr;
	Level::LoadResult loadLevel(int i);
	std::string formatText(int score, int level, int lives, double health, int ammo);
	void setDisplayText();
	int numDigits(int i) const;
	bool hasActor(int x, int y) const;
	bool isFillable(int x, int y) const;
	int m_bonus = 1000;
	int m_levelNumber = 0;
	int m_numCrystals = 0;
	bool m_completed = false;
};

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

#endif // STUDENTWORLD_H_
