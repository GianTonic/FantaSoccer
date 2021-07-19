from votescrap.votescrap.spiders import fantavote
from scrapy.crawler import CrawlerProcess
from scrapy.utils.log import configure_logging
import logging

dic = {}
configure_logging(install_root_handler=True)
logging.disable(50)
# process = CrawlerProcess()
# process.crawl(fantavote.FantavoteSpider)
# process.start()
# process.stop()
# all = fantavote.FantavoteSpider().get_result()
# print(all)