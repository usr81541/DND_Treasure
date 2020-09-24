from Include.Purse import Purse
from Include.Party import Party


def parse_coins(party, purse, coin):
    if coin == "platinum":
        for player in party:
            player.add_platinum(purse.get_platinum() // len(party))

        purse.set_platinum(purse.get_platinum() % len(party))

        if (purse.get_platinum() > len(party) // 2 and
                purse.get_gold() >= (len(party) - purse.get_platinum()) * 10):
            limit = purse.get_platinum()
            for player in party[:limit]:
                player.add_platinum(1)
                purse.subtract_platinum(1)

            for player in party[limit:]:
                player.add_gold(10)
                purse.subtract_gold(10)

    elif coin == "gold":
        for player in party:
            player.add_gold(purse.get_gold() // len(party))

        purse.set_gold(purse.get_gold() % len(party))

        if purse.get_gold() > len(party) // 2:
            if purse.get_electrum() >= (len(party) - purse.get_gold()) * 2:
                limit = purse.get_gold()
                for player in party[:limit]:
                    player.add_gold(1)
                    purse.subtract_gold(1)

                for player in party[limit:]:
                    player.add_electrum(2)
                    purse.subtract_electrum(2)

            elif purse.get_silver() >= (len(party) - purse.get_gold()) * 10:
                limit = purse.get_gold()
                for player in party[:limit]:
                    player.add_gold(1)
                    purse.subtract_gold(1)

                for player in party[limit:]:
                    player.add_silver(10)
                    purse.subtract_silver(10)

    elif coin == "electrum":
        for player in party:
            player.add_electrum(purse.get_electrum() // len(party))

        purse.set_electrum(purse.get_electrum() % len(party))

        if (purse.get_electrum() > len(party) // 2 and
                purse.get_silver() >= (len(party) - purse.get_electrum()) * 5):
            limit = purse.get_electrum()
            for player in party[:limit]:
                player.add_electrum(1)
                purse.subtract_electrum(1)

            for player in party[limit:]:
                player.add_silver(5)
                purse.subtract_silver(5)

    elif coin == "silver":
        for player in party:
            player.add_silver(purse.get_silver() // len(party))

        purse.set_silver(purse.get_silver() % len(party))

        if (purse.get_silver() > len(party) // 2 and
                purse.get_copper() >= (len(party) - purse.get_silver()) * 10):
            limit = purse.get_silver()
            for player in party[:limit]:
                player.add_silver(1)
                purse.subtract_silver(1)

            for player in party[limit:]:
                player.add_copper(10)
                purse.subtract_copper(10)

    elif coin == "copper":
        for player in party:
            player.add_copper(purse.get_copper() // len(party))

        purse.set_copper(purse.get_copper() % len(party))


def divide_purse(party, purse):
    parse_coins(party, purse, "platinum")
    parse_coins(party, purse, "gold")
    parse_coins(party, purse, "electrum")
    parse_coins(party, purse, "silver")
    parse_coins(party, purse, "copper")


# get players
spam = input("Custom party? [Y/N]:\t")
if spam == "Y" or spam == "y":
    isStdParty = False
else:
    isStdParty = True

my_party = Party(isStdParty)

# initialize the common purse
common_purse = Purse()
common_purse.get_purse()

# display initial contents
print("\nThe common purse holds...")
common_purse.display_contents()

divide_purse(my_party.get(), common_purse)
print()

for my_player in my_party.get():
    print(f"Player:\t{my_player.get_name()}")
    my_player.display_contents()
    my_player.total_gold()
    print()

print("The common purse now holds...")
common_purse.display_contents()

input("\nPress ENTER to close...")
