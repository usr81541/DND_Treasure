#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

#include <iostream>

using namespace std;

enum Coin {
    platinum,
    gold,
    electrum,
    silver,
    copper
};

class CoinSlot {
    
private:
    int val {0};
    
public:
    CoinSlot(){
        
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

vector<Player> initParty(bool isStd) {
    vector<Player> party;
    
    if(isStd) {

        party.push_back(Player("Kholwin"));
        party.push_back(Player("Urimus"));
        party.push_back(Player("Raith"));
        party.push_back(Player("El Condor"));
        party.push_back(Player("Caldazar"));
        cout << endl;
    }
    
    else {
        bool go;
        string n;
        
        do {
            cout << "Enter new player's name: ";
            getline(cin, n);
            party.push_back(Player(n));
            
            cout << "Add more players? [Y/N]: ";
            getline(cin, n);
            
            if(n.front() == 'Y' || n.front() == 'y') {
                cout << endl;
                go = true;
            }
            else {
                cout << endl;
                go = false;
            }
        } while (go);
    }
    
    return party;
}

int getTreasure(string request) {
    int val;
    
    while(true) {
        cout << request;
        cin >> val;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\nEnter an integer" << endl;
        }
        else {
            break;
        }
    }
    
    return val;
}

void parse(vector<Player> &party, Purse &purse, Coin coin) {
    int limit;
    int party_size = static_cast<int>(party.size());
    
    switch (coin) {
        case platinum:
            for (int i = 0; i < party_size; i++) {
                party.at(i).platinum.add(purse.platinum.get() / party_size);
            }
            
            purse.platinum.set(purse.platinum.get() % party_size);
            
            if((purse.platinum.get() > party_size / 2) &&
                    (purse.gold.get() >= (party_size - purse.platinum.get()) * 10)) {
                limit = purse.platinum.get();
                
                for(int i = 0; i < limit; i++) {
                    party.at(i).platinum.add(1);
                    purse.platinum.subtract(1);
                }
                
                for(int i = limit; i < party_size; i++) {
                    party.at(i).gold.add(10);
                    purse.gold.subtract(10);
                }
            }
            break;
        case gold:
            for (int i = 0; i < party_size; i++) {
                party.at(i).gold.add(purse.gold.get() / party_size);
            }
            
            purse.gold.set(purse.gold.get() % party_size);
            
            if(purse.gold.get() > party_size / 2) {
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
            for (int i = 0; i < party_size; i++) {
                party.at(i).copper.add(purse.copper.get() / party_size);
            }
            
            purse.copper.set(purse.copper.get() % party_size);
    }
}

void dividePurse(vector<Player> &party, Purse &purse) {
    parse(party, purse, platinum);
    parse(party, purse, gold);
    parse(party, purse, electrum);
    parse(party, purse, silver);
    parse(party, purse, copper);
}

int main() {
    Purse c_purse;
    vector<Player> party;
    string input;
    
    cout << "Custom Party? [Y/N]:\t";
    getline(cin, input);
    
    if(input.front() == 'y' || input.front() == 'Y') {
        party = initParty(false);
    }
    else {
        party = initParty(true);
    }
    
    cout << "Enter common purse value:" << endl;
    c_purse.platinum.set(getTreasure("Platinum:\t"));
    c_purse.gold.set(getTreasure("Gold:\t\t"));
    c_purse.electrum.set(getTreasure("Electrum:\t"));
    c_purse.silver.set(getTreasure("Silver:\t\t"));
    c_purse.copper.set(getTreasure("Copper:\t\t"));
    cout << endl;
    
    cout << "Common Purse (full):" << endl;
    c_purse.displayContents();
    
    dividePurse(party, c_purse);
    
    for(Player p : party) {
        cout << "Player: " << p.getName() << endl;
        p.displayContents();
        p.displayTotalGold();
        cout << endl;
    }
    
    cout << "Common Purse (emptied):" << endl;
    c_purse.displayContents();
    
    system("pause");
    
    return 0;
}