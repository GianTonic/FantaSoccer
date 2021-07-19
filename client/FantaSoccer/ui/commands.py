def NewFile():
    print("New Team")
    # lbl = Label(window, text="Nome: ")
    # lbl.grid(column=0, row=0)
    # txt = Entry(window,width=10)
    # txt.grid(column=1, row=0)
    # btn = Button(window, text="Salva")
    # btn.grid(column=2, row=0)
#def NewTeam():
    # chiede al server di inserire il nome se non è già presente nel db
def OpenFile():
    name = askopenfilename()
    print(name)
def About():
    print("This is a simple example of a menu")
