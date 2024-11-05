#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    m_numCrystals = 0;
    setCompleted(false);
    m_bonus = 1000;
    loadLevel(m_levelNumber);
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::setDisplayText()
{
    int livesLeft = getLives();
    double health = m_avatar->getHealth();
    int ammo = m_avatar->getAmmo();
    // Next, create a string from your statistics, of the form:
    // Score: 0000100 Level: 03 Lives: 3 Health: 70% Ammo: 216 Bonus: 34
    string s = formatText(getScore(), m_levelNumber, livesLeft, health, ammo); // can i use getScore()
    // Finally, update the display text at the top of the screen with your
    // newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}

std::string StudentWorld::formatText(int score, int level, int lives, double health, int ammo) {
    std::string s = "Score: ";
    ostringstream st; // fix this fu nction
    st << score; 
    // 0000700
    for (int i = 0; i < 7 - numDigits(score); i++) {
        s += "0";
    }
    s += st.str() + "  Level: ";
    st = std::ostringstream();
    st << level;
    if (level < 10) {
        s += "0";
    }
    s += st.str() + "  Lives: ";
    st = std::ostringstream();
    st << lives;
    if (lives < 10) {
        s += " ";
    }
    s += st.str() + "  Health: ";
    st = std::ostringstream();
    double percentage = (health / 20) * 100;      // is there a better way idk
    st << percentage;
    for (int i = 0; i < 3 - numDigits(percentage); i++) {
        s += " ";
    }
    s += st.str() + "%  Ammo: ";
    st = std::ostringstream();
    st << ammo;
    for (int i = 0; i < 3 - numDigits(ammo); i++) {
        s += " ";
    }
    s += st.str() + "  Bonus: ";
    st = std::ostringstream();
    st << m_bonus;
    for (int i = 0; i < 4 - numDigits(m_bonus); i++) {   
        s += " ";
    }
    s += st.str();
    return s;
}

int StudentWorld::numDigits(int i) const {
    if (i == 0) {
        return 1;
    }
    int numDigits = 0;
    while (i != 0) {
        i = i / 10;
        numDigits++;
    }
    return numDigits;
}


int StudentWorld::move()
{
    setDisplayText();
    int n = m_actors.size();
    for (int i = 0; i < n; i++) {
        if (m_actors[i]->isAlive()) {
            m_actors[i]->doSomething();
            if (!m_avatar->isAlive()) {
                return  GWSTATUS_PLAYER_DIED;
            }
            if (m_completed) {
                m_levelNumber++;
                return GWSTATUS_FINISHED_LEVEL;
            }
            // if completed return GWSTATUS_FINISHED_LEVEL;
        }
    }
    removeDead();
    if (m_bonus > 0) {
        m_bonus--;
    }
    if (!m_avatar->isAlive()) {
        return  GWSTATUS_PLAYER_DIED;
    }
    if (m_completed) {
        m_levelNumber++;
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::removeDead() {
    int size = m_actors.size();
    for (int i = 0; i < size; i++) {
        if (!m_actors[i]->isAlive()) {
            delete m_actors[i];
            m_actors.erase(m_actors.begin() + i);
            size--;
        }
    }
}

bool StudentWorld::canGenerateThiefBots(int x1, int y1, int x2, int y2, int x, int y) {
    int count = 0;
    int size = m_actors.size();
    // cerr << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x << " " << y << endl;
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            for (int k = 0; k < size; k++) {
                if (m_actors[k] != nullptr && m_actors[k]->canSteal() && m_actors[k]->getX() == i && m_actors[k]->getY() == j) { // check if allowed
                    if (i == x && j == y) {
                        return false;
                    }
                    count++;
                }
            }
        }
    }
    if (count < 3) {
        return true;
    }
    return false;
}

Level::LoadResult StudentWorld::loadLevel(int i) 
{
    m_levelNumber = i;
    std::string s = "level";
    ostringstream st;
    st << i;
    if (i < 10) {
        s += "0";
    }
    s += st.str() + ".txt";
    m_level = new Level(assetPath());
    Level::LoadResult result = m_level->loadLevel(s);
    if (result == Level::load_fail_file_not_found) {
        std::cerr << "not found";
    }
    else if (result == Level::load_fail_bad_format) {
        std::cerr << "bad format";
    }
    else if (result == Level::load_success)
    {
        for (int i = 0; i < VIEW_WIDTH; i++) {
            for (int j = 0; j < VIEW_HEIGHT; j++) {
                Level::MazeEntry thing = m_level->getContentsOf(i, j);
                switch (thing)
                {
                case Level::empty:
                    break;
                case Level::exit:
                    m_actors.push_back(new Exit(this, i, j));
                    break;
                case Level::player:
                    m_avatar = new Avatar(this, i, j);
                    m_actors.push_back(m_avatar);
                    break;
                case Level::horiz_ragebot:
                    m_actors.push_back(new RageBot(this, i, j, GraphObject::right));   
                    break;
                case Level::vert_ragebot:
                    m_actors.push_back(new RageBot(this, i, j, GraphObject::down));
                    break;
                case Level::thiefbot_factory:
                    m_actors.push_back(new ThiefBotFactory(this, i, j, false));
                    break;
                case Level::mean_thiefbot_factory:
                    m_actors.push_back(new ThiefBotFactory(this, i, j, true));
                    break;
                case Level::marble: 
                    m_actors.push_back(new Marble(this, i, j));
                    break;
                case Level::pit: 
                    m_actors.push_back(new Pit(this, i, j));
                    break;
				case Level::crystal:
                    m_actors.push_back(new Crystal(this, i, j));
                    m_numCrystals++;
                    break;
				case Level::restore_health: 
                    m_actors.push_back(new RestoreHealth(this, i, j));
                    break;
				case Level::extra_life:
                    m_actors.push_back(new ExtraLife(this, i, j));
                    break;
				case Level::ammo:
                    m_actors.push_back(new Ammo(this, i, j));
                    break;
                case Level::wall:
                    m_actors.push_back(new Wall(this, i, j));
                    break;
                }
            }
        }
    }
    return result;
}

bool StudentWorld::canMoveTo(double x, double y) { // will need to fix to account for movable objects/powerups at some point
    int size = m_actors.size();
    for (int i = 0; i < size; i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isActive() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            // how to account for marbles
            return false;
        }
    }
    return true;
}

bool StudentWorld::damageAll(int x, int y) {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isAttackable() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            m_actors[i]->damage();
            return true;
        }
    }
    return false;
}

bool StudentWorld::eliminateMarble(int x, int y) {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isAttackable() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) { 
            m_actors[i]->setAlive(false);
            m_actors[i]->setVisible(false);
            return true;
        }
    }
    return false;
}
void StudentWorld::moveMarble(int x, int y, int dir) {
    for (int i = 0; i < m_actors.size(); i++) { // how to pick just the marbles...
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isPushable() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            if (dir == GraphObject::up) {
                if (!hasActor(x, y + 1) || isFillable(x, y + 1)) {
                    m_actors[i]->moveTo(x, y + 1);
                }
            }
            else if (dir == GraphObject::down) {
                if (!hasActor(x, y - 1) || isFillable(x, y - 1)) {
                    m_actors[i]->moveTo(x, y - 1);
                }
            }
            else if (dir == GraphObject::right) { // cannot figure out how to differentiate a pit...
                if (!hasActor(x + 1, y) || isFillable(x + 1, y)) {
                        m_actors[i]->moveTo(x + 1, y);
                }
            }
            else if (dir == GraphObject::left) {
                if (!hasActor(x - 1, y) || isFillable(x - 1, y)) {
                    m_actors[i]->moveTo(x - 1, y);
                }
            }
        }
    } 
}

bool StudentWorld::isFillable(int x, int y) const { 
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isFillable() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            return true;
        }
    }
    return false;
}


bool StudentWorld::hasActor(int x, int y) const {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            return true;
        }
    }
    return false;
}

bool StudentWorld::hasObstacles(int x, int y, int dir, int x2, int y2) {
    if (dir == GraphObject::right) {
        for (int i = x + 1; i < x2; i++) {
            if (!canMoveTo(i, y)) {
                return true;
            }
        }
    }
    else if (dir == GraphObject::left) {
        for (int i = x2 + 1; i < x; i++) {
            if (!canMoveTo(i, y)) {
                return true;
            }
        }
    }
    else if (dir == GraphObject::up) {
        for (int i = y + 1; i < y2; i++) {
            if (!canMoveTo(x, i)) {
                return true;
            }
        }
    }
    else if (dir == GraphObject::down) {
        for (int i = y2 + 1; i < y; i++) {
            if (!canMoveTo(x, i)) {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::hasGoodie(int x, int y) {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr && m_actors[i]->isAlive() && m_actors[i]->isGoodie() && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            return true;
        }
    }
    return false;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != nullptr) {
            delete m_actors[i];
        }
    }
    if (m_level != nullptr) {
        delete m_level;
        m_level = nullptr;
    }
    m_actors.erase(m_actors.begin(), m_actors.end());

}

StudentWorld::~StudentWorld() {
    cleanUp();
}