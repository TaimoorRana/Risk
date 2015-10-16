#ifndef COUNTRY
#define COUNTRY

class Country
{
private:
    int soldiers;
    String name;
    Player owner;
public:
    Country(String name);
    int getTotalSoldiers();
    String getName();
    String getOwner();

    void setOwner(String owner);

    bool addSoldiers(int amount);
    bool removeSoldiers(int amount);
    bool hasSoldiers();

};

#endif // COUNTRY

