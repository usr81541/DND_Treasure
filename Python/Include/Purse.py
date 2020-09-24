class Purse:
    def __init__(self):
        self.platinum = 0
        self.gold = 0
        self.electrum = 0
        self.silver = 0
        self.copper = 0

    def get_purse(self):
        print("\nEnter the purse contents")
        self.platinum = int(input("Platinum: "))
        self.gold = int(input("Gold: "))
        self.electrum = int(input("Electrum: "))
        self.silver = int(input("Silver: "))
        self.copper = int(input("Copper: "))

    def display_contents(self):
        print(f"Platinum:\t{self.platinum}")
        print(f"Gold:\t\t{self.gold}")
        print(f"Electrum:\t{self.electrum}")
        print(f"Silver:\t\t{self.silver}")
        print(f"Copper:\t\t{self.copper}")

    def total_gold(self):
        t_copper = self.copper
        t_silver = self.silver + t_copper // 10
        t_copper %= 10
        t_electrum = self.electrum + t_silver // 5
        t_silver %= 5
        t_gold = self.gold + (t_electrum // 2) + (self.platinum * 10)
        t_electrum %= 2

        print(f"Total value of the purse in gold: {t_gold}gp", end=" ")
        if t_electrum != 0:
            print(f"{t_electrum}ep", end=" ")
        if t_silver != 0:
            print(f"{t_silver}sp", end=" ")
        if t_copper != 0:
            print(f"{t_copper}cp")
        else:
            print()     # print a blank line for formatting

    def get_platinum(self):
        return self.platinum

    def set_platinum(self, p):
        self.platinum = p

    def add_platinum(self, p):
        self.platinum += p

    def subtract_platinum(self, p):
        self.platinum -= p

    def get_gold(self):
        return self.gold

    def set_gold(self, g):
        self.gold = g

    def add_gold(self, g):
        self.gold += g

    def subtract_gold(self, g):
        self.gold -= g

    def get_electrum(self):
        return self.electrum

    def set_electrum(self, e):
        self.electrum = e

    def add_electrum(self, e):
        self.electrum += e

    def subtract_electrum(self, e):
        self.electrum -= e

    def get_silver(self):
        return self.silver

    def set_silver(self, s):
        self.silver = s

    def add_silver(self, s):
        self.silver += s

    def subtract_silver(self, s):
        self.silver -= s

    def get_copper(self):
        return self.copper

    def set_copper(self, c):
        self.copper = c

    def add_copper(self, c):
        self.copper += c

    def subtract_copper(self, c):
        self.copper -= c