import os, re
import tkinter as tk
from tkinter import Toplevel, messagebox as msg
from tkinter.constants import BOTH, BOTTOM, DISABLED, END, NORMAL
# import numpy as num
from ui.commands import *
import teamscrap.scrap as s
import votescrap.scrapfvote as vs
# from PIL import Image
# import schedule
import req, json
# import log as login
# from teamgui import window


class App(tk.Tk):

    def __init__(self, root, day):
        self.actual_day = day
        print("actual day"+ day)
        self.root = root
        root.geometry("600x320")
        # top = tk.Toplevel(class_= login.Log)
        self.menu = tk.Menu(self.root)
        self.root.config(menu=self.menu)
        root.resizable(False, False)
        # self.login_menu()
        # photo = tk.PhotoImage(file='./ui/src/logo.gif')
        # label = tk.Label(root, image=photo)
        # label.pack()
        # self.frame0 = tk.Frame(self)
        self.user_menu()
        # self.teams_showed = []
        # print(self.teams_showed)
        self.frame = self.main_ui()
        self.frame.grid(column=1, row=0, columnspan=3, rowspan=10)
        # print(self.teams_showed)
        # data = req.load_file()
        # if data!='':
        #     for i in data['teams']:
        #         lbl = tk.Label(self, text="Name: ")
        #         lbl.grid(column=0, row=i)
        #         lbl_team = tk.Label(self, text=i['name'])
        #         lbl_team.grid(column=1,row=i)
        #         btn = tk.Button(self, text="Add team's players", command=lambda: self.addPlayerWindow(i['name']))
        #         btn.grid(column=2, row=0)
        #         print(i)
        #         print(i['name'])

        # self.log_ui()
        # self.user_menu()
        # if l.Log(root)==True:
        # 	print("si")

    def user_menu(self):
        filemenu = tk.Menu(self.menu)
        self.menu.add_cascade(label="Menu", menu=filemenu)
        filemenu.add_command(label="Add team", command=self.newTeamWindow)
        # filemenu.add_command(label="Add team's player", command=lambda: self.addPlayerWindow())
        filemenu.add_command(label="Refresh day points", command=self.refresh_point_day)
        filemenu.add_command(label="Show charts")
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=self.root.quit)

    # def fanta_menu(self):
    #     fantamenu = tk.Menu(self.menu)
    #     self.menu.add_cascade(label="Manage Teams", menu=filemenu)
    #     fantamenu.add_command(label="Add team", command=lambda: self.newTeamWindow())
    #     fantamenu.add_command(label="Add team's player", command=lambda: self.addPlayerWindow())
    #     fantamenu.add_command(label="Show my team")
    #     fantamenu.add_command(label="Show charts")

    def newTeamWindow(self):
        newteamwin = tk.Toplevel(self.root)
        # newteamwin = tk.Toplevel()
        newteamwin.title("Insert new Team")
        newteamwin.geometry("400x100")
        lbl = tk.Label(newteamwin, text="Name: ")
        lbl.grid(column=0, row=0)
        self.txt = tk.Entry(newteamwin, width=20)
        self.txt.grid(column=1, row=0)
        lbl2 = tk.Label(newteamwin, text="Owner: ")
        lbl2.grid(column=0, row=1)
        self.own = tk.Entry(newteamwin, width=20)
        self.own.grid(column=1, row=1)
        btn = tk.Button(newteamwin, text="Save", command=self.add_team)
        btn.grid(column=2, row=0)

    def addPlayerWindow(self,team):
        print('modificando la squadra '+team)
        addplayerwin = tk.Toplevel(self.root)
        addplayerwin.title("Insert new Player")
        addplayerwin.geometry("500x600")
        lb0 = tk.Label(addplayerwin, text="Select Team: ")
        lb0.grid(column=0, row=0)
        myscrap = s.teamscrap.TeamscrapSpider()
        ls = list(myscrap.get_squad())

        # getto la lista squadre
        self.value = tk.StringVar()
        self.value.set('select team')
        self.opt = tk.OptionMenu(addplayerwin, self.value, *ls)
        # ascolto il value e chiamo callback
        self.value.trace("w", self.callback)
        self.opt.config(width=30, font=('Helvetica', 12))
        self.opt.grid(column=1, row=0)

        # self.player si riferisce alla stringa visualizzata inizialmente nella select
        # ovvero quello selezionato
        self.player = tk.StringVar()
        self.player.set('select player')
        # inizializzandolo vuoto quando non è stata settata la squadra
        self.players = []
        self.lb1 = tk.Label(addplayerwin, text="select player")
        self.lb1.grid(column=0, row=1)
        # vado a settare le opzioni della select giocatori con la list players
        self.opt1 = tk.OptionMenu(addplayerwin, self.player, '', *self.players)
        self.player.trace("w", self.callplay)
        self.opt1.config(width=30, font=('Helvetica', 12))
        self.opt1.grid(column=1, row=1)

        btn = tk.Button(addplayerwin, text="Add player", command=self.add_player)
        btn.grid(column=0, row=2)
        self.btn_remove = tk.Button(addplayerwin, text="Remove last insert", command=self.rem_last_player, state=DISABLED)
        self.btn_remove.grid(column=1, row=2)
        tk.Label(addplayerwin, text='make sure you entered 20 right players before save', height=2).grid(column=1, row=3)
        self.lista = tk.Text(addplayerwin, state='disabled', height=20, width=30)
        self.lista.grid(column=1, row=4)
        # self.lista.pack(fill=BOTH, pady=5, padx=5, expand=True)
        self.sav = tk.Button(addplayerwin, text="Save", state='disabled', command=lambda: self.save_players(team, self.lista))
        self.sav.grid(column=1, row=5)
        # qui faccio 
        self.tox = 0

    def save_players(addplayerwin, team, players_list):
        if(req.save_teams_players(team, players_list)):
            msg.showinfo(title='Operation complete', message='All players appended to team')
            addplayerwin.main_ui()
            addplayerwin.quit
        else:
            msg.showerror(title='Error ', message='Cannot add players to team')

    # def add_items(self):
    # setto i giocatori della squadra, scrapati al volo
    def callback(addplayerwin, *args):
        addplayerwin.player.set('select player')
        menu = addplayerwin.opt1.children['menu']
        menu.delete(0, "end")
        team = addplayerwin.value.get()
        players = list(s.teamscrap.TeamscrapSpider.get_squad_players(s.teamscrap.TeamscrapSpider, team))
        # aggiungo i nomi come opzioni select
        for player in players:
            p = player['surname'].capitalize() + ' - ' + player['role']
            # print(p)
            # controllo se è già stato scelto allora nemmeno lo faccio visualizzare
            print(player['surname'])
            menu.add_command(label=p, command=lambda i=p: addplayerwin.player.set(i))
        # print(menu)
        return

    def callplay(newteamwin, *args):
        play = newteamwin.player.get()
        print(play)
        return
    
    # pulsante aggiungi giocatore
    def add_player(addplayerwin):
        if addplayerwin.player.get()!='select player':
            if req.chosen(surname=addplayerwin.player.get()) == False:
                # tox = addplayerwin.lista.get('1','end')
                addplayerwin.lista.config(state='normal')
                addplayerwin.lista.insert(END, addplayerwin.player.get()+'\n')
                addplayerwin.lista.config(state='disabled')
                # CONTATORE DI RIGHE
                
                addplayerwin.tox = int(addplayerwin.lista.index('end-1c').split('.')[0]) - 1
                print("totale inseriti " + str(addplayerwin.tox))
                if addplayerwin.tox>=1:
                    addplayerwin.btn_remove.config(state=NORMAL)
                if addplayerwin.tox==20:
                    # print(addplayerwin.lista.count('\n'))
                    addplayerwin.sav.config(state='normal')
                else:
                    addplayerwin.sav.config(state='disabled')
                return
            else:
                msg.showerror(title='Impossibile inserire', message='il giocatore è stato già scelto')
        else:
            msg.showerror(title='Errore', message='seleziona un giocatore prima di continuare')
    
    # pop ultimo elemento lista giocatori
    def rem_last_player(addplayerwin):
        # print('pop last item')
        print(addplayerwin.lista.get(addplayerwin.tox+.0,END+"-1c"))
        addplayerwin.lista.config(state='normal')
        addplayerwin.lista.delete(addplayerwin.tox+.0,END+"-1c")
        addplayerwin.tox=addplayerwin.tox-1
        addplayerwin.lista.config(state='disabled')

    def add_team(newteamwin):
        team = newteamwin.txt.get()
        owner = newteamwin.own.get()
        if team!='' and owner!='':
            dati = {'name': team, 'owner': owner}
            #da convertire in json
            if req.insert_team(dati) == True:
                newteamwin.refresh_ui()
                msg.showinfo(title='operazione eseguita', message='la squadra è stata aggiunta al campionato')
                
                
            else:
                msg.showerror(title='Errore inserimento squadra', message='non posso aggiungere la squada, qualcosa è andato storto')
        else:
            msg.showerror(title='Errore di inserimento', message='inserire il nome di una squadra e il proprietario')
    
    def update_root(self):
        self.root.update()

    def show_team_players(self, team):
        data = req.load_team_players(team)
        if(data!=""):
            print(data)
            players= json.loads(data['players'])
            
            show_team_win = tk.Toplevel(self.root)
            show_team_win.title(team +" players")
            show_team_win.geometry("300x600")
            player_list = tk.Text(show_team_win, height=20, width=30)
            player_list.grid(column=1, row=4)
            for key, value in players.items():
                print('mostra la lista giocatori di '+team)
                player_list.insert(END, key+" role: "+value+"\n")
            player_list.config(state="disabled")

    def main_ui(self):
        data = req.load_db()
        frame0 = tk.Frame(self.root)
        if data!='{}':
            # print(data['teams'])
            # print(data)
            teams = {}
            j = 1
            lbl0 = tk.Label(self.root, text="Menagements ")
            lbl0.grid(column=0, row=0)
            teams= json.loads(data['teams'])
            # print(len(teams))
            # for i in data['teams']:
            for key, value in teams.items():
                # print(j)
                j=j+1
                x = key.split(",")
                print(x[0], '->', x[1])
                # res = json.loads(dict(data['teams']))
                # print(i['name'])
                # print(i['owner'])
                lbl = tk.Label(frame0, text=" ")
                # lbl.grid(column=1, row=j)
                lbl_team = tk.Label(frame0, text=str(x[0])+" ")
                lbl_team.grid(column=2,row=j)
                # lbl = tk.Label(self.root, text=" ")
                # lbl.grid(column=3, row=j)
                if value == '-1':
                    btn = tk.Button(frame0, text="Add players", command=lambda x = x: self.addPlayerWindow(str(x[0])))
                    btn.grid(column=4, row=j)
                else:
                    btn = tk.Button(frame0, text="Show team", command=lambda x = x: self.show_team_players(str(x[0])))
                    btn.grid(column=4, row=j)
                lbl_own = tk.Label(frame0, text="owner: "+str(x[1]))
                lbl_own.grid(column=5,row=j)
                # tupla = [lbl,lbl_team,btn,lbl_own]
                # self.teams_showed.append(tupla)
            return frame0
            
                # print(i)
    def refresh_ui(self):
        self.frame.destroy()
        self.actual_day = req.get_the_day()
        self.__init__(self.root,self.actual_day)
    
    def refresh_point_day(self):
        os.chdir("votescrap/")
        ritorno = os.popen("scrapy crawl fantavote -a day="+self.actual_day+" --nolog").read()
        data = list(eval(ritorno))
        for dictItem in data:
            print(dictItem['player']+":"+dictItem['vote'])
            req.update_votes(dictItem['player'],dictItem['vote'],self.actual_day)
