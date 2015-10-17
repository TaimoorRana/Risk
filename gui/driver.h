#import "player.h"
#import "country.h"


#ifndef DRIVER
#define DRIVER


void assignCountries(players& player[]);

void getReinforcement(player& aPlayer);

void reinforce(country& aCountry);

void reduce(country& aCountry);

void attack (country& atkCountry, country& dfndCountry);

void fortify (country& origin, country& destination, int numSoldiers);




#endif // DRIVER

