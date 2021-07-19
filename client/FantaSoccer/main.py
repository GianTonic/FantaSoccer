# from gui import root
import tkinter as tk
from tkinter import messagebox
from app import App
from client import Client
import hashlib
import req

root = tk.Tk()
login = tk.Toplevel()
width = root.winfo_screenwidth()
height = root.winfo_screenheight()
x = width/2
y = height/2
login.geometry("+"+str(int(x)-100)+"+"+str(int(y)-50))

def log_ui(login):
    usr = tk.Entry(login)
    usr.grid(row=0, column=1)
    psw = tk.Entry(login)
    psw.grid(row=1, column=1)
    psw.config(show="*")
    tk.Label(login, text='username: ', height=2).grid(column=0, row=0)
    tk.Label(login, text='password: ', height=2).grid(column=0, row=1)
    tk.Button(login, text="enter", command=lambda: log_response(usr.get(),psw.get())).grid(column=1, row=2)
    login.bind("<Return>", lambda e: log_response(usr.get(),psw.get()))
    login.protocol('WM_DELETE_WINDOW', confirmExit)
    login.resizable(False, False)

def confirmExit():
    if messagebox.askokcancel('Quit', 'Are you sure you want close the application?'):
        root.destroy()

def log_response(name, psw):
    print(name)
    hashed = hashlib.md5(psw.encode("utf-8")).hexdigest()
    print(hashed)
    resp = req.login_acc(name, hashed)
    if resp!={}:
        day = req.get_the_day()
        if resp==0:
            print('accesso in corso come admin')
            login.destroy()
            app = App(root,day)
            root.deiconify()
            return 0
        elif resp==1:
            print('accesso in corso come user')
            login.destroy()
            client = Client(root,name,day)
            root.deiconify()
            return 1
    else:
        messagebox.showinfo(title='Errore di autenticazione', message='Ricontrolla le tue credenziali')
        return 2

log_ui(login)
# login.bind('<Escape>', lambda e: root.quit)
root.withdraw()
# app = App(root)
root.mainloop()