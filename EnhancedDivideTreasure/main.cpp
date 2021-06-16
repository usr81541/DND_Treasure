#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <json.hpp>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

/*****************************************************************
* Enum class to hold the different coin types
******************************************************************/
enum Coin {
    platinum,
    gold,
    electrum,
    silver,
    copper
};

/*****************************************************************
* CoinSlot class includes an integer and methods to set, get,
* increase, and decrease the integer value
******************************************************************/
class CoinSlot {

private:
    int val;

public:
    CoinSlot(){
        val = 0;
    }

    CoinSlot(int v) {
        val = v;
    }

    int get() {
        return val;
    }

    void set(int v) {
        val = v;
    }

    void add(int v) {
        val += v;
    }

    void subtract(int v) {
        val -= v;
    }
};

/*****************************************************************
* Purse is a collection of CoinSlots and includes methods to
* display the contents, and to display the equivalent value in gold
******************************************************************/
class Purse {

public:
    CoinSlot    platinum,
                gold,
                electrum,
                silver,
                copper;

    void displayContents() {
        cout << "Purse contents:" << endl;
        cout << "Platinum:\t" << platinum.get() << endl;
        cout << "Gold:\t\t" << gold.get() << endl;
        cout << "Electrum:\t" << electrum.get() << endl;
        cout << "Silver:\t\t" << silver.get() << endl;
        cout << "Copper:\t\t" << copper.get() << endl;
        cout << endl;
    }

    void displayTotalGold() {
        int total_gold = gold.get();
        int total_electrum = electrum.get();
        int total_silver = silver.get();
        int total_copper = copper.get();

        total_silver += total_copper / 10;
        total_copper %= 10;
        total_electrum += total_silver / 5;
        total_silver %= 5;
        total_gold += total_electrum / 2;
        total_electrum %= 2;
        total_gold += platinum.get() * 10;

        cout << "The total value in gold is: "
             << total_gold << "gp ";
        if(total_electrum != 0) cout << total_electrum << "ep ";
        if(total_silver != 0) cout << total_silver << "sp ";
        if(total_copper !=0) cout << total_copper << "cp";
        cout << endl;
    }

    Purse() {

    }

};

/*****************************************************************
* Player is a Purse with a name
******************************************************************/
class Player:public Purse {

private:
    string name;

public:
    Player(string n) : Purse() {
        name.assign(n);
    }

    string getName() {
        return name;
    }
};

/*****************************************************************
* Initializes a vector of Players to serve as a party.  The party
* splits the value of the common purse.
******************************************************************/
vector<Player> initParty(bool isStd) {
    vector<Player> party;

    if(isStd) {
        // Standard party for Sidiqi Adventures
        party.push_back(Player("Kholwin"));
        party.push_back(Player("Urimus"));
        party.push_back(Player("Raith"));
        party.push_back(Player("El Condor"));
        party.push_back(Player("Caldazar"));
        cout << endl;
    }

    else {
        bool go {true};
        string n;

        // Routine to create a custom party
        while(go) {
            cout << "Enter new player's name: ";
            getline(cin, n);              // Get's the new player name
            party.push_back(Player(n));   // Adds the player to the party

            while(go) {
                cout << "Add more players? [Y/N]: ";  // Check for more players
                getline(cin, n);
                cout << endl;

                if(n.front() == 'Y' || n.front() == 'y') {
                    break;        // Exit inner loop, repeat outer
                }
                else if(n.front() == 'N' || n.front() == 'n') {
                    go = false;   // Exit both loops
                }
                else {
                  cout << "Invalid input. Try again." << endl;  // Continue
                }
            }
        }
    }

    return party;
}

/*****************************************************************
* Get an integer for a CoinSlot.  Takes a prompt for the integer
* and returns the integer input.
******************************************************************/
int getTreasure(string request) {
    int val;

    while(true) {
        cout << request;
        cin >> val;

        // Check to make sure that an integer was received
        // Loop until valid input
        if(cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << endl << "Enter an integer." << endl;
        }
        else {
            break;
        }
    }

    return val;
}

/*****************************************************************
* parse function splits a purse CoinSlot evenly among the players
* in the party.  It compensates for any shortfall by drawing from
* the next highest value CoinSlot
******************************************************************/
void parse(vector<Player>& party, Purse& purse, Coin coin) {
    int limit;
    int party_size = static_cast<int>(party.size());

    switch (coin) {
        case platinum:
            // Give every player some coin
            for (int i = 0; i < party_size; i++) {
                party.at(i).platinum.add(purse.platinum.get() / party_size);
            }

            // Adjust the quantity available in the purse
            purse.platinum.set(purse.platinum.get() % party_size);

            // Check to see if there is enough value left to continue distributing
            if((purse.platinum.get() > party_size / 2) &&
                    (purse.gold.get() >= (party_size - purse.platinum.get()) * 10)) {
                // Set the partition
                limit = purse.platinum.get();

                // Distribute remaining coin
                for(int i = 0; i < limit; i++) {
                    party.at(i).platinum.add(1);
                    purse.platinum.subtract(1);
                } // At this point, the CoinSlot value should equal 0

                // Distribute next most valuable coin to remaining players
                for(int i = limit; i < party_size; i++) {
                    party.at(i).gold.add(10);
                    purse.gold.subtract(10);
                }
            }
            break;
        case gold:
            // Same procedure as above
            for (int i = 0; i < party_size; i++) {
                party.at(i).gold.add(purse.gold.get() / party_size);
            }

            purse.gold.set(purse.gold.get() % party_size);

            // Variation for gold
            // Can reasonably backfill with either electrum or silver
            if(purse.gold.get() > party_size / 2) {
                // Backfill with electrum
                if (purse.electrum.get() >= (party_size - purse.gold.get()) * 2) {
                    limit = purse.gold.get();

                    for(int i = 0; i < limit; i++) {
                        party.at(i).gold.add(1);
                        purse.gold.subtract(1);
                    }

                    for(int i = limit; i < party_size; i++) {
                        party.at(i).electrum.add(2);
                        purse.electrum.subtract(2);
                    }
                }
                // Backfill with silver
                else if(purse.silver.get() >= (party_size - purse.gold.get()) * 10) {
                    limit = purse.gold.get();

                    for(int i = 0; i < limit; i++) {
                        party.at(i).gold.add(1);
                        purse.gold.subtract(1);
                    }

                    for(int i = limit; i < party_size; i++) {
                        party.at(i).silver.add(10);
                        purse.silver.subtract(10);
                    }
                }
            }
            break;
        case electrum:
            // Same procedure as above
            for (int i = 0; i < party_size; i++) {
                party.at(i).electrum.add(purse.electrum.get() / party_size);
            }

            purse.electrum.set(purse.electrum.get() % party_size);

            if((purse.electrum.get() > party_size / 2) &&
                    (purse.silver.get() >= (party_size - purse.electrum.get()) * 5)) {
                limit = purse.electrum.get();

                for(int i = 0; i < limit; i++) {
                    party.at(i).electrum.add(1);
                    purse.electrum.subtract(1);
                }

                for(int i = limit; i < party_size; i++) {
                    party.at(i).silver.add(5);
                    purse.silver.subtract(5);
                }
            }
            break;
        case silver:
            // Same procedure as above
            for (int i = 0; i < party_size; i++) {
                party.at(i).silver.add(purse.silver.get() / party_size);
            }

            purse.silver.set(purse.silver.get() % party_size);

            if((purse.silver.get() > party_size / 2) &&
                    (purse.copper.get() >= (party_size - purse.silver.get()) * 10)) {
                limit = purse.silver.get();

                for(int i = 0; i < limit; i++) {
                    party.at(i).silver.add(1);
                    purse.silver.subtract(1);
                }

                for(int i = limit; i < party_size; i++) {
                    party.at(i).copper.add(10);
                    purse.copper.subtract(10);
                }
            }
            break;
        case copper:
            // No backfill for coppper
            for (int i = 0; i < party_size; i++) {
                party.at(i).copper.add(purse.copper.get() / party_size);
            }

            purse.copper.set(purse.copper.get() % party_size);
    }
}

/*****************************************************************
* Calls the parse function for each of the five Coin types
******************************************************************/
void dividePurse(vector<Player>& party, Purse& purse) {
    parse(party, purse, platinum);
    parse(party, purse, gold);
    parse(party, purse, electrum);
    parse(party, purse, silver);
    parse(party, purse, copper);
}

int main() {
    Purse c_purse;              // Common purse
    vector<Player> party;       // Party vector
    string input = "N";               // Placeholder for user input
    ifstream infile ("data.json");  // load data file

    json j;
    infile >> j;

    while (input.front() != 'y' && input.front() != 'Y') {
      if (!party.empty()) {
        party.clear();
      }
      cout << "Choose a party:\n\n";
      for (auto& el : j.items()) {
        cout << "\t" << el.key() << endl;

        for(auto& item : el.value()["Characters"]) {
          party.push_back(Player(item));
          cout << "\t\t" << item << endl;
        }

        cout << endl << "Select this party? [Y/N]:\t";
        cin >> input;

        if (input.front() == 'y' || input.front() == 'Y') {
          break;
        }
    }
  }

    // Get common purse value
    cout << "Enter common purse value:" << endl;
    c_purse.platinum.set(getTreasure("Platinum:\t"));
    c_purse.gold.set(getTreasure("Gold:\t\t"));
    c_purse.electrum.set(getTreasure("Electrum:\t"));
    c_purse.silver.set(getTreasure("Silver:\t\t"));
    c_purse.copper.set(getTreasure("Copper:\t\t"));
    cout << endl;

    // Display the initial common purse value
    cout << "Common Purse (full):" << endl;
    c_purse.displayContents();

    // Divide the purse among the party
    dividePurse(party, c_purse);

    // Display each party member's purse after distribution
    for(Player p : party) {
        cout << "Player: " << p.getName() << endl;
        p.displayContents();
        p.displayTotalGold();
        cout << endl;
    }

    // Display the rmaining coin in the common purse
    cout << "Common Purse (emptied):" << endl;
    c_purse.displayContents();

    system("pause");

    return 0;
}
