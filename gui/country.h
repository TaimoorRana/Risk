#ifndef COUNTRY
#define COUNTRY
class Country{
private:

    std::string name,owner;
    int soldiers;
public:
    Country(std::string name);

    int getTotalSoldiers();
    std::string getName();
    std::string getOwner();

    void setOwner(std::string owner);

    bool addSoldiers(int amount);
    bool removeSoldiers(int amount);
    bool hasSoldiers();
};

#endif // COUNTRY

