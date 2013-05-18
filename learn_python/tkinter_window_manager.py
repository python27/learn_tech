from Tkinter import *

class App(Frame):
    def __init__(self,master=None):
        Frame.__init__(self,master)
        self.pack()

myapp = App()

myapp.master.title("The first Tkinter Program")
myapp.master.maxsize(1000,400)

myapp.mainloop()
