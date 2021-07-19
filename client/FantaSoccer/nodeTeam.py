class Team:
    def __init__(self,name):
        self.name=name
        self.points=0
        self.players=list()
    def get_name(self):
        return self.name
    def get_points(self):
        return self.points
    # def get_players(self):
    #     for pl in players:
    #         return 
    def __str__(self):
        return "Squadra:" + str(self.name) + "Punti:" + str(self.points)