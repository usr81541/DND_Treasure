from Include.Purse import Purse


class Player(Purse):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def get_name(self):
        return self.name
