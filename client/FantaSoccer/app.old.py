import tkinter as tk
from tkinter import Toplevel, messagebox as msg
from tkinter.constants import BOTTOM, DISABLED, END

from twisted.python import log
from ui.commands import *
import teamscrap.scrap as s
# import votescrap.scrapfvote as vs
# from PIL import Image
# import schedule
import req
import log as login
# from teamgui import window


class App(tk.Tk):

    def __init__(self, root):
        self.root = root
        root.geometry("600x220")
        # top = tk.Toplevel(class_= login.Log)
        self.menu = tk.Menu(self.root)
        self.root.config(menu=self.menu)
        # self.login_menu()
        # photo = tk.PhotoImage(file='./ui/src/logo.gif')
        # label = tk.Label(root, image=photo)
        # label.pack()
        self.user_menu()
        self.main_ui()
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
        filemenu.add_command(label="Add team", command=lambda: self.newTeamWindow())
        # filemenu.add_command(label="Add team's player", command=lambda: self.addPlayerWindow())
        filemenu.add_command(label="Show my team")
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
        newteamwin.title("Insert new Team")
        newteamwin.geometry("400x100")
        lbl = tk.Label(newteamwin, text="Name: ")
        lbl.grid(column=0, row=0)
        self.txt = tk.Entry(newteamwin, width=10)
        self.txt.grid(column=1, row=0)
        lbl2 = tk.Label(newteamwin, text="Owner: ")
        lbl2.grid(column=0, row=1)
        self.own = tk.Entry(newteamwin, width=10)
        self.own.grid(column=1, row=1)
        btn = tk.Button(newteamwin, text="Save", command=self.add_team)
        btn.grid(column=2, row=0)

    def addPlayerWindow(self,team):
        print('hai selezionato la squadra: '+team)
        newteamwin = tk.Toplevel(self.root)
        newteamwin.title("Insert new Player")
        newteamwin.geometry("500x600")
        lb0 = tk.Label(newteamwin, text="Select Team: ")
        lb0.grid(column=0, row=0)
        myscrap = s.teamscrap.TeamscrapSpider()
        ls = list(myscrap.get_squad())
        # getto la lista squadre
        # print(ls)
        print(ls[0])
        self.value = tk.StringVar()
        self.value.set('select team')
        self.opt = tk.OptionMenu(newteamwin, self.value, *ls)
        # ascolto il value e chiamo callback
        self.value.trace("w", self.callback)
        self.opt.config(width=30, font=('Helvetica', 12))
        self.opt.grid(column=1, row=0)
        # self.player si riferisce alla stringa visualizzata inizialmente nella select
        self.player = tk.StringVar()
        self.player.set('select player')
        # inizializzandolo vuoto quando non è stata settata la squadra
        self.players = []
        self.lb1 = tk.Label(newteamwin, text="Select player: ")
        self.lb1.grid(column=0, row=1)

        self.opt1 = tk.OptionMenu(newteamwin, self.player, '', *self.players)
        self.player.trace("w", self.callplay)
        self.opt1.config(width=30, font=('Helvetica', 12))
        self.opt1.grid(column=1, row=1)

        btn = tk.Button(newteamwin, text="Add player", command=self.add_player)
        btn.grid(column=1, row=2)
        tk.Label(newteamwin, text='make sure you entered 20 right players before save', height=2).grid(column=1, row=3)
        self.lista = tk.Text(newteamwin, state='disabled', height=20, width=30)
        self.lista.grid(column=1, row=4)
        self.sav = tk.Button(newteamwin, text="Save", state='disabled', command=req.save_teams_players(team, self.lista))
        self.sav.grid(column=1, row=5)
        # qui faccio 


    # def add_items(self):
    def callback(newteamwin, *args):
        newteamwin.player.set('select player')
        menu = newteamwin.opt1.children['menu']
        menu.delete(0, "end")
        team = newteamwin.value.get()
        players = list(s.teamscrap.TeamscrapSpider.get_squad_players(s.teamscrap.TeamscrapSpider, team))
        # aggiungo le opzioni
        for player in players:
            p = player['surname'].capitalize() + ' - ' + player['role']
            # print(p)
            # controllo se è già stato scelto allora nemmeno lo faccio visualizzare
            print(player['surname'])
            menu.add_command(label=p, command=lambda i=p: newteamwin.player.set(i))
        # print(menu)
        return

    def callplay(newteamwin, *args):
        play = newteamwin.player.get()
        # da disabilitare se è già stato scelto
        print(play)
        return

    def add_player(newteamwin):
        newteamwin.lista.config(state='normal')
        newteamwin.lista.insert(END, newteamwin.player.get()+'\n')
        newteamwin.lista.config(state='disabled')
        if req.chosen(surname=newteamwin.player.get()) == False:
            if newteamwin.lista.count("\n") == 20:
                newteamwin.sav.config(state='normal')
            else:
                newteamwin.sav.config(state='disabled')
            return
        else:
            msg.showerror(title='Impossibile inserire', message='il giocatore è stato già scelto')
        # if newteamwin.player!='':
        # 	newteamwin.play_lbl.clipboard_append(newteamwin.player)
        # 	listlen = len(newteamwin.play_lbl)# play = newteamwin.player.get()
        # 	print(listlen)
        # 	newteamwin.play_lbl.configure(textvariable=+newteamwin.player.get())
        
    def add_team(newteamwin):
        team = newteamwin.txt.get()
        owner = newteamwin.own.get()
        if team!='' and owner!='':

            dati = '{"name": "'+team+'", "owner": "'+owner+'"}'
            #da convertire in json
            if req.file_op(dati) == True:
                msg.showinfo(title='operazione eseguita', message='la squadra è stata aggiunta al campionato')
                newteamwin.destroy()
                newteamwin.root.main_ui()
            else:
                msg.showerror(title='Errore inserimento squadra', message='non posso aggiungere la squada, qualcosa è andato storto')
        else:
            msg.showerror(title='Errore di inserimento', message='inserire il nome di una squadra e il proprietario')
    
    def main_ui(self):
        data = req.load_file()
        if data!='':
            print('A11')
            print(data)
            # for i in data:
            #     print(i['name'])
            #     print(i['owner'])
                # lbl = tk.Label(self, text="Name: ")
                # lbl.grid(column=0, row=i)
                # lbl_team = tk.Label(self, text=i['name'])
                # lbl_team.grid(column=1,row=i)
                # btn = tk.Button(self, text="Add team's players", command=lambda: self.addPlayerWindow(i['name']))
                # btn.grid(column=2, row=0)
                # print(i)