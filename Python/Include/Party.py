from Include.Player import Player


class Party:
    def __init__(self, std_party):
        self.party = []
        if std_party:
            self.party.append(Player("Kholwin"))
            self.party.append(Player("Urimus"))
            self.party.append(Player("Raith"))
            self.party.append(Player("El Condor"))
            self.party.append(Player("Caldazar"))
        else:
            run = True

            while run:
                name = input("Enter new player's name: ")
                self.party.append(Player(name))

                check = input("Add more players? [Y/N]: ")
                if check == "Y" or check == "y":
                    print()
                else:
                    run = False

    def get(self):
        return self.party
