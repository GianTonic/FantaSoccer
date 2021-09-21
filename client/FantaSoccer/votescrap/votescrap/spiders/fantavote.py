from tkinter.constants import S
import scrapy

class FantavoteSpider(scrapy.Spider):
    # day = 1
    name = 'fantavote'
    allVotes = []
    custom_settings = {
            'LOG_ENABLED': 0,
        }
    start_url = 'https://www.fantacalcio.it/voti-fantacalcio-serie-a/2021-22/'
    url = ''
    def __init__(self, day):
        self.url=self.start_url+day
        # print(self.url)
    # allVotes = []
    # url='https://www.fantacalcio.it/voti-fantacalcio-serie-a/2020-2021/'
    # custom_settings = {
    #     'LOG_ENABLED': 0,
    # }
    # schedula = sched.scheduler(time.time, time.sleep)
# def do_something(sc): 
#     print("Doing stuff...")
#     # do your stuff
#     s.enter(60, 1, do_something, (sc,))

# s.enter(60, 1, do_something, (s,))
# s.run()

    def start_requests(self):
        # print(self.url)
        yield scrapy.Request(url=self.url, callback=self.parse)
    
    def parse(self, response):
        tables = response.selector.xpath('//table')
        # print(len(tables))
        nomi = response.selector.xpath('//tbody/tr[@role="row"]/td[@class="pname"]/a/span[@class="player-name"]/text()').extract()
        votes = response.selector.xpath('//tbody/tr/td[@data-source="1"]/span[@class="label label-green2 label-sms"]/text()').extract()
        # print(len(nomi))
        # print(len(votes))
        for i in range(len(nomi)):
            if nomi[i]!='':
                vote = {"player":nomi[i],"vote":votes[i]}
                # print(vote)
                self.allVotes.append(vote)
        self.get_votes()
        return
    
    def get_votes(self):
        print(self.allVotes)
        # print(self.url+self.day)
    
    def get_votes_avail(self):
        # print(self.allVotes)
        print(self.url+self.day)
    # def ripeti(self):
    #     giornata= self.day+1
    #     if giornata<=39:
    #         str(giornata)
    #         print(self.day)
    #     else:
    #         print("campionato finito")
    #aumento day e schedulo? 
    # solo simulazion
    # day 1
    # schedule.every(10).seconds.do(ripeti)
    # schedula.enter(10,1,)
    # schedula.enter(0,1,start_requests,(str(int(day)+1)))
    # schedula.enter(5,1,start_requests,(str(int(day)+1)))
    # schedula.enter(10,1,start_requests,(str(int(day)+1)))
    # schedula.run()

