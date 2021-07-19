import scrapy

class SquadnameSpider(scrapy.Spider):
    name = 'squadname'
    url = 'https://www.fantacalcio.it/squadre'
    custom_settings = {
        'LOG_ENABLED': 0,
    }
    result = [] #tutti i dict del tipo team, players
    def start_requests(self):
        yield scrapy.Request(url=self.url, callback=self.parse)

    def parse(self, response):
        teams = response.selector.xpath('//h3[@itemprop="name"]/a/text()').getall()
        for team in teams:
            # print("team: "+team)
            yield scrapy.Request(url=self.url+'/'+team,callback=self.getplayer)
        return
    
    def getplayer(self, response):
        squad = response.url.replace(self.url+'/','')
        players = response.selector.xpath('//table/tbody/tr/td/a/text()').getall()
        lista = [] #lista giocatori
        nodo = {} #nodo lista result
        # per 26 giocatori il resto è fuffa li aggiungo alla lista
        for i in range(26):
            lista.append(players[i])
        # del lista[26:]
        nodo['team'] = squad
        nodo['players'] = lista
        # print(nodo)
        self.result.append(nodo)
        return

    def get_result(self):
        return sorted(self.result,key= lambda i: i['team'])
        
