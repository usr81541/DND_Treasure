from Include.Purse import Purse


def divide_purse(common_purse, players):
    player_purse = Purse()

    player_purse.platinum = common_purse.platinum // players
    player_purse.gold = common_purse.gold // players
    player_purse.electrum = common_purse.electrum // players
    player_purse.silver = common_purse.silver // players
    player_purse.copper = common_purse.copper // players

    return player_purse


def left_over(common_purse, players):
    remaining_purse = Purse()

    remaining_purse.platinum = common_purse.platinum % players
    remaining_purse.gold = common_purse.gold % players
    remaining_purse.electrum = common_purse.electrum % players
    remaining_purse.silver = common_purse.silver % players
    remaining_purse.copper = common_purse.copper % players

    return remaining_purse


# get players
players = int(input("Enter the number of players: "))

# initialize the common purse
common_purse = Purse()
common_purse.get_purse()

# display initial contents
print("\nThe common purse holds...")
common_purse.display_contents()

# divide the purse among the players
player_purse = divide_purse(common_purse, players)
# and adjust the remaining value in the common purse
common_purse = left_over(common_purse, players)

# output the results
print("\nEach player receives...")
player_purse.display_contents()
player_purse.total_gold()

print("\nThe common purse now holds...")
common_purse.display_contents()

input("\nPress ENTER to close...")
