#ifndef COUNTRY
#define COUNTRY
class Player;
class Country{
private:
    std::string name;
    Player *owner;
    int soldiers = 0;
public:
    Country(std::string name);

    int getTotalSoldiers();
    std::string getName();
    Player *getOwner();

    void setOwner(Player * owner);

    bool addSoldiers(int amount);
    bool removeSoldiers(int amount);
    bool hasSoldiers();
};

#endif // COUNTRY

