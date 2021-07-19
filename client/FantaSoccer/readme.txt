dipendenze gui tkinter python
pip3 install tk

dipendenze scrapy e xpath
pip3 install scrapy
pip3 install xpath-py


comando effettuato per generare lo spider
scrapy genspider votescrap https://www.fantacalcio.it/voti-fantacalcio-serie-a/

per scrapare i voti
votescrap -> votescrap -> spider -> fantavote.py
all'interno della prima cartella votescrap abbiamo scrapfvote.py 
il quale "avvia" lo scraper fantavote.py 

stesso discorso per teamscrap

genspider teamscrap https://www.fantacalcio.it/squadre

si possono avviare gli scraper da shell con il comando scrpy runspider "nome del file"
all'interno della cartella votescrap (o teamscrap)

scrapy crawl squadname... 
oppure 
scrapy runspider teamscrap 

// der runspider vuole il nome come da queste righe di codice della classe teamscrapspider
class TeamscrapSpider(scrapy.Spider):
    name = 'teamscrap'
//
