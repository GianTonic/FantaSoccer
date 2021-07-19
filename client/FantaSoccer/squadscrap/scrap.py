from scrapy.spiders import squadname
from scrapy.crawler import CrawlerProcess
from scrapy.utils.log import configure_logging
import logging

dic = {}
configure_logging(install_root_handler=True)
logging.disable(50)
process = CrawlerProcess()
process.crawl(squadname.SquadnameSpider)
# process.start() # the script will block here until the crawling is finished
process.start()
all = squadname.SquadnameSpider().get_result()
print(all) # all + ordinata per team 
process.stop()
# getta tutti i nomi delle squadra
def get_team(all):
    for i in all:
        yield i['team']
# getta tutti i nomi delle squadre e la sua lista giocatori
def get_team_and_players(all):
    for i in all:
        yield i['team'], i['players']
# getta tutti i nomi dei giocoratori di una data squadra
# def get_teams_players(all):
#     for i in all:
#         if i['team'] == squadra:
#             return i['players']