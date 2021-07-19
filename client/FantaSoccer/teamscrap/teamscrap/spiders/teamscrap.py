import scrapy

class TeamscrapSpider(scrapy.Spider):
    name = 'teamscrap'
    url = 'https://www.fantacalcio.it/squadre'
    squad = []
    # custom_settings = {
    #     'LOG_ENABLED': 0,
    # }
    result = [] #tutti i dict del tipo team, players
    
    def start_requests(self):
        yield scrapy.Request(url=self.url, callback=self.parse)

    def parse(self, response):
        teams = response.selector.xpath('//h3[@itemprop="name"]/a/text()').getall()
        for team in teams:
            self.squad.append(team)
            # print("team: "+team)
            yield scrapy.Request(url=self.url+'/'+team,callback=self.getplayer)
        return
    
    def getplayer(self, response):
        squad = response.url.replace(self.url+'/','')
        # rows = response.selector.xpath('//table[contains(@class, "tabledt")]/tbody/tr').get()
        lista=[]
        nodo={}
        for row in response.xpath('//table[contains(@class, "tabledt")]/tbody/tr'):
            nodo.clear
            lista.clear
            # print(row)
            player = {
                'surname' : row.xpath('td[2]//text()').extract_first(),
                'role' :row.xpath('td[3]//text()').extract_first(),
            }
            lista.append(player)
            # nodo = {} #nodo lista result
        nodo['team'] = squad
        nodo['players'] = lista
        self.result.append(nodo)
        return

    def get_result(self):
        return sorted(self.result,key= lambda i: i['team'])
    
    def get_squad(self):
        return sorted(self.squad)
    
    def get_squad_players(self,selecteam):
        for nodo in self.result:
            if nodo['team']==selecteam:
                return nodo['players']