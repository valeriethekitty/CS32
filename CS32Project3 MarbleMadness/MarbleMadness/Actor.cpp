#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h" // unsure if i need this
#include <cstdlib> 
#include <time.h> 
#include <vector>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* sw, int ID, int x, int y, bool isVisible, bool isActive, int dir = 0)
    : GraphObject(ID, x, y, dir), m_world(sw)
{
    setVisible(isVisible);
    m_active = isActive; 
}

void Actor::doSomething()
{
    if (!isAlive()) {
        setVisible(false); // may have to just move this to studentworld since dosomething should do nothing
        return;
    }
    return;
}

Pea::Pea(StudentWorld* sw, int x, int y, int dir) : Actor(sw, IID_PEA, x, y, true, false, dir) {
    // how to get it visible for one second when hit wall
} 

void Pea::doSomething() { 
    updateTick();
    /*if (getTickCount() == 1) {
        setVisible(true);
    }*/
    if (!isAlive()) {
        return;
    }
    int dir = getDirection();
    
    if (getWorld()->damageAll(getX(), getY())) {
        setAlive(false);
    }
    if (isAlive()) {
        move(dir);
        if (getWorld()->damageAll(getX(), getY())) {
            setAlive(false);
        }
    } 
    if (!isAlive()) {
        setVisible(false);
    }
}

bool Pea::move(int dir) {
    if (dir == up) {
        moveTo(getX(), getY()+1);
    }
    else if (dir == down) {
        moveTo(getX(), getY()-1);
    }
    else if (dir == right) {
        moveTo(getX()+1, getY());
    }
    else if (dir == left) {
        moveTo(getX()-1, getY());
    }
    return true;
}

Wall::Wall(StudentWorld* sw, int x, int y) : Actor(sw, IID_WALL, x, y, true, true) {
    setAttackable(true);
}

ThiefBot::ThiefBot(StudentWorld* sw, int x, int y, int ID = IID_THIEFBOT) : Robot(sw, ID, x, y, 5, right) {
    std::srand((unsigned)std::time(NULL));
    m_distanceBeforeTurning = std::rand() % 6 + 1;
    setCanSteal(true);
}

void ThiefBot::action() { // also gets the same random numbers every time help
    if (getWorld()->hasGoodie(getX(), getY())) {
        int i = std::rand() % 10;
        if (i == 0) {
            // pick up goodie
            getWorld()->playSound(SOUND_ROBOT_MUNCH);
            return;
        }
    }
    if (m_squaresMoved < m_distanceBeforeTurning) {
        if (move(getDirection())) {
            m_squaresMoved++;
            return;
        }
    }
    m_distanceBeforeTurning = std::rand() % 6 + 1;
    m_squaresMoved = 0;
    bool directions[4] = { false, false, false, false };
    int i = std::rand() % 4;
    directions[i] = true;
    switch (i) {
    case 0:
        setDirection(right);
        break;
    case 1:
        setDirection(left);
        break;
    case 2:
        setDirection(up);
        break;
    case 3:
        setDirection(down);
        break;
    }
    move(getDirection());
    int count = 1;
    while (!move(getDirection()) && count < 4) {
        i = std::rand() % 4;
        while (directions[i] == true) {
            i = std::rand() % 4;
        }
        count++;
        directions[i] = true;
        switch (i) {
        case 0:
            setDirection(right);
            break;
        case 1:
            setDirection(left);
            break;
        case 2:
            setDirection(up);
            break;
        case 3:
            setDirection(down);
            break;
        }
    }
}
void ThiefBot::doSomething() {
    if (!isAlive()) {
        return;
    }
    updateTick();
    if (getTickCount() % getTicksPerMove() != 0) {
        return;
    }
    action();

    if (!isAlive()) {
        setVisible(false); // check if necessary idk
    }
}

MeanThiefBot::MeanThiefBot(StudentWorld* sw, int x, int y) : ThiefBot(sw, x, y, IID_MEAN_THIEFBOT) {

}

void MeanThiefBot::doSomething() {
    if (!isAlive()) {
        return;
    }
    updateTick();
    if (getTickCount() % getTicksPerMove() != 0) {
        return;
    }
    if (!canShoot(getDirection())) {
        action();
    }
    if (!isAlive()) {
        setVisible(false); // check if necessary idk
    }
}

Exit::Exit(StudentWorld* sw, int x, int y) : Actor(sw, IID_EXIT, x, y, false, false) {

}

void Exit::doSomething() {
    if (getWorld()->getCrystals() == 0 && m_played == false) {  
        setVisible(true);
        getWorld()->playSound(SOUND_REVEAL_EXIT);
        m_played = true;
    }
    if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY() && getWorld()->getCrystals() == 0) {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->increaseScore(2000); 
        getWorld()->setCompleted(true);
    }
}

Avatar::Avatar(StudentWorld* sw, int x, int y) : Attackable(sw, IID_PLAYER, x, y, true, true, 20, right) {

} 

bool Actor::move(int dir) {
    double y = getY();
    double x = getX();
    if (dir == up) {
        if (y < VIEW_HEIGHT - 1 && canMoveTo(x, y + 1)) {
            moveTo(x, y + 1);
            return true;
        }
    }
    else if (dir == down) {
        if (y > 0 && canMoveTo(x, y - 1)) {
            moveTo(x, y - 1);
            return true;
        }
    }
    else if (dir == right) {
        if (x < VIEW_WIDTH - 1 && canMoveTo(x + 1, y)) { // < or <=
            moveTo(x + 1, y);
            return true;
        }
    }
    else if (dir == left) {
        if (x > 0 && canMoveTo(x - 1, y)) {
            moveTo(x - 1, y);
            return true;
        }
    }
    return false; 
}

void Actor::shoot(int dir) {
    double y = getY();
    double x = getX();
    if (dir == right) {
        if (x <= VIEW_WIDTH - 1) {
            Pea* m_pea = new Pea(getWorld(), x + 1, y, dir);
            getWorld()->addActor(m_pea);
        }
    }
    else if (dir == left) {
        if (x > 0) {
            Pea* m_pea = new Pea(getWorld(), x - 1, y, dir);
            getWorld()->addActor(m_pea);
        }
    }
    else if (dir == up) {
        if (y <= VIEW_WIDTH - 1) {
            Pea* m_pea = new Pea(getWorld(), x, y + 1, dir);
            getWorld()->addActor(m_pea);
        }
    }
    else if (dir == down) {
        if (y > 0) {
            Pea* m_pea = new Pea(getWorld(), x, y - 1, dir);
            getWorld()->addActor(m_pea);
        }
    }
}

void Avatar::doSomething() {
    if (!isAlive()) {
        return;
    }
    int key = getKey();
    if (key == KEY_PRESS_UP) {
        setDirection(up); // do i need to set direction even if invalid, check on sample game
        move(up);
    }
    if (key == KEY_PRESS_DOWN) {
        setDirection(down); // do i need to set direction even if invalid, check on sample game
        move(down);
    }
    if (key == KEY_PRESS_RIGHT) {
        setDirection(right); // do i need to set direction even if invalid, check on sample game
        move(right);
    }
    if (key == KEY_PRESS_LEFT) {
        setDirection(left); // do i need to set direction even if invalid, check on sample game
        move(left);
    }
    if (key == KEY_PRESS_SPACE) {
        int dir = getDirection(); // play shoot sound
        if (m_ammo > 0) {
            shoot(dir);
            getWorld()->playSound(SOUND_PLAYER_FIRE);
            m_ammo--;
        }
    }
    if (key == KEY_PRESS_ESCAPE) {
        setAlive(false);
        getWorld()->playSound(SOUND_PLAYER_DIE);
        getWorld()->decLives();
    }
    if (!isAlive()) { // ???
        
    }
}

bool Avatar::move(int dir) {
    if (dir == up) {
        getWorld()->moveMarble(getX(), getY() + 1, dir);
    }
    else if (dir == down) {
        getWorld()->moveMarble(getX(), getY() - 1, dir);
    }
    else if (dir == right) {
        getWorld()->moveMarble(getX() + 1, getY(), dir);
    }
    else if (dir == left) {
        getWorld()->moveMarble(getX() - 1, getY(), dir);
    }
    if (Actor::move(dir)) {
        return true;
    }   
    return false;
}

void Avatar::damage() {
    Attackable::damage();
    if (getHealth() > 0) {
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_DIE);
        getWorld()->decLives();
    }
}


// i dont know how to set up the robot inheritance
Robot::Robot(StudentWorld* sw, int ID, int x, int y, int health, int dir) : Attackable(sw, ID, x, y, true, true, health, dir) {
    m_ticksPerMove = (28 - getWorld()->getLevel()) / 4; // the current level number (0, 1, 2, etc.)
    if (m_ticksPerMove < 3) {
        m_ticksPerMove = 3; // no RageBot moves more frequently than this
    }
}

void Robot::damage() {
    Attackable::damage();
    if (getHealth() > 0) {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
    else {
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
    }
}

bool Robot::canShoot(int dir) {
    int x = getWorld()->getPlayer()->getX();
    int y = getWorld()->getPlayer()->getY();
    if ((x > getX() && y == getY() && dir == right) || (x < getX() && y == getY() && dir == left) || (x == getX() && y > getY() && dir == up) || (x == getX() && y < getY() && dir == down)) {
        if (!getWorld()->hasObstacles(getX(), getY(), dir, x, y)) {
            shoot(dir);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        return true;
    }
    return false;
}

RageBot::RageBot(StudentWorld* sw, int x, int y, int dir) : Robot(sw, IID_RAGEBOT, x, y, 10, dir) { // fix
    
}

void RageBot::doSomething() {
    if (!isAlive()) { 
        return;
    }
    updateTick();
    if (getTickCount() % getTicksPerMove() != 0) {
        return;
    }
    int dir = getDirection();
    if (canShoot(dir)) {
        return;
    }
    if (!move(dir)) {
        if (dir == right) {
            setDirection(left);
        }
        else if (dir == left) {
            setDirection(right);
        }
        else if (dir == up) {
            setDirection(down);
        }
        else if (dir == down) {
            setDirection(up);
        }
    }
}

ThiefBotFactory::ThiefBotFactory(StudentWorld* sw, int x, int y, bool meanBot) : Actor(sw, IID_ROBOT_FACTORY, x, y, true, true) {
    std::srand((unsigned)std::time(NULL));
    setAttackable(true); // is this against the spec to repeat this code :(
    m_meanBot = meanBot;
}

void ThiefBotFactory::doSomething() {
    int x = getX();
    int y = getY();
    int x1 = x - 3;
    int x2 = x + 3;
    int y1 = y - 3;
    int y2 = y + 3;
    if (x1 < 0) {
        x1 = 0;
    }
    if (y1 < 0) {
        y1 = 0;
    }
    if (x2 >= VIEW_WIDTH) {
        x2 = VIEW_WIDTH - 1;
    }
    if (y2 >= VIEW_HEIGHT) {
        y2 = VIEW_HEIGHT - 1;
    }
    if (getWorld()->canGenerateThiefBots(x1, y1, x2, y2, x, y)) {
        int i = std::rand() % 50;
        if (i == 0) {
            if (m_meanBot) { 
                getWorld()->addActor(new ThiefBot(getWorld(), x, y, IID_MEAN_THIEFBOT));
            }
            else {
                getWorld()->addActor(new ThiefBot(getWorld(), x, y, IID_THIEFBOT));
            }
            getWorld()->playSound(SOUND_ROBOT_BORN);
        }
        else {
            return;
        }
    }
}



Marble::Marble(StudentWorld* sw, int x, int y) : Attackable(sw, IID_MARBLE, x, y, true, true, 10) { // fix marble active
    setPushable(true); // double check
}

Pit::Pit(StudentWorld* sw, int x, int y) : Actor(sw, IID_PIT, x, y, true, true) {
    setFillable(true);
}

void Pit::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->eliminateMarble(getX(), getY())) {
        setAlive(false);
    }
    if (!isAlive()) {
        setVisible(false); // ig not necessary
    }
}

Goodie::Goodie(StudentWorld* sw, int ID, int x, int y) : Actor(sw, ID, x, y, true, false) {
    setGoodie(true);
}

void Goodie::pickUpGoodie(int score) {
        getWorld()->increaseScore(score);
        setAlive(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
}

Crystal::Crystal(StudentWorld* sw, int x, int y) : Goodie(sw, IID_CRYSTAL, x, y) {
}

void Crystal::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()) {
        pickUpGoodie(50);
        getWorld()->decreaseCrystals();
    }
    if (!isAlive()) {
        setVisible(false); // repeating this a lot, move to somewhere else???
    }
}

RestoreHealth::RestoreHealth(StudentWorld* sw, int x, int y) : Goodie(sw, IID_RESTORE_HEALTH, x, y) {
    
}

void RestoreHealth::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()) {
        pickUpGoodie(500);
        getWorld()->getPlayer()->setHealth(20);
    }
    if (!isAlive()) {
        setVisible(false); // repeating this a lot, move to somewhere else???
    }
}

ExtraLife::ExtraLife(StudentWorld* sw, int x, int y) : Goodie(sw, IID_EXTRA_LIFE, x, y) {  
}

void ExtraLife::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()) {
        pickUpGoodie(1000);
        getWorld()->incLives();
    }
    if (!isAlive()) {
        setVisible(false); // repeating this a lot, move to somewhere else???
    }
}

Ammo::Ammo(StudentWorld* sw, int x, int y) : Goodie(sw, IID_AMMO, x, y) {
}

void Ammo::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()) {
        pickUpGoodie(100);
        getWorld()->getPlayer()->addAmmo(20);
    }
    if (!isAlive()) {
        setVisible(false); // repeating this a lot, move to somewhere else???
    }
}