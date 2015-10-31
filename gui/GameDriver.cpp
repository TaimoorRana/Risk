#include "GameDriver.h"

GameDriver GameDriver::driver;

GameDriver::GameDriver()
{
//	continents[0] = new Continent("Africa", 5);
//	continents[1] = new Continent("Asia", 7);

//	for (int i = 0; i < sizeof(countries); i++)
//	{
//		countries[i] = new Country("country-"+('A'+i), *continents[i%2]);
//	}
}


GameDriver::~GameDriver()
{
}

GameDriver GameDriver::getInstance()
{
	return driver;
}

void GameDriver::splashScreen()
{
	cout << "\tWELCOME TO RISK.... THE BEST STRATEGY GAME EVERRRRRRR!!!\n\n\n\n\n";
}


void GameDriver::setNumberAndNamesOfPlayers()
{
//	cout << "Please enter the number of players: 4";
//	numPlayers = 4;
//	cout << "\n";
//	string myName;
//	for (int i = 0; i < 4; i++)
//	{
//		cout << "Enter the name of player " << i+1 << " : ";
		
//		getline(cin, myName);
//		players[i].name = myName;
//		cout << "\n";
//	}
}


void GameDriver::assignCountries()
{
	
	std::cout << "\n\n****Countries Assigned to players\n\n";
}


void GameDriver::assignPlayersOrder()
{
//	Player* temp = new Player[4];

//	int randIndex;

//	for (int i = 0; i < sizeof(players); i++)
//	{
//		do
//		{
//			randIndex = rand() % numPlayers;
//			if (temp[randIndex].name == "")
//			{
//				temp[randIndex] = players[i];
//			}
//		} while (temp[randIndex].name == "");
//	}

//	players = temp;
}


void GameDriver::getReinforcement(Player& aPlayer)
{
//	aPlayer.reinforcement = 0;
//	int temp = aPlayer.countries;
//	if (temp >= 12)
//		cout<<"YOU WIN!";
//	else if(temp >= 8){
//		aPlayer.reinforcement += 5;
//	} else if (temp >= 6){
//		aPlayer.reinforcement += 2;
//	}
//	cout << "\n\nYou received "<<aPlayer.reinforcement<<" from countries...";
//	Continent* owned = aPlayer.getOwnedContinents();

//	aPlayer.reinforcement += (*owned).getReinforcementBonus();
//	cout << "\n\nYou received " + (*owned).getReinforcementBonus() << " From Continents...";
}


void GameDriver::reinforce(Country& aCountry)
{
	//aCountry.soldiers++;
	//cout<< aCountry.name<< " has: "<< aCountry.soldiers;
//	cout << "\nThe selected country received some reinforcement\n";
}


void GameDriver::reduce(Country& aCountry)
{
//	cout << "The selected country lost some troops";

	
	//aCountry.soldiers--;
	//cout<< aCountry.name<< " has: "<< aCountry.soldiers;
}


void GameDriver::attack(Country& atkCountry, Country& dfndCountry)
{
	// Roll dice
	// Compare dice for each player
	// Remove soldiers based on the highest die value, in case of a tie, the attacker loses a soldier
	// 

//	string ans = "y";
//	cout << "Do you want to attack?";
//	getline(cin, ans);
//	bool attacked = 0;
//	while (ans.compare("y")==0)
//	{
//		cout << "country A attacked country B. Country A lost 2 soldiers\n";
//		cout << "\nDo you want to attack (y/n)?";
//		getline(cin, ans);
//		attacked = 1;
//	}

//	// if attacked, you can fortify once done
//	if (attacked)
//	{
//		cout << "\nDo you want to fortify (y/n)?";
//		string ans2 = "y";
//		getline(cin, ans2);
//		if (ans2.compare("y") == 0)
//			fortify(*countries[2], *countries[1], 4);
//	}
	

}


void GameDriver::fortify(Country& origin, Country& destination, int numSoldiers)
{
	/*if (((*origin).soldiers - numSoldiers) >= 1)
	{
		(*origin).soldiers -= numSoldiers;
		(*destination).soldiers += numSoldiers;
	}*/

//	cout << "\n Soldiers moved to the selected destination\n";
}

void GameDriver::startGame()
{
//	bool winner = 0;
//	int counter = 0;

//	splashScreen();
//	setNumberAndNamesOfPlayers();
//	assignPlayersOrder();
//	assignCountries();
//	while (!winner && counter<16)
//	{
//		counter++;
//		cout << "\nTurn " << counter << "\n";

//		for (int i = 0; i < numPlayers; i++)
//		{
//			cout << "\n***** "<<players[i].name<<" ****\n";
//			getReinforcement(*players);
//			reinforce(*countries[1]);
//			attack(*countries[1], *countries[2]);
//		}

//		if (counter == 7)
//		{
//			cout << "\n\t\t*******" << players[3].name << " LOST *********\n\n";
//			numPlayers--;
//		}
//		else if (counter == 13)
//		{
//			cout << "\n\t\t*******"<< players[2].name <<" WON *********\n\n";
//			return;
//		}
//	}
}
