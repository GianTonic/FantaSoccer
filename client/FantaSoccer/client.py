import tkinter as tk, json
import req
from tkinter.constants import END
from tkinter import messagebox as msg

class Client(tk.Tk):

    def __init__(self, root, cli_name, day):
        self.root = root
        self.name = cli_name
        self.actual_day = day
        root.geometry("400x700")
        root.resizable(False, False)
        # top = tk.Toplevel(class_= login.Log)
        self.menu = tk.Menu(self.root)
        self.root.config(menu=self.menu)
        self.user_menu()
        # self.main_ui(cli_name)
        self.frame = self.main_ui(cli_name)
        self.frame.grid(column=2, row=0, columnspan=4, rowspan=10)

    def user_menu(self):
        filemenu = tk.Menu(self.menu)
        self.menu.add_cascade(label="Menu", menu=filemenu)
        # filemenu.add_command(label="Add team's player", command=lambda: self.addPlayerWindow())
        filemenu.add_command(label="Refresh", command=self.refresh_ui) # giusto per aggiornare il cambio giornata ogni 10 min
        filemenu.add_command(label="Show charts")
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=self.root.quit)
    
    def main_ui(self,cli_name):
        data = req.load_team_name(cli_name)
        team_name = ''
        if data!='{}':
            frame0 = tk.Frame(self.root)
            teams= json.loads(data['teams'])
            for key, value in teams.items():
                x = key.split(",")
                print(x[0], '->', x[1])
                team_name = x[1]
                stored_day = value
                print(stored_day)
        if(team_name!=''):
            lbl0 = tk.Label(self.root, text="Team: "+team_name)
            lbl0.grid(column=2, row=0)
            # lbl0 = tk.Label(self.root, text=" ")
            # lbl0.grid(column=2, row=0)
            lbl2 = tk.Label(self.root, text="team's players")
            lbl2.grid(column=2, row=1)
            frame0 = tk.Frame(self.root)
            if(stored_day<self.actual_day):
                lineup_btn = tk.Button(frame0, text="Set formation for day "+str(self.actual_day), command=lambda: self.lineup_win(team_name, self.actual_day))
            else:
                lineup_btn = tk.Button(frame0, text="Show formation of day "+str(self.actual_day), command=lambda: self.show_formation_day_win(team_name,self.actual_day))
            lineup_btn.grid(column=2, row=2)
            j = 3
            players_list = req.load_team_players(team_name)
            # print(players_list)
            if players_list:
                players=json.loads(players_list['players'])
                # print(players)
                for key, value in players.items():
                    lbl_player = tk.Label(frame0, text=str(key))
                    lbl_player.grid(column=2,row=j)
                    lbl_role = tk.Label(frame0, text=str(value))
                    lbl_role.grid(column=3, row=j)
                    j=j+1
        return frame0

    def show_formation_day_win(self, team, day):
        print(team)
        print(day)
        data = req.load_team_players_of_day(team,day)
        if(data!=""):
            form = tk.Toplevel(self.root)
            form.title("Starting lineup")
            form.geometry("400x700")
            form.resizable(False, False)
            lbl1 = tk.Label(form, text="Formation of day ")
            lbl1.grid(column=0, row=0)
            lbl1 = tk.Label(form, text=day)
            lbl1.grid(column=1, row=1)
            
            # player_list = tk.Text(form, height=20, width=20)
            # player_list.grid(column=2, row=2, columnspan=1, rowspan=20)
            players= json.loads(data['players'])
            if players:
                # print(players)
                j = 3
                for key, value in players.items():
                    lbl_player = tk.Label(form, text=str(key))
                    lbl_player.grid(column=1,row=j)
                    lbl_role = tk.Label(form, text=str(value))
                    lbl_role.grid(column=2, row=j)
                    j=j+1
            

    def lineup_win(self, team, day):
        data = req.load_team_players(team)
        if(data!=""):
            # print(data)
            players= json.loads(data['players'])
            lineupWin = tk.Toplevel(self.root)
            formaz = ['4-4-2','5-3-2']
            self.setted = tk.StringVar(lineupWin)
            self.setted.set('set')
            self.setted.trace("w", self.formaz_setted)
            lineupWin.title(" Set formation of "+team +" for the day "+day)
            lineupWin.geometry("400x700")
            lineupWin.resizable(False, False)
            label1 = tk.Label(lineupWin, text="Set module first: ")
            label1.grid(column=0,row=0)
            formaz = tk.OptionMenu(lineupWin, self.setted, *formaz)
            formaz.grid(column=1, row=0)
            self.role_list = tk.Text(lineupWin, height=20, width=5)
            self.role_list.grid(column=1, row=2, columnspan=1, rowspan=20)
            self.player_list = tk.Text(lineupWin, height=20, width=20)
            self.player_list.grid(column=2, row=2, columnspan=1, rowspan=20)
            j=1 #per grid
            self.sav = tk.Button(lineupWin, text="Save", state='disabled', command=lambda: self.save_formation(team, self.player_list, day))
            self.sav.grid(column=1, row=21)
            self.buttons = [] #colonna bottoni per disabilitare quelli già cliccati
            self.vect_roles = [] #colonna ruoli per fare il match della formazione
            for key, value in players.items():
                but = tk.Button(lineupWin, text=str(key)+" "+str(value), command=lambda index=j-1, name=key, role= value: self.player_but_action(index, name, role), state='disabled')
                print("bottone_ id: "+str(j)+" nome: "+str(key)+" ruolo: "+str(value))
                but.grid(column=0, row=j)
                j=j+1
                self.buttons.append(but)
            self.role_list.config(state="disabled")
            self.player_list.config(state="disabled")
            self.row_added = 0 # int di appoggio per aggiungere i giocatori alla formazione

    def save_formation(lineupWin, team, players_list, day):
        print("settando la formazione della squadra"+team)
        print("per la giornata num ")
        print(day)
        str = players_list.get(1.0,"end-1c")
        x = str.split('\n')
        for i in x:
            # print(i)
            if(i!=''):
                req.insert_formation_day(i,day)
        req.update_setup(team,day)
        # if(req.save_teams_players(team, players_list)):
        #     msg.showinfo(title='Operation complete', message='formation done')
        #     addplayerwin.main_ui()
        #     addplayerwin.quit
        # else:
        #     msg.showerror(title='Error ', message='Cannot save formation')

    def formaz_setted(lineupWin, *args):
        setted = lineupWin.setted.get()
        print(setted)
        if setted!='set':
            lineupWin.role_list.config(state="normal")
            j = 0
            setted+="-4"
            x= setted.split('-')
            lineupWin.role_list.insert(END, "P "+"\n")
            lineupWin.vect_roles.append("P")
            while j<4:
                print("tipo ruolo "+str(j))
                if j==0:
                    placeholder = 'D'
                elif j==1:
                    placeholder = 'C'
                elif j==2:
                    placeholder = 'A'
                elif j==3:
                    placeholder = 'Sub.'
                count = int(x[j])
                i = 0
                while i < count:
                    print("indice per il tipo: "+str(i))
                    # controllo se è lultimo inserimento
                    lineupWin.role_list.insert(END, placeholder+"\n")
                    lineupWin.vect_roles.append(placeholder)
                    i+=1
                j+=1
            for i in lineupWin.buttons:
                i.config(state="normal")
            lineupWin.role_list.config(state="disabled")


    def player_but_action(lineupWin, index, name, role):
        print("cliccato: "+str(index)+" "+name+" "+role)
        if lineupWin.row_added < 11: #sto aggiungendo il primo che sarà sempre il portiere
            if role==lineupWin.vect_roles[lineupWin.row_added]:
                lineupWin.player_list.config(state='normal')
                print("role cliccato: "+role+" in vect: "+lineupWin.vect_roles[lineupWin.row_added])
                lineupWin.player_list.insert(END,name+"\n")
                lineupWin.buttons[index].config(state="disabled")
                lineupWin.row_added+=1
                lineupWin.player_list.config(state='disabled')
            else:
                msg.showerror(title='Error insert', message='you selected a wrong player, please make sure the role match the actual formation ')
        elif lineupWin.row_added>10 and lineupWin.row_added<15:
            lineupWin.player_list.config(state='normal')
            lineupWin.player_list.insert(END,name+"\n")
            lineupWin.buttons[index].config(state="disabled")
            lineupWin.row_added+=1
            lineupWin.player_list.config(state='disabled')
        else:
            # sono riserve non mi vado a leggere il ruolo
            msg.showwarning(title="Stop", message="you can't add more player, save formation or close the windows for undo")
        if lineupWin.row_added==15:
            lineupWin.sav.config(state='normal')
        else:
            lineupWin.sav.config(state='disabled')
        # lineupWin.row_added+=1 #aumento il contatore di elementi dal primo all'11esimo
        # lineupWin.player_list.config(state='disabled')
    
    def refresh_ui(self):
        self.frame.destroy()
        self.actual_day = req.get_the_day()
        self.__init__(self.root,self.name, self.actual_day)