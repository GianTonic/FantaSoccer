from tkinter import *
from tkinter.filedialog import askopenfilename

def NewFile():
    print("New Team")
    # lbl = Label(window, text="Nome: ")
    # lbl.grid(column=0, row=0)
    # txt = Entry(window,width=10)
    # txt.grid(column=1, row=0)
    # btn = Button(window, text="Salva")
    # btn.grid(column=2, row=0)
def OpenFile():
    name = askopenfilename()
    print(name)
def About():
    print("This is a simple example of a menu")
    
root = Tk()
menu = Menu(root)
root.config(menu=menu)
root.title("Fantapiango")
root.geometry('350x200')
filemenu = Menu(menu)

menu.add_cascade(label="Menu", menu=filemenu)
filemenu.add_command(label="Add team", command=NewFile)
filemenu.add_command(label="Add team's player", command=NewFile)
filemenu.add_command(label="Show my team", command=OpenFile)
filemenu.add_command(label="Show charts", command=OpenFile)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=root.quit)
helpmenu = Menu(menu)
menu.add_cascade(label="Help", menu=helpmenu)
helpmenu.add_command(label="About...", command=About)

# mainloop()