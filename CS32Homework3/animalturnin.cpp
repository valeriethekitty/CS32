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