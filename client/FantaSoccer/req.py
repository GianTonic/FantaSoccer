from tkinter import messagebox
import requests, json, os.path

from requests.api import request

def chosen(surname):
    url = 'http://localhost:8030/GET?player='+surname
    pls = requests.get(url,verify=False)
    # print(pls.text)
    if pls.text!='{}':
        return True
    else:
        return False

def load_file():
    if os.path.isfile('data.json'):
        # f = open('data.json','r')
        with open('data.json') as json_file:
            data = json.load(json_file)
            
            print(data)
            return data
    else: 
        return '{}'

def load_db():
    url = 'http://localhost:8030/GET?squad'
    pls = requests.get(url,verify=False)
    if pls.text!='{}':
        # print(pls.text)
        disdiz = {"teams": pls.text}
        stringed = json.dumps(disdiz)
        data = json.loads(stringed)
        return data

def load_team_name(cli_name):
    url = 'http://localhost:8030/GET?owner='+cli_name
    pls = requests.get(url,verify=False)
    if pls.text!='{}':
        print(pls.text)
        # print(pls.text[cli_name])
        disdiz = {"teams": pls.text}
        stringed = json.dumps(disdiz)
        data = json.loads(stringed)
        return data

def load_team_players(team_name):
    url = 'http://localhost:8030/GET?players='+team_name
    # print(url)
    pls = requests.get(url,verify=False)
    if pls.text!='{}':
        print(pls.text)
        # print(pls.text[cli_name])
        disdiz = {"players": pls.text}
        stringed = json.dumps(disdiz)
        data = json.loads(stringed)
        return data

def insert_team(dati):
    #request squad già presenti
    data = load_db() 
    if data!=None:
        teams= json.loads(data['teams'])
        # print(teams)
        canadd=1
        if dati['name'] in teams.keys() | dati['owner'] in teams.values():
            canadd = 0
        if canadd==1:
            # print('allora inserisco'+dati['name']+' di '+dati['owner'])
            url = "http://localhost:8030?squad="+dati['name']+";"+dati['owner']
            # print(url)
            pls = requests.post(url,verify=False)
            if pls.status_code == requests.codes.ok:
                print(pls)
                return True
        else:
            print('errore')
            return False
    else:
        url = "http://localhost:8030?squad="+dati['name']+";"+dati['owner']
            # print(url)
        pls = requests.post(url,verify=False)
        if pls.status_code == requests.codes.ok:
            print(pls)
            return True


def get_the_day():
    url = 'http://localhost:8030/GET?actual_day'
    pls = requests.get(url,verify=False)
    day = {}
    day = json.loads(pls.text)
    return day['actual_day']

def insert_formation_day(player, day):
    url = 'http://localhost:8030/PUT?day_vote='+day+';'+player
    pls = requests.post(url,verify=False)
    if pls.status_code == requests.codes.ok:
            # print(pls)
            print(player+ " inserito")
            return True
    else:
        print("errore, inserimento giocatore nella formazione")
        return False

def update_setup(squadname,day):
    url='http://localhost:8030/PUT?setup='+day+'&name='+squadname
    pls = requests.put(url,verify=False)
    if pls.status_code == requests.codes.ok:
            # print(pls)
            print("setup aggiornato")
            return True

def file_op(dati):
    if os.path.isfile('data.json'):
        #file presente
        canadd=1
        f = open ('data.json', "r+")
        # Reading from file
        data = json.loads(f.read())
        print(data['teams'])
        for i in data['teams']:
            print(i['name'])
            # print(i['name'])
            #se non trova la squadra by name, allora può scriverci
            if i['name'] == dati['name']:
                canadd=0
        #se la sqadra non è presente allora posso aggiungere
        if canadd==1:
            # data.
            # f.write()
            print(dati)
        else:
            return False
    else:
        #per la prima volta
        # f = open('data.json','w')
        with open('data.json', 'w', encoding='utf-8') as f:
            data = {}
            data['teams'] = []
            data['teams'].append(dati)
            x = json.dump(data, f)
            # f.write(x)
    # Closing file
    f.close()
    return True

def save_teams_players(team,players):
    str = players.get(1.0,"end-1c")
    x = str.split('\n')
    print(x)
    for i in x:
        # print(i)
        if i!="":
            j = i.split(" - ")
            print(j[0])
            url = 'http://localhost:8030?player='+team+';'+j[0]+';'+j[1]
            pls = requests.post(url,verify=False)
            if pls.status_code == requests.codes.ok:
                print(j[0]+' appended to the team '+team)
            else:
                return False
    url = 'http://localhost:8030/PUT?squad='+team
    pls = requests.put(url,verify=False)
    if pls.status_code == requests.codes.ok:
        print('setupped to 1')
    else:
        return False
    return True
            

def login_acc(name, hash):
    url = 'http://localhost:8030/GET?login='+name+'&pass='+hash
    # print(url)
    try:
        pls = requests.get(url,verify=False)
        pls.raise_for_status()
        if pls.text!='{}':
            dizio = json.loads(pls.text)
            print('tipo utente: '+dizio[name])
            return int(dizio[name])
        else:
            return {}
    except requests.exceptions.RequestException as err:
        messagebox.showinfo(title='Errore di connessione al db', message='Impossibile connettersi al db')
        raise SystemExit(err)
    # print(pls.text)
    # if pls.text!='{}':
    #     return pls.text
    # else:
    #     return ''

def update_votes(player,vote,day):
    if vote =='-':
        vote=0
    if str(vote).find(","):
        vote = str(vote).replace(',', '.')
    url='http://localhost:8030/PUT?surname='+player+'&number='+str(day)+'&vote='+str(vote)
    pls = requests.put(url,verify=False)
    if pls.status_code == requests.codes.ok:
            # print(pls)
            print("voto assegnato al giocatore"+player)
            return True

def update_points(squadname,day):
    url= 'http://localhost:8030/GET?squad='+squadname+'&day='+day
    pls = requests.get(url,verify=False)
    if pls.text!='{}':
        print(pls.text)
        # print(pls.text[cli_name])
        disdiz = {"players": pls.text}
        stringed = json.dumps(disdiz)
        data = json.loads(stringed)
        return data            

