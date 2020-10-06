#include <iostream>

using namespace std;

struct Purse {
    int platinum {0};
    int gold {0};
    int electrum {0};
    int silver {0};
    int copper {0};
};

Purse getPurse () {
    Purse commonPurse;

    cout << "Enter the purse contents\n";
    cout << "Platinum:\t";
    cin >> commonPurse.platinum;
    cout << "Gold:\t\t";
    cin >> commonPurse.gold;
    cout << "Electrum:\t";
    cin >> commonPurse.electrum;
    cout << "Silver:\t\t";
    cin >> commonPurse.silver;
    cout << "Copper:\t\t";
    cin >> commonPurse.copper;

    return commonPurse;
}

Purse dividePurse(Purse commonPurse, int players) {
    Purse playerPurse;

    playerPurse.platinum = commonPurse.platinum / players;
    playerPurse.gold = commonPurse.gold / players;
    playerPurse.electrum = commonPurse.electrum / players;
    playerPurse.silver = commonPurse.silver / players;
    playerPurse.copper = commonPurse.copper / players;

    return playerPurse;
}

Purse leftOver(Purse commonPurse, int players) {
    Purse remainingPurse;

    remainingPurse.platinum = commonPurse.platinum % players;
    remainingPurse.gold = commonPurse.gold % players;
    remainingPurse.electrum = commonPurse.electrum % players;
    remainingPurse.silver = commonPurse.silver % players;
    remainingPurse.copper = commonPurse.copper % players;

    return remainingPurse;
}

Purse totalGold(Purse totals) {

    totals.silver += totals.copper / 10;    // convert copper to silver
    totals.copper %= 10;                    // leave remainder of copper only
    totals.electrum += totals.silver / 5;   // convert new total of silver to electrum
    totals.silver %= 5;                     // leave remainder of silver only
    totals.gold += totals.electrum / 2;     // convert new total of electrum to gold
    totals.electrum %= 2;                   // leave remainder of electrum only
    totals.gold += totals.platinum * 10;    // convert platinum to gold
    totals.platinum = 0;                    // zero out platinum

    return totals;
}

void displayContents(Purse purse) {
    cout << "Platinum:\t" << purse.platinum << endl;
    cout << "Gold:\t\t" << purse.gold << endl;
    cout << "Electrum:\t" << purse.electrum << endl;
    cout << "Silver:\t\t" << purse.silver << endl;
    cout << "Copper:\t\t" << purse.copper << endl;
}

int main() {
    int players {0};
    Purse commonPurse;
    Purse playerPurse;
    Purse totals;
    Purse remainingPurse;

    cout << "Enter the number of players: ";
    cin >> players;
    cout << endl;

    commonPurse = getPurse();

    playerPurse = dividePurse(commonPurse, players);

    remainingPurse = leftOver(commonPurse, players);

    totals = totalGold(playerPurse);

    cout << "\nEach player receives...\n";
    displayContents(playerPurse);


    cout << "\nTotal value to each player in gold: ";
    cout << totals.gold << "gp ";
    if(totals.electrum != 0) cout << totals.electrum << "ep ";
    if(totals.silver != 0) cout << totals.silver << "sp ";
    if(totals.copper != 0) cout << totals.copper << "cp";
    cout << endl;

    cout << "\nThe common purse now contains...\n";
    displayContents(remainingPurse);

    cout << "\nTotal removed from common purse: " << endl;
    cout << "Platinum:\t" << commonPurse.platinum - remainingPurse.platinum << endl;
    cout << "Gold:\t\t" << commonPurse.gold - remainingPurse.gold << endl;
    cout << "Electrum:\t" << commonPurse.electrum - remainingPurse.electrum << endl;
    cout << "Silver:\t\t" << commonPurse.silver - remainingPurse.silver << endl;
    cout << "Copper:\t\t" << commonPurse.copper - remainingPurse.copper << endl;

    cout << endl;
    system("pause");

    return 0;
}
