#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    Animal(string name) {
        m_name = name;
    }
    virtual void speak() const = 0;

    string name() const {
        return m_name;
    }
    virtual string moveAction() const {
        return "walk";
    }
    virtual ~Animal() {
    }
private: 
    string m_name;
};

class Person : public Animal {
public:
    Person(string name) : Animal(name) {}
};

class Cat : public Animal {
public:
    Cat(string name) : Animal(name) {
    }
    virtual void speak() const {
        cout << "Meow";
    }
    virtual ~Cat() {
        cout << "Destroying " << name() << " the cat" << endl;
    }
private:

};

class Pig : public Animal {
public: 
    Pig(string name, int weight) : Animal(name) {
        m_weight = weight;
    }
    virtual void speak() const {
        if (m_weight >= 180) {
            cout << "Grunt";
        }
        else {
            cout << "Oink";
        }
    }
    virtual ~Pig() {
        cout << "Destroying " << name() << " the pig" << endl;
    }
private: 
    int m_weight;
};

class Duck : public Animal {
public:
    Duck(string name) : Animal(name) {
    }
    virtual void speak() const {
        cout << "Quack";
    }
    virtual string moveAction() const {
        return "swim";
    }
    virtual ~Duck() {
        cout << "Destroying " << name() << " the duck" << endl;
    }
private:

};


void animate(const Animal* a)
{
    a->speak();
    cout << "!  My name is " << a->name()
        << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Puss in Boots");
    // Pigs have a name and a weight in pounds.  Pigs under 180
    // pounds oink; pigs weighing at least 180 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");

    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);

    // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}